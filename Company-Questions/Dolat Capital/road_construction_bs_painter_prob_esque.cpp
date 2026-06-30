/*

Question 3:

Road ConstructionProblem Statement:You need to construct a road of length $N$ (from unit $1$ to $N$).
There are $M$ workers available.Each worker is assigned to work only within a specific segment defined by a start point $S$ and an end point $E$,
inclusive: $[S, E]$.Every unit length of the road must be constructed by at least 1 worker.
It takes exactly 1 hour for one worker to complete the construction of 1 unit segment of the road.
All workers can work simultaneously.The flow of each worker's construction must be continuous (no skipping units).
While the given permissible segments $[S, E]$ of two or more workers can overlap, the actual assigned segments that the workers
construct must not overlap with each other (i.e., you must partition the road among the available workers within their valid ranges).
Find the minimum time required to construct the entire road. If any part of the road is left unconstructed
(it is impossible to cover the entire road from $1$ to $N$), print -1.Function Signature:C++int minTime(int N, int M, int S[], int E[]);
Constraints:$1 \le N \le 1000$$1 \le M \le 100$$1 \le S_i, E_i \le 1000$
Example:Input:$N = 10, M = 3$$S = [1, 6, 1]$$E = [5, 10, 10]$Output: 3Explanation:Worker 1 can work in $[1, 5]$.Worker 2 can work in $[6, 10]$.
Worker 3 can work in $[1, 10]$.To minimize the maximum time taken by any worker:Assign Worker 1 to build segment $[1, 4]$.
(Time = 3 hours)Assign Worker 3 to build segment $[4, 7]$. (Time = 3 hours) (Note: 4 to 7 is 3 units of length: 4-5, 5-6, 6-7).
Assign Worker 2 to build segment $[7, 10]$. (Time = 3 hours)All workers finish in exactly 3 hours, so the minimum time required is 3.

*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Worker
{
    int s, e;
};

// Function to check if it's possible to construct the road in max time 'T'
bool isValid(int T, int N, int M, const vector<Worker> &workers)
{
    int curr = 1;
    vector<bool> used(M, false);

    for (int step = 0; step < M; ++step)
    {
        int best_worker = -1;
        int min_e = 1e9; // Infinity

        // Greedily find the available worker with the smallest 'E' (Earliest Deadline First)
        for (int i = 0; i < M; ++i)
        {
            if (!used[i] && workers[i].s <= curr && workers[i].e > curr)
            {
                if (workers[i].e < min_e)
                {
                    min_e = workers[i].e;
                    best_worker = i;
                }
            }
        }

        // If no worker can start at or before 'curr' to extend the road
        if (best_worker == -1)
        {
            break;
        }

        used[best_worker] = true;
        // The worker works for T hours, but cannot exceed their allowed boundary E
        curr = min(workers[best_worker].e, curr + T);

        if (curr >= N)
        {
            return true;
        }
    }
    return curr >= N;
}

int minTime(int N, int M, vector<int> &S, vector<int> &E)
{
    vector<Worker> workers(M);
    for (int i = 0; i < M; ++i)
    {
        workers[i] = {S[i], E[i]};
    }

    int low = 1, high = N;
    int ans = -1;

    // Binary Search on the minimum time
    while (low <= high)
    {
        int mid = low + (high - low) / 2;

        if (isValid(mid, N, M, workers))
        {
            ans = mid;      // 'mid' is possible, record it
            high = mid - 1; // Try to find an even smaller time
        }
        else
        {
            low = mid + 1; // 'mid' is too small, we need more time
        }
    }

    return ans;
}

int main()
{
    // Example from the image
    int N = 10, M = 3;
    vector<int> S = {1, 6, 1};
    vector<int> E = {5, 10, 10};

    cout << minTime(N, M, S, E) << endl; // Output: 3

    return 0;
}