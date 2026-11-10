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

const int maxn = 1e5 + 5;
const int maxcoor = 2e5 + 5;
int n, q;

struct FENWICK {
  int n;
  int data[maxcoor];

  void update(int index, int val) {
    for (; index < maxcoor; index += index & -index) {
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

struct EVENT {
  int x, y;
  int s;
  int index;

  int type;

  friend bool operator<(const EVENT& a, const EVENT& b) {
    if (a.s != b.s)
      return a.s < b.s;
    else
      return a.type < b.type;
  }
};

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
  vector<EVENT> event;
  event.reserve(n + (q << 1));
  for (int i = 1; i <= n; i++) {
    int x, y;
    cin >> x >> y;
    EVENT temp;
    temp.x = x;
    temp.y = y;
    temp.s = x + y;
    temp.index = i;
    temp.type = 2;
    event.push_back(temp);
  }

  for (int i = 1; i <= q; i++) {
    int x, y, d;
    cin >> x >> y >> d;

    EVENT temp;
    temp.x = x;
    temp.y = y;
    temp.s = x + y;
    temp.index = i;
    temp.type = 1;
    event.push_back(temp);

    temp.s = x + y + d;
    temp.type = 3;
    event.push_back(temp);
  }

  sort(event.begin(), event.end());
  FENWICK coor_x, coor_y;
  int total_point = 0;
  for (const auto& a : event) {
    if (a.type == 2) {
      coor_x.update(a.x, 1);
      coor_y.update(a.y, 1);
      total_point++;
    } else {
      int left_point = coor_x.fetch(a.x - 1);
      int right_point = coor_y.fetch(a.y - 1);
      /// f:
      int val = total_point - left_point - right_point;
      if (a.type == 1) query_res[a.index] -= val;
      else if (a.type == 3) query_res[a.index] += val;
    }
  }

  for (int i = 1; i <= q; i++) cout << query_res[i] << '\n';

}
