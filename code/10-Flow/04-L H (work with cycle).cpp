const int INF = 2000000000;
struct Edge {
  int from, to, cap, flow, index, idx;
  Edge(int from, int to, int cap, int flow, int index, int idx):
    from(from), to(to), cap(cap), flow(flow), index(index), idx(idx) {}
};
struct Dinic {
  int N;
  vector<vector<Edge>>G;
  vector<Edge*>dad;
  vector<int>Q;
  Dinic(int N) : N(N), G(N), dad(N), Q(N) {}
  void AddEdge(int from, int to, int cap, int idx) {
    G[from].emplace_back(from, to, cap, 0, G[to].size(), idx);
    if (from == to) {G[from].back().index++;}
    G[to].emplace_back(to, from, 0, 0, G[from].size() - 1, 0);
  }
  long long BlockingFlow(int s, int t) {
    fill(dad.begin(), dad.end(), (Edge*) NULL);
    dad[s] = &G[0][0] - 1;
    int head = 0, tail = 0;
    Q[tail++] = s;
    while (head < tail) {
      int x = Q[head++];
      for (int i = 0; i < G[x].size(); i++) {
        Edge &e = G[x][i];
        if ((!dad[e.to]) && ((e.cap - e.flow) > 0)) {
          dad[e.to] = &G[x][i];
          Q[tail++] = e.to;
        }
      }
    }
    if (!dad[t]) {return 0;}
    long long totflow = 0;
    for (int i = 0; i < G[t].size(); i++) {
      Edge *start = &G[G[t][i].to][G[t][i].index];
      int amt = INF;
      for (Edge *e = start; amt && (e != dad[s]); e = dad[e->from]) {
        if (!e) {amt = 0; break;}
        amt = min(amt, e->cap - e->flow);
      }
      if (amt == 0) {continue;}
      for (Edge *e = start; amt && (e != dad[s]); e = dad[e->from]) {
        e->flow += amt;
        G[e->to][e->index].flow -= amt;
      }
      totflow += amt;
    }
    return totflow;
  }
  long long GetMaxFlow(int s, int t) {
    long long totflow = 0;
    while (long long flow = BlockingFlow(s, t)) {
      totflow += flow;
    }
    return totflow;
  }
};
int ans[50000];
void cal_ans(const Dinic &dinic) {
  for (int u = 0; u < dinic.N; ++u) {
    for (const Edge &e : dinic.G[u]) {
      if (e.idx != 0) {
        ans[e.idx] += e.flow;
      }
    }
  }
}
void solve(int T) {
  int n, m;  cin >> n >> m;
  int dummy_source = 0;
  int dummy_sink = n + 1;
  Dinic *mr_warlock = new Dinic(n + 2);
  int sum = 0;
  for (int i = 1; i <= m; i++) {
    int u, v, l, h;    cin >> u >> v >> l >> h;
    sum += l;
    ans[i] = l;
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
}