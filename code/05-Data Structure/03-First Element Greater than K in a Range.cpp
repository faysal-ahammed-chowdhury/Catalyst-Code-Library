// tree[n] = max in range
int get_first(int n, int b, int e, int i, int j, int x) { // return index
  push(n, b, e);
  if (b > j || e < i) return -1;
  if (tree[n] <= x) return -1;
  if (b == e) return b;
  int mid = (b + e) >> 1, l = n << 1, r = l + 1;
  int left = get_first(l, b, mid, i, j, x);
  if (left != -1) return left;
  return get_first(r, mid + 1, e, i , j, x);
}