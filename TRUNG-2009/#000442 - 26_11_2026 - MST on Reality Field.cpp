#include <bits/stdc++.h>
using namespace std;

/**
R. Kết nối
giới hạn thời gian mỗi test: 0.5 seconds
giới hạn bộ nhớ mỗi test: 256 megabytes

Sau khi xây dựng nhiều khu văn phòng hiện đại, công ty VT đang triển khai lắp đặt hệ thống truyền tin nội bộ cho các khu văn phòng này.

Công ty VT có n khu văn phòng được đặt tại thành phố X. Các khu văn phòng được đánh số từ 1 đến n. Bản đồ thành phố X được mô phỏng trên mặt phẳng toạ độ Descartes và vị trí của n khu văn phòng lần lượt là n điểm với toạ độ (x_1, y_1), (x_2, y_2), ..., (x_n, y_n). Để xây dựng mạng liên lạc nội bộ cho các khu văn phòng này, công ty VT cần nhắc sử dụng hai phương thức truyền tin: mạng cáp quang và mạng không dây.

Theo đó, công ty có thể lắp đặt một số đường dây cáp quang. Mỗi đường dây sẽ nối hai khu văn phòng với nhau. Công ty dự tính rằng, chi phí lắp đặt cáp quang nối hai khu văn phòng i và j là c × d(i, j), với d(i, j) là khoảng cách Euclid giữa hai điểm (x_i, y_i) và (x_j, y_j), và c là hệ số chi phí lắp đặt cáp quang. Đường cáp quang này cho phép việc truyền tin giữa hai khu văn phòng i và j.

Ngoài ra, công ty có thể lắp đặt một số trạm thu phát sóng ở một số khu văn phòng. Chi phí lắp đặt một trạm thu phát sóng tại mỗi khu văn phòng là giá trị cố định w. Hai khu văn phòng có thể truyền tin trực tiếp cho nhau thông qua mạng không dây nếu tại cả hai khu này đều có trạm thu phát sóng.

Công ty VT muốn lên kế hoạch lắp đặt các đường dây cáp quang và các trạm thu phát sóng sao cho mỗi khu văn phòng có thể truyền tin trực tiếp hoặc gián tiếp tới tất cả n - 1 khu văn phòng còn lại; đồng thời tổng chi phí lắp đặt là nhỏ nhất. Hai khu văn phòng i và j có thể truyền tin (trực tiếp hoặc gián tiếp) cho nhau nếu ít nhất một trong ba điều kiện dưới đây được thoả mãn:

- Đường dây cáp quang nối hai khu văn phòng i và j được xây dựng.
- Cả hai khu văn phòng i và j đều được lắp trạm thu phát sóng.
- Tồn tại một khu văn phòng k sao cho đồng thời có thể truyền tin giữa hai khu văn phòng i và k, lại vừa có thể truyền tin giữa hai khu văn phòng k và j.

Hãy giúp công ty VT tính tổng chi phí lắp đặt nhỏ nhất.

Đầu vào
Dòng đầu tiên chứa số nguyên n (1 ≤ n ≤ 150) — số khu văn phòng của công ty VT tại thành phố X.

Trong n dòng tiếp theo, dòng thứ i chứa hai số nguyên x_i và y_i (0 ≤ x_i, y_i ≤ 10^6) thể hiện vị trí của khu văn phòng thứ i.

Dòng cuối cùng chứa hai số thực w và c (0 ≤ w ≤ 10^7, 0 < c ≤ 3) lần lượt là chi phí lắp đặt một trạm thu phát sóng và hệ số chi phí lắp đặt cáp quang. Các số thực được cho với không quá 7 chữ số ở phần thập phân.

Đầu ra
In ra một số thực duy nhất là giá trị nhỏ nhất của tổng chi phí lắp đặt. Đáp án của bạn được chấp nhận nếu sai khác không quá 10^-6 so với đáp án của ban giám khảo. Nói cách khác, gọi đáp án của ban giám khảo là j và đáp án của bạn là p, đáp án của bạn được chấp nhận khi và chỉ khi |j-p| / max(1,|j|) ≤ 10^-6.

Ví dụ

input
4
0 0
0 100
400 0
400 100
150 1.0

output
500.000000000

input
10
798 126
915 25
797 402
463 45
895 841
523 762
959 982
702 605
235 616
523 78
10000000 1.66

output
3358.234405323

input
5
0 0
0 100
400 0
400 100
2000 2000
500 1

output
1600.000000000

input
8
0 0
100 100
200 200
300 300
400 400
2000 2000
2100 2100
2200 2200
200.0000000 0.5000000

output
824.264068712

Ghi chú
Trong ví dụ thứ nhất, phương án tối ưu cho công ty VT là xây dựng đường dây cáp quang nối hai khu văn phòng 1 và 2, xây dựng đường dây cáp quang nối hai khu văn phòng 3 và 4; sau đó lắp đặt hai trạm thu phát sóng ở các khu văn phòng 1 và 3.
**/

#define _debug 0

#if _debug == 1
void logout() {
  cerr << endl;
}
template<typename H, typename... T>
void logout(H h, T... t) {
  cerr << h << ", ";
  logout(t...);
}
#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:" << endl, logout(__VA_ARGS__)
#define debugtitle cerr << __PRETTY_FUNCTION__ << " line: " << __LINE__ << endl
#define newline cerr << endl

#else
#define debug(...) (void(0))
#define debugtitle (void(0))
#define newline (void(0))

#endif // _debug

const int maxn = 155;
const int maxedge = 1e5 + 5;
int n;
long double w, c;

pair<int, int> task[maxn]; /// x - y

struct EDGE {
  int a, b;
  long double cost;
};
vector<EDGE> edge;

struct DSU {
  int n;
  long double total_cost;
  int data[maxn];
  int bucket[maxn];

  void init(int _n) {
    n = _n;
    total_cost = 0;
    iota(data, data + maxn, 0);
    fill_n(bucket, maxn, 1);
  }

  int fnd(int index) {
    if (data[index] == index)
      return index;
    return data[index] = fnd(data[index]);
  }

  void make_union(const EDGE& x) {
    int a = fnd(x.a);
    int b = fnd(x.b);
    if (a != b) {
      if (bucket[a] < bucket[b])
        swap(a, b);
      bucket[a] += bucket[b];
      data[b] = a;
      total_cost += x.cost;
    }
  }
} dsu;

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
    cin >> task[i].first >> task[i].second;
  }
  cin >> w >> c;

  for (int i = 1; i <= n; i++) {
    edge.push_back({i, n + 1, w});
    for (int j = i + 1; j <= n; j++) {
      long double delta_x = task[j].first - task[i].first;
      long double delta_y = task[j].second - task[i].second;
      edge.push_back({i, j, c * hypot(delta_x, delta_y)});
    }
  }

  sort(edge.begin(), edge.end(), [&](const EDGE& x, const EDGE& y) {
    return x.cost < y.cost;
  });

  #if _debug == 1
  cerr << fixed << setprecision(7);
  for (const EDGE& x : edge) {
    debug(x.a, x.b, x.cost);
  }
  newline;
  #endif // _debug

  dsu.init(n + 1);
  for (const EDGE& x : edge) {
    dsu.make_union(x);
  }
  long double total_case = dsu.total_cost;

  dsu.init(n);
  for (const EDGE& x : edge) {
    if (x.a != n + 1 && x.b != n + 1) {
      dsu.make_union(x);
    }
  }
  long double fiber_case = dsu.total_cost;

  cout << fixed << setprecision(7) << min(total_case, fiber_case);
}
