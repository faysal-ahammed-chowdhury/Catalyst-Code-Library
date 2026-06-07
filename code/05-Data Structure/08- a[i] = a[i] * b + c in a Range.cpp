// Problem: Range Affine Range Sum
// lazy1[n] = 1; lazy2[n] = 0; // init in build
// lazy1[n] *= x; lazy2[n] += y; // when upd
mint tree[4 * N], lazy1[4 * N], lazy2[4 * N];
void push(int n, int b, int e) {
  if (lazy1[n] == 1 or lazy2[n] == 0) return;
  tree[n] = tree[n] * lazy1[n] + lazy2[n] * (e - b + 1);
  if (b != e) {
    int mid = (b + e) >> 1, l = n << 1, r = l + 1;
    lazy1[l] *= lazy1[n];
    lazy2[l] = lazy2[l] * lazy1[n] + lazy2[n];
    lazy1[r] *= lazy1[n];
    lazy2[r] = lazy2[r] * lazy1[n] + lazy2[n];
  }
  lazy1[n] = 1; lazy2[n] = 0;
}