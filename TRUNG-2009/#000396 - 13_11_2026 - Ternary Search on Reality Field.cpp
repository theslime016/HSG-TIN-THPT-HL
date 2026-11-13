#include <bits/stdc++.h>
using namespace std;

/**
File: MINDIST.txt

Bài 1. Khoảng cách

Với hai điểm P(xP, yP), Q(xQ, yQ) trên mặt phẳng Oxy, khoảng cách Euclid giữa hai điểm P, Q được tính theo công thức:
d(P, Q) = sqrt((xP - xQ)^2 + (yP - yQ)^2)

Yêu cầu:
Cho 4 số nguyên là tọa độ hai điểm A(xA, yA), B(xB, yB) và tìm điểm M nằm trên trục Ox để giá trị d(M, A) + d(M, B) đạt giá trị nhỏ nhất.

Dữ liệu: vào từ file MINDIST.INP
Dữ liệu vào gồm nhiều bộ dữ liệu tương ứng với nhiều test. Dòng đầu tiên chứa một số nguyên dương không lớn hơn 20 là số lượng các bộ dữ liệu. Các dòng tiếp theo chứa các bộ dữ liệu.
Mỗi bộ dữ liệu gồm một dòng duy nhất chứa 4 số nguyên xA, yA, xB, yB (-10^6 ≤ xA, yA, xB, yB ≤ 10^6).

Kết quả: Ghi ra file MINDIST.OUT
Với mỗi bộ dữ liệu, ghi ra trên một dòng một số nguyên là phần nguyên của số d(M, A) + d(M, B).

Ví dụ:
MINDIST.INP
1
0 1 2 1

MINDIST.OUT
2
**/

#define _debug 1

const long long inf = 2e6;
long long a, b, c, d;
double get_dist(long long x) {
  double left = sqrt( (a - x) * (a - x) + b * b );
  double right = sqrt( (c - x) * (c - x) + d * d );
  return left + right;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);

#if _debug == 1
  freopen("input.inp", "r", stdin);

#else
  freopen("MINDIST.INP", "r", stdin);
  freopen("MINDIST.OUT", "w", stdout);

#endif // _debug

  int t;
  cin >> t;
  while (t--) {
    cin >> a >> b >> c >> d;

    double l = -inf, r = inf;
    for (int i = 1; i <= 100; i++) {
      double mid1 = l + (r - l)/3.0;
      double mid2 = r - (r - l)/3.0;
      double val1 = get_dist(mid1);
      double val2 = get_dist(mid2);
      if (val1 < val2) {
        r = mid2;
      } else {
        l = mid1;
      }
    }
    long long res = get_dist(l);
    cout << res << '\n';
  }

}
