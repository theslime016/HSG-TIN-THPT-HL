#include <bits/stdc++.h>
using namespace std;

#define _debug 0

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

const int maxn = 4005;
char A[maxn][maxn];
int visited[maxn][maxn];

int main() {
  cin.tie(0)->sync_with_stdio(0);

  #if _debug == 1
  freopen("input.inp", "r", stdin);

  #else

  #endif // _debug

  int row, col;
  cin >> row >> col;
  pair<int, int> start_point = {-1, -1};
  for (int i = 1; i <= row; i++) {
    for (int j = 1; j <= col; j++) {
      cin >> A[i][j];
      if (A[i][j] != '.' && start_point.first == -1) {
        start_point = {i, j};
      }
    }
  }

  struct POINT {
    int x, y;
    int level;
  };

  deque<POINT> dq;
  dq.push_back({start_point.first, start_point.second, 1});
  visited[start_point.first][start_point.second] = 1;
  int max_level = 0;

  int dx[] = {1, 0, -1, 0};
  int dy[] = {0, 1, 0, -1};

  while (!dq.empty()) {
    POINT a = dq.front();
    dq.pop_front();

    max_level = max(max_level, a.level);
    for (int i = 0; i < 4; i++) {
      int new_x = a.x + dx[i];
      int new_y = a.y + dy[i];

      if (!(new_x >= 1 && new_y >= 1 && new_x <= row
          && new_y <= col)) continue;
      if (visited[new_x][new_y]) continue;
      if (A[new_x][new_y] == '.') continue;

      visited[new_x][new_y] = 1;
      if (A[new_x][new_y] == A[a.x][a.y]) {
        dq.push_front({new_x, new_y, a.level});
      } else {
        dq.push_back({new_x, new_y, a.level + 1});
      }
    }
  }

  cout << max_level;

}
