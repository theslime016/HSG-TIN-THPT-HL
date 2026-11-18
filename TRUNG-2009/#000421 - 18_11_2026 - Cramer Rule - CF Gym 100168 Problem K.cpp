#include <bits/stdc++.h>
using namespace std;

#define _debug 0

#if _debug == 1
void log_out() {cerr << endl;}
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

int main() {
  cin.tie(0)->sync_with_stdio(0);

  #if _debug == 1
  freopen("input.inp", "r", stdin);

  #elif _debug == 2
  freopen("input.inp", "r", stdin);

  #else
  freopen("intersec1.in", "r", stdin);
  freopen("intersec1.out", "w", stdout);

  #endif // _debug

  long double a1, b1, c1;
  long double a2, b2, c2;
  cin >> a1 >> b1 >> c1 >> a2 >> b2 >> c2;
  c1 = -c1;
  c2 = -c2;

  auto get_det = [&](long long x1, long long y1, long long x2, long long y2) {
    return x1 * y2 - y1 * x2;
  };
  long double det = get_det(a1, b1, a2, b2);
  long double det_x = get_det(c1, b1, c2, b2);
  long double det_y = get_det(a1, c1, a2, c2);

  long double x = det_x / det;
  long double y = det_y / det;
  cout << fixed << setprecision(6) << x << ' ' << y;
}
