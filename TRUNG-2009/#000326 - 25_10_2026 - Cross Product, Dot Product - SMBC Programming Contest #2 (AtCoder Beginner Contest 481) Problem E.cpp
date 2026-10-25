#include <bits/stdc++.h>
using namespace std;

#define _debug 0

#if _debug == 1
#define debug(x) cerr << #x << ':' << (x) << ' ';
#define newline cerr << '\n';

#else
#define debug(x)
#define newline

#endif // _debug

const int maxn = 2e5 + 5;
const long long inf = 1e18;

struct POINT {
  long long x, y;
  int part;

  POINT() = default;
  POINT(long long x, long long y) {
    this->x = x;
    this->y = y;
    if (y >= 0) {
      if (x > 0) part = 1;
      else part = 2;
    } else if (y < 0) {
      if (x <= 0) part = 3;
      else part = 4;
    }
  }

  friend long long dot_product(const POINT& a, const POINT& b) {
    return a.x*b.x + a.y*b.y;
  }

  friend long long cross_product(const POINT& a, const POINT& b) {
    return a.x*b.y - a.y*b.x;
  }

  friend bool operator<(const POINT& a, const POINT& b) {
    if (a.part != b.part) return a.part < b.part;

    long long val = cross_product(a, b);
    if (val != 0) return val > 0;
    else return dot_product(a, a) < dot_product(b, b);
  }

} point[maxn << 1];

int main() {
  cin.tie(0)->sync_with_stdio(0);

#if _debug == 1
  freopen("input.inp", "r", stdin);

#elif _debug == 2
  freopen("input.inp", "r", stdin);

#else

#endif // _debug

  int t;
  cin >> t;
  while (t--) {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
      long long x, y;
      cin >> x >> y;
      point[i] = POINT(x, y);
    }

    sort(point + 1, point + n + 1);
    for (int i = 1; i <= n; i++) {
      point[i + n] = point[i];
    }

    #if _debug == 1

    for (int i = 1; i <= n; i++) {
      debug(i);
      debug(point[i].x);
      debug(point[i].y);
      debug(point[i].part);
      newline;
    }

    #endif // _debug

    int res = 0;
    int ptr1 = 1;
    int ptr2 = 1;
    while (ptr1 <= n) {
      while (ptr2 + 1 <= 2*n && ptr2 - ptr1 + 2 <= n &&
             cross_product(point[ptr1], point[ptr2 + 1]) >= 0) ptr2++;
      res = max(res, ptr2 - ptr1 + 1);
      ptr1++;
    }

    cout << res << '\n';
  }


}
