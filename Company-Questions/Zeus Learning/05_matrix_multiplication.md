// Q5 [MEDIUM - 3/4 marks] Logic for matrix multiplication
// ROUND CONTEXT: asked directly. Paper expects: dimension rule + triple loop.
//
// RULE: A(m x n) * B(n x p) = C(m x p). colsA MUST equal rowsB.
// FORMULA: C[i][j] = sum over k of A[i][k] * B[k][j]
// LOOPS: for i in 0..m-1: for j in 0..p-1: { C[i][j]=0; for k in 0..n-1: C[i][j]+=A[i][k]*B[k][j]; }
// COMMON PAPER ERRORS: forgetting C[i][j]=0, wrong loop bounds, multiplying
// without checking colsA==rowsB, using int for huge values.
//
// EXAMPLE:
//   A = [1 2 | 3 4] (2x2), B = [5 6 | 7 8] (2x2)
//   C[0][0]=1*5+2*7=19, C[0][1]=1*6+2*8=22, C[1][0]=3*5+4*7=43, C[1][1]=3*6+4*8=50
#include <bits/stdc++.h>
using namespace std;

vector<vector<long long>> multiply(const vector<vector<long long>>& A,
                                   const vector<vector<long long>>& B) {
    int m = A.size(), n = A[0].size(), n2 = B.size(), p = B[0].size();
    if (n != n2) throw invalid_argument("colsA must equal rowsB");
    vector<vector<long long>> C(m, vector<long long>(p, 0)); // init 0!
    for (int i = 0; i < m; i++)
        for (int j = 0; j < p; j++)
            for (int k = 0; k < n; k++)
                C[i][j] += A[i][k] * B[k][j];
    return C;
}

int main() {
    vector<vector<long long>> A = {{1,2},{3,4}}, B = {{5,6},{7,8}};
    auto C = multiply(A, B);
    cout << "C =\n";
    for (auto &row : C) { for (auto x : row) cout << x << ' '; cout << '\n'; }
    cout << "(expected 19 22 / 43 50)\n";
    // Non-square: A(2x3)*B(3x2) = C(2x2)
    vector<vector<long long>> A2 = {{1,2,3},{4,5,6}}, B2 = {{7,8},{9,10},{11,12}};
    auto C2 = multiply(A2, B2);
    cout << "C2[0][0]=" << C2[0][0] << " (expected 58)  C2[1][1]=" << C2[1][1] << " (expected 154)\n";
    return 0;
}
