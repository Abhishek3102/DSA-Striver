// Q10 [MEDIUM - related] Reverse linked list + string palindrome/frequency
// WHY: medium accuracy+speed drills (GFG/LeetCode style) that fit 3-4 marks.
// A) Reverse singly LL iteratively: prev=NULL; cur=head; nxt=cur->next...
// B) Palindrome string ignoring case/non-alnum (two pointers).
// C) Frequency of chars (Direct addressing: freq[256]).
#include <bits/stdc++.h>
using namespace std;

struct ListNode { int val; ListNode* next; ListNode(int v): val(v), next(nullptr) {} };
ListNode* reverseList(ListNode* head) {
    ListNode* prev = nullptr;
    while (head) { ListNode* nxt = head->next; head->next = prev; prev = head; head = nxt; }
    return prev;
}
bool isPalindromeStr(const string& s) {
    int l = 0, r = (int)s.size() - 1;
    while (l < r) {
        while (l < r && !isalnum((unsigned char)s[l])) l++;
        while (l < r && !isalnum((unsigned char)s[r])) r--;
        if (tolower((unsigned char)s[l]) != tolower((unsigned char)s[r])) return false;
        l++; r--;
    }
    return true;
}
array<int,256> freqCount(const string& s) { array<int,256> f{}; f.fill(0); for (unsigned char c : s) f[c]++; return f; }

int main() {
    ListNode* h = new ListNode(1); h->next = new ListNode(2); h->next->next = new ListNode(3);
    h = reverseList(h);
    cout << "Reversed LL: "; for (auto* p = h; p; p = p->next) cout << p->val << ' ';
    cout << "(expected 3 2 1)\n";
    cout << "Palindrome 'A man, a plan, a canal: Panama'? " << (isPalindromeStr("A man, a plan, a canal: Panama") ? "yes" : "no") << " (yes)\n";
    auto f = freqCount("hello");
    cout << "freq l=" << f['l'] << " (2)  freq o=" << f['o'] << " (1)\n";
    return 0;
}
