#include <bits/stdc++.h>
using namespace std;

/**
BÀI TOÁN: ĐIỂM ĐẶT SÁCH (BOOK.*)
Cho một đồ thị dạng cây gồm N đỉnh, các đỉnh được đánh số từ 1 đến N. Trên cây có M đỉnh được đánh dấu (đây là các đỉnh có người cần sử dụng sách).
Người ta muốn chọn ra một đỉnh trên cây để làm nơi đặt một cuốn sách. Biết rằng, cuốn sách này chỉ có thể tác động (cho mượn) tới các đỉnh nằm trong bán kính khoảng cách tối đa là D (khoảng cách giữa hai đỉnh được tính bằng số lượng cạnh trên đường đi ngắn nhất giữa chúng).
Yêu cầu: Hãy tính số lượng đỉnh trên cây có thể được chọn làm nơi đặt cuốn sách, sao cho TẤT CẢ M đỉnh được đánh dấu đều có thể tiếp cận được cuốn sách này (tức là khoảng cách từ điểm đặt sách đến M đỉnh được đánh dấu đều không vượt quá D).

Dữ liệu vào: Đọc từ file văn bản BOOK.INP
- Dòng đầu tiên chứa 3 số nguyên dương N, M, D (1 ≤ M ≤ N ≤ 10^5; 0 ≤ D ≤ N).
- Dòng thứ hai chứa M số nguyên phân biệt thể hiện chỉ số của M đỉnh được đánh dấu.
- N - 1 dòng tiếp theo, mỗi dòng chứa 2 số nguyên u và v mô tả một cạnh nối trực tiếp giữa hai đỉnh u và v trên cây (1 ≤ u, v ≤ N).

Kết quả: Ghi ra file văn bản BOOK.OUT
- Một số nguyên duy nhất là số lượng đỉnh có thể chứa sách thỏa mãn yêu cầu bài toán.

Ví dụ:
BOOK.INP
6 2 2
2 4
1 2
2 3
2 4
4 5
4 6

BOOK.OUT
3

Giải thích ví dụ:
- 2 đỉnh được đánh dấu là 2 và 4.
- Khoảng cách tác động tối đa D = 2.
- Các đỉnh có thể đặt sách là:
  + Đỉnh 2: cách đỉnh 2 (0) <= 2, cách đỉnh 4 (1) <= 2.
  + Đỉnh 4: cách đỉnh 2 (1) <= 2, cách đỉnh 4 (0) <= 2.
  + Đỉnh 3: cách đỉnh 2 (1) <= 2, cách đỉnh 4 (2) <= 2.
=> Có 3 đỉnh thỏa mãn (2, 3, 4).
**/

#define _debug 1

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
vector<int> adj[maxn];
int diff[maxn];
int n, m, d;

int visited[maxn];
int timer = 1;

int task[maxn];

int main() {
  cin.tie(0)->sync_with_stdio(0);

  #if _debug == 1
  freopen("input.inp", "r", stdin);

  #else
  freopen("BOOK.INP", "r", stdin);
  freopen("BOOK.OUT", "w", stdout);

  #endif // _debug

  cin >> n >> m >> d;
  for (int i = 1; i <= m; i++) cin >> task[i];

  for (int i = 1; i < n; i++) {
    int a, b;
    cin >> a >> b;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }

  deque<pair<int, int>> dq; /// index
  for (int i = 1; i <= n; i++) {
    dq.push_back({task[i], 0});
    visited[task[i]] = ++timer;

    while (!dq.empty()) {
      int index = dq.front().first;
      int dist = dq.front().second;
      dq.pop_front();

      diff[index]++;

      if (dist + 1<= d) {
        for (int x : adj[index]) {
          if (visited[x] == timer) continue;
          visited[x] = timer;
          dq.push_back({x, dist + 1});
        }
      }
    }
  }

  #if _debug == 1
  cerr << "diff: " << endl;
  for (int i = 1; i <= m; i++) cerr << diff[i] << ' ';
  newline;

  #endif // _debug

  int cnt = 0;
  for (int i = 1; i <= n; i++) {
    if (diff[i] == m) cnt++;
  }

  cout << cnt;


}
