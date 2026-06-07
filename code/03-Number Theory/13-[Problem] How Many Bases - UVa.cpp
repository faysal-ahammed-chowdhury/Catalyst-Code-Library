// Given a number $N^M$, find out the number of integer bases in which it has exactly T trailing zeroes.
int solve_greater_or_equal(vector<int> e, int t) {
  int ans = 1;
  for (auto i : e) {
    ans = 1LL * ans * (i / t + 1) % mod;
  }
  return ans;
}
// e contains $e_1$, $e_2$ -> ${p_1}^{e_1}$, ${p_2}^{e_2}$
int solve_equal(vector<int> e, int t) {
  return (solve_greater_or_equal(e, t) - solve_greater_or_equal(e, t + 1) + mod) % mod;
}