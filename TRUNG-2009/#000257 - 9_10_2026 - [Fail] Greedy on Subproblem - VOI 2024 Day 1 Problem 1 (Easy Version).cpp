#include <bits/stdc++.h>
using namespace std;
#define _debug 1

/*
Cho mot grid NxN va M point. Co the xay 2 thanh bao phu 1 hang va 1 cot.
Moi point co 1 trong so, tinh max tong trong so cua tat ca cac point nam tren it nhat 1 thanh.
Moi point chi tinh mot lan.
Co Q query, moi query thay doi trong so cua point index i thanh w
Cac query ap dung len trang thai ban dau.

Test co dang:
N M Q
M dong: X Y W
Q dong: I W

1 <= N <= 1e3
1 <= M, Q <= 1e6
1 <= W <= 1e9

*/

const int maxn = 1e3 + 5;
long long A[maxn][maxn];
int n, m, q;
struct POINT {
  int x, y;
  long long w;
} point[maxn];

long long sum_x[maxn];
long long sum_y[maxn];
void proc(int index, const long long& val) {
  auto [x, y, w] = point[index];
  long long temp_x = sum_x[x] - w + val;
  long long temp_y = sum_y[y] - w + val;
  long long temp_w = val;
  swap(temp_x, sum_x[x]);
  swap(temp_y, sum_y[y]);
  swap(temp_w, point[index].w);

  #if _debug == 1
  long long temp_A = val;
  swap(A[x][y], temp_A);

  cout << index << ' ' << val << '\n';
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      cout << A[i][j] << ' ';
    } cout << '\n';
  }

  swap(A[x][y], temp_A);
  #endif // _debug

  long long best = 0;
  for (int i = 1; i <= m; i++) {
    best = max(best, sum_x[ point[i].x ] + sum_y[ point[i].y ] - point[i].w);
  }
  cout << best << '\n';

  swap(temp_x, sum_x[x]);
  swap(temp_y, sum_y[y]);
  swap(temp_w, point[index].w);

  #if _debug == 1
  cout << '\n';
  #endif // _debug

}

int main() {
  cin.tie(0)->sync_with_stdio(0);

#if _debug == 1
  freopen("input.inp", "r", stdin);
#else
  freopen("input.inp", "r", stdin);
  freopen("output.out", "w", stdout);
#endif // _debug

  cin >> n >> m >> q;
  for (int i = 1; i <= m; i++) {
    int x, y;
    long long w;
    cin >> x >> y >> w;
    A[x][y] = w;
    point[i] = {x, y, w};
    sum_x[x] += w;
    sum_y[y] += w;
  }

#if _debug == 1
  for (int i = 1; i <= m; i++) {
    cout << point[i].x << ' ' << point[i].y << ' ' << point[i].w << '\n';
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      cout << A[i][j] << ' ';
    }
    cout << '\n';
  }
  cout << '\n';
#endif

  for (int i = 1; i <= q; i++) {
    int index;
    long long val;
    cin >> index >> val;
    proc(index, val);
  }

}
