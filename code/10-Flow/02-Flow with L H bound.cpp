const long long inf = 1LL << 61;
struct Dinic {
  struct edge {int to, rev; long long flow, w; int id;};
  int n, s, t, mxid;
  vector<int> d, flow_through; vector<int> done;
  vector<vector<edge>>g;
  Dinic() {}
  Dinic(int _n) {
    n = _n + 10; mxid = 0;
    g.resize(n);
  }
  void AddEdge(int u, int v, long long w, int id = -1) {
    edge a = {v, (int)g[v].size(), 0, w, id};
    edge b = {u, (int)g[u].size(), 0, 0, -1};//for bidirectional edges cap(b) = w
    g[u].emplace_back(a);
    g[v].emplace_back(b);
    mxid = max(mxid, id);
  }
  bool bfs() {
    d.assign(n, -1); d[s] = 0;
    queue<int> q; q.push(s);
    while (!q.empty()) {
      int u = q.front(); q.pop();
      for (auto &e : g[u]) {
        int v = e.to;
        if (d[v] == -1 && e.flow < e.w) d[v] = d[u] + 1, q.push(v);
      }
    }
    return d[t] != -1;
  }
  long long dfs(int u, long long flow) {
    if (u == t) return flow;
    for (int &i = done[u]; i < (int)g[u].size(); i++) {
      edge &e = g[u][i];
      if (e.w <= e.flow) continue;
      int v = e.to;
      if (d[v] == d[u] + 1) {
        long long nw = dfs(v, min(flow, e.w - e.flow));
        if (nw > 0) {
          e.flow += nw;
          g[v][e.rev].flow -= nw;
          return nw;
        }
      }
    }
    return 0;
  }
  long long max_flow(int _s, int _t) {
    s = _s; t = _t;
    long long flow = 0;
    while (bfs()) {
      done.assign(n, 0);
      while (long long nw = dfs(s, inf)) flow += nw;
    }
    flow_through.assign(mxid + 10, 0);
    for (int i = 0; i < n; i++) for (auto e : g[i]) if (e.id >= 0) flow_through[e.id] = e.flow;
    return flow;
  }
};
struct LR_Flow {
  Dinic F;
  int n, s, t;
  struct edge {int u, v, l, r, id;};
  vector<edge> edges;
  LR_Flow() {}
  LR_Flow(int _n) {
    n = _n + 10; s = n - 2, t = n - 1;;
    edges.clear();
  }
  void AddEdge(int u, int v, int l, int r, int id = -1) {
    assert(0 <= l && l <= r);
    edges.push_back({u, v, l, r, id});
  }
  bool feasible(int _s = -1, int _t = -1, int L = -1, int R = -1) {
    if (L != -1) edges.push_back({_t, _s, L, R, -1});
    F = Dinic(n);
    long long target = 0;
    for (auto e : edges) {
      int u = e.u, v = e.v, l = e.l, r = e.r, id = e.id;
      if (l != 0) {
        F.AddEdge(s, v, l);
        F.AddEdge(u, t, l);
        target += l;
      }
      F.AddEdge(u, v, r - l, id);
    }
    auto ans = F.max_flow(s, t);
    if (L != -1) edges.pop_back();
    if (ans < target) return 0; //not feasible
    return 1;
  }
  int max_flow(int _s, int _t) { //-1 means flow is not feasible
    int mx = 1e9;
    int ans = -1, l = 0, r = mx;        //l=-mx
    while (l <= r) {
      int mid = l + r >> 1;
      if (feasible(_s, _t, mid, mx)) ans = mid, l = mid + 1;
      else r = mid - 1;
    }
    return ans;
  }
  int min_flow(int _s, int _t) { //-1 means flow is not feasible
    int mx = 1e9;
    int ans = -1, l = 0, r = mx;        //l=-mx
    while (l <= r) {
      int mid = l + r >> 1;
      if (feasible(_s, _t, 0, mid)) ans = mid, r = mid - 1;
      else l = mid + 1;
    }
    return ans;
  }
};
int n, m;  cin >> n >> m;
int dummy_source = 0;
int dummy_sink = n + 1;
Dinic *mr_warlock = new Dinic(n + 2);
int sum = 0;
for (int i = 1; i <= m; i++) {
  int u, v, l, h;    cin >> u >> v >> l >> h;
  sum += l; ans[i] = l;
  mr_warlock->AddEdge(u, v, h - l, i);
  mr_warlock->AddEdge(u, dummy_sink, l, 0);
  mr_warlock->AddEdge(dummy_source, v, l, 0);
}
int z = mr_warlock->GetMaxFlow(dummy_source, dummy_sink);
if (sum != z) {NO; return;}
cal_ans(*mr_warlock);
YES;
for (int i = 1; i <= m; i++) {
  cout << ans[i] << endl;
}