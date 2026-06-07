int nxt[N][26], dp[N];
int f(int i) {
  if (i > n) return 0;
  int &ans = dp[i];
  if (ans != -1) return ans;
  ans = 1;
  for (int c = 0; c < 26; c++) {
    ans = (ans + f(nxt[i][c])) % mod;
  }
  return ans;
}
// nxt[i][c] = nxt c strictly after i
void solve() {
  cin >> s; s = '.' + s;
  cout << f(0) << '\n';
}