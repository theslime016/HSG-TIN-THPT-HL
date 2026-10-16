#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

typedef tree<int, int, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_map;

const int maxn = 2e5 + 5;
int A[maxn], B[maxn];

struct FRACTION {
  long long up, down;

  FRACTION(__int128_t a, __int128_t b) {
    __int128_t d = __gcd(abs(a), abs(b));
    if (b < 0) {
      a = -a;
      b = -b;
    }
    up = a/d;
    down = b/d;
  }

  friend FRACTION operator+(const FRACTION& a, const FRACTION& b) {
    __int128_t up = (__int128_t)a.up * (__int128_t)b.down + b.up * a.down;
    __int128_t down = a.down * b.down;
    return FRACTION(up, down);
  }

  friend FRACTION operator-(const FRACTION& a, const FRACTION& b) {
    __int128_t up = (__int128_t)a.up * b.down - (__int128_t)b.up * a.down;
    __int128_t down = a.down * b.down;
    return FRACTION(up, down);
  }

  friend FRACTION operator*(const FRACTION& a, const FRACTION& b) {
    __int128_t up = (__int128_t)a.up * b.up;
    __int128_t down = (__int128_t)a.down * b.down;
    return FRACTION(up, down);
  }

  friend bool operator<(const FRACTION& a, const FRACTION& b) {
    __int128_t c1 = (__int128_t)a.up * b.down;
    __int128_t c2 = (__int128_t)b.up * a.down;
    return c1 < c2;
  }

  FRACTION& make_abs() {
    if (this->up < 0) this->up = -up;
    if (this->down < 0) this->down = -down;
    return *this;
  }
};

FRACTION calc(const vector<pair<FRACTION, long long>>& point, long long rem, long long total) {
  long long current = 0;
  FRACTION local(0, 1);
  for (const auto& x : point) {
    current += abs(x.second);
    if (current * 2LL >= total) {
      local = x.first;
      break;
    }
  }

  FRACTION lim_up(1, 1);
  FRACTION lim_down(-1, 1);

  if (lim_up < local) local = lim_up;
  if (local < lim_down) local = lim_down;

  FRACTION res(rem, 1);
  res.make_abs();
  for (const auto& x : point) {
    res = res + (FRACTION(x.second, 1) * (local - x.first)).make_abs();
  }
  return res.make_abs();
}

#define _debug 0
int main() {
  cin.tie(0)->sync_with_stdio(0);

#if _debug == 1
  freopen("input.inp", "r", stdin);
#else

#endif // _debug

  int n;
  cin >> n;
  for (int i = 1; i <= n; i++) cin >> A[i];
  for (int i = 1; i <= n; i++) cin >> B[i];

  vector<pair<FRACTION, long long>> point1, point2; // coor - weight
  point1.reserve(n);
  point2.reserve(n);
  long long total1 = 0, total2 = 0;
  long long rem1 = 0, rem2 = 0;
  for (int i = 1; i <= n; i++) {
    if (B[i] == 0) rem1 += abs(A[i]);
    if (B[i] != 0) {
      total1 += abs(B[i]);
      point1.push_back({FRACTION(A[i], B[i]), abs(B[i])});
    }

    if (A[i] == 0) rem2 += abs(B[i]);
    if (A[i] != 0) {
      total2 += abs(A[i]);
      point2.push_back({FRACTION(B[i], A[i]), abs(A[i])});
    }
  }

  sort(point1.begin(), point1.end());
  sort(point2.begin(), point2.end());

  FRACTION res = min(calc(point1, rem1, total1), calc(point2, rem2, total2));
  cout << res.up << ' ' << res.down;
}
