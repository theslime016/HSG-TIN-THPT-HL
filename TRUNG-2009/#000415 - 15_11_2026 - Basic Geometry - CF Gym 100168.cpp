#include <bits/stdc++.h>
using namespace std;

#define _debug 0

struct POINT {
  long long x, y;

  POINT operator-(const POINT& other) {
    POINT res;
    res.x = x - other.x;
    res.y = y - other.y;
    return res;
  }

  void operator+(const POINT& other) {
    POINT res;
    res.x = x + other.x;
    res.y = y + other.y;
  }

  long double get_len() {
    return sqrt(x*x + y*y);
  }

  friend long long dot_product(const POINT& a, const POINT& b) {
    return a.x * b.x + a.y * b.y;
  }

  friend long long cross_product(const POINT& a, const POINT& b) {
    return a.x * b.y - a.y * b.x;
  }
};

using VECTOR = POINT;

int main() {
  cin.tie(0)->sync_with_stdio(0);

#if _debug == 1
  freopen("input.inp", "r", stdin);

#else
  freopen("distance4.in", "r", stdin);
  freopen("distance4.out", "w", stdout);

#endif // _debug

  POINT a, b, c;
  cin >> c.x >> c.y;
  cin >> a.x >> a.y >> b.x >> b.y;

  VECTOR AB = b - a;
  VECTOR AC = c - a;

  VECTOR BA = a - b;
  VECTOR BC = c - b;

  long double res = -1;
  if (dot_product(AB, AC) < 0) {
    res = AC.get_len();
  } else if (dot_product(BA, BC) < 0) {
    res = BC.get_len();
  } else {
    long double up = abs(cross_product(AB, AC));
    long double down = AB.get_len();
    res = up / down;
  }

  cout << fixed << setprecision(6) << res;
}
