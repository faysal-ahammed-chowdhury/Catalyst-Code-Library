// Problem: Save The Trees - LOJ
// Given N trees in order, each with height and type, partition them into groups so that every tree is used, no group contains duplicate types, each groups cost is its tallest trees height, minimize total cost.
// $helper[j]=dp[j-1]+rangemax(j,i);$ ($i$ to $j$ in same group)
// $dp[i]=min(helper[j])$ for all possible valid $j$
const int N = 2e5 + 9, inf = 1e18;
int a[N], b[N], n, lft_idx[N], dp[N];
map<int, int> last_pos;
void solve() {
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i] >> b[i]; // type, height
  }
  for (int i = 1; i <= n; i++) {
    if (last_pos.find(a[i]) == last_pos.end()) lft_idx[i] = 1;
    else lft_idx[i] = last_pos[a[i]] + 1;
    lft_idx[i] = max(lft_idx[i], lft_idx[i - 1]);
    last_pos[a[i]] = i;
  }
  // segtree range min query and range add upd
  st1.build(1, 1, n);
  st2.build(1, 1, n);
  memset(dp, 0, sizeof dp);
  stack<pair<int, int>> stk;
  stk.push({inf, 0});
  for (int i = 1; i <= n; i++) {
    int x = b[i], lft = lft_idx[i], pos = i;
    while (!stk.empty() and stk.top().second >= lft and stk.top().first <= x) {
      int mx = st2.query(1, 1, n, stk.top().second + 1, pos);
      st2.upd(1, 1, n, stk.top().second + 1, pos, -mx);
      st2.upd(1, 1, n, stk.top().second + 1, pos, x);
      st1.upd(1, 1, n, stk.top().second + 1, pos, -mx);
      st1.upd(1, 1, n, stk.top().second + 1, pos, x);
      pos = stk.top().second;
      stk.pop();
    }
    int mx = st2.query(1, 1, n, stk.top().second + 1, pos);
    st2.upd(1, 1, n, stk.top().second + 1, pos, -mx);
    st2.upd(1, 1, n, stk.top().second + 1, pos, x);
    st1.upd(1, 1, n, stk.top().second + 1, pos, -mx);
    st1.upd(1, 1, n, stk.top().second + 1, pos, x);
    stk.push({x, i});
    dp[i] = st1.query(1, 1, n, lft, i);
    if (i + 1 <= n) st1.upd(1, 1, n, i + 1, i + 1, dp[i]);
  }
}