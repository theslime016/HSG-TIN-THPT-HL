#include <bits/stdc++.h>
using namespace std;

/*
TRCUT
Cho một đồ thị dạng cây gồm n đỉnh đánh số từ 1 đến n, đỉnh i có trọng số a_i. Cho k lần cắt cây (mỗi lần xóa một cạnh hiện đang có) ta sẽ có một rừng gồm k+1 cây. Trọng số của một cây được định nghĩa bằng tổng trọng số các đỉnh có trong cây đó.
Bài toán yêu cầu hãy tìm cách cắt cây sao cho trọng số lớn nhất của các cây sinh ra là nhỏ nhất.
Dữ liệu: Nhập từ file văn bản TRCUT.INP
- Dòng đầu tiên gồm hai số n, k (1 <= k < n <= 5 * 10^5)
- Dòng thứ hai ghi n số a_1, a_2, ..., a_n là trọng số các đỉnh (0 <= a_i <= 10^3)
- n-1 dòng tiếp theo, mỗi dòng gồm hai số u, v mô tả một cạnh của cây
Kết quả: Ghi ra file văn bản TRCUT.OUT
- Một số nguyên duy nhất là trọng số của cây có trọng số lớn nhất trong phương án tối ưu

Ràng buộc:
- Subtask 1 (20%): n <= 20
- Subtask 2 (20%): n <= 200
- Subtask 3 (20%): n <= 1000, a_i = 1 với mọi i = 1, 2, ..., n
- Subtask 4 (40%): Không có ràng buộc bổ sung

Ví dụ:
TRCUT.INP
8 2
7 4 3 8 5 7 5 4
2 1
3 1
4 3
5 2
6 1
7 6
8 1

TRCUT.OUT
20
*/

#if defined(__has_include) && __has_include("slime_debug_016.h")
#include "slime_debug_016.h"

#else
#define _debug 0

#endif // defined

/// MACRO
#if _debug == 1
#define debug(x) cerr << #x << ':' << (x) << ' ';
#define newline cerr << '\n';

#else
#define debug(x) 42
#define newline 42

#endif // _debug

const int maxn = 5e5 + 5;
const int inf = 1e9;

int A[maxn];
vector<int> adj[maxn];
int n, k;
int cut;
long long make_dfs(int index, int parent, long long lim) {
  vector<long long> current;
  for (int x : adj[index]) {
    if (x == parent) continue;
    current.push_back(make_dfs(x, index, lim));
  }

  sort(current.begin(), current.end());
  long long sum = A[index];
  for (long long y : current) {
    if (y + sum <= lim) sum += y;
    else cut++;
  }
  return sum;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);

#if _debug == 1
  freopen("input.inp", "r", stdin);

#elif _debug == 2
  freopen("input.inp", "r", stdin);

#else
  freopen("trcut.inp", "r", stdin);
  freopen("trcut.out", "w", stdout);

#endif // _debug

  cin >> n >> k;
  int l = inf, r = 0;
  for (int i = 1; i <= n; i++) {
    cin >> A[i];
    l = min(l, A[i]);
    r += A[i];
  }
  for (int i = 1; i < n; i++) {
    int a, b;
    cin >> a >> b;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }

  for (int d = r - l; d > 0; d >>= 1) {
    while (r - d >= l) {
      cut = 0;
      make_dfs(1, 0, r - d);
      if (cut <= k) r -= d;
      else break;
    }
  }

  cout << r;

}
