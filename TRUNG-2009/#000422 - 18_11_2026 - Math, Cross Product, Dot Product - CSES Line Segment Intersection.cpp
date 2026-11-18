#include <bits/stdc++.h>
using namespace std;

#define _debug 0

struct POINT {
  long long x, y;
  POINT() = default;
  POINT(long long _x, long long _y) {
    x = _x;
    y = _y;
  }

  POINT operator+(const POINT& other) const {
    POINT res;
    res.x = x + other.x;
    res.y = y + other.y;
    return res;
  }
  POINT operator-(const POINT& other) const {
    POINT res;
    res.x = x - other.x;
    res.y = y - other.y;
    return res;
  }

  friend long long square_dist(const POINT& v) {
    return v.x * v.x + v.y * v.y;
  }

  friend long long get_dot(const POINT& a, const POINT& b) {
    return a.x * b.x + a.y * b.y;
  }

  friend long long get_det(const POINT& a, const POINT& b) {
    return a.x * b.y - a.y * b.x;
  }
};

int main() {
  cin.tie(0)->sync_with_stdio(0);

  #if _debug == 1
  freopen("input.inp", "r", stdin);

  #else

  #endif // _debug

  int t;
  cin >> t;

  auto on_bound = [](long long a, long long b, long long c, long long d) {
    if (a > b) swap(a, b);
    if (c > d) swap(c, d);
    return max(a, c) <= min(b, d);
  };

  auto get_sign = [](long long x) {
    if (x > 0) return 1;
    else if (x < 0) return -1;
    else return 0;
  };

  while (t--) {
    POINT a, b, c, d;
    cin >> a.x >> a.y >> b.x >> b.y;
    cin >> c.x >> c.y >> d.x >> d.y;

    if (!on_bound(a.x, b.x, c.x, d.x) || !on_bound(a.y, b.y, c.y, d.y)) {
      cout << "NO" << '\n';
      continue;
    }

    int z1 = get_sign(get_det(b - a, c - a));
    int z2 = get_sign(get_det(b - a, d - a));

    int z3 = get_sign(get_det(d - c, a - c));
    int z4 = get_sign(get_det(d - c, b - c));

    if (z1 * z2 <= 0 && z3 * z4 <= 0) {
      cout << "YES" << '\n';
    } else {
      cout << "NO" << '\n';
    }
  }

}
