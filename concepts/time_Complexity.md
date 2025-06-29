---

## 🔍 **What Makes an Algorithm "Feasible"?**

When we say an algorithm is “feasible,” we mean:

> It can run within **a reasonable time**, usually under **1 to 2 seconds**, depending on the context (like competitive programming or user-facing software).

### 💡 Key Idea:

Modern computers (and online judges) can generally perform about **10⁸ operations per second**.

This is a widely used **benchmark** in algorithm analysis and is based on the CPU instruction processing speed (millions of instructions per second — MIPS).

---

## 🧮 Let's Do the Math:

### 1. **Assume n = 10⁶ (1 million elements)**

### 2. Consider an O(n²) Algorithm:

That would mean approximately:

$$
n^2 = (10^6)^2 = 10^{12} = 1,000,000,000,000 \text{ operations}
$$

### 3. How Long Would That Take?

Let’s divide the number of operations by how many a computer can handle per second (10⁸ ops/sec):

$$
\frac{10^{12}}{10^8} = 10^4 = 10,000 \text{ seconds}
$$

➡️ That’s almost **3 hours** to run a single test case.

🛑 **Conclusion**: This is way too slow. No online judge or user will wait 3 hours for your solution to run.

---

## ✅ Now Try O(n log n):

$$
n \log n = 10^6 \cdot \log_2 10^6 \approx 10^6 \cdot 20 = 2 \times 10^7
$$

So around **20 million operations**.

$$
\frac{2 \times 10^7}{10^8} = 0.2 \text{ seconds}
$$

✅ **Totally acceptable** — this will run comfortably under 1 second.

---

## ✅ What About O(n)?

$$
n = 10^6 \Rightarrow 1 \text{ million operations}
$$

$$
\frac{10^6}{10^8} = 0.01 \text{ seconds}
$$

⚡ Super fast.

---

## 📊 Quick Comparison Table:

| Time Complexity | Approx. Operations for n = 10⁶ | Estimated Time (at 10⁸ ops/sec) | Feasible? |
| --------------- | ------------------------------ | ------------------------------- | --------- |
| O(1)            | 1                              | negligible                      | ✅        |
| O(log n)        | \~20                           | negligible                      | ✅        |
| O(n)            | 10⁶                            | 0.01 sec                        | ✅        |
| O(n log n)      | \~2×10⁷                        | 0.2 sec                         | ✅        |
| O(n²)           | 10¹²                           | 10,000 sec (\~3 hours)          | ❌        |
| O(2ⁿ)           | insane                         | forget about it                 | ❌❌❌    |

---

## 🔁 What If n = 1000?

$$
n^2 = 10^6 \Rightarrow \text{1 million operations}
\Rightarrow \text{~0.01 sec}
$$

✅ **Feasible** for O(n²)

That’s why you’ll often see O(n²) algorithms used for n ≤ 1000.

---

## ✅ Final Conclusion:

We conclude **O(n²)** is **not feasible for n = 10⁶** based on:

- Realistic CPU operation limits (\~10⁸ ops/sec)
- Time per test case limits (typically ≤ 1 second)
- Simple math: O(n²) = 10¹² operations is too many

So unless there's a **very low constant factor** or special optimization, O(n²) for large inputs is impractical.

---
