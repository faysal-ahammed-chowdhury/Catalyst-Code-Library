// Given a complete binary tree, $i-th$ node grows $a_i$ roses per day and deliver to $u$ in $dis(u, i)$ days. Alice at node $u$, How many roses he will get within $t$ days? $u$ and $t$ for $Q$ queries.
// Idea: as it is a complete binary tree, max dis is $2*logn$. We can do DP on Tree for $~40$ days.
ll dp[N][45], dp2[N][45];
void dfs(int u, int p) {
  for (int i = 1; i <= 40; i++) {
    dp[u][i] = i * a[u];
  }
  for (auto v : g[u]) {
    if (v != p) {
      dfs(v, u);
      for (int i = 1; i <= 40; i++) {
        dp[u][i] += dp[v][i - 1];
      }
    }
  }
}
void dfs2(int u, int p) {
  for (int i = 2; u != 1 and i <= 40; i++) {
    dp2[u][i] = (dp[p][i - 1] + dp2[p][i - 1]) - dp[u][i - 2];
  }
  for (auto v : g[u]) {
    if (v != p) {
      dfs2(v, u);
    }
  }
}
int32_t main() {
  cin >> n; ll sum = 0;
  for (int i = 1; i <= n; i++) {
    cin >> a[i]; sum += a[i];
  }
  dfs(1, 0); // rose from subtree
  dfs2(1, 0); // rose from par
  int q; cin >> q;
  while (q--) {
    int u, t; cin >> u >> t;
    int extra = t - 40;
    t = min(40, t);
    ll ans = dp[u][t] + dp2[u][t];
    if (extra > 0) ans += 1ll * extra * sum;
    cout << ans << '\n';
  }
}