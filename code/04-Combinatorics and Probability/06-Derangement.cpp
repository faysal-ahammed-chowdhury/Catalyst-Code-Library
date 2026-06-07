// number of combinations such that $a_i != i$ of a permuation $a$
const int N = 1e6 + 100, int p = 1e9 + 7;
ll der[N];
void countDer() {
  der[1] = 0; der[2] = 1;
  for (ll i = 3; i <= N; ++i) {
    der[i] = (i - 1) % p * (der[i - 1] % p + der[i - 2] % p);
    der[i] %= p;
  }
}