inline bool better (pair <int, int> P, pair<int, int> Q) { // from AlphaQ
  auto [u, x] = P; auto [v, y] = Q; // $u * 2^x + v * 2^y <= u + v * 2^{(x+y)} --> u <= v * 2 ^ y$
  long long bound = v;
  for (int i = 0; i < y and bound < inf; ++i) bound *= 2;
  return u <= bound;
}