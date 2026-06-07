// Problem: CSES/task/2081 (Number of distinct path of len $k_1...k_2$)
// Complexity: $O(n(logn)^2)$
int par[N], ans; // $par[i]=i$ initially
deque<int> suff[N];
int find(int i) {
  return (i == par[i] ? i : par[i] = find(par[i]));
}
int get_sum(int node, int l, int r) {
  if (l > r) return 0;
  return suff[node][l] - (r + 1 < suff[node].size() ? suff[node][r + 1] : 0);
}
void merge(int u, int v) {
  if ((u = find(u)) == (v = find(v))) return;
  bool swapped = false;
  if (suff[u].size() >= suff[v].size()) {
    swap(u, v); swapped = true;
  }
  for (int i = 0; i < suff[u].size(); i++) {
    int x = suff[u][i] - (i + 1 < suff[u].size() ? suff[u][i + 1] : 0);
    int need_mn = max(0ll, k1 - i - 1);
    int tmp = suff[v].size() - 1;
    int need_mx = min(tmp, k2 - i - 1);
    ans += get_sum(v, need_mn, need_mx) * x;
  }
  // merging two suffix sum
  if (swapped) { // normal way (child size choto)
    suff[v][0] += suff[u][0]; int idx = 1;
    for (auto x : suff[u]) {
      if (idx < suff[v].size()) suff[v][idx] += x;
      else suff[v].push_back(x);
      idx++;
    }
  }
  else { // child size boro
    int idx = 0; bool first = true;
    for (auto x : suff[u]) {
      if (first) first = false; continue;
      if (idx < suff[v].size()) suff[v][idx] += x;
      else suff[v].push_back(x);
      idx++;
    }
    suff[v].push_front(1 + suff[v].front());
  }
  par[u] = v;
}
void dfs(int u, int p) {
  suff[u].push_back(1); // initially 0 len er cnt 1
  for (auto v : g[u]) {
    if (v != p) {
      dfs(v, u);
      merge(u, v);
    }
  }
}