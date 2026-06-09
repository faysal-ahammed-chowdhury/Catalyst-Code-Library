typedef vector<long long> vll;
typedef long double ld;
#define int long long
struct point {
  int x, y;
  point() {}
  point( int x, int y ) { this->x = x; this->y = y; }
  bool operator<( const point &other ) {
    if ( x == other.x ) return y < other.y;
    return x < other.x;
  }
};
int crossProduct( point &a, point &b, point &c ) {
  return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}
vector<point> hull( vector<point> a ) {
  vector<point> v = a;
  sort(v.begin(), v.end());
  vector<point> lower, upper;
  for ( auto& p : v ) {
    while ( lower.size() >= 2 && crossProduct(lower[lower.size() - 2], lower.back(), p) < 0 ) // <= for coleniar
      lower.pop_back();
    lower.push_back(p);
  }
  for ( int i = v.size() - 1; i >= 0; i-- ) {
    point p = v[i];
    while ( upper.size() >= 2 && crossProduct(upper[upper.size() - 2], upper.back(), p) < 0 ) // <= for coleniar
      upper.pop_back();
    upper.push_back(p);
  }
  lower.pop_back();
  upper.pop_back();
  lower.insert(lower.end(), upper.begin(), upper.end());
  return lower;
}
void senritsu() {
  int n; cin >> n;
  vector<point> a(n); for ( int i = 0; i < n; i++ ) cin >> a[i].x >> a[i].y;
  a = hull(a);
  n = a.size();
  cout << n << endl;
  for ( auto c : a ) cout << c.x << ' ' << c.y << endl;
}