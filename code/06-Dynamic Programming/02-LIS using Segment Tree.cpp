int32_t main() {
  int n; cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i]; // a[i] must be >= 2
  }
  // dp[i] = LIS ending at pos $i$
  st.build(1, 1, M); // range max query, and upd idx with max(cur_val, new_val)
  for (int i = 1; i <= n; i++) {
    dp[i] = 1;
    if (a[i] != 1) {
      int mx = st.query(1, 1, M, 1, a[i] - 1);
      mx++;
      dp[i] = max(dp[i], mx);
    }
    st.upd(1, 1, M, a[i], dp[i]);
  }
  int ans = 0;
  for (int i = 1; i <= n; i++) ans = max(ans, dp[i]);
  cout << ans << '\n';
}