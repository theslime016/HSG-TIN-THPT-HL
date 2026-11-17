#include <bits/stdc++.h>
using namespace std;

#define _debug 0

#if _debug == 1
void log_out() {
  cerr << endl;
}
template<typename H, typename... T>
void log_out(H h, T... t) {
  cerr << h << ", ";
  log_out(t...);
}
#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:" << endl, log_out(__VA_ARGS__)
#define debug_title cerr << __PRETTY_FUNCTION__ << " line: " << __LINE__ << endl
#define newline cerr << endl

#else
#define debug(...) (void(0))
#define debug_title (void(0))
#define newline (void(0))

#endif // _debug

const int maxn = 2e5 + 5;
int n;

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

  friend long long square_dist(const POINT& a, const POINT& b) {
    long long left = a.x - b.x;
    long long right = a.y - b.y;
    return left * left + right * right;
  }

  friend long long get_dot(const POINT& a, const POINT& b) {
    return a.x * b.x + a.y * b.y;
  }

  friend long long get_det(const POINT& a, const POINT& b) {
    return a.x * b.y - a.y * b.x;
  }
};

POINT point[maxn];
POINT hull[maxn];
int hull_ptr;

int main() {
  cin.tie(0)->sync_with_stdio(0);

#if _debug == 1
  freopen("input.inp", "r", stdin);

#elif _debug == 2
  freopen("input.inp", "r", stdin);

#else

#endif // _debug

  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> point[i].x >> point[i].y;
  }
  sort(point + 1, point + n + 1, [&](const POINT& a, const POINT& b) {
    if (a.x != b.x)
      return a.x < b.x;
    else
      return a.y < b.y;
  });

#if _debug == 1
  cerr << "point: " << endl;
  for (int i = 1; i <= n; i++) {
    debug(i, point[i].x, point[i].y);
  }
#endif // _debug

  hull[++hull_ptr] = point[1];
  for (int i = 2; i <= n; i++) {
    while (hull_ptr >= 2) {
      POINT h1 = hull[hull_ptr-1];
      POINT h2 = hull[hull_ptr];
      long long det = get_det(h2 - h1, point[i] - h2);

      if (det > 0)
        hull_ptr--;
      else
        break;
    }
    hull[++hull_ptr] = point[i];
  }

  int lower_hull_cnt = hull_ptr;
  for (int i = n - 1; i >= 1; i--) {
    while (hull_ptr >= lower_hull_cnt + 1) {
      POINT h1 = hull[hull_ptr-1];
      POINT h2 = hull[hull_ptr];

      long long det = get_det(h2 - h1, point[i] - h2);
      if (det > 0)
        hull_ptr--;
      else
        break;
    }
    hull[++hull_ptr] = point[i];
  }
  hull_ptr--;

  cout << hull_ptr << '\n';
  for (int i = 1; i <= hull_ptr; i++) {
    cout << hull[i].x << ' ' << hull[i].y << '\n';
  }
}
