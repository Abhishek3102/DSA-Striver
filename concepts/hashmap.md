---

## First loop

```cpp
for (int x : arr) {
    freq[x]++;
}
```

### What this loop **means**

This is a **range-based for loop**.

Read it in English:

> “For **each element `x` inside `arr`**, do something.”

So if:

```cpp
arr = {1, 2, 2, 3}
```

The loop runs like this:

```
x = 1 → freq[1]++
x = 2 → freq[2]++
x = 2 → freq[2]++
x = 3 → freq[3]++
```

### What `freq[x]++` does

* `freq` is an `unordered_map<int,int>`
* `freq[x]`:

  * If `x` **does not exist**, map creates it with value `0`
  * Then `++` increases it

So this line:

```cpp
freq[x]++;
```

is equivalent to:

> “Increase the count of value `x` by 1”

---

### Can this be written using index-based loop?

✅ **YES — 100%**

Exact same logic:

```cpp
for (int i = 0; i < arr.size(); i++) {
    freq[arr[i]]++;
}
```

Both are identical in behavior.

💡 Rule of thumb:

- Use **range-based loop** when you only care about values
- Use **index-based loop** when you need index `i`

---

## Second loop

```cpp
for (auto &p : freq) {
    cout << p.first << " -> " << p.second << endl;
}
```

This loop iterates over the **map itself**.

### What is `p`?

Each `p` is a **key–value pair**:

```cpp
p.first   // key   (the number)
p.second  // value (its frequency)
```

So if `freq` contains:

```
{1:2, 2:3, 3:1}
```

The loop runs like:

```
p = (1,2)
p = (2,3)
p = (3,1)
```

### Why `auto &p`?

- `auto` → compiler figures out the type
- `&` → avoid copying the pair (faster)

You can _mentally read it_ as:

> “For each (number, frequency) pair in the map…”

---

## Other ways to write the **second loop**

### 1️⃣ Using explicit type (no `auto`)

```cpp
for (pair<int, int> p : freq) {
    cout << p.first << " -> " << p.second << endl;
}
```

(or technically correct version)

```cpp
for (pair<const int, int> p : freq) {
    cout << p.first << " -> " << p.second << endl;
}
```

---

### 2️⃣ Using iterator (old-school, very important to know)

```cpp
for (auto it = freq.begin(); it != freq.end(); it++) {
    cout << it->first << " -> " << it->second << endl;
}
```

Read it as:

> “Start at the beginning of the map and move until the end.”

---

### 3️⃣ Structured bindings (C++17+ — very clean)

```cpp
for (auto &[key, value] : freq) {
    cout << key << " -> " << value << endl;
}
```

This is equivalent to:

```cpp
key   = p.first
value = p.second
```

---

## Mental template (this is what helps you write it yourself)

### Counting loop template

```cpp
for (each element x in array) {
    frequency[x]++;
}
```

### Printing loop template

```cpp
for (each (key, value) in frequency_table) {
    print key and value
}
```
