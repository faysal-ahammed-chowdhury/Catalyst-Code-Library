typedef vector<long long> vll;
typedef long double ld;
#define int long long
struct point {
  ld x, y;
  point() {}
  point( ld x, ld y ) { this->x = x; this->y = y; }
  bool operator<( const point &other ) {
    if ( x == other.x ) return y < other.y;
    return x < other.x;
  }
  bool operator==( const point &other ) {
    return ( x == other.x && y == other.y );
  }
  bool operator!=( const point &other ) {
    return ( x != other.x || y != other.y );
  }
  point operator-( const point &other ) {
    return {x - other.x, y - other.y};
  }
};
ld crossProduct( point &a, point &b, point &c ) {
  return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}
ld crossProduct( point &a, point &b ) {
  return a.x * b.y - a.y * b.x;
}
bool inside( point &a, point &b, point &c ) {
  return crossProduct(a, b, c) >= 0;
}
bool intersection( point &a, point &b, point &c, point &d, point &ans ) { // 2 line intersection point
  point ab = b - a;
  point cd = d - c;
  ld det = crossProduct( ab, cd );
  if ( det == 0 ) return false; // parallel or collinear
  ld z1 = crossProduct( a, b );
  ld z2 = crossProduct( c, d );
  ans.x = (ld)(z1 * (c.x - d.x) - z2 * (a.x - b.x)) / det;
  ans.y = (ld)(z1 * (c.y - d.y) - z2 * (a.y - b.y)) / det;
  return true;
}
vector<point> innerhull( vector<point> a, vector<point> b ) {
  int n = a.size();
  vector<point> ans = b;
  for ( int i = 0; i < n; i++ ) {
    point x = a[i], y = a[(i + 1) % n];
    vector<point> temp = ans; ans.clear();
    int m = temp.size();
    if ( m == 0 ) break;
    for ( int j = 0; j < m; j++ ) {
      point p = temp[j], q = temp[(j + 1) % m];
      int pIn = inside(x, y, p);
      int qIn = inside(x, y, q);
      if ( pIn ) ans.push_back(p);
      if ( pIn != qIn ) {
        point cur;
        if ( intersection(x, y, p, q, cur) ) {
          ans.push_back(cur);
        }
      }
    }
    if ( !ans.empty() ) {
      vector<point> temp;
      temp.push_back(ans[0]);
      for ( int j = 1; j < ans.size(); j++ ) {
        if ( ans[j] != ans[j - 1]  ) {
          temp.push_back(ans[j]);
        }
      }
      ans = temp;
    }
  }
  return ans;
}
ld areaOfPolygon( vector<point> a ) {
  if ( a.size() < 3 ) return 0.0;
  a.push_back(a[0]);
  int n = a.size();
  ld ans = 0;
  for ( int i = 0; i < n - 1; i++ ) {
    ans += a[i].x * a[i + 1].y;
    ans -= a[i].y * a[i + 1].x;
  }
  if ( ans < 0 ) ans = -ans;
  return ans / 2.0;
}
void senritsu() {
  int n, m; cin >> n >> m;
  vector<point> a(n), b(m);
  for ( int i = 0; i < n; i++ ) {
    cin >> a[i].x >> a[i].y;
  }
  for ( int i = 0; i < m; i++ ) {
    cin >> b[i].x >> b[i].y;
  }
  vector<point> in = innerhull(a, b);
  cout << fixed << setprecision(4) << areaOfPolygon(in) << endl;
}
