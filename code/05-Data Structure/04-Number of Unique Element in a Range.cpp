vector<pair<int, int>> Q[QQ]; 
int main() {
  int n; cin >> n;
  for(int i = 1; i <= n; i++) cin >> a[i];
  int q; cin >> q;
  for(int i = 1; i <= q; i++) {
    int l, r; cin >> l >> r;
    Q[r].push_back({l, i});
  }
  st.build(1, 1, n); // range sum and point add
  map<int, int> last_idx;
  for(int r = 1; r <= n; r++) {
    if(last_idx.find(a[r]) != last_idx.end()) {
      st.upd(1, 1, n, last_idx[a[r]], -1);
    }
    last_idx[a[r]] = r;
    st.upd(1, 1, n, r, 1);
    for(auto i: Q[r]) {
      int l = i.first, id = i.second;
      ans[id] = st.query(1, 1, n, l, r);
    }
  }
}