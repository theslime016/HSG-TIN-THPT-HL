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

#define _debug 0

long long get_dist(long long a, long long b, long long c, long long d) {
  long long x = (a - c);
  long long y = (b - d);
  return sqrt(x * x + y * y);
}

long long a, b, c, d;
long long make(long long x) {
  long long d1 = get_dist(x, 0, a, b);
  long long d2 = get_dist(x, 0, c, d);
  return d1 + d2;
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
    long long up = (a * a - c * c) + (b * b - d * d);
    long long down = 2 * (a - c);

    long long x = up/down;
    long long res = min({make(x), make(x + 1), make(x-1)});
    cout << res << '\n';
  }
}
