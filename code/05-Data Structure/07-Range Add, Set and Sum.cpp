// Problem: Range Updates and Sums - CSES
struct ST {
  int tree[4 * N];
  pair<int, int> lazy[4 * N]; // val, types
  // lazy[n].first = 0; default for all n
  // lazy[n].second = -1; default for all n
  void push(int n, int b, int e) {
    if (lazy[n].first == 0) return;
    if (lazy[n].second == 1) { // set
      tree[n] = lazy[n].first * (e - b + 1);
    }
    else { // add
      tree[n] += lazy[n].first * (e - b + 1);
    }
    if (b != e) {
      int l = n << 1, r = l + 1;
      if (lazy[l].second == 1) {
        if (lazy[n].second == 1) lazy[l].first = lazy[n].first;
        else lazy[l].first += lazy[n].first;
      }
      else {
        if (lazy[n].second == 1) {
          lazy[l].first = lazy[n].first;
          lazy[l].second = 1;
        }
        else lazy[l].first += lazy[n].first;
      }
      if (lazy[r].second == 1) {
        if (lazy[n].second == 1) lazy[r].first = lazy[n].first;
        else lazy[r].first += lazy[n].first;
      }
      else {
        if (lazy[n].second == 1) {
          lazy[r].first = lazy[n].first;
          lazy[r].second = 1;
        }
        else lazy[r].first += lazy[n].first;
      }
    }
    lazy[n].first = 0; lazy[n].second = -1;
  }
} st;