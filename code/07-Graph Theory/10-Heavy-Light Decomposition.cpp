// Per Query Complexity: $O(logn^2)$
// Path and subtree updates and queries.
const int N = 2e5 + 9, LOG = 20, inf = 1e9; // change here
vector<int> g[N];
int par[N][LOG], depth[N], sz[N];
int disc[N], finish[N], timer, head[N];
int n;
void dfs(int u, int p = 0) {
  par[u][0] = p;
  depth[u] = depth[p] + 1;
  sz[u] = 1;
  for (int i = 1; i < LOG; i++) {
    par[u][i] = par[par[u][i - 1]][i - 1];
  }
  if (p) g[u].erase(find(g[u].begin(), g[u].end(), p));
  for (auto &v : g[u]) {
    if (v != p) {
      dfs(v, u);
      sz[u] += sz[v];
      if (sz[v] > sz[g[u][0]]) swap(v, g[u][0]);
    }
  }
}
void dfs_hld(int u) {
  disc[u] = ++timer;
  for (auto v : g[u]) {
    head[v] = (v == g[u][0] ? head[u] : v);
    dfs_hld(v);
  }
  finish[u] = timer;
}
int kth(int u, int k) {
  assert(k >= 0);
  for (int i = 0; i < LOG; i++) {
    if (CHECK(k, i)) u = par[u][i];
  }
  return u;
}
int query_up(int u, int v) {
  int ans = -inf; // change here
  while (head[u] != head[v]) {
    ans = max(ans, st.query(1, 1, n, disc[head[u]], disc[u])); // change here
    u = par[head[u]][0];
  }
  ans = max(ans, st.query(1, 1, n, disc[v], disc[u])); // change here
  return ans;
}
int query(int u, int v) {
  int lc = lca(u, v);
  int ans = query_up(u, lc);
  if (v != lc) {
    ans = max(ans, query_up(v, kth(v, depth[v] - depth[lc] - 1))); // change here
  }
  return ans;
}
void solve() {
  cin >> n;
  for (int i = 2; i <= n; i++) {
    int u, v; cin >> u >> v;
    g[u].push_back(v);
    g[v].push_back(u);
  }
  dfs(1);
  head[1] = 1;
  dfs_hld(1);
  st.build(1, 1, n);
}