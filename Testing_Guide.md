# Testing — Interview Prep Guide

## Why this matters
You won't be asked to write complex test suites. You'll be asked: "Did you write tests in your projects?", "What's the difference between unit and integration tests?", "How would you test this function?" This doc gives you the concepts + working examples in Jest (JS/TS) and Pytest (Python) — the two stacks you use.

---

## Part 1: The Testing Pyramid

```
        /  E2E  \        <- few: full app through browser/API (slow, expensive, brittle)
       /---------\
      / Integration\     <- some: modules + real DB/HTTP (moderate speed)
     /--------------\
    /   Unit tests   \   <- many: single function/class in isolation (fast, cheap)
   /------------------\
```

**Principle:** many unit tests, fewer integration tests, a handful of E2E tests. The higher you go, the slower and flakier it gets.

| Type | Tests | Example |
|---|---|---|
| **Unit** | One function/class, dependencies mocked | `calculateEMI(amount, rate, months)` returns correct value |
| **Integration** | Modules together with real DB/queue | POST /signup actually inserts a user row |
| **E2E** | Whole system through the real interface | Playwright/Cypress: login -> add item -> checkout |
| **Regression** | Any test that catches a previously-fixed bug | Bug #123 test stays in the suite forever |
| **Smoke** | Quick "is it alive at all" checks after deploy | health endpoint returns 200 |

---

## Part 2: Vocabulary you must know (rapid-fire)

- **Assertion**: the check that passes/fails — `expect(sum).toBe(3)`
- **Test case**: one scenario: input -> expected output
- **Test suite**: a group of test cases (one file/describe block)
- **AAA pattern**: Arrange (setup data) -> Act (call the thing) -> Assert (verify result)
- **Mock**: fake object replacing a dependency, with expectations (userRepo.findById returns a fake user)
- **Stub**: simpler than a mock — just returns canned data, no expectations
- **Spy**: wraps a real object and records calls (was sendEmail actually called?)
- **Fixture**: fixed test data setup
- **Setup/teardown**: code that runs before/after each test (fresh test DB)
- **Coverage**: % of code executed by tests (line/branch). Don't chase 100% — cover logic, not boilerplate
- **Flaky test**: passes/fails randomly (time, network, ordering). Real interviewers care about this
- **TDD**: write the failing test first, then the code. Know the red-green-refactor cycle
- **Edge case**: boundary input — empty list, 0, negative, max int, null

---

## Part 3: Unit tests — Jest (JS/TS, your React/Node side)

```javascript
// money.js
function calculateEMI(principal, annualRate, months) {
  if (principal <= 0 || months <= 0) throw new Error("invalid input");
  const r = annualRate / 12 / 100;
  if (r === 0) return principal / months;
  const emi = (principal * r * Math.pow(1 + r, months)) / (Math.pow(1 + r, months) - 1);
  return Math.round(emi * 100) / 100;
}
module.exports = { calculateEMI };
```

```javascript
// money.test.js
const { calculateEMI } = require("./money");

describe("calculateEMI", () => {
  // AAA: Arrange -> Act -> Assert
  test("calculates EMI for a standard loan", () => {
    const emi = calculateEMI(100000, 12, 12);      // Act
    expect(emi).toBeCloseTo(8884.88, 2);            // Assert
  });

  test("handles zero interest", () => {
    expect(calculateEMI(12000, 0, 12)).toBe(1000);
  });

  test("throws on invalid input", () => {
    expect(() => calculateEMI(-5, 10, 12)).toThrow("invalid input");
    expect(() => calculateEMI(100, 10, 0)).toThrow();
  });
});
```

**Common Jest matchers:**
```javascript
expect(x).toBe(5)            // exact (===), for primitives
expect(obj).toEqual({...})   // deep equality, for objects
expect(x).toBeCloseTo(1.23)  // floats (never use toBe for floats!)
expect(arr).toContain(2)
expect(fn).toThrow()
expect(x).toBeNull() / toBeUndefined() / toBeTruthy() / toBeFalsy()
expect(x).toMatch(/regex/)   // strings
```

**Lifecycle hooks:**
```javascript
beforeAll(() => { /* once: start test DB container */ });
beforeEach(() => { /* every test: reset state */ });

### 3.1 Mocks & spies in Jest (this is what they actually probe)

```javascript
// emailService.js
async function sendWelcomeEmail(user) {
  const res = await fetch("https://mail.api/send", {
    method: "POST",
    body: JSON.stringify({ to: user.email, template: "welcome" }),
  });
  return res.ok;
}

// userService.js — the function under test
async function registerUser(userRepo, mailer, user) {
  const existing = await userRepo.findByEmail(user.email);
  if (existing) throw new Error("email taken");
  const saved = await userRepo.save(user);
  await mailer.sendWelcomeEmail(saved);
  return saved;
}

// userService.test.js — mock the dependencies, test the LOGIC
test("registers user and sends welcome email", async () => {
  const userRepo = {
    findByEmail: jest.fn().mockResolvedValue(null),          // stub data
    save: jest.fn().mockResolvedValue({ id: 1, email: "a@b.c" }),
  };
  const mailer = { sendWelcomeEmail: jest.fn().mockResolvedValue(true) };

  const saved = await registerUser(userRepo, mailer, { email: "a@b.c" });

  expect(saved.id).toBe(1);
  expect(userRepo.findByEmail).toHaveBeenCalledWith("a@b.c");
  expect(mailer.sendWelcomeEmail).toHaveBeenCalledTimes(1);   // spy behavior
});

test("rejects duplicate email", async () => {
  const userRepo = { findByEmail: jest.fn().mockResolvedValue({ id: 9 }) };
  const mailer = { sendWelcomeEmail: jest.fn() };

  await expect(registerUser(userRepo, mailer, { email: "a@b.c" }))
    .rejects.toThrow("email taken");
  expect(mailer.sendWelcomeEmail).not.toHaveBeenCalled();     // key assertion!
});
```

**Why mock?** The unit test tests REGISTER logic, not the mail API. Real HTTP calls make tests slow, flaky, and costly. Mock the boundary, assert the interaction.

```javascript
// mocking a whole module
jest.mock("./emailService");
const { sendWelcomeEmail } = require("./emailService");
sendWelcomeEmail.mockResolvedValue(true);

// mocking fetch
global.fetch = jest.fn().mockResolvedValue({ ok: true, json: async () => ({ id: 1 }) });

// spying on an existing object
const spy = jest.spyOn(console, "error").mockImplementation(() => {});
expect(spy).toHaveBeenCalled();
```

### 3.2 Async testing (know this — freshers fumble here)

```javascript
// ALWAYS await / return the promise — otherwise the test passes before it finishes!
test("fetches user", async () => {
  const user = await getUser(1);        // async/await style (preferred)
  expect(user.id).toBe(1);
});

test("rejects on 404", async () => {
  await expect(getUser(999)).rejects.toThrow("not found");
});
```

---

## Part 4: Unit tests — Pytest (Python/FastAPI side)

```python
# discount.py
def apply_discount(cart: list[dict], code: str) -> float:
    """cart items: {"price": float, "qty": int}"""
    total = sum(i["price"] * i["qty"] for i in cart)
    if code == "SAVE10":
        total *= 0.9
    elif code == "SAVE20":
        if total < 1000:
            raise ValueError("SAVE20 requires min 1000")
        total *= 0.8
    return round(total, 2)
```

```python
# test_discount.py
import pytest
from discount import apply_discount

def test_no_code_returns_total():
    assert apply_discount([{"price": 100, "qty": 2}], "") == 200.0

def test_save10_gives_10_percent():
    assert apply_discount([{"price": 100, "qty": 2}], "SAVE10") == 180.0

def test_save20_min_amount_enforced():
    with pytest.raises(ValueError):
        apply_discount([{"price": 100, "qty": 2}], "SAVE20")

# parametrize = same test, many inputs (interviewers love seeing this)
@pytest.mark.parametrize("code,expected", [
    ("", 200.0),
    ("SAVE10", 180.0),
])
def test_discount_codes(code, expected):
    cart = [{"price": 100, "qty": 2}]
    assert apply_discount(cart, code) == expected
```

```bash
pip install pytest
pytest -v                 # run all, verbose
pytest test_discount.py   # one file
pytest -k "save20"        # tests matching name
pytest --cov=discount     # coverage (pytest-cov plugin)
```

**Pytest features worth naming in interviews:**
- `@pytest.fixture` — reusable setup (a test DB session) injected by argument name
- `@pytest.mark.parametrize` — data-driven tests
- Plain `assert` with introspection (shows actual vs expected on failure)


---

## Part 5: API/Integration tests (your strongest story)

This is the most practical thing to demo: test your FastAPI/Express endpoints against a test database.

```python
# test_api.py — FastAPI with httpx TestClient
from fastapi.testclient import TestClient
import pytest
from app.main import app

client = TestClient(app)

def test_create_and_get_user():
    # 1. create
    resp = client.post("/api/users", json={"name": "Ashish", "email": "a@b.c"})
    assert resp.status_code == 201
    user_id = resp.json()["id"]

    # 2. read it back
    resp = client.get(f"/api/users/{user_id}")
    assert resp.status_code == 200
    assert resp.json()["email"] == "a@b.c"

def test_duplicate_email_returns_409():
    client.post("/api/users", json={"name": "X", "email": "dup@b.c"})
    resp = client.post("/api/users", json={"name": "Y", "email": "dup@b.c"})
    assert resp.status_code == 409

def test_unauthorized_access_blocked():
    resp = client.get("/api/transactions")        # no Authorization header
    assert resp.status_code == 401

def test_validation_error():
    resp = client.post("/api/users", json={"name": ""})   # missing email
    assert resp.status_code == 422
```

**What this proves to the interviewer:** you test status codes, auth boundaries, validation, AND business rules — not just the happy path.

```javascript
// Express/Node with supertest
const request = require("supertest");
const app = require("./app");

test("POST /api/users creates a user", async () => {
  const res = await request(app)
    .post("/api/users")
    .send({ name: "Ashish", email: "a@b.c" });
  expect(res.status).toBe(201);
  expect(res.body).toMatchObject({ email: "a@b.c" });
});
```

**Test DB strategy (mention this):** run integration tests against a separate test DB (or in-memory SQLite / testcontainers); roll back or seed fresh data per test so tests never depend on execution order.

---

## Part 6: Frontend (React) testing — the short version

```javascript
// React Testing Library — philosophy: test BEHAVIOR, not implementation
import { render, screen, fireEvent } from "@testing-library/react";
import Counter from "./Counter";

test("increments count on click", () => {
  render(<Counter />);
  fireEvent.click(screen.getByRole("button", { name: /increment/i }));
  expect(screen.getByText("Count: 1")).toBeInTheDocument();
});
```

- **RTL philosophy**: query like a user would (roles, labels, text) — not by internals
- **Hooks**: test through components (`renderHook` exists for isolated hook tests)
- **Jest vs Vitest**: same API; Vite projects (like your revision-guide) typically use **Vitest** + RTL
- **E2E**: Playwright or Cypress for real-browser flows

---

## Part 7: CI integration (1 paragraph, big impression)

"Tests run automatically in CI (GitHub Actions) on every push/PR — if any test fails, the PR can't merge. That's how you prevent regressions from reaching main." Know that the pipeline step is just `npm test` / `pytest` with a non-zero exit code failing the build (links back to exit codes in the shell doc).

---

## Part 8: Interview Q&A rapid fire

**Q: Unit vs integration vs E2E?**
Unit = one function in isolation, mocked deps, milliseconds. Integration = real modules + real DB/HTTP. E2E = whole system via real browser/API. Pyramid: many unit, some integration, few E2E.

**Q: What are mocks and why use them?**
Fakes for dependencies. Make tests fast, deterministic, and independent of external systems. Also let you test error paths (API down, DB duplicate) that are hard to reproduce for real.

**Q: Mock vs stub vs spy?**
Stub = returns canned data. Mock = stub + expectations about calls. Spy = wraps a real object, records how it was used.

**Q: How do you test async code?**
Jest: `async/await` in the test + `await expect(...).rejects.toThrow()`. Pytest: `pytest.raises` or `asyncio` markers. The classic bug: forgetting to await, so the test passes vacuously.

**Q: What would you test in this function? (their favorite)**
Happy path, boundaries (0, empty, max), invalid input -> error thrown, side effects (was X called?). Answer with the AAA structure.

**Q: What is code coverage? Should you aim for 100%?**
% of code executed by tests. No — 100% encourages meaningless tests. Cover business logic and edge cases; config/boilerplate doesn't need it. Meaningful 70% > hollow 100%.

**Q: What makes a test flaky and how do you fix it?**
Hidden dependencies: real time, random data, network, shared state, execution order. Fixes: freeze time, seed randomness, mock network, isolate data per test, fixed ordering.

**Q: Did you write tests in YOUR project? (have a real answer!)**
"In paisapulse I wrote pytest integration tests for the auth and transaction endpoints — checking 401 without tokens, 409 on duplicate email, and validation failures. In the React app I used Vitest + React Testing Library for the form components. Tests run in CI before deploy."

If you haven't yet — actually add 5-6 such tests to one project before interviews. It's a 2-hour task that changes this answer completely.

**Q: TDD — what is it, do you practice it?**
Write failing test -> write minimal code to pass -> refactor. Honest answer: "I know the cycle; I use it for tricky logic like validators, but generally write tests alongside the feature."


