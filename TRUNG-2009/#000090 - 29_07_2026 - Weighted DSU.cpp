#include <bits/stdc++.h>
using namespace std;

// Tags: #Data_Structures, #Disjoint_Set_Union, #Weighted_DSU, #Graph

// [MÔ TẢ BÀI TOÁN]
// Bạn là một kỹ sư trắc địa đang phải khôi phục bản đồ tọa độ của N trạm
// phát sóng nằm trên một đường thẳng. Toàn bộ hồ sơ về tọa độ tuyệt đối
// đã bị mất, bạn chỉ còn lại một máy đo khoảng cách tương đối.

// Bạn liên tục nhận được các báo cáo và truy vấn. Có hai loại thao tác
// bạn phải xử lý:
// - Loại 1 (Báo cáo): `1 i j W` — Trạm j nằm cách trạm i một khoảng bằng
//   W về phía dương (Tức là A[j] - A[i] = W).
//   + Nếu báo cáo này hợp lệ (chưa biết hoặc khớp với dữ liệu cũ), hãy
//     ghi nhận nó.
//   + Nếu báo cáo này mâu thuẫn với những dữ liệu đã được xác nhận
//     trước đó, hãy in ra "CONFLICT" và bỏ qua báo cáo này.
// - Loại 2 (Truy vấn): `2 i j` — Sếp của bạn muốn biết khoảng cách từ
//   trạm i đến trạm j (Tức là A[j] - A[i] = ?).
//   + Nếu dữ liệu hiện tại đủ để suy ra khoảng cách, in ra kết quả.
//   + Nếu hai trạm chưa được liên kết trong cùng hệ quy chiếu, in ra
//     "UNKNOWN".

// [INPUT FORMAT]
// - Dòng đầu tiên chứa hai số nguyên dương N và Q (1 <= N <= 10^5,
//   1 <= Q <= 10^5) lần lượt là số lượng trạm phát sóng và số thao tác.
// - Q dòng tiếp theo, mỗi dòng bắt đầu bằng số type (1 hoặc 2).
//   + Nếu type = 1, tiếp theo là 3 số nguyên i, j, W
//     (-10^9 <= W <= 10^9).
//   + Nếu type = 2, tiếp theo là 2 số nguyên i, j.

// [OUTPUT FORMAT]
// - Với mỗi thao tác loại 1 bị mâu thuẫn logic, in ra "CONFLICT" trên
//   một dòng.
// - Với mỗi thao tác loại 2, in ra giá trị A[j] - A[i], hoặc "UNKNOWN"
//   trên một dòng.

// [EXAMPLE]
// * Input:
// 5 8
// 1 1 2 5
// 1 2 3 3
// 2 1 3
// 1 4 5 10
// 1 2 4 2
// 2 1 5
// 1 3 5 8
// 2 3 5

// * Output:
// 8
// 17
// CONFLICT
// 9

struct uf {
  int n;
  vector<int> data;
  vector<long long> dist;

  uf(int n) {
    this->n = n;
    data.resize(n + 1);
    iota(data.begin(), data.end(), 0LL);
    dist.assign(n + 1, 0);
  }

  pair<int, long long> find(int index) {
    if (index == data[index])
      return {index, dist[index]};
    auto [root, d] = find(data[index]);
    data[index] = root;
    dist[index] += d;
    return {root, dist[index]};
  }

  long long process(int u, int v, long long w, int q) {
    auto [d1, w1] = find(u);
    auto [d2, w2] = find(v);
    if (d1 != d2) {
      if (q == 2)
        return LLONG_MAX;
      data[d1] = d2;
      dist[d1] = dist[v] + w - dist[u];

      return true;
    } else {
      if (q == 1) {
        return (w1 - w2 == w);
      } else {
        return w1 - w2;
      }
    }
  }
};

int main() {
  cin.tie(0)->sync_with_stdio(false);

  int n, q;
  cin >> n >> q;
  uf dsu(n);
  while (q--) {
    int s;
    cin >> s;
    int a, b, w;
    if (s == 1) {
      cin >> a >> b >> w;
      if (!dsu.process(a, b, w, s))
        cout << "CONFLICT" << '\n';
    } else {
      cin >> a >> b;
      long long res = dsu.process(a, b, 0, s);
      if (res == LLONG_MAX)
        cout << "UNKNOWN" << '\n';
      else
        cout << res << '\n';
    }
  }

  return 0;
}
