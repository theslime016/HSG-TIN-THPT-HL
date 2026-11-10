#include <bits/stdc++.h>
using namespace std;

/*
TRIQUERY

Trên mặt phẳng tọa độ Oxy cho n điểm có tọa độ nguyên (x1, y1), (x2, y2), …, (xn, yn). Bạn cần trả lời Q truy vấn, mỗi truy vấn cho bởi bộ ba số nguyên (x, y, d) thể hiện yêu cầu đếm số lượng điểm trong số n điểm trên nằm trong tam giác ABC với A(x, y), B(x + d, y) và C(x, y + d). Chú ý: Điểm nằm trên biên cũng được tính là nằm trong tam giác.

Dữ liệu: Nhập từ file văn bản TRIQUERY.INP
- Dòng đầu tiên chứa hai số nguyên dương n, Q (1 ≤ n, Q ≤ 10^5).
- n dòng tiếp theo, dòng thứ i chứa hai số nguyên xi, yi (1 ≤ xi, yi ≤ 2 × 10^5).
- Q dòng tiếp theo, mỗi dòng mô tả một truy vấn gồm ba số nguyên x, y, d với (1 ≤ x, y, d ≤ 2 × 10^5).

Hai số liên tiếp nhau trên một dòng cách nhau bằng khoảng trống.

Kết quả: Ghi ra file văn bản TRIQUERY.OUT
In ra Q dòng, mỗi dòng ghi một số nguyên là kết quả thực hiện một truy vấn (in theo thứ tự các truy vấn xuất hiện trong dữ liệu nhập).

Ràng buộc:
- Subtask 1 (50%): n, Q ≤ 1000.
- Subtask 2 (50%): Không có ràng buộc bổ sung.

Ví dụ:
(Ví dụ trong file PDF bị lỗi trích xuất định dạng, không thể khôi phục chính xác.)
*/

#if defined(__has_include) && __has_include("slime_debug_016.h")
#include "slime_debug_016.h"

#if defined(SLIME_DEBUG_016) && SLIME_DEBUG_016 == 1
#define _debug 1
#else
#define _debug 0
#endif // defined

#else
#define _debug 0

#endif // defined

/// MACRO
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
#define newline cerr << endl

#else
#define debug(...) (void(0))
#define newline (void(0))

#endif // _debug

const int maxn = 2e5 + 5;
int n, q;

struct FENWICK {
  int n;
  vector<int> data;

  FENWICK(int _n) {
    n = _n;
    data.assign(n + 1, 0);
  }

  void update(int index, int val) {
    for (; index <= n; index += index & -index) {
      data[index] += val;
    }
  }

  int fetch(int index) {
    int res = 0;
    for (; index > 0; index -= index & -index) {
      res += data[index];
    }
    return res;
  }
};

struct POINT {
  int x, y;
  int type;
  int index;
  int d;

  friend bool operator<(const POINT& a, const POINT& b) {
    int s1 = a.x + a.y;
    int s2 = b.x + b.y;
    if (s1 != s2) return s1 < s2;
    else return a.type < b.type;
  }
};

int query_intersect[maxn];
int query_res[maxn];

int main() {
  cin.tie(0)->sync_with_stdio(0);

#if _debug == 1
  freopen("input.inp", "r", stdin);

#else
  freopen("triquery.inp", "r", stdin);
  freopen("triquery.out", "w", stdout);

#endif // _debug

  cin >> n >> q;
  vector<POINT> point;
  point.reserve(n + 2 * q);
  for (int i = 1; i <= n; i++) {
    int x, y;
    cin >> x >> y;
    POINT temp;
    temp.x = x;
    temp.y = y;
    temp.type = 2;
    temp.index = i;
    point.push_back(temp);
  }

  for (int i = 1; i <= q; i++) {
    int x, y, d;
    cin >> x >> y >> d;
    POINT temp1;
    temp1.x = x;
    temp1.y = y;
    temp1.type = 1;
    temp1.index = i;
    temp1.d = d;
    point.push_back(temp1);

    POINT temp2;
    temp2.x = x + d;
    temp2.y = y;
    temp2.type = 3;
    temp2.index = i;
    temp2.d = d;
    point.push_back(temp2);
  }

  /// type: 1 -> S1, 2 -> norm, 3 -> S2

  sort(point.begin(), point.end());
  #if _debug == 1
  cerr << "point: " << endl;
  for (const auto& a : point) {
    debug(a.x, a.y, a.type, a.index);
  }
  newline;
  #endif // _debug

  FENWICK coor_x(maxn), coor_y(maxn);
  int total_point = 0;
  for (const auto& a : point) {
    if (a.type == 2) { /// norm
      coor_x.update(a.x, 1);
      coor_y.update(a.y , 1);
      total_point++;
    } else if (a.type == 1) { /// S1
      int left_point = coor_x.fetch(a.x-1);
      int right_point = coor_y.fetch(a.y-1);
      int intersect = left_point + right_point - total_point;
      query_intersect[a.index] = intersect;
      debug(a.type, a.index, left_point, right_point);
    } else if (a.type == 3) { /// S2
      int left_point = coor_x.fetch(a.x-a.d-1);
      int right_point = coor_y.fetch(a.y-1);
      int res = total_point - left_point - right_point + query_intersect[a.index];
      debug(a.type, a.index, total_point, query_intersect[a.index]);

      query_res[a.index] = res;
    }
  }

  for (int i = 1; i <= q; i++) {
    cout << query_res[i] << '\n';
  }

  #if _debug == 1
  newline;
  debug(total_point);
  newline;

  for (int i = 1; i <= q; i++) {
    debug(i, query_intersect[i]);
  }
  #endif // _debug

}
