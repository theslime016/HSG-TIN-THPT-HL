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
#define debug(x)
#define newline

#endif // _debug

const int maxn = 200;
const int maxh = 10;
const long long mod = 10;

long long lcm(long long a, long long b) {
  return (a / __gcd(a, b)) * b;
}

long long binary_exp(long long base, long long exp) {
  long long res = 1;
  while (exp > 0) {
    if (exp & 1) res = (res * base) % mod;
    base = (base * base) % mod;
    exp >>= 1;
  }
  return res;
}


long long pref[maxn][maxh];
long long total[maxh];
long long lpf[maxn];
long long phi[maxn];

void make_lpf() {
  iota(lpf, lpf + maxn, 0LL);
  for (int i = 2; i*i < maxn; i++) {
    if (lpf[i] == i) {
      for (int j = i * i; j < maxn; j+=i) {
        if (lpf[j] == j) lpf[j] = i;
      }
    }
  }
}

void make_phi() {
  iota(phi, phi + maxn, 0);
  phi[0] = phi[1] = 0;
  for (int i = 2; i < maxn; i++) {
    if (phi[i] == i) {
      for (int j = i; j < maxn; j+=i) {
        phi[j] -= phi[j] / i;
      }
    }
  }
}

long long get_phi_prime(long long p) {
  return p - 1;
}

long long get_cycle(long long x) {
  long long res = 1;
  while (x > 1) {
    res = lcm(res, get_phi_prime(lpf[x]));
    x /= lpf[x];
  }
  return res;
}

long long get_T(long long x, long long h, long long cycle_exp) {
  if (h == 1) return x % mod;
  else if (h == 2) return binary_exp(x, x);

  long long exp;
  if (x%2 == 0) exp = cycle_exp;
  else if (x%4 == 1) exp = 1;
  else exp = 3;
  return binary_exp(x, exp);
}

long long get_val(long long x, long long h, long long cycle_base) {
  if (h >= 3) h = 3;
  long long q = x / cycle_base;
  long long r = x % cycle_base;

  return q * total[h] + pref[r][h];
}


int main() {
  cin.tie(0)->sync_with_stdio(0);

#if _debug
  freopen("input.inp", "r", stdin);

#else
  freopen("THAP.INP", "r", stdin);
  freopen("THAP.OUT", "w", stdout);

#endif // _debug

  make_lpf();
  make_phi();
  long long cycle_exp = get_cycle(mod);
  long long cycle_base = lcm(mod, cycle_exp);

  for (int j = 1; j <= 3; j++) {
    for (int i = 1; i <= cycle_base; i++) {
      long long T = get_T(i, j, cycle_exp);
      total[j] += T;
      pref[i][j] = pref[i-1][j] + T;
    }
  }

  int q;
  cin >> q;
  while (q--) {
    long long l, r;
    long long exp;
    cin >> l >> r >> exp;

    cout << get_val(r, h, cycle_base) - get_val(l - 1, h, cycle_base) << '\n';
  }
}
