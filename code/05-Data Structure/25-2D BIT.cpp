const int N = 2500 + 10;
int a[N][N], tree[N][N];
void update(int x, int y, int val) { // x and y is the coordinate from range update
  for (int i = x; i < N; i += i & (-i)) {
    for (int j = y; j < N; j += j & (-j)) {
      tree[i][j] += val;
    }
  }
}
int query(int x, int y) {
  int res = 0;
  for (int i = x; i < N; i += i & (-i)) {
    for (int j = y; j < N; j += j & (-j)) {
      res += tree[i][j];
    }
  }
  return res;
}
void range_add(int a, int b, int c, int d, int val) {
  update(a, b, val);
  update(a, d + 1, -val);
  update(c + 1, b, -val);
  update(c + 1, d + 1, val);
}