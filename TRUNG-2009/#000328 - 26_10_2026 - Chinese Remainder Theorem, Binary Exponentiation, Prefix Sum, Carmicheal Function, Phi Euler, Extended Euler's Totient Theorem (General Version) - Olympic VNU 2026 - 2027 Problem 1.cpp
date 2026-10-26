#include <bits/stdc++.h>
using namespace std;

#if defined(__has_include) && __has_include("slime_debug_016.h")
#include "slime_debug_016.h"

#else
#define _debug 0

#endif // defined

///
#if _debug
#define debug(x) cerr << #x << ':' << (x) << ' ';
#define newline cerr << '\n';

#else
#define debug(x) 42
#define newline 42

#endif // _debug

const long long mod = 10;

long long lcm(long long a, long long b) {
  return (a / __gcd(a, b)) * b;
}

long long binary_exp(long long base, long long exp, long long m) {
  long long res = 1;
  while (exp > 0) {
    if (exp & 1) res = (res * base) % m;
    base = (base * base) % m;
    exp >>= 1;
  }
  return res;
}

long long get_phi(long long n) {
  long long res = n;
  for (int p = 2; p * p <= n; p++) {
    if (n%p == 0) {
      while (n % p == 0) n /= p;
      res -= res / p;
    }
  }
  if (n > 1) res -= res / n;
  return res;
}

long long tower(long long n, long long h, long long m) {
  if (m == 1) return 0;
  if (h == 1) return n % m;

  long long phi_m = get_phi(m);

  long long exp = tower(n, h - 1, phi_m);

  return binary_exp(n, exp + phi_m, m);
}

long long cycle;
int maxh;

vector<vector<long long>> pref;
vector<long long> total_cycle;

void init() {
  long long temp_phi = mod;
  cycle = mod;
  maxh = 1;

  while (temp_phi > 1) {
    temp_phi = get_phi(temp_phi);
    cycle = lcm(cycle, temp_phi);
    maxh++;
  }

  pref.assign(maxh + 1, vector<long long>(cycle + 1, 0));
  total_cycle.assign(maxh + 1, 0);

  for (int h = 1; h <= maxh; h++) {
    for (int i = 1; i <= cycle; i++) {
      pref[h][i] = pref[h][i - 1] + tower(i, h, mod);
    }
    total_cycle[h] = pref[h][cycle];
  }
}

long long get_sum(long long x, long long h) {
  if (x <= 0) return 0;
  long long q = x / cycle;
  long long r = x % cycle;
  return q * total_cycle[h] + pref[h][r];
}


int main() {
  cin.tie(0)->sync_with_stdio(0);

#if _debug
  freopen("input.inp", "r", stdin);

#else
  freopen("THAP.INP", "r", stdin);
  freopen("THAP.OUT", "w", stdout);

#endif // _debug

  init();

  int q;
  cin >> q;
  while (q--) {
    long long l, r;
    long long h;
    cin >> l >> r >> h;

    h = h >= maxh ? maxh : h;
    cout << get_sum(r, h) - get_sum(l - 1, h) << '\n';
  }

}
