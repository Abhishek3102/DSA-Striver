// here a pile of bananas will be given and a fixed time that is no. of hours will be given.
// return the minimum integer k such that koko can eat all bananas within k hours.

// piles[] = [3 6 7 11] h = 8
// so suppose we take 2 bananas/hr, then for 3 koko will need 2 hrs bcoz we take ceil of all value (here it was 1.5, 3 % 2 = 1.5) so we take 2.
// 3 hrs for 6, 4 hrs for 7, 6 hrs for 11. so this is not the required solution coz hrs is exceeding max hrs. so we increasing bananas/hr. as we increase it,the no. of hrs reduces.
// for 3 bananas/hr, the total time will be 4+3+2+1 = 10hrs.
// so we go with 4 bananas/hr which will exactly match with 8 hrs. if we further increase banana/hr the no. of hrs will reduce, but we only require the min rate in which given hours is reached. so we will stick with 4 ban/hr.
// answer will always lie between 1 and max value of given array
// so see we taken all val from 1 to 11 and then apply bs on it.
// low = 1, high = 11 so mid = 6. when 6 ban/hr, we are under the deadline which will come as 1+1+2+2 = 6hrs < 8 hrs(given)
// so we will store 6 as answer, but since we have to find min possible answer we eliminate the right side fully from 6 and search in left for any smaller ans than 6.
// and then when high crosses low, is the condition where bs will end and the ans which is stored at that point will be the final answer.

#include <bits/stdc++.h>
using namespace std;

// Helper function to compute total hours needed at given eating speed
int func(vector<int> arr, int hourly)
{
    int totalHrs = 0;
    for (int i = 0; i < arr.size(); i++)
    {
        totalHrs += ceil((double)arr[i] / (double)hourly);
    }
    return totalHrs;
}

// Binary search to find minimum eating speed to finish bananas within given time
int kokoBananasBinarySearch(vector<int> arr, int h)
{
    int n = arr.size();
    int MaximumElement = *max_element(arr.begin(), arr.end());
    int low = 1, high = MaximumElement;
    // since minimum ans is required, so we store highest int as max.
    // similarly assign int min to asnwer, when maximum is required.
    int ans = INT_MAX;

    while (low <= high)
    {
        int mid = low + (high - low) / 2;
        int totalHrs = func(arr, mid);

        if (totalHrs <= h)
        {
            ans = mid; // Possible answer found, try smaller speed
            high = mid - 1;
        }

        else
        {
            low = mid + 1; // Speed too slow, increase it
        }
    }
    return ans;
}

// total tc : O(n) * O(log base 2 (max_element))
int main()
{
    vector<int> piles = {3, 6, 7, 11};
    int h = 8;

    int result = kokoBananasBinarySearch(piles, h);
    cout << "Minimum bananas/hour: " << result << endl;

    return 0;
}