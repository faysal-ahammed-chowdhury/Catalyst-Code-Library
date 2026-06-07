// Given a tree, each node has a char. Print max len subsequence any path which is a palindrome. (CF/1771/D)
// Time: $O(N^2)$
int nxt[N][N], dp[N][N];
vector<int> vec;
void dfs(int u, int p) {
  vec.push_back(u);
  for (auto v: g[u]) {
    if (v != p) dfs(v, u);
  }
}
int f(int u, int v) {
  if (v == u) return 1;
  int &ans = dp[u][v];
  if (ans != -1) return ans;
  ans = 0;
  if (s[u] == s[v]) ans = 2 + (nxt[u][v] == v ? 0 : f(nxt[u][v], nxt[v][u]));
  else ans = max(f(nxt[u][v], v), f(u, nxt[v][u]));
  return ans;
}
void solve() {
  cin >> n >> s; s = '.' + s;
  for (int i = 1; i < n; i++) {
    int u, v; cin >> u >> v;
    g[u].push_back(v);
    g[v].push_back(u);
  }
  // $nxt[u][v]$ = next node after $u$ if I want to go from $u$ to $v$
  for (int u = 1; u <= n; u++) {
    for (auto x : g[u]) {
      vec.clear();
      dfs(x, u);
      for (auto v : vec) nxt[u][v] = x;
    }
  }
  memset(dp, -1, sizeof dp);
  int ans = 0;
  for (int u = 1; u <= n; u++) {
    for (int v = 1; v <= n; v++) {
      ans = max(ans, f(u, v));
    }
  }
  cout << ans << '\n';
}