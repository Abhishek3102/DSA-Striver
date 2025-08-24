// here an array will be given and a threshold too which will be any integer. now we have to find
// a divisor which is less than equal to threshold when divided and added(ceil of remainder) by all elements of array.
// eg : [1 2 5 9] and threshold = 6. so take divisor as 4.
// so 1 % 4 = ceil(0.25) = 1. 2 % 4 = ceil(0.5) = 1. 5 % 4 = ceil(1.25) = 2. 9 % 4 = ceil(2.25) = 3.
// so 1 + 1 + 2 + 3 = 7 which is not less than or equal to 6(threshold) so we have to take other divisor.
// ans will always lie b/w 1 and max element of array

#include <bits/stdc++.h>
using namespace std;

int sumByD(vector<int> arr, int div)
{
    int sum = 0;
    int n = arr.size();
    for (int i = 0; i < n; i++)
    {
        sum = sum + ceil((double)(arr[i]) / (double)(div));
    }
    return sum;
}

int func(vector<int> arr, int threshold)
{
    int n = arr.size();

    int maxi = *max_element(arr.begin(), arr.end());
    int ans = -1;
    int low = 1, high = maxi;
    while (low <= high)
    {
        int mid = low + (high - low) / 2;
        if (sumByD(arr, mid) <= threshold)
        {
            ans = mid;      // ans found
            high = mid - 1; // look for smaller ans
        }

        else
        {
            low = mid + 1; // look for bigger ans
        }
    }
    return ans;
}

int main()
{
    vector<int> arr = {1, 2, 5, 9};
    int threshold = 6;

    int result = func(arr, threshold);

    if (result != -1)
        cout << "Minimum divisor: " << result << endl;
    else
        cout << "No valid divisor found within the threshold." << endl;

    return 0;
}
