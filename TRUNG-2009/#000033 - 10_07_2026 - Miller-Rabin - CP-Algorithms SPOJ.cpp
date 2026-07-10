#include <bits/stdc++.h>
using namespace std;

typedef __int128_t int128;
typedef __uint128_t uint128;

long long binpow(long long a, long long d, long long n) {
  long long res = 1;
  a %= n;
  while (d > 0) {
    a = (int128)a * a % n;
    if (d & 1)
      res = (int128)res * a % n;
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

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  long long t, n;
  cin >> t;
  while (t--) {
    cin >> n;
    cout << ((f(n)) ? "YES" : "NO") << '\n';
  }

  return 0;
}
