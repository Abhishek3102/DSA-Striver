# API Design — Interview Prep Guide

## Why this matters
"Design an API for X" is a standard mid-interview task, and "what status code would you return for...?" is a classic trap question. You already build APIs (FastAPI/Express) — this doc teaches you to talk about them like an engineer.

---

## Part 1: REST fundamentals

**REST** = an architectural style where everything is a **resource** identified by a URL, manipulated with standard **HTTP methods**.

**The core rules:**
1. **Resources are nouns, not verbs** — the method IS the verb
2. **Stateless** — every request carries everything needed (token, params); server keeps no client session between requests
3. **Uniform interface** — same conventions everywhere

| Method | Meaning | Idempotent? | Safe? |
|---|---|---|---|
| GET | Read | Yes | Yes (no state change) |
| POST | Create / trigger | **No** | No |
| PUT | Replace entirely | Yes | No |
| PATCH | Partial update | No (usually) | No |
| DELETE | Remove | Yes | No |

**Idempotent** = calling it once or 10 times gives the same server state. Interviewers LOVE this word.
- Why it matters: if a network drops after `PUT /users/5` and the client retries, no harm. Retrying `POST /orders` could create duplicate orders — that's why payment APIs use **idempotency keys**.

### URL design — right vs wrong

```
GET    /api/users                 # list all users
GET    /api/users/42              # one user
POST   /api/users                 # create user
PUT    /api/users/42              # replace user 42
PATCH  /api/users/42              # partially update user 42
DELETE /api/users/42              # delete user 42

GET    /api/users/42/transactions         # nested: user 42's transactions
POST   /api/users/42/transactions         # create transaction for user 42
GET    /api/transactions?userId=42        # same thing, as a filter

# BAD (verbs in URLs)            # GOOD
POST /getUser?id=42         ->    GET /api/users/42
POST /deleteUser/42        ->    DELETE /api/users/42
POST /users/createNew      ->    POST /api/users
```

**Tricky one interviewers ask: "How do you express 'change password' in REST?"**
`PATCH /users/42` with `{"password": "..."}` or a sub-resource: `POST /users/42/password-change`. Not `/changePassword` (verb). Either is acceptable — the point is knowing the debate.

**Filtering / pagination / sorting via query params:**
```
GET /api/transactions?userId=42&status=failed&page=2&limit=20&sort=-created_at
```

---

## Part 2: Status codes — the interview trap questions

**Success:**
- `200 OK` — general success (GET, PATCH)
- `201 Created` — POST succeeded (ideally return the new resource + `Location` header)
- `204 No Content` — success, nothing to return (DELETE, or PUT with no body back)

**Client errors (4xx) — user's fault:**
- `400 Bad Request` — malformed input / validation failed
- `401 Unauthorized` — actually means **unauthenticated**: no/invalid token
- `403 Forbidden` — authenticated but **not allowed** (role lacks permission)
- `404 Not Found` — resource doesn't exist
- `409 Conflict` — duplicate email, conflicting version
- `422 Unprocessable Entity` — syntactically valid JSON, semantically wrong (FastAPI's default for Pydantic errors)
- `429 Too Many Requests` — rate limit hit (+ `Retry-After` header)

**Server errors (5xx) — your fault:**
- `500 Internal Server Error` — unhandled exception
- `502 Bad Gateway` — upstream (behind proxy) returned garbage
- `503 Service Unavailable` — overloaded / down for maintenance
- `504 Gateway Timeout` — upstream too slow

**Trap Qs (memorize these):**
1. **401 vs 403?** 401 = "who are you?" (bad/missing credentials). 403 = "I know you, but no."
2. **400 vs 422?** Both validation; 422 = well-formed but invalid semantics. FastAPI returns 422 automatically; many APIs just use 400. Consistency matters more than the choice.
3. **Failed DELETE — resource didn't exist?** 404 (some argue 204 for idempotency — state the tradeoff, win points)
4. **POST succeeds but you return nothing?** 201 with body, or 204. (201 preferred for creation)


---

## Part 3: Pagination (asked in almost every API design round)

**Offset pagination:**
```
GET /api/items?page=3&limit=20
=> SQL: LIMIT 20 OFFSET 40
```
- Pros: simple, random access, "jump to page 5"
- Cons: **slow on huge tables** (DB still scans skipped rows), and **rows shift** if data changes between pages (duplicates/misses)

**Cursor pagination (what modern APIs use):**
```
GET /api/items?limit=20&cursor=eyJpZCI6NDJ9     # cursor = encoded last position (id/timestamp)
=> SQL: WHERE id > 42 ORDER BY id LIMIT 20
```
- Pros: stable under inserts/deletes, fast at any depth (index seek, no offset scan)
- Cons: no random access, no "total pages"

**Answer template:** "For feeds/infinite scroll I'd use cursor pagination — stable and fast. For admin tables where users jump pages, offset is fine. `OFFSET 100000` is O(n); cursor avoids that."

Response envelope convention:
```json
{
  "data": ["..."],
  "pagination": { "next_cursor": "abc", "has_more": true }
}
```

---

## Part 4: Versioning & real-world headers

**Why version?** Once clients depend on your API, breaking changes (removed fields, changed types) break them.

**Strategies:**
```
URL path (most common):   /api/v1/users  ->  /api/v2/users
Header:                   Accept: application/vnd.myapp.v2+json
Query param:              /api/users?version=2
```
**Breaking:** removing/renaming a field, changing a type or error code. **Not breaking:** adding an optional field, adding an endpoint.

**Headers/concepts to name-drop:**
- `Retry-After` on 429 (when to retry)
- `ETag` / `If-None-Match` — caching; server returns `304 Not Modified` if unchanged
- `Idempotency-Key` — client UUID on POSTs so retries don't double-charge (Stripe does this)
- `X-Request-ID` — correlate one request across services in logs
- HATEOAS — hypermedia links in responses; know the word, say "rarely used in practice"

**Consistent error format (belongs with Part 2's status codes):**
```json
{ "error": { "code": "EMAIL_TAKEN", "message": "A user with this email already exists",
             "details": [{ "field": "email", "issue": "duplicate" }] } }
```

---

## Part 5: Securing an API (connects to the Security doc)

1. **HTTPS everywhere** — non-negotiable
2. **AuthN/AuthZ** — JWT/OAuth; validate on every protected route
3. **Input validation** — Pydantic/Zod schemas reject bad shapes with 422/400
4. **Rate limiting** — per IP/user/token (429 + Retry-After)
5. **Don't leak internals** — 500s return a generic message; details go to logs. Never reveal whether an email exists ("invalid credentials", not "user not found")
6. **Mass assignment protection** — accept only whitelisted fields; never `User(**request.json())` letting a client set `"role": "admin"`
7. **Output scoping / IDOR** — never return password hashes; a user requesting `/api/users/999` who isn't user 999 => 403


---

## Part 6: REST vs GraphQL vs gRPC (know when, not just what)

| | REST | GraphQL | gRPC |
|---|---|---|---|
| Model | Resources + HTTP verbs | One endpoint, client-defined queries | RPC over HTTP/2, protobuf |
| Payload | Fixed by server | Exactly what client asked | Compact binary |
| Over/under-fetching | Possible | Solved | N/A |
| Caching | HTTP caching works well | Harder | Not standard |
| Best for | Public/general APIs | Flexible UIs over complex data | Internal microservice calls, speed |

**One-liner:** "REST by default, GraphQL when clients need flexible views over relational data, gRPC for internal service-to-service communication."

**GraphQL in 30 seconds:**
```graphql
query {
  user(id: 42) { name posts { title } }   # client picks fields = no over-fetching
}
```
Terms to know: **schema, resolver, query vs mutation, N+1 problem** (solved by DataLoader batching).

---

## Part 7: Webhooks & long operations (bonus points)

**Webhook** = YOU call THEM when an event happens (API = they call you). E.g. payment gateway calls your `/webhooks/payment`. Always: verify the HMAC signature, respond `200` fast, process async, make handling **idempotent** (they retry on failure).

**Long-running operations:** don't hold an HTTP request for 2 minutes.
- Return `202 Accepted` + `Location: /api/jobs/123`; client polls job status
- Or push completion via websocket/SSE

---

## Part 8: The "design an API" answer framework (rehearse out loud)

Given "Design an API for a food delivery app":

1. **Resources**: `users`, `restaurants`, `menu_items`, `orders`
2. **Endpoints with proper verbs**:
```
POST   /api/orders                    # place order -> 201
GET    /api/orders/42                 # status check
GET    /api/orders?status=active      # my active orders
PATCH  /api/orders/42/status          # restaurant marks prepared (403 if not owner)
```
3. **Auth**: JWT; customers can only read their OWN orders (IDOR check)
4. **Status codes**: 201 create, 401/403 auth, 404 unknown id, 409 conflict, 422 validation, 429 rate limit
5. **Pagination**: cursor for order history
6. **Non-happy paths**: payment failure -> 402/409, order stays `pending`; `Idempotency-Key` on order creation so retries don't double-order
7. **Async**: status updates via polling/websocket; restaurant notified via queue
8. **Versioning + docs**: `/api/v1`, OpenAPI/Swagger (FastAPI auto-docs at /docs)

Walk through in exactly this order — resources, endpoints, auth, errors, pagination, async — and you'll outshine 90% of freshers.

### Rapid-fire revision
- Nouns not verbs; the HTTP method is the verb
- 401 vs 403, 400 vs 422, 404 vs 409 — know all three pairs cold
- Idempotency: PUT/DELETE yes, POST no; idempotency-key for payments
- Cursor over offset for large/infinite datasets
- IDOR: always scope queries by the authenticated user
- 202 + job polling for slow operations
- OpenAPI/Swagger = self-generating API docs



