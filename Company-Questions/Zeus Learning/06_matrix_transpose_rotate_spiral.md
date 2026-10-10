// Q6 [MEDIUM - related] Transpose, rotate-90, spiral (matrix trio)
// WHY: same family as matrix multiplication; pen-paper loves hand-tracing.
// Transpose: B[j][i]=A[i][j].  Square in-place: swap(i,j) for j>i.
// Rotate 90 CW: transpose + reverse each row. (CCW: transpose + reverse each col)
// Spiral: 4 boundaries top/bottom/left/right shrinking.
#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> transposeMat(const vector<vector<int>>& A) {
    int m = A.size(), n = A[0].size();
    vector<vector<int>> B(n, vector<int>(m));
    for (int i = 0; i < m; i++) for (int j = 0; j < n; j++) B[j][i] = A[i][j];
    return B;
}
void rotate90CW(vector<vector<int>>& A) { // square n x n, in-place
    int n = A.size();
    for (int i = 0; i < n; i++) for (int j = i + 1; j < n; j++) swap(A[i][j], A[j][i]);
    for (int i = 0; i < n; i++) reverse(A[i].begin(), A[i].end());
}
vector<int> spiralOrder(const vector<vector<int>>& A) {
    int top = 0, bottom = (int)A.size() - 1, left = 0, right = (int)A[0].size() - 1;
    vector<int> out;
    while (top <= bottom && left <= right) {
        for (int j = left; j <= right; j++) out.push_back(A[top][j]); top++;
        for (int i = top; i <= bottom; i++) out.push_back(A[i][right]); right--;
        if (top <= bottom) { for (int j = right; j >= left; j--) out.push_back(A[bottom][j]); bottom--; }
        if (left <= right) { for (int i = bottom; i >= top; i--) out.push_back(A[i][left]); left++; }
    }
    return out;
}
int main() {
    vector<vector<int>> A = {{1,2,3},{4,5,6},{7,8,9}};
    auto T = transposeMat(A);
    cout << "Transpose[0]: " << T[0][0] << T[0][1] << T[0][2] << " (147)\n";
    rotate90CW(A);
    cout << "Rotated[0]: " << A[0][0] << A[0][1] << A[0][2] << " (expected 741)\n";
    vector<vector<int>> B = {{1,2,3},{4,5,6},{7,8,9}};
    auto s = spiralOrder(B);
    cout << "Spiral: "; for (int x : s) cout << x << ' ';
    cout << "(expected 1 2 3 6 9 8 7 4 5)\n";
    return 0;
}
