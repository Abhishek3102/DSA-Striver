#include <bits/stdc++.h>
using namespace std;

void inser_sort(int arr[], int n)
{
    // best t.c. -> O(N) already sorted array
    // avg, worst t.c. -> O(N^2)
    for (int i = 0; i < n; i++)
    {
        int swaps = 0;
        int j = i;
        while (j > 0 && arr[j - 1] > arr[j])
        {
            int temp = arr[j - 1];
            arr[j - 1] = arr[j];
            arr[j] = temp;
            j--;
            swaps++;
        }
        cout << swaps << endl;
    }
}

int main()
{
    int n;
    cin >> n;
    int arr[n];
    for (int i = 0; i < n; i++)
        cin >> arr[i];

    inser_sort(arr, n);
    for (int i = 0; i < n; i++)
    {
        cout << arr[i] << " ";
    }
    return 0;
}

/*

Initial Array: 46 13 24 9 20 52
i = 0 (46)

    Already the first element → no swaps
    ✅ swaps = 0

i = 1 (13)

    Compare with 46 → swap → [13, 46, 24, 9, 20, 52]
    ✅ swaps = 1

i = 2 (24)

    Compare with 46 → swap

    Compare with 13 → no swap
    → [13, 24, 46, 9, 20, 52]
    ✅ swaps = 1

i = 3 (9)

    9 < 46 → swap

    9 < 24 → swap

    9 < 13 → swap
    → [9, 13, 24, 46, 20, 52]
    ✅ swaps = 3

i = 4 (20)

    20 < 46 → swap

    20 < 24 → swap

    20 > 13 → stop
    → [9, 13, 20, 24, 46, 52]
    ✅ swaps = 2

i = 5 (52)

    Already in correct position
    ✅ swaps = 0

Final Output:

0
1
1
3
2
0
9 13 20 24 46 52

----------------------------------------------------------------------------------

Great! Let's do both:

---

## ✅ 1. **Count Comparisons (Instead of Swaps)**

In **insertion sort**, a **comparison** happens every time we check `arr[j - 1] > key`.

So for each element, we can count how many times it compares itself to prior elements — this gives you a better idea of time complexity rather than just physical swaps.

---

## ✅ 2. **Use Real Insertion-style Shifting (No Swaps)**

In actual insertion sort, instead of swapping on every comparison (which is inefficient), we:

1. Store the `key` (current element).
2. Shift all larger elements one position ahead.
3. Insert the `key` in the correct spot.

---

## 🔧 Modified Code (Both Improvements)

```cpp
#include <bits/stdc++.h>
using namespace std;

void insertion_sort(int arr[], int n)
{
    for (int i = 1; i < n; i++) // Start from 1, since 0th element is trivially sorted
    {
        int key = arr[i];
        int j = i - 1;
        int comparisons = 0;

        // Shift elements greater than key to the right
        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j--;
            comparisons++;
        }

        // One final comparison that failed (optional: count it)
        if (j >= 0) comparisons++;

        arr[j + 1] = key;

        cout << "Pass " << i << ": comparisons = " << comparisons << endl;
    }
}
```

---

## 🔎 Input:

```plaintext
6
46 13 24 9 20 52
```

## ✅ Output (for comparisons):

```
Pass 1: comparisons = 1
Pass 2: comparisons = 2
Pass 3: comparisons = 3
Pass 4: comparisons = 3
Pass 5: comparisons = 1
```

---

## 🔁 Final Sorted Array:

```plaintext
9 13 20 24 46 52
```

---

## 🧠 Key Takeaways:

* Comparisons better reflect algorithm's performance.
* Actual insertion sort uses **shifting**, not repeated swapping — more efficient.
* Total comparisons here: `1 + 2 + 3 + 3 + 1 = 10` — not bad for 6 elements.

---

Would you like to visualize this as a step-by-step table or compare it with selection/merge sort side-by-side?

*/