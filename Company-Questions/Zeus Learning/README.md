# Zeus Learning — Pen-and-Paper DSA Round (C++ Practice Pack)

Based on real experience: 3 hours, 20 marks, 10 questions.
- Easy (2 marks): find error in pseudocode
- Medium/Hard (3-4 marks): tree depth, matrix multiplication, inheritance/OOP output

Folder: `Company-Questions/Zeus Learning/`
All files are self-contained C++17, compile with `g++ file.cpp -o file && ./file`.

| # | File | Round topic it covers | Marks |
|---|------|-----------------------|-------|
| 01 | `01_find_error_array_sum.cpp` | Easy: off-by-one / `<=` vs `<`, uninitialised sum | 2 |
| 02 | `02_find_error_swap_scope.cpp` | Easy: pass-by-value vs reference, `=` vs `==` | 2 |
| 03 | `03_tree_max_depth.cpp` | Medium: depth/height of tree (recursive + BFS) | 3-4 |
| 04 | `04_tree_min_depth_diameter_balanced.cpp` | Related-medium: min depth, diameter, balanced check | 3-4 |
| 05 | `05_matrix_multiplication.cpp` | Medium: logic for A(m×n) * B(n×p) + dimension check | 3-4 |
| 06 | `06_matrix_transpose_rotate_spiral.cpp` | Related-medium: transpose, rotate 90, spiral print | 3-4 |
| 07 | `07_oops_inheritance_virtual.cpp` | Medium: inheritance + virtual function output prediction | 3-4 |
| 08 | `08_oops_constructor_destructor_order.cpp` | Related-medium: constructor/destructor order, slicing, diamond | 3-4 |
| 09 | `09_sorting_searching_pseudocode.cpp` | Related: bubble sort + binary search error-spotting (pen-paper favourite) | 2-3 |
| 10 | `10_linkedlist_string_medium.cpp` | Related-medium: reverse LL, palindrome, frequency count | 3-4 |
| — | `00_MOCK_TEST.md` | Printable 10-Q / 20-mark mock paper (3 hr) with answers | — |

## How to use for pen-paper practice
1. Read only the `BUGGY / QUESTION` comment block, try on paper (no compiler).
2. Write expected output / corrected code by hand — that is what Zeus asks.
3. Then compile and check with the `main()` demo.
4. Time yourself: 18 min/question = 3 hours for 10.

## Quick revision formulas (memorise for paper)
- Tree depth: `depth(NULL)=0; depth(node)=1+max(depth(L),depth(R))`
- Matrix mult: `C[i][j] = sum_k A[i][k]*B[k][j]`, needs `colsA == rowsB`, loops i(m) → j(p) → k(n), init C to 0.
- Virtual: base pointer + `virtual` = derived version runs; without `virtual` = base version runs.
- Binary search needs sorted array + `mid = low + (high-low)/2`, loop `while(low<=high)`.
