// Problem: CF/0-1 MST
// A Complete Graph. $m$ edges have weight 1, rest have 0. MST?
const int N = 200000 + 9;
set<int> g[N], non_vis;
void dfs(int u) {
  non_vis.erase(u);
  for (int v = 1; v <= n; v++) {
    if (v == u) continue;
    auto it = non_vis.lower_bound(v);
    if (it == non_vis.end()) break;
    v = *it;
    if (g[u].find(v) != g[u].end()) continue;
    dfs(v);
  }
}
int32_t main() {
  int m; cin >> n >> m;
  while (m--) {
    int u, v; cin >> u >> v;
    g[u].insert(v);
    g[v].insert(u);
  }
  for (int i = 1; i <= n; i++) non_vis.insert(i);
  int component_cnt = 0;
  for (int i = 1; i <= n; i++) {
    if (non_vis.find(i) != non_vis.end()) {
      component_cnt++;
      dfs(i);
    }
  }
  cout << component_cnt - 1 << '\n';
}