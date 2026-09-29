vector<int> productExceptSelf(vector<int> &nums)
{
    //     int n = nums.size();
    //     int product = 1;
    //     for(int i = 0; i<n; i++){
    //         if(nums[i]) continue;
    //         product = product * nums[i+1];
    //     }
    //     return {product};
    // }
    int n = nums.size();

    // left[i] = product of all elements to the LEFT of index i
    // right[i] = product of all elements to the RIGHT of index i
    vector<int> left(n, 1), right(n, 1), result(n);

    // Build the left product array
    // For index 0, there is nothing on the left, so left[0] = 1
    for (int i = 1; i < n; i++)
    {
        // Everything before i = everything before i-1
        // multiplied by nums[i-1]
        left[i] = left[i - 1] * nums[i - 1];
    }

    // Build the right product array
    // For the last index, there is nothing on the right,
    // so right[n-1] = 1
    for (int i = n - 2; i >= 0; i--)
    {
        // Everything after i = everything after i+1
        // multiplied by nums[i+1]
        right[i] = right[i + 1] * nums[i + 1];
    }

    // For each index:
    // result[i] = product of elements on the left
    //           * product of elements on the right
    //
    // This gives the product of every element except nums[i].
    for (int i = 0; i < n; i++)
    {
        result[i] = left[i] * right[i];
    }

    return result;
}