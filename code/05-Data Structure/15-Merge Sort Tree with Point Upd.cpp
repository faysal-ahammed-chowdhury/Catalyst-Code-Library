struct MST { // merge sort tree
  o_set<array<int, 2>> tree[4 * N]; // greater<T>
  o_set<array<int, 2>> merge(o_set<array<int, 2>> &a, o_set<array<int, 2>> &b) {
    int i = 0, j = 0;
    int n = a.size(), m = b.size();
    o_set<array<int, 2>> ans;
    for (auto x : a) ans.insert(x);
    for (auto x : b) ans.insert(x);
    return ans;
  }
  void build(int n, int b, int e) {
    if (b == e) {
      tree[n].insert({a[b], b});
      return;
    }
    int mid = (b + e) >> 1, l = n << 1, r = l + 1;
    build(l, b, mid);
    build(r, mid + 1, e);
    tree[n] = merge(tree[l], tree[r]);
  }
  void upd(int n, int b, int e, int i, int x) {
    if (b == e) {
      tree[n].erase({a[b], b});
      tree[n].insert({x, b});
      a[b] = x;
      return;
    }
    int mid = (b + e) >> 1, l = n << 1, r = l + 1;
    tree[n].erase({a[i], i});
    tree[n].insert({x, i});
    if (i <= mid) upd(l, b, mid, i, x);
    else upd(r, mid + 1, e, i, x);
  }
  int query(int n, int b, int e, int i, int j, int k) {
    if (b > j || e < i) return 0;
    if (b >= i && e <= j) {
      int idx = tree[n].order_of_key({k, inf});
      return idx;
    }
    int mid = (b + e) >> 1, l = n << 1, r = l + 1;
    int L = query(l, b, mid, i, j, k);
    int R = query(r, mid + 1, e, i, j, k);
    return (L + R);
  }
} mst;