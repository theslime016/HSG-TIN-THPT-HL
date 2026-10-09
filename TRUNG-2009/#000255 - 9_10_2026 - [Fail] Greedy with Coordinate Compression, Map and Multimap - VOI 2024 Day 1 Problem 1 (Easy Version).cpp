#include <bits/stdc++.h>
using namespace std;

/*
Câu 1. Trạm tiếp sóng viễn thông (TOWER.CPP)

Một khu công nghệ cao được quy hoạch trên một mặt phẳng toạ độ dạng lưới ô vuông kích thước N x N, các hàng đánh số từ 1 đến N từ trên xuống dưới, các cột đánh số từ 1 đến N từ trái sang phải. Khu công nghệ có M máy chủ, máy chủ thứ i (1 <= i <= M) đặt tại ô (R_i, C_i) và có lượng dữ liệu phát ra là W_i đơn vị.

Tập đoàn viễn thông dự định chọn lắp đặt hai tuyến cáp quang chính, mỗi tuyến cáp quang phủ sóng toàn bộ một hàng hoặc một cột của bảng:
- Tuyến thứ nhất phủ trọn vẹn một hàng hoặc một cột.
- Tuyến thứ hai phủ trọn vẹn một hàng hoặc một cột.
- Hai tuyến này phải phân biệt (không được chọn cùng một hàng hoặc cùng một cột).

Một máy chủ được coi là kết nối thành công nếu ô chứa máy chủ đó nằm trên ít nhất một trong hai tuyến cáp đã chọn. Tổng lượng dữ liệu thu thập được là tổng lượng W_i của tất cả các máy chủ kết nối thành công.

Để linh hoạt mở rộng, ban quản lý đưa ra Q đề xuất nâng cấp độc lập. Ở đề xuất thứ j (1 <= j <= Q), máy chủ thứ T_j được nâng cấp dung lượng phát thêm D_j đơn vị (các máy chủ khác giữ nguyên giá trị ban đầu). Sau mỗi đề xuất, cấu hình lại trở về trạng thái gốc.

Yêu cầu: Tính tổng lượng dữ liệu lớn nhất có thể kết nối được với hiện trạng ban đầu và với mỗi phương án trong Q đề xuất nâng cấp.

Dữ liệu vào: Đọc từ file văn bản TOWER.INP:
- Dòng đầu chứa ba số nguyên N, M, Q (2 <= N <= 10^9; 2 <= M <= 10^5; 1 <= Q <= 10^5).
- M dòng tiếp theo, dòng thứ i chứa ba số nguyên R_i, C_i, W_i (1 <= R_i, C_i <= N; 1 <= W_i <= 10^9). Dữ liệu đảm bảo không có hai máy chủ nào đặt cùng một ô.
- Q dòng tiếp theo, dòng thứ j chứa hai số nguyên T_j và D_j (1 <= T_j <= M; 1 <= D_j <= 10^9) mô tả phương án nâng cấp thứ j.

Kết quả: Ghi ra file văn bản TOWER.OUT:
- Dòng đầu tiên ghi một số nguyên là tổng dữ liệu lớn nhất ở trạng thái ban đầu.
- Q dòng tiếp theo, dòng thứ j ghi tổng dữ liệu lớn nhất tương ứng với phương án nâng cấp thứ j.

Ràng buộc:
- Subtask 1 (20% số điểm): N <= 100; M, Q <= 100.
- Subtask 2 (20% số điểm): N <= 2000; M, Q <= 2000.
- Subtask 3 (20% số điểm): Q = 0 hoặc D_j = 0 với mọi j.
- Subtask 4 (20% số điểm): Hai tuyến cáp quang bắt buộc phải gồm: một đường theo hàng và một đường theo cột.
- Subtask 5 (20% số điểm): Không có ràng buộc gì thêm.
*/

const int maxnode = 1e5 + 5;
const long long inf = 1e18;
//const int padding = 131072;

long long sum_x[maxnode];
long long sum_y[maxnode];

struct NODE {
  long long x, y;
  long long w;
  int x_compress;
  int y_compress;
} node[maxnode];

struct KEY {
  long long v1, v2;
  int index;
};

multimap<long long, int> row, col; // sum; index_compress
map<pair<int, int>, long long> occur; // x-y; w
KEY proc_x(int index, long long diff) {
  long long old_val = sum_x[ node[index].x_compress ];
  long long new_val = old_val + diff;
  row.erase(row.find(old_val));
  row.insert({new_val, -1});
  auto it = --row.end();
  KEY res = {(*it).first, (*(--it)).first, (*it).second};
  row.erase(row.find(new_val));
  row.insert({old_val, node[index].x_compress});
  return res;
}

KEY proc_y(int index, long long diff) {
  long long old_val = sum_y[ node[index].y_compress ];
  long long new_val = old_val + diff;
  col.erase(col.find(old_val));
  col.insert({new_val, -1});
  auto it = --col.end();
  KEY res = {(*it).first, (*(--it)).first, (*it).second};
  col.erase(col.find(new_val));
  col.insert({old_val, node[index].y_compress});
  return res;
}

void solve(int index, long long diff) {
  auto [xbest1, xbest2, index1] = proc_x(index, diff);
  auto [ybest1, ybest2, index2] = proc_y(index, diff);
  long long res = -inf;
  res = max({res, xbest1 + xbest2, ybest1 + ybest2});
  if (occur.count({index1, index2})) {
    res = max(res, xbest1 + ybest1 - occur[ {index1, index2}]);
  } else {
    res = max(res, xbest1 + ybest1);
  }
  cout << res << '\n';
}

#define _debug 1
int main() {
  cin.tie(0)->sync_with_stdio(0);

#if _debug == 1
  freopen("input.inp", "r", stdin);
#else
  freopen("TOWER.INP", "r", stdin);
  freopen("TOWER.OUT", "w", stdout);
#endif // _debug

  long long n;
  int m;
  int q;
  cin >> n >> m >> q;

  vector<long long> xcoor, ycoor;
  xcoor.reserve(m);
  ycoor.reserve(m);
  for (int i = 1; i <= m; i++) {
    cin >> node[i].x >> node[i].y >> node[i].w;
    xcoor.push_back(node[i].x);
    ycoor.push_back(node[i].y);
  }

  sort(xcoor.begin(), xcoor.end());
  xcoor.erase(unique(xcoor.begin(), xcoor.end()), xcoor.end());

  sort(ycoor.begin(), ycoor.end());
  ycoor.erase(unique(ycoor.begin(), ycoor.end()), ycoor.end());

  for (int i = 1; i <= m; i++) {
    int xfnd = lower_bound(xcoor.begin(), xcoor.end(), node[i].x) - xcoor.begin() + 1;
    int yfnd = lower_bound(ycoor.begin(), ycoor.end(), node[i].y) - ycoor.begin() + 1;
    sum_x[xfnd] += node[i].w;
    sum_y[yfnd] += node[i].w;
    node[i].x_compress = xfnd;
    node[i].y_compress = yfnd;
    occur.insert({{xfnd, yfnd}, node[i].w});
  }

  for (int index = 1; index <= xcoor.size(); index++) {
    row.insert({sum_x[index], index});
  }

  for (int index = 1; index <= ycoor.size(); index++) {
    col.insert({sum_y[index], index});
  }

  solve(1, 0);
  for (int i = 1; i <= q; i++) {
    int index;
    long long diff;
    cin >> index >> diff;
    solve(index, diff);
  }

}
