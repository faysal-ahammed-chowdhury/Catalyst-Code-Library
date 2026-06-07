const int N = 2e5 + 9;
const int B = 2500;
struct query {
  int l, r, t, id;
  bool operator < (const query& x) const {
    if (l / B == x.l / B) {
      if (r / B == x.r / B) return t < x.t;
      return r / B < x.r / B;
    }
    return l / B < x.l / B;
  }
} Q[N];
struct upd {
  int pos, old, cur;
} U[N];
int a[N], cnt[N], f[N], ans[N], l, r, t;
int sum = 0, now[N];
inline void add(int x) {
  int val = now[x];
  if ( val % 3 != 0 ) val = 0;
  if ( cnt[x] == 0 ) sum += val;
  ++cnt[x];
}
inline void del(int x) {
  int val = now[x];
  if ( val % 3 != 0 ) val = 0;
  --cnt[x];
  if ( cnt[x] == 0 ) sum -= val;
}
inline void update(int pos, int x) {
  if (l <= pos && pos <= r) {
    add(x);
    del(a[pos]);
  }
  a[pos] = x;
}
map <int, int> mp;
int nxt = 0;
int get(int x) {
  if ( !mp.count(x) ) {
    mp[x] = nxt; now[nxt] = x;
    nxt++;
  }
  return mp[x];
}
void AmeDoko() {
  int n, q; cin >> n >> q;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    a[i] = get(a[i]);
  }
  int nq = 0, nu = 0;
  for (int i = 1; i <= q; i++) {
    int ty, l, r;
    cin >> ty >> l >> r;
    if (ty == 1) ++nq, Q[nq] = { l, r, nu, nq };
    else ++nu, U[nu].pos = l, U[nu].old = a[l], a[l] = get(r), U[nu].cur = a[l];
  }
  sort(Q + 1, Q + nq + 1);
  t = nu, l = 1, r = 0;
  for (int i = 1; i <= nq; i++) {
    int L = Q[i].l, R = Q[i].r, T = Q[i].t;
    while (t < T) t++, update(U[t].pos, U[t].cur);
    while (t > T) update(U[t].pos, U[t].old), t--;
    if (R < l) {
      while (l > L) add(a[--l]);
      while (l < L) del(a[l++]);
      while (r < R) add(a[++r]);
      while (r > R) del(a[r--]);
    }
    else {
      while (r < R) add(a[++r]);
      while (r > R) del(a[r--]);
      while (l > L) add(a[--l]);
      while (l < L) del(a[l++]);
    }
    ans[Q[i].id] = sum;
  }
  for (int i = 1; i <= nq; i++) cout << ans[i] << '\n';
}