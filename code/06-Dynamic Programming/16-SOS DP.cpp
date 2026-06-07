void AmeDoko() {
  fill(f, f + (1 << N), INT_MAX);
  int n; cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> a[i];
    f[a[i]] = a[i];
  }
  for (int mask = 0; mask < (1 << N); mask++) {
    for ( int i = mask; i > 0; i -= (i & -i)) {
      int temp = (mask ^ ( i & -i ));
      if ( f[temp] != INT_MAX ) {
        f[mask] = f[temp];
        break;
      }
    }
  }
  for (int i = 0; i < n; i++) {
    if (f[ ~a[i] & ((1 << N) - 1) ] != INT_MAX) cout << f[ ~a[i] & ((1 << N) - 1) ] << ' ';
    else cout << -1 << ' ';
  }
}