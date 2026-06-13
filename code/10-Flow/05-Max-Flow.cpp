const int INF = 2000000000;
struct Edge {
  int from, to, cap, flow, index;
  Edge(int from, int to, int cap, int flow, int index):
    from(from), to(to), cap(cap), flow(flow), index(index) {}
};
struct Dinic {
  int N;
  vector<vector<Edge>>G;
  vector<Edge*>dad;
  vector<int>Q;
  Dinic(int N) : N(N), G(N), dad(N), Q(N) {}
  void AddEdge(int from, int to, int cap) {
    G[from].emplace_back(from, to, cap, 0, G[to].size());
    if (from == to) {G[from].back().index++;}
    G[to].emplace_back(to, from, 0, 0, G[from].size() - 1);
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
  bool augment_one(int s, int t) {
    vector<int> parV(N, -1), parE(N, -1);
    queue<int> q;
    q.push(s);
    parV[s] = s;
    while (!q.empty() && parV[t] == -1) {
      int u = q.front(); q.pop();
      for (int i = 0; i < G[u].size(); i++) {
        Edge &e = G[u][i];
        if ((e.cap - e.flow) > 0 && parV[e.to] == -1) {
          parV[e.to] = u;
          parE[e.to] = i;
          q.push(e.to);
          if (e.to == t) break;
        }
      }
    }
    if (parV[t] == -1) return false;
    int v = t;
    while (v != s) {
      int u = parV[v];
      int ei = parE[v];
      Edge &e = G[u][ei];
      e.flow += 1;
      G[e.to][e.index].flow -= 1;
      v = u;
    }
    return true;
  }
};
void PrintGraph(const Dinic &dinic) {
  for (int u = 0; u < dinic.N; ++u) {
    for (const Edge &e : dinic.G[u]) {
      cout << "From: " << e.from
           << ", To: " << e.to
           << ", Cap: " << e.cap
           << ", Flow: " << e.flow
           << ", ReverseIndex: " << e.index
           << endl;
    }
  }
}
// Initialization : Dinic *mr_warlock=new Dinic(n+1);
// Add Edge : mr_warlock->AddEdge(a,b,c);
// Get Max Flow : mr_warlock->GetMaxFlow(s,t);
// delete (mr_warlock);
//or
// Initialization : Dinic mr_warlock(n+1);
// Add Edge : mr_warlock.AddEdge(a,b,c);
// Get Max Flow : mr_warlock.GetMaxFlow(s,t);
// delete: no need
/*
    --augment_one--
    store edge id
    e_id[i][j]=mr_warlock.G[i+1].size();
    u->v
    Edge &e = mr_warlock.G[u][e_id[i][j]];
    Edge &rev = mr_warlock.G[v][e.index];
    set :
        e.cap=0;
        rev.vap=0;
    check if possible to switch
    if not
        e.cap = saved_cap;
        e.flow = saved_flow;
        rev.cap = saved_rcap;
        rev.flow = saved_rflow;
*/