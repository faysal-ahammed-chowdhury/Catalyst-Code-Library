// A sequence $w_1, w_2, ...,w_n$ and Q queries, l and r will be given. Calculate $w_l^{(w_{l+1}^{...^{(w_r)}})}$
// $n^x \bmod m = n^{\phi(m) + x \bmod \phi(m)} \bmod m$
inline int MOD(int x, int m) {
  if (x < m) return x;
  return x % m + m;
}
int power(int n, int k, int mod) {
  int ans = MOD(1, mod);
  while (k) {
    if (k & 1) ans = MOD(ans * n, mod);
    n = MOD(n * n, mod);
    k >>= 1;
  }
  return ans;
}
int f(int l, int r, int m) {
  if (l == r) return MOD(a[l], m);
  if (m == 1) return 1;
  return power(a[l], f(l + 1, r, phi(m)), m);
}