#include <bits/stdc++.h>
using namespace std;

typedef __int128_t int128;
typedef __uint128_t uint128;

long long binpow(long long a, long long d, long long n) {
  long long res = 1;
  a %= n;
  while (d > 0) {
    if (d & 1)
      res = (int128)res * a % n;
    a = (int128)a * a % n;
    d >>= 1;
  }
  return res;
}

bool composite(long long a, int s, long long d, long long n) {
  a = binpow(a, d, n);
  if (a == n - 1 || a == 1)
    return false;

  for (int r = 1; r < s; r++) {
    a = (int128)a * a % n;
    if (a == n - 1)
      return false;
  }
  return true;
}

bool f(long long n) {
  if (n < 2)
    return false;
  if (n == 2 || n == 3)
    return true;
  if (n % 2 == 0)
    return false;

  static int base[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};
  int s = 0;
  long long d = n - 1;
  while (!(d & 1)) {
    d >>= 1;
    s++;
  }
  for (int a : base) {
    if (n == a)
      return true;
    if (composite(a, s, d, n))
      return false;
  }
  return true;
}

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
long long g(long long t, long long s, long long mod) {
  return (long long)(((int128)t * t + s) % mod);
}
long long pollard_rho_floyd(long long n) {
  if (n % 2 == 0)
    return 2;
  while (true) {
    long long x, y;
    x = y = 2;
    long long d = 1;
    long long c = uniform_int_distribution<long long>(1, n - 1)(rng);
    while (d == 1) {
      x = g(x, c, n);
      y = g(g(y, c, n), c, n);
      d = __gcd(x > y ? x - y : y - x, n);
    }
    if (d != n)
      return d;
  }
}

map<long long, int> pf;
void solve(long long n) {
  if (n == 1)
    return;
  if (f(n)) {
    pf[n]++;
    return;
  }
  long long q = pollard_rho_floyd(n);
  solve(q);
  solve(n / q);
  return;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  long long n;
  for (int i = 0; i <= 10; i++) {
    cin >> n;
    if (n == 0)
      return 0;

    pf.clear();
    solve(n);
    for (auto it = pf.begin(); it != pf.end(); it++) {
      cout << it->first << '^' << it->second << ' ';
    }
    cout << '\n';
  }

  return 0;
}
