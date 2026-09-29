# 06 — Graphs Syntax

## Build adjacency list (input: n nodes, m edges)
```cpp
int n,m; cin>>n>>m; vector<vector<int>> adj(n); // 0-indexed; use n+1 for 1-indexed
for(int i=0;i<m;i++){ int u,v;cin>>u>>v; adj[u].push_back(v); adj[v].push_back(u); } // undirected — drop 2nd push for directed
```
```cpp
vector<vector<pair<int,int>>> wadj(n); // weighted: {neighbour, weight}
wadj[u].push_back({v,w});
```

## BFS (shortest path unweighted, level order)
```cpp
vector<int> dist(n,-1); queue<int> q; q.push(0); dist[0]=0; // dist=-1 means unvisited
while(!q.empty()){ int u=q.front();q.pop();
  for(int v:adj[u]) if(dist[v]==-1){ dist[v]=dist[u]+1; q.push(v); } } // first visit = shortest
```

## DFS recursive + iterative
```cpp
vector<bool> vis(n,false); // must have — prevents infinite loop on cycle
void dfs(int u, vector<vector<int>>&adj, vector<bool>&vis){ vis[u]=true; cout<<u;
  for(int v:adj[u]) if(!vis[v]) dfs(v,adj,vis); } // go deep first
```
```cpp
stack<int> s; s.push(0); vis[0]=true; // iterative version
while(!s.empty()){ int u=s.top();s.pop(); for(int v:adj[u]) if(!vis[v]){vis[v]=true;s.push(v);} }
```

## Topological sort — Kahn (BFS, only DAG)
```cpp
vector<int> indeg(n,0); for(auto &e:adj) for(int v:e) indeg[v]++; // count incoming
queue<int> q; for(int i=0;i<n;i++) if(indeg[i]==0) q.push(i); // start with zero-dep
vector<int> topo; while(!q.empty()){ int u=q.front();q.pop(); topo.push_back(u);
  for(int v:adj[u]) if(--indeg[v]==0) q.push(v); } // remove u, unlock neighbours
// if topo.size()!=n → cycle exists
```

## Dijkstra (non-negative weights)
```cpp
vector<int> d(n,1e9); d[0]=0; priority_queue<pair<int,int>,vector<pair<int,int>>,greater<>> pq; pq.push({0,0}); // {dist,node} min-heap
while(!pq.empty()){ auto [du,u]=pq.top();pq.pop(); if(du>d[u]) continue; // stale entry skip
  for(auto [v,w]:wadj[u]) if(d[v]>du+w){ d[v]=du+w; pq.push({d[v],v}); } } // relax edge
```

## DSU (Union-Find) — components, Kruskal, cycle
```cpp
struct DSU{ vector<int> p,r; DSU(int n):p(n),r(n,0){ iota(p.begin(),p.end(),0);} // parent[i]=i initially
  int find(int x){ return p[x]==x?x:p[x]=find(p[x]); } // path compression
  bool unite(int a,int b){ a=find(a);b=find(b); if(a==b) return false; // already same set
    if(r[a]<r[b]) swap(a,b); p[b]=a; if(r[a]==r[b]) r[a]++; return true; } }; // union by rank
```

---
## 6 Must-Do Problems (sufficient for this topic)

1. **Number of Islands (LC 200)** — Input: grid of `1/0` → count components. Why: DFS/BFS on matrix with `dr/dc` directions. Visit-mark pattern = graph visited array.
2. **Clone Graph / BFS-DFS fluency (LC 133)** — Why: adj-list traversal + `vis` map + queue. If you can clone, you can do any BFS/DFS.
3. **Course Schedule I + II (LC 207, 210)** — Input: `n=2, prereqs=[[1,0]]` → `true / [0,1]`. Why: Kahn's topo template + cycle detect (`topo.size()!=n`). II just returns the order.
4. **Shortest: Dijkstra / Network Delay Time (LC 743)** — Input: `times=[[2,1,1],[2,3,1],[3,4,1]], n=4, k=2` → `2`. Why: min-heap `{dist,node}` + relax + stale-skip. Teaches weighted vs BFS.
5. **Number of Provinces / DSU intro (LC 547)** — Input: adj matrix → component count. Why: DSU `find/unite` OR DFS — do once each way to feel both.
6. **Rotting Oranges (LC 994)** — Input: grid with `0/1/2` → minutes. Why: multi-source BFS (push all 2s first) + level counting. Direct extension of BFS template.

