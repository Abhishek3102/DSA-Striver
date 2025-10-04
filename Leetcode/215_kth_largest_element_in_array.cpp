bool comp(int a, int b)
{
    return a > b;
}
class Solution
{
public:
    int findKthLargest(vector<int> &nums, int k)
    {
        int n = nums.size();

        sort(nums.begin(), nums.end(), comp);
        return nums[k - 1];
    }
};