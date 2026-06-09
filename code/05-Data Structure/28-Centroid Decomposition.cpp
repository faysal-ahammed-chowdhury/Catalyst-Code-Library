set<int>graph[N];
int par[N];
int sz[N];
int ans[N];
int nn = 0;
void dfs_sz(int x, int p) {
  sz[x] = 1;
  nn++;
  for (auto u : graph[x]) {
    if (u != p) {
      dfs_sz(u, x);
      sz[x] += sz[u];
    }
  }
}
int dfs_centroid(int x, int p) {
  for (auto u : graph[x]) {
    if (u != p && sz[u] > nn / 2) {
      return dfs_centroid(u, x);
    }
  }
  return x;
}
void decompose(int x, int p) {
  nn = 0;
  dfs_sz(x, x);
  int centroid = dfs_centroid(x, x);
  if (p == -1) {p = centroid;}
  par[centroid] = p;
  for (auto u : graph[centroid]) {
    graph[u].erase(centroid);
    decompose(u, centroid);
  }
  graph[centroid].clear();
}
int query(int node) {
  int x = node;
  int res = LLMax;
  while (1) {
    res = min(res, find_dis(node, x) + ans[x]);
    if (x == par[x]) {break;}
    x = par[x];
  }
  return res;
}
void update(int node) {
  int x = node;
  while (1) {
    ans[x] = min(ans[x], find_dis(node, x));
    if (x == par[x]) {break;}
    x = par[x];
  }
}