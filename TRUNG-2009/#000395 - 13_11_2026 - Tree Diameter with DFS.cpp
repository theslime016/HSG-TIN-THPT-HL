#include <bits/stdc++.h>
using namespace std;

/**
File: FLIGHT.txt

Bài 4. Đường bay

Một đất nước có N hòn đảo, để di chuyển giữa các hòn đảo, chính phủ đã xây dựng N - 1 đường bay đảm bảo giữa hai đảo bất kỳ luôn có thể di chuyển tới nhau. Tuy nhiên, do quá ít đường bay nên để đi từ một đảo tới một đảo khác có thể phải di chuyển qua rất nhiều đảo trung gian. Thời gian chờ đợi cho mỗi chuyến bay luôn là điều khủng khiếp với mỗi người dân. Do đó, chính phủ lên đề án sẽ thay đổi: hủy bỏ một đường bay và thay thế vào đó là một đường bay khác. Đề án càng hiệu quả nếu như để di chuyển giữa hai đảo bất kỳ, số chuyến bay của hành khách phải đi nhiều nhất là ít nhất. Hay nói cách khác, số chặng bay hành khách phải đi để di chuyển giữa hai đảo bất kỳ trong trường hợp xấu nhất là ít nhất.

Yêu cầu:
Hãy xác định số chặng bay tối thiểu để có thể di chuyển giữa mọi cặp đảo bất kỳ sau khi thay đổi.

Dữ liệu: vào từ file FLIGHT.INP
- Dòng đầu chứa số nguyên N (N ≤ 2500).
- N - 1 dòng tiếp, dòng thứ i chứa ba số nguyên ui, vi (1 ≤ ui ≠ vi ≤ N) thể hiện đường bay hai chiều giữa 2 đảo ui và vi.

Kết quả: Ghi ra file FLIGHT.OUT
Một số nguyên duy nhất là số chặng bay tối thiểu cần thiết để có thể di chuyển giữa mọi cặp đảo bất kỳ. Trường hợp không tìm được phương án tăng hiệu quả thì ghi ra -1.

Ví dụ:
FLIGHT.INP
4
1 2
2 3
3 4

FLIGHT.OUT
2

Giải thích:
Ban đầu, để đi giữa 1 và 4 cần bay 3 chặng. Nếu bỏ chặng bay 3-4, thay bằng chặng bay 2-4, có thể di chuyển giữa hai đảo bất kỳ sau không quá 2 chặng bay.

Ràng buộc:
- 30% số test có n ≤ 80.
**/

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

const int maxn = 2505;
vector<int> adj[maxn];
pair<int, int> task[maxn];
int n;

int dfs1_index = 0;
int dfs1_dist = 0;
void make_dfs1(int index, int parent, int dist) {
  if (dist > dfs1_dist) {
    dfs1_dist = dist;
    dfs1_index = index;
  }

  for (int x : adj[index]) {
    if (x == parent) continue;
    make_dfs1(x, index, dist + 1);
  }
}

int diameter = 0;
void make_dfs2(int index, int parent, int dist, int stop) {
  diameter = max(diameter, dist);
//  debug(index, parent, dist, stop);

  for (int x : adj[index]) {
    if (x == parent || x == stop) continue;
    make_dfs2(x, index, dist + 1, stop);
  }
}

int make_diameter(int tar, int stop) {
  dfs1_dist = dfs1_index = diameter = 0;

  make_dfs1(tar, stop, 0);
  make_dfs2(dfs1_index, 0, 0, stop);
  return diameter;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);

  #if _debug == 1
  freopen("input.inp", "r", stdin);

  #else
  freopen("FLIGHT.INP", "r", stdin);
  freopen("FLIGHT.OUT", "w", stdout);

  #endif // _debug

  cin >> n;
  for (int i = 1; i < n; i++) {
    int a, b;
    cin >> a >> b;
    adj[a].push_back(b);
    adj[b].push_back(a);
    task[i] = {a, b};
  }

  int res = make_diameter(1, 0);
  debug(res);

  int local = res;
  for (int i = 1; i < n; i++) {
    int a = task[i].first;
    int b = task[i].second;

    int d1 = make_diameter(a, b);
    int d2 = make_diameter(b, a);
    int cut = (d1 + 1)/2 + (d2 + 1)/2 + 1;
    local = min(local, max({cut, d1, d2}));

    debug(a, b, d1, d2, local);
  }

  if (local < res) cout << local;
  else cout << -1;
}
