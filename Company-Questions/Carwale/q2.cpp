/*

### 2. Reorder it

You are given two arrays **A** and **B** of length **N** and an integer denoting **P** which will be used for hashing. 

An array **C** is formed as follows:

ci=(ai+bi)(modP)c sub i equals open paren a sub i plus b sub i close paren space open paren mod space cap P close paren
𝑐𝑖=(𝑎𝑖+𝑏𝑖)(mod𝑃)
 

It is given that the length of **C** will be
min

(

𝑁

,

𝑃

)
.
You can reorder one of the arrays **A** or **B** but **not both**. 

You want the array **C** to be **lexicographically smallest**. 

Your task is to print the **hash** of the resulting array **C**. 

**Note:** 

* Let **C** be 0-indexed, print the
hash

=

∑

(

𝑐𝑖

⋅𝑃𝑖

)

mod109+7
.

### Function Description

Complete the Solve function in the editor. 

### Parameters:

* **N**: INTEGER — Size of the array A (and B).
* **P**: INTEGER — The base for hashing / modulo divisor.
* **A**: INTEGER ARRAY — The array A.
* **B**: INTEGER ARRAY — The array B.

### Return Value:

* The function must return an INTEGER denoting the hash value of the array C modulo
109

+7
.

### Input Format for Debugging:

* The first line contains an integer, N, denoting the size of arrays A and B.
* The next line contains an integer, P, denoting the base of the hash.
* Each line

ii
𝑖
 of the

Ncap N
𝑁
 subsequent lines (where
0

≤𝑖

<𝑁
) contains an integer describing A[i].
* Each line

ii
𝑖
 of the

Ncap N
𝑁
 subsequent lines (where
0

≤𝑖

<𝑁
) contains an integer describing B[i].

### Sample Testcases

### **Sample Case 1**

* **Input:** 

text

2
5
5
8
9
6

Use code with caution.
* **Output:** 

text

0

Use code with caution.
* **Explanation:**
We don't reorder any of the arrays.
So array C will be like:
[

(

5

+9

)

%

5

,

(

8

+6

)

%

5

]

=

[

0

,

0

]

Hash

=0

### **Sample Case 2**

* **Input:** 

text

2
2
9
2
3
1

Use code with caution.
* **Output:** 

text

2

Use code with caution.
* **Explanation:**
We don't need to reorder any of the arrays.

𝐶

=

[

0

,

1

]

Hash

=0

⋅20

+1

⋅21

=2

### **Sample Case 3**

* **Input:** 

text

4
2
6
7
1
9
1
5
8
4

Use code with caution.
* **Output:** 

text

24

Use code with caution.
* **Explanation:**
We reorder

Acap A
𝐴
 to be:
[

7

,

9

,

1

,

6

]

Bcap B
𝐵
 can't be reordered since we reorder

Acap A
𝐴
.

𝐶

=

[

0

,

2

,

1

,

2

]

Hash

=0

⋅20

+2

⋅21

+1

⋅22

+2

⋅23

=0

+4

+4

+16

=24

*/

#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

// Helper function to generate the lexicographically smallest array C
// when 'fixed_arr' is kept in its original order and 'perm_arr' can be reordered.
vector<int> get_smallest_c(int n, const vector<int> &fixed_arr, const vector<int> &perm_arr)
{
    vector<int> c(n);
    multiset<int> ms;

    // Store all remainders of the permutable array
    for (int num : perm_arr)
    {
        ms.insert(num % n);
    }

    // Greedily match each element of the fixed array
    for (int i = 0; i < n; ++i)
    {
        int x = fixed_arr[i] % n;

        // The ideal remainder to get a sum of 0 modulo n
        int target_rem = (n - x) % n;

        // Find the smallest available remainder >= target_rem
        auto it = ms.lower_bound(target_rem);

        // If no element >= target_rem exists, wrap around to the smallest overall element
        if (it == ms.end())
        {
            it = ms.begin();
        }

        int chosen_rem = *it;
        c[i] = (x + chosen_rem) % n;

        // Remove the used remainder from the multiset
        ms.erase(it);
    }
    return c;
}

// Function matching the interface required by the online compiler environment
int Solve(int N, int P, int *A, int *B)
{
    long long MOD = 1e9 + 7;

    vector<int> vecA(A, A + N);
    vector<int> vecB(B, B + N);

    // Case 1: Keep B fixed, permute A
    vector<int> c1 = get_smallest_c(N, vecB, vecA);

    // Case 2: Keep A fixed, permute B
    vector<int> c2 = get_smallest_c(N, vecA, vecB);

    // Select the lexicographically smaller array C
    vector<int> &best_c = (c1 < c2) ? c1 : c2;

    // Compute the polynomial rolling hash
    long long total_hash = 0;
    long long current_power = 1; // Represents P^i % MOD

    for (int i = 0; i < N; ++i)
    {
        long long term = (best_c[i] * current_power) % MOD;
        total_hash = (total_hash + term) % MOD;

        // Update power for next iteration: P^(i+1)
        current_power = (current_power * P) % MOD;
    }

    return total_hash;
}

int main()
{
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, p;
    if (cin >> n >> p)
    {
        vector<int> A(n), B(n);
        for (int i = 0; i < n; ++i)
            cin >> A[i];
        for (int i = 0; i < n; ++i)
            cin >> B[i];

        cout << Solve(n, p, A.data(), B.data()) << "\n";
    }

    return 0;
}
