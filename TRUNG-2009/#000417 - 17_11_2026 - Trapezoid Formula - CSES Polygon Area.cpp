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
#define debugtitle cerr << __PRETTY_FUNCTION__ << " line: " << __LINE__ << endl
#define newline cerr << endl

#else
#define debug(...) (void(0))
#define debugtitle (void(0))
#define newline (void(0))

#endif // _debug


struct POINT {
  long long x, y;

  POINT operator-(const POINT& other) const {
    POINT res;
    res.x = x - other.x;
    res.y = y - other.y;
    return res;
  }

  POINT operator+(const POINT& other) const {
    POINT res;
    res.x = x + other.x;
    res.y = y + other.y;
    return res;
  }

  long long get_slen() {
    return x*x + y*y;
  }

  friend long long dot_product(const POINT& a, const POINT& b) {
    return a.x * b.x + a.y * b.y;
  }

  friend long long cross_product(const POINT& a, const POINT& b) {
    return a.x * b.y - a.y * b.x;
  }

  friend long long get_det(const POINT& o, const POINT& a, const POINT& b) {
    return cross_product(a - o, b - o);
  }
};

using VECTOR = POINT;

const int maxn = 1005;
const long long inf = 1e18;
int n;

POINT point[maxn];

int main() {
  cin.tie(0)->sync_with_stdio(0);

#if _debug == 1
  freopen("input.inp", "r", stdin);

#else

#endif // _debug

  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> point[i].x >> point[i].y;
  }

  long long res = 0;
  for (int i = 1; i < n; i++) {
    res += (point[i].x - point[i+1].x) * (point[i].y + point[i + 1].y);
  }
  res += (point[n].x - point[1].x) * (point[1].y + point[n].y);
  cout << abs(res);
}
