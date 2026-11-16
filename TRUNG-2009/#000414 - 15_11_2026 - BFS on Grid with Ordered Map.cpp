#include <bits/stdc++.h>
using namespace std;

/**
Dịch chuyển tức thời

Thông tin chung:
- Điểm: 1600p
- Giới hạn thời gian: 1s
- Giới hạn bộ nhớ: 256 MB
- Input: BAI4.INP
- Output: BAI4.OUT

Mô tả:
Một trò chơi diễn ra trên bảng số gồm N dòng và M cột. Các dòng được đánh số từ 1 đến N từ trên xuống dưới, các cột được đánh số từ 1 đến M từ trái sang phải. Ô ở dòng u, cột v gọi là ô (u, v) và chứa số nguyên không âm A_{u,v}.

Từ ô (u, v), người chơi có thể đi tới:
- một ô chung cạnh: (u - 1, v), (u + 1, v), (u, v - 1), (u, v + 1) với điều kiện ô đó nằm trong bảng.
- một ô bất kỳ...

(Ghi chú: Nội dung đề bài trong file HTML bị cắt ngang tại đây, không có đầy đủ phần yêu cầu, Input, Output và Ví dụ).
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
#define debug_title cerr << __PRETTY_FUNCTION__ << " line: " << __LINE__ << endl
#define newline cerr << endl

#else
#define debug(...) (void(0))
#define debug_title (void(0))
#define newline (void(0))

#endif // _debug

const int maxn = 1e3 + 5;
int A[maxn][maxn];

int used[maxn * maxn];
int dist[maxn][maxn];

int row_num, col_num;
int start_x, start_y;
int end_x, end_y;

int main() {
  cin.tie(0)->sync_with_stdio(0);

#if _debug == 1
  freopen("input.inp", "r", stdin);

#elif _debug == 2
  freopen("input.inp", "r", stdin);

#else
  freopen("BAI4.INP", "r", stdin);
  freopen("BAI4.OUT", "w", stdout);

#endif // _debug

  cin >> row_num >> col_num;
  cin >> start_x >> start_y;
  cin >> end_x >> end_y;

  map<int, vector<pair<int, int>>> teleport;
  for (int i = 1; i <= row_num; i++) {
    for (int j = 1; j <= col_num; j++) {
      cin >> A[i][j];
      teleport[ A[i][j] ].push_back({i, j});
    }
  }

  memset(dist, -1, sizeof dist);
  deque<pair<int, int>> dq; /// x - y
  dq.push_back({start_x, start_y});
  dist[start_x][start_y] = 0;

  int dx[] = {0, 0, 1, -1};
  int dy[] = {1, -1, 0, 0};

  int res = -1;
  while (!dq.empty()) {
    int x = dq.front().first;
    int y = dq.front().second;
    dq.pop_front();

    if (x == end_x && y == end_y) {
      res = dist[x][y];
      break;
    }

    for (int i = 0; i < 4; i++) {
      int new_x = x + dx[i];
      int new_y = y + dy[i];

      if (!(new_x >= 1 && new_y >= 1))
        continue;
      if (!(new_x <= row_num && new_y <= col_num))
        continue;
      if (A[new_x][new_y] == 0)
        continue;
      if (dist[new_x][new_y] != -1)
        continue;

      dist[new_x][new_y] = dist[x][y] + 1;
      dq.push_back({new_x, new_y});
    }

    for (const auto& item : teleport[ A[x][y] ]) {
      if (dist[item.first][item.second] != -1) continue;
      if (A[item.first][item.second] == 0) continue;

      dist[item.first][item.second] = dist[x][y] + 1;
      dq.push_back(item);
    }
    teleport[ A[x][y] ].clear();

    #if _debug == 1
    cerr << "dq: " << endl;
    for (const auto& item : dq) cerr << item.first << ',' << item.second << ' ';
    newline;
    newline;
    #endif // _debug

  }

  cout << res;

}
