// Problem: Slimes - Atcoder DP Contest
// Given n slimes. Choose two adjacent slimes, and combine them into a new slime. The new slime has a size of x+y, where x and y are the sizes of the slimes before combining them. Here, a cost of x+y is incurred. Example-
// (10, 20, 30, 40) → (30, 30, 40)
// (30, 30, 40) → (60, 40)
// (60, 40) → (100) ans = 190
// Solution: Think reverse. We are given the final sum, from $i$ to $j$. Now we will cut any point between $i$ to $j$ and calculate the cost
// Time: $O(n^3)$
ll fun(int i, int j) {
  if (i == j) return 0;
  ll &ans = dp[i][j];
  if (ans != -1) return ans;
  ll cur = 0;
  for (int x = i; x <= j; x++) {
    cur += a[x];
  }
  ans = inf;
  for (int x = i; x < j; x++) {
    ans = min(ans, cur + fun(i, x) + fun(x + 1, j));
  }
  return ans;
}
cout << fun(1, n) << '\n';