// Problem: How Many Zeroes? - LightOJ
// How many zeroes between n to m $(n<=m)$. 100 to 102 ans 4
ll fun2(int i, bool is_small) {
  if (i == sz) return 1;
  int l = 0, r = s[i] - '0';
  if (is_small) r = 9;
  ll &ans = dp2[i][is_small];
  if (ans != -1) return ans;
  ans = 0;
  for (int x = l; x <= r; x++) {
    ans += fun2(i + 1, (is_small | (x < r)));
  }
  return ans;
}
ll fun(int i, bool is_small, bool has_started) {
  if (i == sz) return 0;
  int l = 0, r = s[i] - '0';
  if (is_small) r = 9;
  ll &ans = dp1[i][is_small][has_started];
  if (ans != -1) return ans;
  ans = 0;
  for (int x = l; x <= r; x++) {
    bool new_has_started = has_started | (x != 0);
    ans += fun(i + 1, (is_small | (x < r)), new_has_started);
    if (x == 0 and has_started) {
      ans += fun2(i + 1, (is_small | (x < r)));
    }
  }
  return ans;
}
void get(long long x) {
  if (x < 0) return; s = "";
  while (x > 0) {
    char c = (x % 10) + '0';
    s += c; x /= 10;
  }
  reverse(s.begin(), s.end());
  sz = s.size();
  memset(dp1, -1, sizeof(dp1));
  memset(dp2, -1, sizeof(dp2));
}
void solve() {
  ll n, m; cin >> n >> m;
  get(n - 1);
  memset(dp1, -1, sizeof(dp1));
  memset(dp2, -1, sizeof(dp2));
  ll ans1 = (n == 0) ? 0 : fun(0, false, false);
  get(m);
  ll ans2 = fun(0, false, false);
  cout << ans2 - ans1 + (n == 0) << '\n';
}