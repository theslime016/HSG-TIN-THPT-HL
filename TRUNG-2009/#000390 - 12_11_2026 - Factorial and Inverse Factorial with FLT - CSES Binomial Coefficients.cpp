#include <bits/stdc++.h>
using namespace std;

#define _debug 0

const int maxn = 1e6 + 5;
const long long mod = 1e9 + 7;
long long fact[maxn], inv_fact[maxn];

long long binary_exp(long long base, long long exp) {
  long long res = 1;
  while (exp > 0) {
    if (exp & 1) {
      res = (res * base) % mod;
    }
    base = (base * base) % mod;
    exp >>= 1;
  }
  return res;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);

#if _debug == 1
  freopen("input.inp", "r", stdin);

#else

#endif // _debug

  fact[0] = 1;
  for (long long x = 1; x < maxn; x++) {
    fact[x] = (fact[x - 1] * x) % mod;
  }

  inv_fact[maxn - 1] = binary_exp(fact[maxn - 1], mod - 2);
  for (long long x = maxn - 2; x >= 0; x--) {
    inv_fact[x] = (inv_fact[x + 1] * (x + 1)) % mod;
  }

  int t;
  cin >> t;
  while (t--) {
    long long a, b;
    cin >> a >> b;
    long long res = fact[a];
    res = (res * inv_fact[b]) % mod;
    res = (res * inv_fact[a - b]) % mod;
    cout << res << '\n';
  }

}
