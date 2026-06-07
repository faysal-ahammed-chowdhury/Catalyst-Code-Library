// returns nCr modulo mod where mod is a prime
// Complexity: ?
ll Lucas(ll n, ll r) {
  if (r < 0 || r > n) return 0;
  if (r == 0 || r == n) return 1;
  if (n >= MOD) {
    return (Lucas(n / MOD, r / MOD) % MOD * Lucas(n % MOD, r % MOD) % MOD) % MOD;
  }
  return (((fact[n] * invFact[r]) % MOD) * invFact[n - r]) % MOD;
}