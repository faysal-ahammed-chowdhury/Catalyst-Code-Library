struct HopcroftKarp { //O( E*sqrt(V) )
  static const int MAX = 1005;
  const int INF = 1 << 30;
  vector<int> G[MAX];
  int n, m, match[MAX], dist[MAX];
  // n: number of nodes on left side, nodes are numbered 1 to n
  // m: number of nodes on right side, nodes are numbered n+1 to n+m
  // G = NIL[0] ? G1[G[1---n]] : G2[G[n+1---n+m]]
  void init(int N, int M) {
    memset(match, 0, sizeof match);
    n = N, m = M;
    for (int i = 0; i <= m + n; i++)G[i].clear();
  }
  inline void addEdge(int u, int v) {
    G[u].pb(v);
  }
  bool bfs() {
    queue<int> Q;
    for (int i = 1; i <= n; i++) {
      if (match[i] == 0) {
        dist[i] = 0;
        Q.push(i);
      }
      else dist[i] = INF;
    }
    dist[0] = INF;
    while (!Q.empty()) {
      int u = Q.front(); Q.pop();
      if (u != 0) {
        for (int v : G[u]) {
          if (dist[match[v]] == INF) {
            dist[match[v]] = dist[u] + 1;
            Q.push(match[v]);
          }
        }
      }
    }
    return (dist[0] != INF);
  }
  bool dfs(int u) {
    if (u != 0) {
      for (int v : G[u]) {
        if (dist[match[v]] == dist[u] + 1) {
          if (dfs(match[v])) {
            match[v] = u;
            match[u] = v;
            return true;
          }
        }
      }
      dist[u] = INF;
      return false;
    }
    return true;
  }
  int bpm() {
    int matching = 0;
    while (bfs())
      for (int i = 1; i <= n; i++)
        if (match[i] == 0 && dfs(i))
          matching++;
    return matching;
  }
} HK;
//  HK.init(n, m);
//  HK.addEdge(u, v);
//  int maxMatching = HK.bpm();
// Max independent set = N - matching
// Min node cover = matching
// Min edge cover = N - matching  (if egde cover exist)
// Min path cover = N - matching (DAG)