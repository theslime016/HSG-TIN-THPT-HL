#include <bits/stdc++.h>
using namespace std;

typedef __int128_t int128;
typedef __uint128_t uint128;

void read(int128 &val) {
  val = 0;
  int c;

  while ((c = cin.get()) != EOF && isspace(c)) {
  }

  if (c == EOF || !isdigit(c)) {
    return;
  }

  while (c != EOF && isdigit(c)) {
    val = val * 10 + (c - '0');
    c = cin.get();
  }

  return;
}
int128 binpow(int128 a, int128 d, int128 n) {
  int128 res = 1;
  a %= n;
  while (d > 0) {
    if (d & 1)
      res = res * a % n;
    a = a * a % n;
    d >>= 1;
  }
  return res;
}

bool composite(int128 a, int s, int128 d, int128 n) {
  a = binpow(a, d, n);
  if (a == n - 1 || a == 1)
    return false;

  for (int r = 1; r < s; r++) {
    a = a * a % n;
    if (a == n - 1)
      return false;
  }
  return true;
}

bool f(int128 n) {
  if (n < 2)
    return false;
  if (n == 2 || n == 3)
    return true;
  if (n % 2 == 0)
    return false;

  static int base[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};
  int s = 0;
  int128 d = n - 1;
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
int128 g(long long t, long long s, int128 mod) {
  return (((int128)t * t + s) % mod);
}
const long long mod = 1e9 + 7;
long long pollard_rho_floyd(int128 n) {
  if (n % 2 == 0)
    return 2;
  while (true) {
    long long x, y;
    x = y = 2;
    long long d = 1;
    long long c = uniform_int_distribution<long long>(1, mod)(rng);
    while (d == 1) {
      x = g(x, c, n);
      y = g(g(y, c, n), c, n);
      d = __gcd(x > y ? (int128)(x - y) : (int128)(y - x), n);
    }
    if (d != n)
      return d;
  }
}

vector<int128> pf;
void solve(int128 n) {
  if (n == 1)
    return;
  if (f(n)) {
    pf.push_back(n);
    return;
  }
  int128 q = pollard_rho_floyd(n);
  solve(q);
  solve(n / q);
  return;
}

int buff[32];
void print(int128 a) {
  int pos = 0;
  for (; pos < 30 && a > 0; pos++) {
    buff[pos] = a % 10;
    a /= 10;
  }
  while (pos--)
    cout << buff[pos];
  return;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int128 n;
  pf.reserve(100);
  for (int i = 0; i <= 10; i++) {
    read(n);
    if (n == 0)
      return 0;

    pf.clear();
    solve(n);
    sort(pf.begin(), pf.end());
    pf.push_back(0);
    long long last = -1;
    int exp = 0;
    for (long long a : pf) {
      if (a != last) {
        if (last != -1) {
          print(last);
          cout << '^';
          print(exp);
          cout << ' ';
        }
        last = a;
        exp = 1;
      } else {
        exp++;
      }
    }
    cout << '\n';
  }

  return 0;
}
