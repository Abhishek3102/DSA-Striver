# MOCK TEST — Zeus Learning Pen-and-Paper (20 marks / 3 hours)

Attempt on PAPER first (no compiler). ~18 min per question.

## Section A — Easy, 2 marks each (spot + fix the bug)
**Q1.** `int sum; for(i=0;i<=n;i++) sum+=arr[i];` List 2 errors, rewrite. (see `01_`)
**Q2.** `void swap(int a,int b){...}` called as `swap(x,y)`; then `if(x=y)`. Why doesn't it swap, and what does the `if` do? Fix both. (see `02_`)
**Q3.** Bubble sort inner loop `for(j=0;j<n-i;j++) if(a[j]>a[j+1]) swap(...)`. What crashes? Fix. (see `09_`)
**Q4.** Binary search `while(low<high)` with `mid=(low+high)/2` on unsorted array. List 3 issues. (see `09_`)

## Section B — Medium/Hard, 3-4 marks each
**Q5.** Write recursive pseudocode for max depth of binary tree + dry-run on `[1,2,3,4]` (4 left child). Answer: 3. (see `03_`)
**Q6.** Given A(m×n), B(n×p): write multiplication pseudocode + state the compatibility condition + compute `[[1,2],[3,4]]*[[5,6],[7,8]]`. Answer: `[[19,22],[43,50]]`. (see `05_`)
**Q7.** Base pointer `Animal* p = new Dog(); p->speak(); p->move();` where `speak` is virtual and `move` is not. Predict output. Explain. (see `07_`)
**Q8.** Order of constructor/destructor for `Derived : public Base` object; what is object slicing? (see `08_`)
**Q9.** Transpose + rotate-90-CW logic for matrix; rotate `[[1,2,3],[4,5,6],[7,8,9]]`. Answer first row `7 4 1`. (see `06_`)
**Q10.** Reverse a singly linked list (iterative) + check string palindrome ignoring case. (see `10_`)

## Answers (fold the page before peeking)
A1: init `sum=0`, `i<n`. A2: pass-by-reference + `==`. A3: `j<n-i-1`. A4: sort first, `<=`, safe mid.
B5: `1+max(L,R)`. B6: need colsA==rowsB, triple loop. B7: `Dog barks` / `Animal moves`. B8: base→derived ctor, reverse dtor; slicing drops derived part. B9: transpose+reverse rows. B10: 3-pointer reversal; two-pointer string check.
