const int N = 2e5 + 9, K = 20; // change here
int a[N], tree[N][K];
int log2_floor(unsigned long long i) {
  return i ? __builtin_clzll(1) - __builtin_clzll(i) : -1;
}
void build(int n) {
  for (int i = 1; i <= n; i++) {
    tree[i][0] = a[i];
  }
  for (int k = 1; k < K; k++) {
    for (int i = 1; i + (1 << k) - 1 <= n; i++) {
      tree[i][k] = min(tree[i][k - 1], tree[i + (1 << (k - 1))][k - 1]); // change here
    }
  }
}
int query(int l, int r) {
  int k = log2_floor(r - l + 1);
  return min(tree[l][k], tree[r - (1 << k) + 1][k]); // change here
}
build(n);