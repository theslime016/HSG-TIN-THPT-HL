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

const int maxn = 1e5 + 5;
int n, k;

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
POINT point[maxn];
vector<POINT> hull;
int get_pos(const POINT& p) {
  if (hull.size() <= 2) return 0;
  long long d1 = get_det(hull[1] - hull[0], p - hull[1]);
  long long d2 = get_det(hull[0] - hull.back(), p - hull[0];
  if (d1 < 0 || d2 < 0) return 0;
  if (d1 == 0 || d2 == 0) return 2;

  POINT v1 = p - hull[0];

  int l = 1, r = hull.size() - 1;
  while (r - l + 1 > 2) {
    int mid = (l + r) >> 1;

    POINT v2 = hull[mid] - hull[0];
    long long det = get_det(v2, v1);
    if (det <= 0) {
      r = mid;
    } else {
      l = mid;
    }
  }

  long long det = get_det(hull[r] - hull[l], p - hull[r]);
  if (det < 0) return 0;
  else if (det > 0) return 1;
  else return 2;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);

#if _debug == 1
  freopen("input.inp", "r", stdin);

#elif _debug == 2
  freopen("input.inp", "r", stdin);

#else

#endif // _debug

  cin >> n;
  for (int i = 1; i <= n; i++)
    cin >> point[i].x >> point[i].y;

  if (n <= 2) {
    cout << 0;
    return 0;
  }

  sort(point + 1, point + n + 1, [&](const POINT& a, const POINT& b) {
    if (a.x != b.x)
      return a.x < b.x;
    else
      return a.y < b.y;
  });

  #if _debug == 1
  for (int i = 1; i <= n; i++) {
    debug(i, point[i].x, point[i].y);
  }
  newline;
  #endif // _debug

  hull.reserve(n);
  hull.push_back(point[1]);
  for (int i = 2; i <= n; i++) {
    while (hull.size() >= 2) {
      POINT p1 = hull[hull.size() - 2];
      POINT p2 = hull[hull.size() - 1];

      long long det = get_det(p2 - p1, point[i] - p2);
      if (det <= 0) hull.pop_back();
      else break;
    }
    hull.push_back(point[i]);
  }
  int lower_hull_cnt = hull.size();
  for (int i = n - 1; i >= 1; i--) {
    while (hull.size() >= lower_hull_cnt + 1) {
      POINT p1 = hull[hull.size() - 2];
      POINT p2 = hull[hull.size() - 1];

      long long det = get_det(p2 - p1, point[i] - p2);
      if (det <= 0) hull.pop_back();
      else break;
    }
    hull.push_back(point[i]);
  }
  hull.pop_back();

  cin >> k;
  int res = 0;
  for (int i = 1; i <= k; i++) {
    POINT p;
    cin >> p.x >> p.y;
    res += get_pos(p) > 0;
  }
  cout << res;

}
