# JavaScript Internals — Interview Prep Guide

## Why this matters
Frontend and full-stack interviews live on these questions: event loop, closures, prototypes, hoisting, `this`, promises. Expect "what does this print?" snippets. Every example below is runnable — actually run them in the browser console or Node to internalize.

---

## Part 1: The Event Loop (THE most asked JS question)

**JS is single-threaded** — one call stack. Async work (timers, network, I/O) is handed to the browser/Node runtime, and the **event loop** decides what runs next on the stack.

**The components:**
1. **Call stack** — where synchronous code executes
2. **Web APIs / Node APIs** — timers, fetch, DOM events (not part of JS itself)
3. **Macrotask queue (task queue)** — `setTimeout`, `setInterval`, I/O, UI events
4. **Microtask queue** — promise callbacks (`.then/.catch/.finally`), `queueMicrotask`, `MutationObserver`
5. **Event loop** — when the call stack is empty: **drain ALL microtasks first**, then take ONE macrotask, then drain microtasks again, repeat

**Execution order per tick:**
```
run sync code -> microtasks (ALL of them) -> one macrotask -> microtasks -> one macrotask -> ...
```

```javascript
console.log("1");                                  // sync
setTimeout(() => console.log("2"), 0);             // macrotask
Promise.resolve().then(() => console.log("3"));    // microtask
console.log("4");                                  // sync

// Output: 1 4 3 2
// Why: sync first (1,4), then ALL microtasks (3), then macrotask (2).
// setTimeout 0 does NOT mean "run immediately" — it means "queue as macrotask".
```

**The famous layered version:**
```javascript
console.log("start");

setTimeout(() => {
  console.log("timeout1");
  Promise.resolve().then(() => console.log("promise inside timeout"));
}, 0);

Promise.resolve().then(() => {
  console.log("promise1");
  setTimeout(() => console.log("timeout2"), 0);
});

console.log("end");

// Output:
// start
// end
// promise1            <- microtasks run before ANY macrotask
// timeout1            <- first macrotask
// promise inside timeout  <- microtask after each macrotask
// timeout2            <- queued during microtask, runs next macrotask
```

**Key rules to state out loud:**
- Microtasks always beat macrotasks, even a 0ms timeout
- Each macrotask is followed by a FULL microtask drain
- `async/await` is promise syntax sugar: code after `await` behaves like a `.then` (microtask)

```javascript
async function test() {
  console.log("a");
  await null;                  // everything below queues as microtask
  console.log("c");
}
test();
console.log("b");
// Output: a b c
```

**Interview Q: "Does setTimeout(fn, 0) run exactly after 0ms?"**
No. It runs after the minimum delay AND when the call stack + all microtasks are done. If sync code blocks for 2 seconds, the callback waits 2+ seconds. JS has no accurate timers, only minimums.

**Interview Q: "What blocks the event loop?"**
Long synchronous code (huge loop, JSON.parse of giant string, sync XHR). Result: frozen UI, unhandled requests. Fix: chunk work, use Web Workers (browser) / worker threads (Node).

---

## Part 2: Closures

**A closure is a function that remembers the variables from the scope where it was created, even after that outer function has returned.**

```javascript
function counter() {
  let count = 0;                 // lives on because innerFn references it
  return function innerFn() {
    count++;
    return count;
  };
}
const inc = counter();
inc(); // 1
inc(); // 2  <- count survived after counter() returned
const inc2 = counter();
inc2(); // 1  <- separate closure, separate count
```

**Classic interview trap — closures in loops (var vs let):**
```javascript
for (var i = 0; i < 3; i++) {
  setTimeout(() => console.log(i), 0);
}
// Prints: 3 3 3  — all three callbacks share ONE var i (function-scoped),
// by the time they run, the loop finished and i === 3

for (let i = 0; i < 3; i++) {
  setTimeout(() => console.log(i), 0);
}
// Prints: 0 1 2  — let creates a NEW binding per iteration (block-scoped),
// each closure captures its own i
```
This single question tests: closures + var/let scoping + event loop. Master it.

**Practical uses (say these in interviews):**
- Data privacy / module pattern (encapsulate state)
- Function factories (`const mul2 = multiply(2)`)
- Memoization, debounce, throttle, once()
- React hooks: `useState`'s setter closes over state; stale-closure bugs in hooks come from this

```javascript
// debounce — the classic closure use case
function debounce(fn, delay) {
  let timer;                              // captured state
  return function (...args) {
    clearTimeout(timer);
    timer = setTimeout(() => fn.apply(this, args), delay);
  };
}
```


---

## Part 3: Hoisting & declarations

**Hoisting** = during compilation, declarations are moved to the top of their scope (conceptually). What actually happens: the engine **allocates memory for declarations before executing code**.

```javascript
console.log(a);   // undefined  (var is hoisted AND initialized to undefined)
console.log(b);   // ReferenceError: Cannot access 'b' before initialization (TDZ)
console.log(c);   // ReferenceError: Cannot access 'c' before initialization (TDZ)
var a = 1;
let b = 2;
const c = 3;
```

**Function declarations vs expressions:**
```javascript
sayHi();          // "hi" — function declarations are FULLY hoisted (body included)
function sayHi() { console.log("hi"); }

bye();            // TypeError: bye is not a function
var bye = function () { console.log("bye"); };
// var bye was hoisted as undefined -> calling undefined throws TypeError
// (note: with let/const it would be ReferenceError/TDZ instead)
```

**var vs let vs const (know all three rows cold):**

| | var | let | const |
|---|---|---|---|
| Scope | function | block | block |
| Hoisted | yes, init `undefined` | yes, but TDZ | yes, but TDZ |
| Re-declare | allowed | not allowed | not allowed |
| Re-assign | allowed | allowed | **not allowed** |

**TDZ (Temporal Dead Zone)** — the window between entering scope and the `let/const` declaration line, where accessing the variable throws ReferenceError. State this term explicitly; it signals depth.

```javascript
// const freezes the BINDING, not the value:
const arr = [1, 2];
arr.push(3);      // fine!
arr = [];         // TypeError: Assignment to constant variable

const obj = { a: 1 };
obj.a = 2;        // fine
// To truly freeze: Object.freeze(obj) (shallow)
```

**Hoisting trap question:**
```javascript
var x = 21;
function foo() {
  console.log(x);   // undefined — NOT 21!
  var x = 20;       // local var x is hoisted within foo, shadowing global
}
foo();
```

---

## Part 4: Prototypes & inheritance

**Every JS object has an internal link `[[Prototype]]` (accessible via `__proto__` or `Object.getPrototypeOf`).** Property lookup walks up this chain until found or `null` — that's the **prototype chain**.

```javascript
const animal = { eats: true };
const dog = Object.create(animal);   // dog.__proto__ === animal
dog.barks = true;

dog.barks;   // true  (own property)
dog.eats;    // true  (found on prototype — delegation, not a copy)
dog.fly;     // undefined (walked entire chain, hit null)

// hasOwnProperty distinguishes own vs inherited
dog.hasOwnProperty("barks");      // true
dog.hasOwnProperty("eats");       // false
```

**`class` is syntax sugar over prototypes:**
```javascript
class User {
  constructor(name) { this.name = name; }        // instance property
  greet() { return `hi ${this.name}`; }          // stored on User.prototype
}

const u = new User("ashish");
u.greet();                       // "hi ashish" — found on prototype
u.hasOwnProperty("greet");       // false
u.hasOwnProperty("name");        // true

// The old ES5 equivalent under the hood:
function User2(name) { this.name = name; }
User2.prototype.greet = function () { return `hi ${this.name}`; };
```

**What `new` does (4 steps — ask frequently):**
1. Creates a fresh object `{}`
2. Links its `[[Prototype]]` to `Constructor.prototype`
3. Calls the constructor with `this` = the new object
4. Returns the object (unless constructor returns an object explicitly)

**Interview Q: "Difference between `__proto__` and `prototype`?"**
- `prototype` — a property of constructor FUNCTIONS; the object that instances will link to
- `__proto__` / `[[Prototype]]` — the actual link on every OBJECT
`u.__proto__ === User.prototype` → true.

**Interview Q: "How does inheritance work in class terms?"**
```javascript
class Admin extends User {
  constructor(name, level) {
    super(name);            // MUST call super before using this
    this.level = level;
  }
}
// Admin.prototype.__proto__ === User.prototype  -> chain works both for
// instances AND for static/method lookup
```


---

## Part 5: `this` (the #1 source of tricky output questions)

**`this` is decided by HOW a function is CALLED, not where it's defined** (except arrow functions).

**The 5 rules, in order of precedence:**
1. **`new` binding** → `this` = the newly created object
2. **Explicit binding** (`call`/`apply`/`bind`) → `this` = the given object
3. **Implicit binding** → `this` = the object left of the dot at call time
4. **Default binding** → `this` = `globalThis` (or `undefined` in strict mode)
5. **Arrow functions** → `this` is inherited from the enclosing lexical scope; call/apply/bind CANNOT change it

```javascript
const user = {
  name: "ashish",
  hello()  { console.log(`hi ${this.name}`); },
  helloArrow: () => console.log(`hi ${this.name}`),
};

user.hello();        // "hi ashish"  (implicit: object left of the dot)
user.helloArrow();   // "hi undefined" — arrow has no own this, takes outer (module/global) scope

const ref = user.hello;
ref();               // "hi undefined" — called with NO object -> default binding

setTimeout(user.hello, 100);        // "hi undefined" — same reason
setTimeout(() => user.hello(), 100); // "hi ashish" — wrapper restores implicit binding
```

**call / apply / bind:**
```javascript
function intro(city, role) { return `${this.name} from ${city}, ${role}`; }
const u = { name: "ashish" };

intro.call(u, "Delhi", "dev");       // comma-separated args
intro.apply(u, ["Delhi", "dev"]);    // array of args (a = array)
const bound = intro.bind(u);         // returns NEW function, this locked forever
bound("Delhi", "dev");
```

**The classic tricky one — `this` in callbacks and nested functions:**
```javascript
const obj = {
  items: [1, 2, 3],
  print() {
    console.log(this.items);              // works: implicit binding
    this.items.forEach(function (n) {
      console.log(this);                  // undefined/global! plain callback = default binding
    });
    this.items.forEach((n) => console.log(this === obj));  // true true true — arrow inherits print's this
  },
};
```

**Arrow function rules (rapid fire):**
- No own `this`, `arguments`, `super`, or `prototype`
- Can't be used as constructors (`new` fails)
- Perfect for callbacks where you want the enclosing `this`
- Bad as object methods (no own `this`) and bad as prototype methods

**Interview Q: "How does `this` work in a React class component vs hooks?"**
Class: methods lose `this` in callbacks (why people `.bind(this)` in constructors). Hooks: arrow functions/closures keep the right reference.

---

## Part 6: Promises & async/await

**A Promise** = object representing a future value. States: **pending → fulfilled | rejected** (settled, irreversible).

```javascript
const p = new Promise((resolve, reject) => {
  setTimeout(() => resolve("done"), 1000);
});
p.then(v => console.log(v)).catch(e => console.log(e)).finally(() => console.log("always"));
```

**Combinators (memorize the differences):**
| | Resolves when | Rejects when |
|---|---|---|
| `Promise.all` | ALL resolve | FIRST rejection (fail-fast) |
| `Promise.allSettled` | always — full status list | never |
| `Promise.race` | first settled (either) | first rejection if it comes first |
| `Promise.any` | FIRST fulfillment | all reject -> `AggregateError` |

```javascript
// Classic use: allSettled for parallel API calls where partial failure is OK
const results = await Promise.allSettled([fetchA(), fetchB(), fetchC()]);
const ok = results.filter(r => r.status === "fulfilled").map(r => r.value);
```

**async/await internals (say this):**
- `async` function ALWAYS returns a promise
- `await` pauses the function (not the thread!), queues the rest as a microtask, yields control to the event loop
- `await` on a non-promise value still yields one microtask tick

**Error handling in async code:**
```javascript
// try/catch works for await
try {
  const res = await fetch(url);
  if (!res.ok) throw new Error(`HTTP ${res.status}`);   // fetch does NOT throw on 404/500!
  const data = await res.json();
} catch (err) { console.error(err); }

// Sequential vs parallel (performance question they love):
const a = await fetchA();     // SEQUENTIAL: total = tA + tB  (slow, wrong pattern)
const b = await fetchB();

const [x, y] = await Promise.all([fetchA(), fetchB()]);  // PARALLEL: total = max(tA, tB)
```

**Tricky output — await inside loops:**
```javascript
const delays = [100, 50, 200];
for (const d of delays) {
  await new Promise(r => setTimeout(r, d));   // sequential: 100 then 50 then 200
}

delays.forEach(async d => {
  await new Promise(r => setTimeout(r, d));   // PARALLEL-ish! forEach doesn't await.
  console.log(d);                             // prints 50, 100, 200 (completion order)
});
// Lesson: forEach ignores the returned promises. Use for...of for sequential,
// Promise.all(map()) for parallel.
```

**Chaining rule:** every `.then` returns a NEW promise; returning a value passes it on; returning a promise unwraps it; throwing skips to the next `.catch`.
```javascript
Promise.resolve(1)
  .then(v => v + 1)             // 2
  .then(v => { throw new Error("boom"); })
  .then(() => console.log("skipped"))
  .catch(e => e.message + "!")  // "boom!" — catch RECOVERS, chain continues
  .then(v => console.log(v));   // "boom!"
```

---

## Part 7: Types, coercion & equality (trick-question fuel)

**`==` vs `===`:** `==` coerces types before comparing; `===` checks type + value. Rule: always use `===`, know `==` only for output questions.

```javascript
// The classics:
null == undefined;      // true  (special case - they equal nothing else)
null === undefined;     // false
NaN == NaN;             // false  (NaN is not equal to anything, even itself)
// correct NaN check:
Number.isNaN(NaN);      // true

"" == 0;                // true   ("" coerces to 0)
"0" == 0;               // true
[] == "";               // true   ([] -> "" via toString)
[] == 0;                // true   ("" -> 0)
[1] == 1;               // true
{} == "[object Object]" // true (toString)
0 == false;             // true
```

**Falsy values — memorize the list:**
`false, 0, -0, 0n, "", null, undefined, NaN` — everything else is truthy, including `"0"`, `"false"`, `[]`, `{}`.

```javascript
Boolean("0");   // true
Boolean([]);    // true
Boolean({});    // true
!!0;            // false
```

**typeof — memorize the quirks:**
```javascript
typeof null;         // "object"  <- famous JS bug, historical. Interview favorite!
typeof undefined;    // "undefined"
typeof function(){}; // "function"
typeof [];           // "object"  <- use Array.isArray([]) instead
typeof NaN;          // "number"
```

**Pass by value vs reference:**
- Primitives (number, string, boolean, null, undefined, symbol, bigint) -> copied by VALUE
- Objects/arrays/functions -> copied by REFERENCE (the reference itself is passed by value)

```javascript
let a = { x: 1 };
let b = a;
b.x = 2;
console.log(a.x);   // 2 - same object

let p = 1, q = p;
q = 2;
console.log(p);     // 1 - primitives copied

function mutate(list) { list.push(4); }      // mutates caller's array!
function reassign(list) { list = [9]; }      // only rebinds the local parameter
const nums = [1, 2, 3];
mutate(nums);  console.log(nums);   // [1,2,3,4]
reassign(nums); console.log(nums);  // still [1,2,3,4]
```

**Shallow vs deep copy:**
```javascript
const original = { a: 1, nested: { b: 2 } };

// Shallow copies - nested objects still SHARED:
const s1 = { ...original };
s1.nested.b = 99;
console.log(original.nested.b);   // 99 !!


---

## Part 8: Tricky JS output questions (rapid-fire drill)

Cover the answers, predict, then verify in console. This is the section to redo the night before.

```javascript
// Q1 - chained comparisons
console.log(1 < 2 < 3);         // true   (1<2 -> true -> 1; 1 < 3)
console.log(3 > 2 > 1);         // false  (3>2 -> true -> 1; 1 > 1 -> false)

// Q2 - object/array coercion
console.log([] + []);           // ""
console.log([] + {});           // "[object Object]"

// Q3 - floating point
console.log(0.1 + 0.2 === 0.3); // false (0.30000000000000004)
// fix: Math.abs(a - b) < Number.EPSILON

// Q4
console.log(typeof typeof 1);   // "string" (typeof 1 -> "number"; typeof "number" -> "string")

// Q5 - hoisting
(function () {
  console.log(a);   // undefined (var hoisted)
  var a = 5;
})();

// Q6 - closure counters
function make() {
  let n = 0;
  return () => ++n;
}
const f1 = make(), f2 = make();
console.log(f1(), f1(), f2());   // 1 2 1

// Q7 - event loop
console.log("A");
setTimeout(() => console.log("B"), 0);
Promise.resolve().then(() => console.log("C"));
console.log("D");
// A D C B

// Q8 - microtask queue order
Promise.resolve()
  .then(() => { console.log(1); })
  .then(() => { console.log(2); });
console.log(3);
// 3 1 2

// Q9 - await ordering (tricky!)
async function f() {
  console.log(1);
  await Promise.resolve();
  console.log(4);
}
console.log(0);
f();
console.log(2);
Promise.resolve().then(() => console.log(3));
// 0 1 2 3 4  - continuation after await (4) is queued AFTER then(3)

// Q10 - this binding
const o = { x: 42, getX: function () { return this.x; } };
console.log(o.getX());    // 42
const g = o.getX;
console.log(g());         // undefined
console.log(g.call(o));   // 42

// Q11 - object key order
const obj = { a: 1 };
obj["b"] = 2;
obj[3] = 3;
console.log(Object.keys(obj));  // ["3", "a", "b"]  (integer-like keys FIRST, then insertion)
console.log(obj[3] === obj["3"]); // true (same key)

// Q12 - sort is IN PLACE + string sort by default!
[1, 10, 2].sort();               // [1, 10, 2]  ("1" < "10" < "2" as strings)
[1, 10, 2].sort((a, b) => a - b); // [1, 2, 10] - always pass a comparator

// Q13 - arrow implicit return
const f1 = (x) => ({ val: x });   // parens -> returns object
const f2 = (x) => { val: x };     // braces -> block, returns undefined
console.log(f1(5), f2(5));        // {val:5} undefined

// Q14 - strings immutable
let s = "hello";
s[0] = "H";
console.log(s);                   // "hello"

// Q15 - the loop classic
for (var i = 0; i < 3; i++) setTimeout(() => console.log(i));
for (let j = 0; j < 3; j++) setTimeout(() => console.log(j));
// 3 3 3 then 0 1 2

// Q16 - promise executor is SYNCHRONOUS
new Promise((resolve) => {
  console.log("executor");        // prints immediately
  resolve();
}).then(() => console.log("then"));
console.log("after");
// executor -> after -> then

// Q17 - error propagation
Promise.resolve()
  .then(() => { throw new Error("x"); })
  .catch(() => console.log("caught"))    // recovers
  .then(() => console.log("continues")); // both print

// Q18 - object reference equality
const a2 = { v: 1 }, b2 = { v: 1 };
console.log(a2 == b2, a2 === b2);   // false false (different references)
console.log(a2.v === b2.v);         // true

// Q19 - implicit boolean
console.log(!!"false");   // true  (non-empty string)
console.log(!!undefined); // false
console.log([].length ? "y" : "n");  // "n" (length 0 falsy) but [] itself is truthy

// Q20 - null vs undefined
console.log(null ?? "fallback");    // "fallback"
console.log(0 ?? "fallback");       // 0      (?? only skips null/undefined)
console.log(0 || "fallback");       // "fallback" (|| skips all falsy)
console.log("" ?? "x", "" || "x");  // "" "x"  <- ?? vs || difference, asked a lot
```

**Method for answering output questions out loud (partial credit lives here):**
1. Mark all sync statements - they run first
2. Queue microtasks (thens, awaits) in order
3. Queue macrotasks (timers, events)
4. For `this`: find the call site, apply the 5 rules
5. Narrate the reasoning, don't just blurt the answer

---

## Part 9: Quick-revision one-liners

- Event loop: sync -> ALL microtasks -> ONE macrotask -> microtasks -> ...
- Microtasks: promise callbacks, queueMicrotask. Macrotasks: setTimeout, I/O, events
- Closures = function + captured scope; cause the var-loop `3 3 3` bug
- `let/const` in loops create a fresh binding per iteration
- Hoisting: `var` initializes undefined; `let/const` sit in TDZ; function declarations hoist fully
- `this`: new > call/bind/apply > object.dot > default; arrows inherit lexically, unchangeable
- `__proto__` is the object's link; `.prototype` is the constructor's template
- `new` = create object, link prototype, call with this, return
- async fn always returns a Promise; await queues the rest as a microtask
- Promise.all fail-fast; allSettled never fails; race first settled; any first success
- `==` coerces, `===` doesn't; only 8 falsy values; `typeof null === "object"`
- Objects are reference types: spread is a shallow copy, structuredClone is deep
- `sort()` mutates in place and sorts as strings by default



