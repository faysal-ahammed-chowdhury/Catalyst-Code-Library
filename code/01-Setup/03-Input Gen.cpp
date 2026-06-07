mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count()); 
ll get_rand(ll l, ll r) { 
  assert(l <= r);
  return l + rnd() % (r - l + 1);
}