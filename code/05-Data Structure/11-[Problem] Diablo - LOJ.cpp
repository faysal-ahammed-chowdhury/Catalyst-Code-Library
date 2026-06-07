// Add element at the End, and Remove Kth Index (also print it's value)
int deleted_idx;
struct ST {
  pair<int, int> tree[4 * (N + Q)]; // sum, alive_cnt
  pair<int, int> query(int n, int b, int e, int x) {
    if (b > e) return { -1, -1};
    if (tree[n].second < x) return {tree[n].second, -1};
    if (b == e) {
      deleted_idx = b;
      return tree[n];
    }
    int mid = (b + e) >> 1, l = n << 1, r = l + 1;
    pair<int, int> L = query(l, b, mid, x);
    if (L.second != -1) return L;
    pair<int, int> R = query(r, mid + 1, e, x - L.first);
    return R;
  }
} st;
void solve() {
  int id = n, end = n + q + 5;
  while (q--) {
    char c; cin >> c;
    if (c == 'a') {
      int p; cin >> p;
      st.upd(1, 1, end, ++id, p, 1);
    }
    else {
      int k; cin >> k;
      pair<int, int> ans = st.query(1, 1, end, k);
      if (ans.second == -1) cout << "none\n";
      else {
        cout << ans.first << '\n';
        st.upd(1, 1, end, deleted_idx, 0, 0);
      }
    }
  }
}