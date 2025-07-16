// a number should appear more than n/3 times in an array of n elements
// so in this question, we have to find the number of numbers that appear more than n/3 times. that is the count of majority element

#include <bits/stdc++.h>
using namespace std;

list<int> find_maj_element(int nums[], int n)
{
    list<int> ls;
    for (int i = 0; i < n; i++)
    {
        // Problem with ls[0] != nums[i] check: Using ls[0], which is incorrect because std::list is not directly indexable like a vector or array.
        // if (ls.size() == 0 || ls[0] != nums[i])
        {
            int count = 0;
            for (int j = 0; j < n; j++)
            {
                if (nums[j] == nums[i])
                    count++;
                if (count > n / 3)
                    ls.push_back(nums[i]);
            }
        }
        if (ls.size() == 2)
            break;
    }
    return ls;
}

vector<int> find_majority_element(int nums[], int n)
{
    // tc : O(N ^ 2) and sc : O(1) coz ls will only store 2 elements
    vector<int> ls;

    // O(N)
    for (int i = 0; i < n; i++)
    {
        // Check if the number is already in the vector
        if (ls.size() == 0 || ls[0] != nums[i])
        {
            int count = 0;

            // Count the occurrences of nums[i]
            // O(N)
            for (int j = 0; j < n; j++)
            {
                if (nums[j] == nums[i])
                {
                    count++;
                }
            }

            if (count > n / 3)
            {
                ls.push_back(nums[i]);
            }
        }

        if (ls.size() == 2)
            break;
    }

    return ls;
}

// using hashmap
vector<int> find_majority_element_better(int arr[], int n)
{
    vector<int> ls;
    map<int, int> mpp;
    int mm = (n / 3) + 1;
    for (int i = 0; i < n; i++)
    {
        mpp[arr[i]]++;
        if (mpp[arr[i]] == mm)
        {
            ls.push_back(arr[i]);
        }
        if (ls.size() == 2)
            break;
    }

    return ls;
}

// his code for better approach using hashmap and sort the order of elements in answer
vector<int> majorityElement(vector<int> v)
{
    vector<int> ls;
    map<int, int> mpp;
    int n = v.size();
    int mini = (int)(n / 3) + 1;
    for (int i = 0; i < n; i++)
    {
        mpp[v[i]]++;
        if (mpp[v[i]] == mini)
        {
            ls.push_back(v[i]);
        }
        if (ls.size() == 2)
            break;
    }
    sort(ls.begin(), ls.end());
    return ls;
}

vector<int> majorityElementOptimal(vector<int> v)
{
    int count1 = 0, count2 = 0;
    int element1 = INT_MIN;
    int element2 = INT_MIN;
    for (int i = 0; i < v.size(); i++)
    {
        if (count1 == 0 && element2 != v[i])
        {
            count1 = 1;
            element1 = v[i];
        }
        else if (count2 == 0 && element1 != v[i])
        {
            count2 = 1;
            element2 = v[i];
        }

        else if (v[i] == element1)
            count1++;
        else if (v[i] == element2)
            count2++;

        else
        {
            count1--;
            count2--;
        }
    }
    vector<int> ls;
    count1 = 0, count2 = 0;
    for (int i = 0; i < v.size(); i++)
    {
        if (element1 == v[i])
            count1++;
        if (element2 == v[i])
            count2++;
    }

    int mini = (int)(v.size() / 3) + 1;
    if (count1 >= mini)
        ls.push_back(element1);
    if (count2 >= mini)
        ls.push_back(element2);
    sort(ls.begin(), ls.end());
    return ls;
}

int main()
{
    /*
    brute force approach

    int nums[] = {3, 1, 3, 3, 2, 2, 1, 1};
    int n = sizeof(nums) / sizeof(nums[0]);

    vector<int> majority_elements = find_majority_element(nums, n);

    for (int ele : majority_elements)
    {
        cout << ele << " ";
    }

    return 0;

    */

    // better approach using hashmap

    int arr1[] = {3, 1, 3, 3, 2, 2, 1, 1};
    int n1 = sizeof(arr1) / sizeof(arr1[0]);

    /*
    int n2;
    cout << "Enter number of elements: ";
    cin >> n2;

    int arr2[n2];
    cout << "Enter " << n2 << " elements: ";
    for (int i = 0; i < n2; i++) {
        cin >> arr2[i];
    }
    */

    vector<int> majority_elements = find_majority_element_better(arr1, n1);

    // vector<int> majority_elements = find_majority_element_better(arr2, n2);

    cout << "Majority elements (appears more than n/3 times): ";
    for (int ele : majority_elements)
    {
        cout << ele << " ";
    }
    cout << endl;

    return 0;
}