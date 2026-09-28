# Python Internals — Interview Prep Guide

## Why this matters
Backend + AI/data interviews drill Python internals: GIL, generators, decorators, mutability, memory. And "what does this print?" snippets (mutable defaults!) are extremely common. Every example is runnable — verify in `python -i`.

---

## Part 1: The GIL (Global Interpreter Lock)

**What it is:** a mutex in CPython that allows **only ONE thread to execute Python bytecode at a time**, even on multi-core machines.

**Why does it exist?** CPython's memory management (reference counting) is not thread-safe. One lock is simpler/faster than fine-grained locks on every object.

**The critical interview nuance — threads vs processes in Python:**

| Workload | Threads help? | Why |
|---|---|---|
| **CPU-bound** (loops, math, parsing) | NO | GIL: only one thread runs bytecode at a time |
| **I/O-bound** (network, disk, DB, API calls) | YES | GIL is RELEASED during I/O waits |

```python
# During time.sleep() or a network request, a thread releases the GIL,
# so other threads CAN run. That's why threading works for I/O-heavy code.

# CPU-bound correct choices:
# 1. multiprocessing  - separate processes, separate GILs, true parallelism
# 2. C extensions (NumPy, pandas) release the GIL during heavy C work
# 3. concurrent.futures.ProcessPoolExecutor for CPU, ThreadPoolExecutor for I/O
```

```python
from concurrent.futures import ThreadPoolExecutor, ProcessPoolExecutor

# I/O-bound: threads are fine (GIL released while waiting)
with ThreadPoolExecutor(max_workers=10) as ex:
    results = list(ex.map(fetch_url, urls))

# CPU-bound: use processes
with ProcessPoolExecutor() as ex:
    results = list(ex.map(cpu_heavy_fn, chunks))
```

**Standard follow-ups:**
- **"Is Python multi-threaded?"** — "Threads exist and are useful for I/O; but CPython's GIL prevents parallel execution of Python bytecode, so CPU-bound work needs multiprocessing."
- **"What about asyncio?"** — Single-threaded cooperative concurrency: one thread, coroutines yield control at `await` points. Great for thousands of concurrent I/O tasks (your FastAPI stack!), useless for CPU-bound work (blocks the whole loop).
- **"Did GIL removal happen?"** — Python 3.13 ships an experimental free-threaded build (PEP 703); GIL-free is the direction, but CPython in production still has the GIL. Knowing this makes you look current.
- **Threads vs asyncio vs multiprocessing one-liner:** "Threads for I/O with blocking libs, asyncio for massive I/O concurrency with async libs, processes for CPU-bound."

---

## Part 2: Execution model & memory management

**Everything is an object.** Names (variables) are REFERENCES to objects — think name-tag, not box.

```python
a = [1, 2, 3]
b = a              # b points to the SAME list object
b.append(4)
print(a)           # [1, 2, 3, 4]
print(a is b)      # True - identity check (same object)
```

**Reference counting + garbage collection:**
- Every object keeps a **refcount**; drops to 0 -> freed immediately (that's the primary mechanism)
- Circular references (a.b = b, b.a = a) never hit 0 -> the **cyclic GC** (generational: gen0/1/2) handles them
- `sys.getrefcount(obj)` shows the count (+1 for the temporary reference in the call)
- `gc.collect()` triggers collection manually; `del x` just removes a name, it doesn't "delete" the object

**Small int caching / interning (classic trap):**
```python
a = 256; b = 256
print(a is b)      # True  - CPython caches ints -5..256

a = 257; b = 257
print(a is b)      # False (in a script; implementation detail!)
print(a == b)      # True
# Lesson: use == for values, `is` ONLY for None/True/False singletons

s1 = "hello"; s2 = "hello"
print(s1 is s2)    # True (string interning for identifier-like strings)
```

**Mutability — THE most tested Python topic:**

| Immutable (can't change in place) | Mutable (can change in place) |
|---|---|
| int, float, str, bool, tuple, frozenset | list, dict, set, custom objects |

```python
# Consequences of immutability:
s = "hi"
s.upper()          # returns NEW string; s unchanged
print(s)           # "hi"

t = ([1, 2], 3)    # tuple is immutable, but its LIST element is mutable!
t[0].append(3)     # works fine -> ([1, 2, 3], 3)
# This is why tuples containing lists are unhashable:
# hash(t) raises TypeError - hashability requires all elements immutable
```

**The #1 famous Python gotcha — mutable default argument:**
```python
def add_item(item, items=[]):      # default list created ONCE at def time!
    items.append(item)
    return items

print(add_item(1))    # [1]
print(add_item(2))    # [1, 2]  <- SAME list reused! Not [2]!

# Correct pattern:
def add_item(item, items=None):
    if items is None:
        items = []
    items.append(item)
    return items
```
Interviewers use this as a screener. Also know: defaults are evaluated once when the function is DEFINED, not per call — check with `add_item.__defaults__`.

**Shallow vs deep copy (same trap, list version):**
```python
import copy
orig = [[1, 2], [3, 4]]

shallow = orig.copy()          # or list(orig), orig[:], dict(d), {...}
shallow[0].append(9)
print(orig)                    # [[1, 2, 9], [3, 4]] - inner lists SHARED

deep = copy.deepcopy(orig)
deep[0].append(7)
print(orig)                    # unchanged
```


---

## Part 3: Iterators & Generators

**Iterator protocol:** an object is an iterator if it has `__iter__` and `__next__`. Iterables (list, str, dict) have `__iter__` returning an iterator. `for` loops call exactly these under the hood:

```python
# What a for loop really does:
for x in [1, 2, 3]:
    print(x)

# is equivalent to:
it = iter([1, 2, 3])       # __iter__
while True:
    try:
        x = next(it)       # __next__
        print(x)
    except StopIteration:
        break
```

**Generators = functions with `yield`** — they produce values lazily, one at a time, pausing between calls. Calling a generator function returns a generator object WITHOUT executing the body.

```python
def countdown(n):
    print("starting")        # nothing prints until first next()!
    while n > 0:
        yield n
        n -= 1

gen = countdown(3)           # no output yet — body not started
next(gen)    # prints "starting", returns 3
next(gen)    # returns 2            (state is FROZEN between calls)
next(gen)    # returns 1
next(gen)    # raises StopIteration

for x in countdown(3):      # idiomatic usage
    print(x)
```

**Why generators matter (say these):**
1. **Memory**: produce one item at a time — process a 10 GB file line by line without loading it
2. **Lazy evaluation**: infinite sequences are representable
3. **Composable pipelines**: gen -> gen -> consumer, all streaming

```python
# Memory example (interview favorite):
def squares_list(n):     return [i * i for i in range(n)]     # builds ALL n items in RAM
def squares_gen(n):      return (i * i for i in range(n))     # generator expr, O(1) memory

# Reads like a pipeline, uses constant memory:
import re
def error_lines(path):
    with open(path) as f:
        for line in f:
            if "ERROR" in line:
                yield line

# Generator expressions (parentheses, not brackets):
total = sum(x * x for x in range(1_000_000))   # never builds the full list
```

**Interview traps:**
```python
# 1. Generators are SINGLE-USE (exhausted):
g = (x for x in [1, 2, 3])
print(list(g))    # [1, 2, 3]
print(list(g))    # []  <- already consumed!

# 2. yield pauses, return stops permanently

# 3. List comprehension vs generator expr in function calls:
sum([x * x for x in range(10)])    # builds intermediate list
sum(x * x for x in range(10))      # streams - prefer this
```

**`yield` also enables coroutines/generators-as-pipelines — mentioning `yield from` delegation and generator-based streaming gets bonus points.**

---

## Part 4: Closures & Decorators

**Closures in Python** — same concept as JS: inner function remembers enclosing scope after the outer returns.

```python
def make_multiplier(n):
    def multiply(x):
        return x * n        # captures n
    return multiply

double = make_multiplier(2)
triple = make_multiplier(3)
double(5)   # 10
triple(5)   # 15

# nonlocal: modify the captured variable (read-only by default)
def counter():
    count = 0
    def inc():
        nonlocal count
        count += 1
        return count
    return inc

c = counter()
c(), c()   # 1, 2
# (global for module-level, nonlocal for enclosing function scope)
```

**Decorators = functions that wrap functions** — take a function, return an enhanced function. `@deco` is syntax sugar for `f = deco(f)`.

```python
import functools, time

def timer(func):
    @functools.wraps(func)                 # preserves name/docstring (say this!)
    def wrapper(*args, **kwargs):
        start = time.perf_counter()
        result = func(*args, **kwargs)
        print(f"{func.__name__} took {time.perf_counter() - start:.4f}s")
        return result
    return wrapper

@timer                                      # = slow_add = timer(slow_add)
def slow_add(a, b):
    time.sleep(1)
    return a + b
```

**Decorators with arguments = three nested layers:**
```python
def retry(times):                          # 1. takes the ARGUMENTS
    def deco(func):                        # 2. takes the function
        @functools.wraps(func)
        def wrapper(*args, **kwargs):      # 3. wraps the call
            for attempt in range(times):
                try:
                    return func(*args, **kwargs)
                except Exception:
                    if attempt == times - 1:
                        raise
                    time.sleep(2 ** attempt)   # exponential backoff
        return wrapper
    return deco

@retry(times=3)
def flaky_api_call():
    ...
```

**Must-know built-in decorators:**
- `@staticmethod` — no self/cls; plain function in class namespace
- `@classmethod` — receives `cls`; alternative constructors: `User.from_json(d)`
- `@property` — method accessed like an attribute; enables validation without breaking callers
- `@functools.lru_cache` — memoization: `@lru_cache(maxsize=None)` on fib() turns exponential into linear (classic demo)
- `@functools.wraps` — inside your own decorators to keep metadata
- `@dataclass` — auto-generates `__init__`, `__repr__`, `__eq__`

```python
class Temperature:
    def __init__(self): self._c = 0
    @property
    def celsius(self): return self._c
    @celsius.setter
    def celsius(self, v):
        if v < -273.15: raise ValueError("below absolute zero")
        self._c = v
```


---

## Part 5: Functions, scoping & OOP internals

**Scoping = LEGB** (Local -> Enclosing -> Global -> Built-in). Python resolves names in that order at call time (dynamic, not at def time).

```python
x = "global"
def outer():
    x = "enclosing"
    def inner():
        print(x)      # "enclosing" (LEGB lookup)
    inner()
outer()
```

**Assignment creates a LOCAL name by default** — this is the classic surprise:
```python
x = 10
def f():
    print(x)      # UnboundLocalError! Because x = 20 below makes x LOCAL for the whole function
    x = 20
# Fix with `global x` (module scope) or `nonlocal x` (enclosing scope) — but avoiding
# mutation of outer scope is better style
```

**`*args` / `**kwargs`:**
```python
def f(*args, **kwargs): ...
f(1, 2, a=3)        # args=(1,2), kwargs={'a': 3}

def g(a, b=2, *args, key, **kw): ...   # key is KEYWORD-ONLY (after *args)

# Unpacking is used everywhere:
print(*[1, 2, 3])                    # 1 2 3
merged = {**d1, **d2}
first, *rest = [1, 2, 3, 4]          # first=1, rest=[2,3,4]
```

**Default args, keyword-only, and the `is None` idiom — see the mutable-default trap in Part 2.**

**OOP internals — the dunder methods they ask about:**

```python
class Vector:
    def __init__(self, x, y):        # constructor (after __new__ allocates)
        self.x, self.y = x, y
    def __repr__(self):              # for DEVELOPERS: repr(v), debugger, console
        return f"Vector({self.x}, {self.y})"
    def __str__(self):               # for USERS: str(v), print(v)
        return f"({self.x}, {self.y})"
    def __eq__(self, other):         # enables v1 == v2
        return isinstance(other, Vector) and (self.x, self.y) == (other.x, other.y)
    def __add__(self, other):        # enables v1 + v2
        return Vector(self.x + other.x, self.y + other.y)
    def __len__(self): return 2
    def __getitem__(self, i):        # enables v[0] -> makes object iterable-ish
        return (self.x, self.y)[i]

# __repr__ vs __str__: repr = unambiguous/debug, str = readable.
# If only __repr__ is defined, str() falls back to it.
```

**Interview Q: "What's the difference between `__new__` and `__init__`?"**
`__new__` creates and returns the instance (static, called first); `__init__` initializes the already-created instance (returns None). `__new__` is how singletons/immutables customize creation.

**Class vs instance attributes (classic trap):**
```python
class Dog:
    tricks = []                 # CLASS attribute - SHARED by all instances!
    def __init__(self, name):
        self.name = name        # INSTANCE attribute - per object

d1, d2 = Dog("a"), Dog("b")
d1.tricks.append("sit")
print(d2.tricks)        # ['sit']  <- shared! Same gotcha as mutable default args

d1.tricks = ["roll"]    # creates an INSTANCE attribute shadowing the class one
```

**Method types:**
```python
class MyClass:
    def method(self): ...                    # instance method: self = instance
    @classmethod
    def cmethod(cls): ...                    # cls = the CLASS (alt constructors)
    @staticmethod
    def smethod(): ...                       # no auto first arg; utility

# MRO - Method Resolution Order (multiple inheritance):
class A: pass
class B(A): pass
class C(A): pass
class D(B, C): pass
print(D.mro())   # D -> B -> C -> A -> object (C3 linearization)
# Classic question: diamond problem - MRO guarantees each class appears once, in a
# consistent order. super() follows the MRO, not just the direct parent!
```


---

## Part 6: Common gotchas & idioms they test

```python
# 1. Late binding in loops (Python's version of the JS var-loop bug):
funcs = [lambda: i for i in range(3)]
print([f() for f in funcs])       # [2, 2, 2]  <- ALL lambdas share the SAME i

# Fix - bind via default arg (evaluated at def time):
funcs = [lambda i=i: i for i in range(3)]
print([f() for f in funcs])       # [0, 1, 2]

# 2. Integer division:
print(7 // 2, 7 % 2, 7 / 2)       # 3 1 3.5   (// floors, / always float)
print(-7 // 2)                    # -4  (floors toward NEGATIVE infinity!)

# 3. Chained comparison (Python-unique):
print(1 < 5 < 10)                 # True (1 < 5 AND 5 < 10)

# 4. Handy stdlib:
from collections import defaultdict, Counter
d = defaultdict(list)
d["k"].append(1)                  # no KeyError
Counter("banana").most_common(1)  # [('a', 3)]

# 5. enumerate & zip instead of index gymnastics:
for i, item in enumerate(items, start=1): ...
for a, b in zip(list1, list2): ...

# 6. EAFP style ("easier to ask forgiveness") - name-drop this:
try:
    val = d["key"]
except KeyError:
    val = default
# Pythonic preference order: d.get("key", default) > try/except > `in` check

# 7. with = context manager (__enter__/__exit__):
with open("f.txt") as f: ...      # closed even on exception
# DB sessions, locks, FastAPI Depends - all use this protocol

# 8. Truthiness: falsy = 0, 0.0, "", [], {}, set(), (), None, False
# But check None explicitly - 0 and "" are valid results:
if result is not None: ...        # NOT `if result:`
```

**Performance idioms (backend interviews love these):**
```python
# String building: NEVER += in a loop (quadratic); join is O(n)
s = ", ".join(str(x) for x in items)

# Membership: set/dict O(1) vs list O(n)
big_set = set(big_list)
if x in big_set: ...


---

## Part 7: Tricky Python output questions (rapid-fire drill)

```python
# Q1 - mutable default (the classic)
def f(x, l=[]):
    l.append(x)
    return l
print(f(1))   # [1]
print(f(2))   # [1, 2]   <- SAME list reused!

# Q2 - shallow copy
a = [[1, 2], [3, 4]]
b = a.copy()
b[0].append(9)
print(a)          # [[1, 2, 9], [3, 4]]

# Q3 - is vs == on ints
a, b = 256, 256
c, d = 257, 257
print(a is b, c is d)    # True False

# Q4 - late binding
funcs = [lambda: i for i in range(3)]
print([f() for f in funcs])      # [2, 2, 2]

# Q5 - generator lazy & single-use
def gen():
    print("start")
    yield 1
g = gen()                 # nothing prints yet
print(list(g))            # start  \n  [1]
print(list(g))            # []

# Q6 - tuple with mutable element
t = (1, [2, 3])
t[1].append(4)
print(t)                  # (1, [2, 3, 4])

# Q7 - strings immutable
s = "hello"
print(s.upper(), s)       # HELLO hello   (s.upper() returns NEW string)

# Q8 - // floors negatives
print(-7 // 2, int(-7 / 2))   # -4 -3   (floor vs truncate)

# Q9 - class attribute sharing
class C:
    items = []
x, y = C(), C()
x.items.append(1)
print(y.items)            # [1]

# Q10 - [x]*n shares rows
grid = [[0] * 3] * 2
grid[0][0] = 1
print(grid)               # [[1, 0, 0], [1, 0, 0]]
# Fix: [[0] * 3 for _ in range(2)]

# Q11 - bool is int
print(True + True)        # 2
print(0.1 + 0.2 == 0.3)   # False

# Q12 - finally always runs
def div(a, b):
    try:
        return a / b
    except ZeroDivisionError:
        return "inf"
    finally:
        print("done")
print(div(1, 0))          # done \n inf

# Q13 - slicing
lst = [1, 2, 3, 4, 5]
print(lst[1:4], lst[::-1], lst[-2:])   # [2,3,4] [5,4,3,2,1] [4,5]

# Q14 - empty containers are fresh objects
print([] is [], {} is {})     # False False
print(None is None)           # True (singleton)

# Q15 - round half to EVEN (banker's rounding)
print(round(0.5), round(1.5), round(2.5))   # 0 2 2

# Q16 - sort with key
pairs = [(1, "b"), (2, "a")]
print(sorted(pairs, key=lambda p: p[1]))    # [(2, 'a'), (1, 'b')]

# Q17 - mutation without assignment works without `global`
def f():
    total.append(1)       # mutation OK; assignment would need `global`
total = []
f()
print(total)              # [1]

# Q18 - except order matters
try:
    raise ValueError("v")
except ValueError as e:
    print("value", e)     # specific FIRST, Exception LAST (else unreachable)
```

**Method for output questions:**
1. Check mutability of everything involved
2. Check default args / class attributes (created ONCE)
3. Identity (`is`) vs value (`==`)
4. Generators: lazy + single-use
5. Remember: `-7//2 == -4`, `True + True == 2`, `round(2.5) == 2`

---

## Part 8: Quick-revision one-liners

- GIL: one thread runs Python bytecode at a time; released during I/O; CPU-bound -> multiprocessing; 3.13 has experimental free-threading
- asyncio: single thread, cooperative at `await`; ideal for I/O-heavy APIs (FastAPI)
- Threads (blocking I/O) vs asyncio (massive async I/O) vs processes (CPU) — know when each
- Everything is an object; variables are references; refcount 0 frees; cyclic GC handles cycles
- Small ints (-5..256) cached; `is` only for None/True/False
- Mutable: list/dict/set; Immutable: int/str/tuple/frozenset; tuple of lists = unhashable
- Mutable defaults created ONCE at def time — use None sentinel
- Shallow copy shares nested objects; `copy.deepcopy` doesn't
- Generators: lazy, O(1) memory, single-use; `yield` freezes state
- Decorator: `@deco` = `f = deco(f)`; with args = 3 nested functions; always `functools.wraps`
- LEGB; assignment makes names local (UnboundLocalError); `nonlocal`/`global`
- `__new__` creates, `__init__` initializes; class attributes SHARED by instances
- MRO (C3) + `super()` follow MRO; diamond problem solved
- `__repr__` dev-facing, `__str__` user-facing; dunder methods power operators
- Performance: join > +=, set membership > list, lru_cache, generators for big data
- Trap list: mutable defaults, `[x]*n` shared rows, late-binding lambdas, `-7//2==-4`, `round(2.5)==2`, `True+True==2`, generator exhaustion



