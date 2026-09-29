# 11 — Input / Output & Debugging Syntax

## Fast IO (top of every program)
```cpp
ios::sync_with_stdio(false); cin.tie(nullptr); // disables C/C++ sync + unties cin/cout — much faster
```

## LeetCode vs GFG input (why you get confused)
```cpp
// LeetCode: you get head/root/nums ALREADY BUILT — only write function body, no cin
// e.g. TreeNode* f(TreeNode* root) — root is given, just traverse
// GFG/local: YOU read input — int n; cin>>n; vector<int> v(n); for...cin
```

## Reading until end / multiple test cases
```cpp
int T; cin>>T; while(T--){ /* solve once */ } // GFG test cases pattern
// while(cin>>x){ /* process till EOF */ } // unknown amount of input
// after cin>>n before getline: cin.ignore(); // eat leftover newline
```

## Printing answers (match judge exactly)
```cpp
for(int i=0;i<n;i++){ if(i) cout<<' '; cout<<v[i]; } cout<<'\n'; // space-separated, no trailing space issue
cout<< (ok?"YES\n":"NO\n"); // ternary print
cout<<fixed<<setprecision(2)<<ans<<'\n'; // 2-decimal float (needs <iomanip>)
```

## Debug print (comment out before submit)
```cpp
#define debug(x) cerr << #x << " = " << x << '\n' // prints var NAME + value to stderr (judge ignores stderr)
// usage: debug(n); — shows "n = 5"
```
```cpp
// print vector in one line while debugging:
for(auto x:v) cerr<<x<<' '; cerr<<'\n';
```

## Types & limits (avoid overflow WA)
```cpp
long long x = 1e18; // use long long for sums/products — int overflows at 2e9
const int INF = 1e9; const long long LINF = 4e18; // infinity sentinels for min/dist
const int MOD = 1e9+7; ans = (ans + x) % MOD; // mod after every add/mul in counting DP
```

---
## 5 Practice Drills (sufficient for this topic — do on local compiler, not LeetCode)

1. **Multi-testcase array sum** — Input: `T` then each `n` + array. Why: locks `while(T--)` + per-case `vector` reinit. #1 GFG pattern.
2. **Matrix input + print transpose** — Read `r c` + grid, print transpose. Why: nested loops + `mat[j][i]` indexing. Kills row/col confusion.
3. **Full-line string with spaces** — Read `n`, then a sentence via `getline`. Why: practices `cin.ignore()` + `getline` + `stringstream` split. Needed for string problems locally.
4. **Tree build + inorder print** — Input: `n` + level array with `-1`, build via file-05 `build()` and print inorder. Why: bridges LeetCode (given root) vs local (build yourself).
5. **Debug-with-cerr drill** — Take any WA solution, add `debug()` macro + vector dump to `cerr`, find bug without `cout`. Why: builds habit of stderr debugging so judge output stays clean.

