#include <bits/stdc++.h>
using namespace std;

/**
Chuyển bưu phẩm

Steve là nhân viên bưu điện ở một làng nhỏ miền núi. Toàn bộ địa hình khu vực có thể biểu diễn dưới dạng lưới ô vuông kích thước n x n ô, mỗi ô khá bằng phẳng, ô (i, j) có độ cao trung bình là h_{i,j}. Ở một ô là trạm bưu điện duy nhất của làng (đánh dấu là "P"), những ô còn lại hoặc là đồng cỏ (đánh dấu là ".") hoặc có một nhà ở (đánh dấu là "K").
Mỗi sáng Steve có nhiệm vụ mang thư báo, bưu phẩm từ trạm bưu điện đến giao từng nhà trong khu vực và quay trở lại trạm bưu điện sau khi phát xong gói bưu phẩm cuối cùng.
Từ một ô Steve có thể đi sang ô kề cạnh hoặc kề đỉnh. Steve không ngại đường xa, chỉ ngại nhất phải lên dốc cao vì vậy đã chọn một lộ trình đảm bảo chênh lệch giữa nơi cao nhất và nơi thấp nhất trên đường đi là nhỏ nhất.

Yêu cầu: Cho n các h_{i,j} và bản đồ khu vực (1 ≤ h_{i,j} ≤ 10^6, 2 ≤ n ≤ 50, i, j = 1 ÷ n). Trong khu vực có ít nhất một nhà và có đúng một trạm bưu điện. Hãy xác định chênh lệch độ cao giữa nơi cao nhất và nơi thấp nhất trên đường đi của Steve.

Dữ liệu: Vào từ file văn bản MAILMAN.INP:
- Dòng đầu tiên chứa số nguyên n;
- Dòng thứ i trong n dòng tiếp theo chứa xâu độ dài n mô tả khu vực, các ký tự của xâu thuộc tập {P, K, .};
- Dòng thứ j trong n dòng tiếp theo chứa n số nguyên h_{j,1}, h_{j,2}, ..., h_{j,n}.

Kết quả: Đưa ra file văn bản MAILMAN.OUT một số nguyên – kết quả tìm được.

Ví dụ:
MAILMAN.INP
3
K.P
...
K.K
3 3 4
9 5 9
8 3 7

MAILMAN.OUT
5
**/

#define _debug 1

#if _debug == 1
void log_out() {cerr << endl;}
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

const int maxn = 55;
const int inf = 1e9;
int n;

char A[maxn][maxn];
int H[maxn][maxn];

int visited[maxn][maxn];
int timer = 0;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  #if _debug == 1
  freopen("input.inp", "r", stdin);

  #else
  freopen("MAILMAN.INP", "r", stdin);
  freopen("MAILMAN.OUT", "w", stdout);

  #endif // _debug

  cin >> n;
  int post_x = -1, post_y = -1;
  int house_cnt = 0;;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      cin >> A[i][j];
      if (A[i][j] == 'P') {
        post_x = i;
        post_y = j;
      } else if (A[i][j] == 'K') {
        house_cnt++;
      }
    }
  }

  vector<int> comp;
  comp.reserve(n * n);
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      cin >> H[i][j];
      comp.push_back(H[i][j]);
    }
  }

  sort(comp.begin(), comp.end());
  comp.erase(unique(comp.begin(), comp.end()), comp.end());

  int post_index = lower_bound(comp.begin(), comp.end(), H[post_x][post_y]) - comp.begin();

  int dx[] = {1, 0, -1, 0, 1, -1, 1, -1};
  int dy[] = {0, 1, 0, -1, 1, -1, -1, 1};

  auto check = [&](int l, int r) {
    if (l > r) return false;
    deque<pair<int, int>> dq; /// x - y
    dq.push_back({post_x, post_y});
    visited[post_x][post_y] = ++timer;

    int active = 0;

    while (!dq.empty()) {
      int x = dq.front().first;
      int y = dq.front().second;
      dq.pop_front();

      for (int i = 0; i < 8; i++) {
        int new_x = x + dx[i];
        int new_y = y + dy[i];
        if (visited[new_x][new_y] == timer) continue;
        if (!(new_x >= 1 && new_y >= 1)) continue;
        if (!(new_x <= n && new_y <= n)) continue;
        if (H[new_x][new_y] >= comp[l] && H[new_x][new_y] <= comp[r]) {
          visited[new_x][new_y] = timer;
          if (A[new_x][new_y] == 'K') active++;
          dq.push_back({new_x, new_y});
        }
      }

    }
    return active == house_cnt;
  };

  int res = inf;
  int r = post_index;
  for (int l = 0; l <= post_index; l++) {
    while (!check(l, r) && r + 1 < comp.size()) r++;
    if (check(l, r)) res = min(res, comp[r] - comp[l]);
  }

  cout << res;

}
