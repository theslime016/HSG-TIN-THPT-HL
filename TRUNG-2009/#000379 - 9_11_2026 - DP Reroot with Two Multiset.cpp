#include <bits/stdc++.h>
using namespace std;

/*
PARL

Tại ByteLand, có tất cả n thượng nghị sĩ ở trong n ngôi biệt thự (đánh số từ 1 đến n), giữa hai ngôi nhà có một đường đi duy nhất: đường đi trực tiếp hoặc không trực tiếp (đi qua các con đường khác). Tất cả các ngôi nhà đều đi được đến nhau.

Mỗi thượng nghị sĩ khi đi từ nhà mình đến thượng viện, phải trả 1 USD khi đi qua một con phố (phố là đường nối trực tiếp hai nhà bất kỳ). Trong quyền hạn của mình, Chủ tịch Thượng viện có quyền qui định miễn lệ phí cho các thượng nghị sĩ trên k tuyến phố và đặt trụ sở tại một biệt thự bất kỳ trong số n biệt thự ở trên.

Bạn hãy viết chương trình tính xem với cách chọn trụ sở và k tuyến phố miễn phí một cách hợp lý thì tổng số tiền nhỏ nhất phải trả của tất cả các thượng nghị sĩ là bao nhiêu?

Dữ liệu: Nhập từ file văn bản PARL.INP
- Dòng đầu tiên chứa hai số nguyên n và k (1 ≤ n ≤ 10^4; 0 < k < n).
- n − 1 dòng tiếp theo, mỗi dòng chứa 2 số i, j có nghĩa là có con phố nối ngôi nhà i và ngôi nhà j (1 ≤ i, j ≤ n; i ≠ j).
Hai số liên tiếp trên cùng một dòng cách nhau bằng khoảng trống (space).

Kết quả: Ghi ra file văn bản PARL.OUT một số nguyên là tổng chi phí tối thiểu phải trả.

Ràng buộc:
- Subtask 1 (25%): n ≤ 30.
- Subtask 2 (25%): 30 < n ≤ 1000.
- Subtask 3 (25%): 1000 < n ≤ 3000.
- Subtask 4 (10%): 3000 < n ≤ 5000.
- Subtask 5 (15%): Không có ràng buộc bổ sung.

Ví dụ:
(Bảng ví dụ trong file PDF bị lỗi trích xuất định dạng, không thể khôi phục chính xác. Chuỗi thô trích được: "13 3 11 1 2 12 3 2 2 8 2 7 5 5 4 5 6 8 9 8 10 10 11 10 12 10 13".)
*/

#if defined(__has_include) && __has_include("slime_debug_016.h")
#include "slime_debug_016.h"

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
#define debug(...) void(0)
#define newline void(0)

#endif // _debug

const int maxn = 1e4 + 5;
const long long inf = 1e18;
int n, k;
vector<int> adj[maxn];

int child[maxn];

long long current_edge[maxn];
int ptr_current_edge = 0;

void make_build(int index, int parent) {
  child[index] = 1;
  for (int x : adj[index]) {
    if (x == parent) continue;

    make_build(x, index);

    child[index] += child[x];

    current_edge[ ++ptr_current_edge ] = child[x];
  }
}

struct DYNAMICK {
  int cnt;
  long long sum;
  multiset<long long> left_val, right_val;

  DYNAMICK() = default;

  void init(int _cnt) {
    cnt = _cnt;
    sum = 0;
  }

  void balance() {
    while (left_val.size() > cnt) {
      auto it = prev(left_val.end());
      long long val = *it;
      left_val.erase(it);
      sum -= val;
      right_val.insert(val);
    }

    while (left_val.size() < cnt && right_val.size()) {
      auto it = right_val.begin();
      long long val = *it;
      left_val.insert(val);
      sum += val;
      right_val.erase(it);
    }
  }

  void ins(long long val) {
    left_val.insert(val);
    sum += val;

    balance();
  }

  void del(long long val) {
    auto it = left_val.find(val);
    if (it != left_val.end()) {
      left_val.erase(it);
      sum -= val;
    } else {
      right_val.erase(right_val.find(val));
    }
    balance();
  }

} container;

long long res = inf;

void make_dfs(int index, int parent) {

  for (int x : adj[index]) {
    if (x == parent) continue;

    long long old_child = child[x];
    long long new_child = child[index] - child[x];

    container.ins(new_child);
    container.del(old_child);

    res = min(res, container.sum);

    child[x] = n;

    make_dfs(x, index);

    container.del(new_child);
    container.ins(old_child);

    child[x] = old_child;
  }

}


int main() {
  cin.tie(0)->sync_with_stdio(0);

#if _debug == 1
  freopen("input.inp", "r", stdin);

#elif _debug == 2
  freopen("input.inp", "r", stdin);

#else
  freopen("parl.inp", "r", stdin);
  freopen("parl.out", "w", stdout);

#endif // _debug

  cin >> n >> k;
  for (int i = 1; i < n; i++) {
    int a, b;
    cin >> a >> b;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }

  if (k == n-1) {
    cout << 0;
    return 0;
  }

  make_build(1, 0);

  sort(current_edge + 1, current_edge + n);

#if _debug == 1
  newline;
  for (int i = 1; i <= n; i++) {
    debug(i, child[i]);
  }

  newline;
  cerr << "current_edge: " << endl;
  for (int i = 1; i < n; i++) cerr << current_edge[i] << ' ';
  newline;
#endif

  /// tinh tong k element max trong mot tap N phan tu thay doi 1 element moi lan

  container.init((n-1) - k);
  for (int i = 1; i < n; i++) {
    container.ins(current_edge[i]);
  }
  res = min(res, container.sum);

  make_dfs(1, 0);

  cout << res;
}
