bool cmp(pair<int, int> a, pair<int, int> b) { // for vector, arr,..
  if (a.first != b.first) return a.first > b.first;
  return a.second < b.second; // must return false for equal elements
}
struct cmp { // for set, map, pq,..
  bool operator()(const int& a, const int&b) const {
    return a > b;
  }
};