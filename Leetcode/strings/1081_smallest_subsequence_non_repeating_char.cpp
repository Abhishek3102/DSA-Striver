/*

Given a string s, return the lexicographically smallest subsequence of s that contains all the distinct characters of s exactly once.

Example 1:

Input: s = "bcabc"
Output: "abc"
Example 2:

Input: s = "cbacdcbc"
Output: "acdb"

*/

#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    string smallestSubsequence(string s)
    {
        vector<int> lastIndex(26);
        vector<bool> visited(26, false);

        // Store last occurrence of each character
        for (int i = 0; i < s.size(); i++)
        {
            lastIndex[s[i] - 'a'] = i;
        }

        string st;

        for (int i = 0; i < s.size(); i++)
        {
            char c = s[i];

            // Skip if already included
            if (visited[c - 'a'])
                continue;

            // Remove larger characters if they appear later
            while (!st.empty() &&
                   st.back() > c &&
                   lastIndex[st.back() - 'a'] > i)
            {
                visited[st.back() - 'a'] = false;
                st.pop_back();
            }

            st.push_back(c);
            visited[c - 'a'] = true;
        }

        return st;
    }
};

/*

This is one of those problems that looks impossible at first, but once you understand the pattern (**last occurrence + visited + monotonic stack**), you'll be able to solve many similar string problems.

I'll start from the basics.

---

# Problem Statement

Given a string

```text
s = "cbacdcbc"
```

We have to return the **lexicographically smallest subsequence** that contains **every distinct character exactly once**.

Notice

```
String : c b a c d c b c
```

Distinct characters are

```
a
b
c
d
```

Each should appear **only once** in the answer.

Possible answers:

```
cadb
cbad
acdb
...
```

Smallest lexicographically is

```
acdb
```

---

# First Concept: Lexicographical Order

Think of dictionary order.

```
a < b < c < d
```

Compare strings character by character.

Example

```
abc
abd
```

Compare

```
a = a
b = b
c < d
```

Therefore

```
abc < abd
```

Another

```
bac
cab
```

First character

```
b < c
```

So

```
bac < cab
```

Whenever possible we want **smaller letters earlier**.

---

# Second Concept: Subsequence

Subsequence means

You can delete characters.

You cannot change order.

Example

```
abcde
```

Possible subsequences

```
ace
abd
bc
```

Impossible

```
eca
```

because order changed.

---

# Third Concept: Why can't we simply sort?

Input

```
cbacdcbc
```

Sorting gives

```
abbcccd
```

Remove duplicates

```
abcd
```

But

```
abcd
```

is NOT a subsequence of original string.

So sorting is illegal.

---

# Fourth Concept: We need to decide while traversing

Suppose

```
cbacdcbc
```

We're reading left to right.

When we see

```
c
```

Should we keep it?

Maybe.

Maybe not.

Later we might find

```
a
```

which is smaller.

Can we remove current c?

Only if another c exists later.

Otherwise removing it means we lose character c forever.

So we need to know

> **Will this character appear again?**

This is exactly why we store the **last occurrence**.

---

# Understanding lastIndex

Code

```cpp
vector<int> lastIndex(26);
```

creates

```
index

0
1
2
...
25
```

Each index represents one alphabet.

```
0 -> a
1 -> b
2 -> c
3 -> d

...

25 -> z
```

Initially

```
lastIndex

a = 0
b = 0
c = 0
...
```

We'll overwrite them.

---

Suppose

```
s = "bcabc"
```

Let's traverse.

### i = 0

```
b
```

ASCII trick

```
'b' - 'a'

98 - 97

= 1
```

So

```cpp
lastIndex['b'-'a']=0;
```

means

```
last occurrence of b is currently 0
```

Table

```
a -> 0
b -> 0
c -> 0
```

---

### i = 1

```
c
```

```
'c'-'a'

99-97

=2
```

Store

```
lastIndex[2]=1
```

Now

```
c last seen at 1
```

---

### i = 2

```
a
```

```
'a'-'a'

97-97

=0
```

Store

```
lastIndex[0]=2
```

---

### i =3

```
b
```

Now update

```
lastIndex[1]=3
```

Old value

```
0
```

gets replaced.

Why?

Because this is the **newest occurrence**.

---

### i =4

```
c
```

Update

```
lastIndex[2]=4
```

Final table

```
a ->2
b ->3
c ->4
```

Meaning

```
Last a occurs at index 2

Last b occurs at index 3

Last c occurs at index 4
```

That's exactly what we wanted.

---

# Why subtract 'a'?

This is one of the most common C++ tricks.

Characters are integers internally.

ASCII values

```
'a' =97

'b' =98

'c' =99
```

Subtracting

```
'a'-'a'

97-97

0
```

```
'b'-'a'

98-97

1
```

```
'z'-'a'

122-97

25
```

So

```
'a'

↓

0
```

```
'b'

↓

1
```

```
'c'

↓

2
```

Very convenient for arrays of size 26.

Instead of writing

```
lastIndex['a']=...
```

(which would require an array of size 128 or 256), we map letters to indices `0`–`25`.

---

# Understanding visited

Now another array

```cpp
vector<bool> visited(26,false);
```

Initially

```
a false
b false
c false
d false
...
```

Meaning

```
No character has been placed in answer yet.
```

Suppose answer becomes

```
ac
```

Then

```
visited[a]=true

visited[c]=true
```

Now if another

```
c
```

comes later

We don't want

```
acc
```

We only need one c.

So

```cpp
if(visited[c-'a'])
    continue;
```

means

```
Already taken.

Ignore it.
```

---

# Why reset visited to false while popping?

Suppose answer currently

```
cb
```

Now we encounter

```
a
```

We decide to remove

```
b
```

and

```
c
```

Answer becomes

```
(empty)
```

Since

```
b
```

is removed,

it's no longer in answer.

Therefore

```
visited[b]=false
```

Otherwise later if another

```
b
```

appears,

the algorithm would wrongly think

```
b already exists
```

even though we removed it.

---

# Why use a stack?

Suppose answer

```
c
```

Next character

```
b
```

We want

```
b
```

before

```
c
```

if possible.

The last inserted character is

```
c
```

So we remove it.

Stacks are perfect because we always remove from the end.

Instead of an actual `stack<char>`, we use a `string`:

```cpp
string st;
```

Appending

```
push_back()
```

Removing

```
pop_back()
```

Last character

```
back()
```

Exactly like a stack.

---

# The Most Important While Loop

```cpp
while(!st.empty() &&
      st.back()>c &&
      lastIndex[st.back()-'a']>i)
```

Let's understand every condition.

---

## Condition 1

```cpp
!st.empty()
```

Need something to pop.

---

## Condition 2

```cpp
st.back()>c
```

Example

Current answer

```
c
```

Current letter

```
a
```

Since

```
c>a
```

Replacing gives smaller answer.

Good.

---

Example

```
answer

a

current

c
```

```
a<c
```

Don't remove.

---

## Condition 3

```cpp
lastIndex[st.back()-'a']>i
```

This is the safety condition.

Suppose current answer

```
c
```

Current character

```
a
```

Can we remove c?

Only if another c comes later.

If

```
last occurrence of c

>

current index
```

then yes.

Otherwise

No.

---

# Dry Run

```
bcabc
```

Last occurrence

```
a=2

b=3

c=4
```

Answer

```
""
```

---

## i=0

```
b
```

visited false

Stack empty

Push

```
b
```

---

## i=1

```
c
```

Top

```
b
```

Is

```
b>c ?

No
```

Push

```
bc
```

---

## i=2

```
a
```

Top

```
c
```

```
c>a

Yes
```

Can remove?

```
last c =4

4>2

Yes
```

Pop c

Answer

```
b
```

Now top

```
b
```

```
b>a

Yes
```

Can remove?

```
last b=3

3>2

Yes
```

Pop b

Now empty

Push a

Answer

```
a
```

---

## i=3

```
b
```

Top

```
a

a>b?

No
```

Push

```
ab
```

---

## i=4

```
c
```

Top

```
b

b>c?

No
```

Push

```
abc
```

Done.

Answer

```
abc
```

---

# Another Dry Run (Harder)

```
cbacdcbc
```

Last occurrence

```
a=2

b=6

c=7

d=4
```

Process:

| Character | Stack           |
| --------- | --------------- |
| c         | c               |
| b         | pop c → b       |
| a         | pop b → a       |
| c         | ac              |
| d         | acd             |
| c         | already visited |
| b         | acdb            |
| c         | already visited |

Final

```
acdb
```

Notice we **did not pop `d`** when `b` arrived because `d`'s last occurrence was already behind us (`lastIndex['d'] = 4` and current index is `6`). If we removed `d`, we'd never get it back.

---

# Overall Algorithm

1. Traverse the string once to record the **last index** where each character appears.
2. Traverse the string again.
3. If the current character is already in the answer (`visited`), skip it.
4. Otherwise, while:

   * the answer is not empty,
   * the last character in the answer is larger than the current character,
   * and that last character appears again later,

   remove it from the answer and mark it as not visited.
5. Add the current character to the answer and mark it as visited.
6. The resulting string is the lexicographically smallest subsequence containing each distinct character exactly once.

---

## This Pattern Appears in Many Problems

Whenever you see:

* "smallest/largest lexicographical sequence,"
* "remove duplicate letters,"
* "keep each character once,"
* "remove `k` digits/characters while keeping order,"

think of this combination:

* **Last occurrence array** → to know if it's safe to remove a character.
* **Visited array** → to avoid duplicates.
* **Monotonic stack** → to build the optimal answer greedily.

Once this pattern clicks, many seemingly different string problems become much easier to recognize and solve.


*/