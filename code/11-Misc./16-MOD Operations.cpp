inline ll modAdd(ll a, ll b, ll MOD) {ll res = a + b; res += ((res >> 63) & MOD); if (res >= MOD) res -= MOD; return res;}
inline ll modSub(ll a, ll b, ll MOD) {ll res = a - b; res += ((res >> 63) & MOD); if (res >= MOD) res -= MOD; return res;}
inline ll modMul(ll a, ll b, ll MOD) {a %= MOD; b %= MOD; a += ((a >> 63) & MOD); b += ((b >> 63) & MOD); return (a * b) % MOD; }
inline ll modInverse(ll a, ll MOD) {return modPow(a, MOD - 2, MOD);}
inline ll modDiv(ll a, ll b, ll MOD) {return modMul(a, modInverse(b, MOD), MOD);}
inline ll modMulBigMod(ll a, ll b, ll MOD) {a %= MOD; b %= MOD; a += ((a >> 63) & MOD); b += ((b >> 63) & MOD); return (ll)((__int128)a * b % MOD);}
