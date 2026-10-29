#include <bits/stdc++.h>
using namespace std;

#if defined(__has_include) && __has_include("slime_debug_016.h")
#include "slime_debug_016.h"

#else
#define _debug 0

#endif // defined

/// DEBUG MACRO
#if _debug == 1
#define debug(x) cerr << #x << ':' << (x) << ' ';
#define newline cerr << '\n';

#else
#define debug(x) 42
#define newline 42

#endif // _debug

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

const int maxn = 2e5 + 5;
const int maxval = 1e6 + 5;
int lpf[maxval];
long long prime_hash[maxval];

long long A_hash[maxn];
long long pref_hash[maxn];

long long f(long long x) {
  return x * rng();
}

int main() {
  cin.tie(0)->sync_with_stdio(0);

#if _debug == 1
  freopen("input.inp", "r", stdin);

#else

#endif // _debug

  iota(lpf, lpf + maxval, 0);
  for (int i = 2; i < maxval; i++) {
    if (lpf[i] == i) {
      prime_hash[i] = f(rng());
      for (long long j = (long long) i * i; j < maxval; j += i) {
        if (lpf[j] == j) lpf[j] = i;
      }
    }
  }

  int t;
  cin >> t;
  while (t--) {
    int n;
    cin >> n;

    long long res = 0;

    map<long long, int> cnt; // xor hash value - cnt
    for (int i = 1; i <= n; i++) {
      long long x;
      cin >> x;

      A_hash[i] = 0;

      while (x > 1) {
        int parity = 0;
        int val = lpf[x];
        while (x%val == 0 && x > 1) {
          x /= val;
          parity = !parity;
        }
        if (parity) A_hash[i] ^= prime_hash[val];
      }

      pref_hash[i] = pref_hash[i-1] ^ A_hash[i];
      cnt[ pref_hash[i] ]++;

      #if _debug == 1
      debug(i);
      debug(A_hash[i]);
      debug(pref_hash[i]);
      newline;
      for (const auto& x : cnt) {
        debug(x.first);
        debug(x.second);
        newline;
      }
      newline;
      #endif // _debug

    }

    for (int i = 1; i <= n; i++) {
      res += cnt[ A_hash[i] ];
    }

    cout << res << '\n';
  }


}
