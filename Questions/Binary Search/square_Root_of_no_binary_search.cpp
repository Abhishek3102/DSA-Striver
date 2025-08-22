#include <bits/stdc++.h>
using namespace std;

int findSqrt(int n)
{
    int ans = 1;
    for (int i = 0; i <= n; i++)
    {
        if (i * i <= n)
        {
            ans = i;
        }
        else
        {
            break;
        }
    }
    return ans;
}

// using binary here
// here binary search is used bcoz, binary search is used when answer can be found upto a certain point in an array and after that answer will surely not be found
// for eg, consider 28. take low = 1 and high = 28, in first check mid will come as 14 which is greater than 28 according to condition (i * i <= n). so eliminate whole right side starting from 28.
// then consider low = 1 and high = 13, then mid will come as 7, which is also greater than 28. so again eliminate whole right side.
// then, low = 1, high = 6. so mid will be 3 which is less than 28, 3 * 3 is not less than 28. so update answer as 3, coz this can be one of the answer. so look for bigger answer and if not found then 3 will be the ans. now low = 4 and high = 6, so mid will be 5.
// 5 is also the ans, but we will update low to 6 and check for it as well which will be false. so the final ans is 5.
int findSqrtBinarySearch(int n)
{
    int low = 1, high = n;
    int ans = 1;
    while (low <= high)
    {
        int mid = low + (high - low) / 2; // Prevents overflow compared to (low + high) / 2
        if ((mid * mid) <= n)
        {
            ans = mid;     // mid is a possible answer
            low = mid + 1; // Try to find a bigger value
        }
        else
        {
            high = mid - 1; // mid is too large, look on the left half
        }
    }
    return ans;
    // return high;  both high and ans will give the correct answer.
}

int main()
{
    cout << findSqrtBinarySearch(28);
    return 0;
}