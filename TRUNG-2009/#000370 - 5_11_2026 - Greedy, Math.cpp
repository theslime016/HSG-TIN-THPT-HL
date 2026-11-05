#include <bits/stdc++.h>
using namespace std;

/*
B. Uống trà sữa, có trà xanh

time limit per test: 0.25 seconds
memory limit per test: 32 megabytes
input: discounts.inp
output: discounts.out

Trà xanh có nhiều công dụng thần kì. Trà xanh ngăn chặn sâu răng, giảm nguy cơ ung thư và tăng cường hệ miễn dịch. Không chỉ tốt cho sức khỏe, trà xanh còn giúp làm đẹp da, điều trị mụn và không gây dị ứng. Bởi vậy mà những bạn đã có người yêu — những người luôn muốn bản thân trông thật quyến rũ — luôn luôn đem trà xanh bên mình. Một bạn trẻ có người yêu lâu năm tâm sự: Kể từ ngày có được nửa kia, mình nhận ra trà xanh quyến rũ vô cùng. Ban đầu mới chạm môi thì thấy đắng, chứ sau này thấy ngọt ngào, xanh mát và hấp dẫn lắm. Vì thế mà cứ thứ ba nào mình cũng phải có trà xanh. Kể từ khi được quảng cáo rầm rộ bởi cặp đôi "Tú Túng", trà xanh trở nên nổi tiếng, và xuất hiện nhiều hơn trên các thực đơn đồ uống, bên cạnh trà sữa.

Quán trà sữa của GSPVH có bán n loại đồ uống khác nhau. Trong số này, một số loại là trà xanh, còn lại là trà sữa. Các thức uống được đánh số từ 1 đến n và giá cho một ly đồ uống thứ i là p_i. Để bắt trend hút khách, GSPVH đưa ra chương trình khuyến mại hấp dẫn: Với mỗi hóa đơn có ít nhất một ly trà xanh, ly rẻ nhất trong hóa đơn sẽ được giảm 50%. Chú ý rằng, chỉ có một ly duy nhất trong hóa đơn được giảm, kể cả trong hóa đơn có nhiều ly cùng rẻ nhất.

Để chuẩn bị cho bữa tiệc sinh nhật tròn 71 tuổi, Híu dự định mua hết toàn bộ thực đơn đồ uống trong tiệm của GSPVH. Tuy nhiên, do số lượng đồ uống cần mua quá lớn, Híu nhờ k người bạn của mình tới tiệm của GSPVH để mua về. Mỗi người bạn của Hiếu sẽ mua ít nhất một ly đồ uống, sao cho mỗi loại (trong số n loại đồ uống mà GSPVH bán) được mua một và chỉ một lần bởi một người bạn nào đó. Sau khi nghe tới chương trình khuyến mại của GSPVH, Híu muốn chia các loại trà sữa để k người bạn tới mua sao cho tổng số tiền của k hóa đơn là nhỏ nhất.

Input
Dòng đầu tiên chứa số nguyên θ (1 ≤ θ ≤ 5) là số thứ tự của subtask chứa test này.

Dòng đầu tiên chứa hai số nguyên n và k (1 ≤ k ≤ n ≤ 220797), lần lượt là số loại đồ uống có bán tại tiệm của GSPVH và số người bạn của Híu sẽ đến mua trà sữa.

Trong n dòng còn lại, dòng thứ i mô tả đồ uống thứ i với hai số nguyên p_i và t_i (1 ≤ p_i ≤ 10^9, 1 ≤ t_i ≤ 2), trong đó p_i là giá của đồ uống thứ i, và t_i = 1 nếu đồ uống thứ i là trà xanh, t_i = 2 nếu đồ uống thứ i là trà sữa.

Output
Dòng đầu tiên in ra một số thực với chính xác một chữ số sau phần thập phân thể hiện tổng số tiền nhỏ nhất của k hóa đơn.

Trong k dòng còn lại, dòng thứ i mô tả hóa đơn thứ i với số nguyên c_i (1 ≤ c_i ≤ n) là số đồ uống người bạn thứ i mua về, nối tiếp bởi c_i số nguyên X_{i, 1}, X_{i, 2}, ..., X_{i, c_i} (1 ≤ X_{i, j} ≤ n) là số thứ tự của các đồ uống được mua về bởi người bạn này.

Nếu có nhiều phương án tối ưu, bạn được đưa ra một phương án bất kì.

Scoring

- Subtask 1 (16 điểm): t_1 = t_2 = ... = t_n = 2 (mọi loại đồ uống đều là trà sữa).
- Subtask 2 (16 điểm): t_1 = t_2 = ... = t_n = 1 (mọi loại đồ uống đều là trà xanh).
- Subtask 3 (20 điểm): n ≤ 10 và k ≤ 3.
- Subtask 4 (24 điểm): n ≤ 1000 và k ≤ 3.
- Subtask 5 (24 điểm): Không có ràng buộc gì thêm.

Examples

input
3
3 2
2 1
3 2
3 1
output
5.5
2 1 2
1 3

input
3
4 3
4 1
1 2
2 2
3 2
output
8.0
1 1
2 4 2
1 3
*/

#if defined(__has_include) && __has_include("slime_debug_016.h")
#include "slime_debug_016.h"

#else
#define _debug 0

#endif // defined

/// MACRO
#if _debug == 1
void log_out() {
  cerr << '\n';
}
template<typename H, typename... T>
void log_out(H h, T... t) {
  cerr << h << ", ";
  log_out(t...);
}

#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:\n", log_out(__VA_ARGS__)
#define newline cerr << '\n'

#else
#define debug(...) void(0)
#define newline void(0)

#endif // _debug

const long long inf = 1e18;

int main() {
  cin.tie(0)->sync_with_stdio(0);
#if _debug == 1
  freopen("input.inp", "r", stdin);

#elif _debug == 2
  freopen("input.inp", "r", stdin);

#else
  freopen("discounts.inp", "r", stdin);
  freopen("discounts.out", "w", stdout);

#endif // _debug

  int discounts;
  cin >> discounts;

  int n, k;
  cin >> n >> k;
  vector<pair<long long, int>> type1, type2; // value - index
  type1.reserve(n);
  type2.reserve(n);
  for (int i = 1; i <= n; i++) {
    long long cost;
    int type;
    cin >> cost >> type;
    if (type == 1) type1.push_back({cost * 10LL, i});
    else if (type == 2) type2.push_back({cost * 10LL, i});
  }

  sort(type1.begin(), type1.end());
  sort(type2.begin(), type2.end());

  #if _debug == 1
  cerr << "type1: " << '\n';
  for (const auto& x : type1) {
    debug(x.first, x.second);
  }
  newline;
  #endif // _debug

  vector<int> task;
  task.reserve(k);

  long long res = 0;
  while (k > 1 && !type1.empty()) {
    long long val = type1.back().first;
    int index = type1.back().second;

    task.push_back(index);

    type1.pop_back();
    k--;
    res += val / 2;
  }

  while (k > 1 && !type2.empty()) {
    long long val = type2.back().first;
    int index = type2.back().second;

    task.push_back(index);

    type2.pop_back();
    k--;
    res += val;
  }

  long long min_val = inf;
  int flag = 0;
  long long sum = 0;
  for (const pair<long long, int>& x : type1) {
    flag = 1;
    sum += x.first;
    min_val = min(min_val, x.first);
  }

  for (const pair<long long, int>& x : type2) {
    sum += x.first;
    min_val = min(min_val, x.first);
  }

  debug(flag, min_val, sum);

  if (flag) {
    res += (min_val)/2;
    res += (sum - min_val);
  } else {
    res += (sum);
  }

  cout << res/10 << '.' << res%10 << '\n';

  for (int index : task) {
    cout << 1 << ' ' << index << '\n';
  }

  cout << type1.size() + type2.size() << ' ';
  for (const pair<long long, int>& x : type1) cout << x.second << ' ';
  for (const pair<long long, int>& x : type2) cout << x.second << ' ';

}
