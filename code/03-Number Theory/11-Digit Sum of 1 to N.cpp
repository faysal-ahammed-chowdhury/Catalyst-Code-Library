// for n=10, ans = 1+2+...+9+1+0
ll solve(ll n) {
  ll res = 0, p = 1;
  while (n / p > 0) {
    ll left = n / (p * 10);
    ll cur  = (n / p) % 10, right = n % p;
    res += left * 45 * p;
    res += (cur * (cur - 1) / 2) * p;
    res += cur * (right + 1); p *= 10;
  } return res;
}
int totalDigits(int n) {
  if ( n <= 0 ) return 0;
  int p = 1, total = 0;
  for ( int d = 1; d <= 18; d++ ) {
    int L = p, R = min(n, p * 10 - 1);
    if ( R >= L ) total += (R - L + 1) * 1LL * d;
    p *= 10; if ( p > n ) break;
  } return total;
}