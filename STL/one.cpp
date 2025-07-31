#include <bits/stdc++.h>
using namespace std;
void explainPair()
{
    pair<int, int> p = {1, 3};
    // p.first gives 1st value of pair and p.second gives 2nd
    cout << p.first << " " << p.second;
    // output : 1 3
    cout << endl;

    // for storing more than 2 variables in a pair, use nesting pair
    pair<int, pair<int, int>> pp = {1, {3, 5}};
    cout << pp.first << " " << pp.second.second << " " << pp.second.first;
    cout << endl;
    // output : 1 5 3

    // pair array
    pair<int, int> arr[] = {{1, 3}, {2, 4}, {7, 69}};
    cout << arr[1].second;
    // output : 4 bcoz arr[1] = {2,4} and second value of arr is 4.
}

void explainVector()
{
    // size of vector can be increased even if it is defined statically, vector is dynamic in nature

    vector<int> v;     // This line creates an empty container
    v.push_back(1);    // This sends the value inside the vector
    v.emplace_back(2); // This also adds the value to the vector at the end but it's faster than push_backs and it adds the value dynamically to vector
    cout << v[0] << " " << v[1];
    cout << endl;

    vector<pair<int, int>> vec;
    vec.push_back({1, 5});
    vec.emplace_back(3, 8);
    cout << vec[1].first << " " << vec[1].second << endl;

    vector<int> v4(5, 100); // here a container with 5 instances of 100 is defined i.e. {100,100,100,100,100}

    vector<int> vect(5); // this will define a container with 5 instance of any value, probably garbage value

    // To copy a container into some other vector:
    vector<int> v2(v4); // here v2 will be a vector with same container as v

    vector<int>::iterator eee = v4.begin(); // v4.begin() points to memory where vector v4's values are stored and *eee gives the value stored at that memory location
    eee++;
    cout << "Values of vector v4: ";
    for (auto eee = v4.begin(); eee != v4.end(); ++eee)
    // here end means after the container and not the last value
    // so to go to last value, do eee-- after v4.end()
    // v4.back() will give the last value.
    {
        cout << *(eee) << " "; // Values of vector v4: 100 100 100 100 100
    }

    // Deletion
    // {10,20,30,40,50}
    v.erase(v.begin() + 1, v.begin() + 4); // here first value in included and second is not
    // result will be : {10, 50} bcoz 20,30,40 will be deleted and not 50 coz it is excluded.

    // Insertion
    vector<int> vec1(3, 65);              // {65,65,65}
    vec1.insert(vec1.begin(), 48);        // {48, 65, 65, 65}
    vec1.insert(vec1.begin() + 2, 4, 57); // {48,65,65,57,57,57,57,65}

    // {11, 123}
    cout << v.size(); // 2

    // {10,20}
    v.pop_back(); // {10}

    // v1 -> {10,20}
    // v2 -> {30,40}
    // v1.swap(v2); // v1 -> {30,40} , v2 -> {10,20}

    v.clear(); // erases the entire vector
}

void printList(list<int> &lst)
{
    for (int val : lst)
    {
        cout << val << " ";
    }
    cout << endl;
}

void explainList()
{
    list<int> ls;

    ls.push_back(2);    // {2}
    ls.emplace_back(4); // {2,4}

    printList(ls);

    ls.push_front(5);   // {5,2,4}
    ls.emplace_front(); // {0,5,2,4} bcoz no value was given as argument in emplace_front so default 0 was taken
    printList(ls);
}

void explainDeque()
{
    deque<int> dq;
    dq.push_back(1);    //{1}
    dq.emplace_back(2); //{1,2}
    dq.push_front(3);   // {3,1,2}
    dq.emplace_back(4); //{3,1,2,4}

    dq.pop_back();  // {3,1,2}
    dq.pop_front(); // {1,2}

    dq.back();
    dq.front();

    // remaining funcs. same as vector
    // begin, end, rbegin, rend, clear, insert, size, swap
}

void explainStack()
{
    // follows last in first out principle, so latest value gets added at front

    stack<int> st;
    st.push(1);    // {1}
    st.push(2);    // {2,1}
    st.push(4);    // {4,2,1}
    st.emplace(7); // {7,4,2,1}

    cout << st.top(); // prints 7

    st.pop(); // st now looks like {4,2,1} bcoz lifo, so latest value gets removed first

    cout << st.size();  // 3
    cout << st.empty(); // false

    stack<int> st1, st2;
    st1.swap(st2);

    // all operations like push(), pop(), top() in stack have time complexity O(1) i.e. all happens in constant time
}

void explainQueue()
{
    // FIFO : follows first in first out principle
    // so latest entered value gets removed at last while least recent value gets removed first

    queue<int> q;
    q.push(1);    // {1}
    q.push(2);    // {1,2}
    q.emplace(5); // {1,2,5}

    q.back() += 5;

    cout << q.back(); // prints 10 since q.back() was 5 and 5 got added to it

    cout << q.front(); // prints 1

    q.pop(); // {2,10} removed least recently entered value

    // size, swap, empty same as stack
}

void explainPQ()
{
    // Maximum heap
    priority_queue<int> pq;
    pq.push(5);    // {5}
    pq.push(2);    // {5,2}
    pq.push(8);    // {8,5,2}
    pq.emplace(9); // {9,8,5,2}

    cout << pq.top(); // prints 9
    pq.pop();         // {8,5,2}

    // size, swap, empty same as stack

    // Minimum Heap
    priority_queue<int, vector<int>, greater<int>> pq;
    pq.push(5);     //{5}
    pq.push(2);     // {2,5}
    pq.push(8);     // {2,5,8}
    pq.emplace(10); // {2,5,8,10}

    cout << pq.top(); // prints 2

    // Time complexities :
    // push(), pop() : O(log n)
    // top() : O(1)
}

void explainSet()
{
    // Stores everything in sorted order and only unique values
    set<int> st;
    st.insert(1);  // {1}
    st.emplace(2); // {1,2}
    st.insert(2);  // {1,2} another 2 did not go in bcoz one 2 was already there
    st.insert(4);  // {1,2,4}
    st.insert(3);  // {1,2,3,4}

    // {1,2,3,4}
    auto it = st.find(3); // point to the iteration where 3 is

    auto it = st.find(9); // point to st.end() bcoz value not there in set

    //{1,2,4,5}
    st.erase(5); // erases 5, takes logarithmic time. Finds and erases 5 → O(log n) coz it has to search using binary search

    int cnt = st.count(6); // if 6 present then will return 1 else 0

    auto it = st.find(4); // O(log n) .find() function uses binary search tree traversal to locate the element.
    st.erase(it);         // takes constant time.  // Directly erases 4 → O(1) coz position is already known from above line so no need to search

    // {1,2,3,4,5}
    auto it1 = st.find(2);
    auto it2 = st.find(4);
    st.erase(it1, it2); // after erase, {1,4,5} are left bcoz [first, last).

    // lower_bound() and upper_bound() function work in same way as in vector

    auto it = st.lower_bound(2); // val >= . the smallest value greater than equal to (num). here -> 2
    auto it = st.upper_bound(3); // val > . the smallest value greater than (num). here -> 4.

    // In set, everything happens in O(log N) time
}

void explainMultiSet()
{
    // Same at set but stores duplicate values too unlike set

    multiset<int> ms;
    ms.insert(1); // {1}
    ms.insert(1); // {1,1}
    ms.insert(1); // {1,1,1}

    ms.erase(1); // erases all values of 1, so this is called erase element

    int cnt = ms.count(1); // gives count of all occurences of 1

    ms.erase(ms.find(1)); // erases only single 1 not all 1's. so this is erase address of a particular value

    // rest everything same as set
}

void explainUOSet()
{
    unordered_set<int> ust;

    // lower_bound and upper_bound function do not work, rest all are
    // same as set, it doesn't stores value in a sorted manner but stores unique values only
    // it has a better complexity than set in most cases, except when some collisions occur

    // generally all functions have a time complexity of O(1)
    //  but in the rarest case, it can go to O(N)
}

void explainMap()
{
    // a data structure which stores value in key, value format, they both can have any data type
    // key will be unique, value may or may not be
    // stores unique keys in sorted order

    map<int, int> mpp1;
    map<int, pair<int, int>> mpp2;
    map<pair<int, int>, int> mpp3;

    mpp1[1] = 2; // here 1 is the key and 2 is the value
    // mpp2.emplace(3, {1, 4}); Your call is: mpp2.emplace(3, {1,4}); The compiler sees (int, {...}) where {1,4} is an initializer list.
    // It cannot deduce how to convert {1,4} to the pair<int,int> parameter needed for the mapped type.
    mpp2.emplace(3, make_pair(1, 4));
    for (auto it : mpp2)
    {
        cout << it.first << " " << it.second.second << endl; // 3 4
    }

    mpp1.insert({2, 8});
    mpp3[{4, 6}] = 11;

    /*
    Suppose all values were a single map, so it would be stored in this way
        {
            {1,2}
            {2,8}
            {3,1}
            {{4,6}, 11}
        }
    */

    for (auto it : mpp1)
    {
        cout << it.first << " " << it.second << endl;
    }

    cout << mpp1[1];
    cout << mpp1[5]; // if anything doesn't exist it prints null

    auto it = mpp1.find(1);
    // cout << *(it).second;

    auto it = mpp1.lower_bound(2);
    auto it = mpp1.upper_bound(3);

    // erase swap size empty same as others
}

void explainMultiMap()
{
    // stores duplicate keys but in sorted manner
    // all functions as map
    // only map[key] can't be used
}

void explainUnorderedMap()
{
    // stores duplicate keys but not in sorted order
    // all functions time complexity : O(1)
}

bool comp(pair<int, int> p1, pair<int, int> p2)
{
    if (p1.second < p2.second)
        return true;
    if (p1.second > p2.second)
        return false;

    // if above two don't match, then both are same
    if (p1.first > p2.first)
        return true;
    return false;
}

void explainExtra()
{
    // sort(a, a+n); [a, a+n);
    // sort(v.begin(), v.end()) same as above

    // sort(a+2, a+4) will sort a+2 and a+3 but not a+4

    // sort in descending order
    // sort(a, a+4, greater<int>)

    cout << "---------------------";

    pair<int, int> a[] = {{1, 2}, {2, 1}, {4, 1}};
    // sort it according to second element
    // if second element is same,
    // then sort according to first element but in descending order

    // sort(a, a+n, comp);
    // The above sort will give result as : {{4,1}, {2,1}, {1,2}}

    int num = 7;
    int cnt = __builtin_popcount(num);
    // this will return 3 bcoz 7 : 1 1 1 i.e. 1*2^0 +1*2^1 + 1*2^2

    // if num was 6 then cnt would have returned 2 bcoz 6 : 1 1 0

    string s = "123";

    do
    {
        cout << s << endl;
    } while (next_permutation(s.begin(), s.end()));
    // if u need all permutation, then start from the first sorted value, give the lowest value of arrival

    // int maxi = *max_element(a, a + n); gives value of max element from an array
}

int main()
{
    explainList();
    return 0;
}