vector<int> plusOne(vector<int> &digits)
{
    int n = digits.size();

    // Walk from the least-significant digit (rightmost) to the most-significant (leftmost)
    for (int i = n - 1; i >= 0; i--)
    {
        if (digits[i] < 9)
        {
            // If current digit isn't 9, just add 1 and we’re done (no carry).
            digits[i] += 1;
            return digits;
        }
        // If it is 9, it becomes 0 and we carry 1 to the next more-significant digit.
        digits[i] = 0;
    }

    // If we finished the loop, all digits were 9 (e.g., 9, 99, 999).
    // Insert a leading 1 to represent the carried 1 at the new most-significant place.
    digits.insert(digits.begin(), 1);
    return digits;
}

/*
explanation :
Step-by-step examples

[1, 2, 3] → start at 3 (<9), make it 4 → [1, 2, 4] (early return).

[1, 2, 9] → 9 becomes 0 with carry → move to 2 (<9), make it 3 → [1, 3, 0].

[9, 9, 9] → all become 0, loop ends → insert leading 1 → [1, 0, 0, 0].

Why traverse from the end?
Because addition propagates from least significant digit to most significant digit—exactly how we do grade-school addition. Starting from the right:
You increment once.
If there’s no carry (digit < 9), you can stop immediately (best case O(1)).
Only when you see a 9 do you set it to 0 and carry to the left.
Starting from the left would force you to reach the right end anyway (and you wouldn’t know whether a carry will ripple), so it’s less efficient and more complex.

Complexity
Time: O(n) in the worst case (all 9s), often better due to early return.
Extra space: O(1) amortized (in-place). In the all-9s case, insert may reallocate but still overall O(n) time for the shift, which is unavoidable since the result has length n+1.

How an experienced CP/DSA/LeetCode programmer “revises” this
Mental model / pattern

Category: Array + simulation of elementary addition with carry.
Key idea: Work from LSD → MSD; stop early when no carry.
Edge case: All digits are 9 → length grows by 1.

Pitfalls to avoid
Converting digits to an integer (overflow for large inputs).
Forgetting the all-9s case.
Mutating and then also building a new vector unnecessarily.

*/