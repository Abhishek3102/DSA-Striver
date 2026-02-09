## Intuition in one sentence

> The window always contains **unique characters**, and when a duplicate appears, we **jump the left pointer forward** instead of shrinking slowly.

---

## When is Sliding Window MOST optimal?

Sliding window is best when **all of these are true** 👇

### ✅ 1. The problem involves a **contiguous subarray / substring**

Examples:

- Substring
- Subarray
- Continuous segment

❌ Not good for:

- Subsequences
- Random selections

---

### ✅ 2. You are asked for **max / min / longest / shortest**

Examples:

- Longest substring without repeating characters
- Maximum sum subarray of size `k`
- Minimum window containing all characters

---

### ✅ 3. The window can **expand and shrink logically**

You can:

- Expand → add a new element
- Shrink → remove an old element
- Maintain some condition (sum, frequency, uniqueness)

---

### ✅ 4. Brute force is **O(n²)** but feels wasteful

Sliding window usually reduces:

```
O(n²) → O(n)
```

---

## Classic problems where sliding window is ideal

- Longest substring without repeating characters ✅ (this one)
- Longest substring with at most K distinct characters
- Maximum sum subarray of size K
- Minimum window substring
- Count of subarrays with given sum (sometimes)
- Fruits into baskets
- Longest subarray with sum ≤ K

---

## When sliding window is NOT a good idea

- When order doesn’t matter
- When elements can’t be “removed” cleanly
- When the window condition depends on future elements
- When backtracking or DP is required

---

## Final mental model 🧠

Think of sliding window as:

> “I’m scanning once, remembering just enough about the past to move forward intelligently.”
