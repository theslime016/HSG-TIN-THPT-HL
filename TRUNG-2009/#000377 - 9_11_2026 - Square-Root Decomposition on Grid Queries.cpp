#include <bits/stdc++.h>
using namespace std;

/*
TABLE

Points: 100 (p)
Time limit: 1.0s
Memory limit: 1G
Input: stdin
Output: stdout
Author: lethanhbinh

Cho một bảng số gồm m hàng và n cột. Các hàng đánh số 1, 2, ..., m từ trên xuống dưới còn các cột đánh số 1, 2, ..., n từ trái qua phải. Ô nằm ở giao của hàng i (1 ≤ i ≤ m) và cột j (1 ≤ j ≤ n) gọi là ô (i, j) và có giá trị ban đầu là a_ij. Cần thực hiện Q thao tác trên bảng số, mỗi thao tác thuộc một trong hai loại:

- Thao tác loại 1 có dạng: 1 x y u v w
  Có nghĩa là với mỗi ô nằm trong hình chữ nhật có ô trái trên là (x, y) và ô phải dưới là (u, v) sẽ được cộng thêm w.

- Thao tác loại 2 có dạng: 2 x y u v
  Có nghĩa cần đưa ra tổng giá trị của các ô nằm trong hình chữ nhật có ô trái trên là (x, y) và ô phải dưới là (u, v).

Input
- Dòng đầu chứa ba số nguyên dương m, n, Q (m, n ≤ 500).
- Dòng thứ i (1 ≤ i ≤ m) trong m dòng tiếp theo chứa n số nguyên không âm a_i1, a_i2, ..., a_in (a_ij ≤ 10^9).
- Dòng thứ k (1 ≤ k ≤ Q) trong Q dòng tiếp theo mô tả thao tác thứ k.
  + Nếu là thao tác loại 1, dòng gồm 6 số nguyên: 1 x y u v w
    (1 ≤ x ≤ u ≤ m; 1 ≤ y ≤ v ≤ n; 0 ≤ w ≤ 10^9).
  + Nếu là thao tác loại 2, dòng gồm 5 số nguyên: 2 x y u v
    (1 ≤ x ≤ u ≤ m; 1 ≤ y ≤ v ≤ n).

Output
- Ghi ra một số dòng, mỗi dòng tương ứng là câu trả lời cho thao tác loại 2 lần lượt xuất hiện trong dữ liệu vào.

Example
Test 1

Input:
2 3 3
0 0 0
0 0 0
2 1 1 2 3
1 1 1 2 3 1
2 1 1 2 2

Output:
0
4

Scoring
- Subtask 1 (30% số điểm): Q ≤ 100.
- Subtask 2 (30% số điểm): Q ≤ 10^5 và các thao tác loại 1 xuất hiện trước thao tác loại 2.
- Subtask 3 (20% số điểm): Q ≤ 10^4.
- Subtask 4 (20% số điểm): Q ≤ 10^5.
*/

#if defined(__has_include) && __has_include("slime_debug_016.h")
#include "slime_debug_016.h"

#else
#define _debug 0

#endif // defined

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


const int maxn = 505;
const int maxtask = 1e5 + 5;
int row_num, col_num, q;

long long A[maxn][maxn];
long long pref[maxn][maxn];
long long diff[maxn][maxn];

struct TASK {
  int x, y;
  int u, v;
  long long val;
} task[maxtask];
int ptr_task = 0;

void build() {
  memset(diff, 0, sizeof diff);

  while (ptr_task > 0) {
    TASK current = task[ptr_task];
    diff[ current.x ][ current.y ] += current.val;

    diff[ current.u + 1][ current.y ] -= current.val;

    diff[ current.x ][ current.v + 1] -= current.val;

    diff[ current.u + 1 ][ current.v + 1 ] += current.val;

    ptr_task--;
  }


  for (int i = 1; i <= row_num; i++) {
    for (int j = 1; j <= col_num; j++) {
      diff[i][j] += diff[i-1][j] + diff[i][j-1] - diff[i-1][j-1];
      A[i][j] += diff[i][j];
      pref[i][j] = A[i][j] + pref[i-1][j] + pref[i][j-1] - pref[i-1][j-1];
    }
  }

#if _debug == 1
  newline;
  cerr << "diff: " << endl;
  for (int i = 1; i <= row_num; i++) {
    for (int j = 1; j <= col_num; j++) {
      cerr << diff[i][j] << ' ';
    }
    newline;
  }
  newline;

#endif // _debug

}


int main() {
  cin.tie(0)->sync_with_stdio(0);

#if _debug == 1
  freopen("input.inp", "r", stdin);

#elif _debug == 2
  freopen("input.inp", "r", stdin);

#else

#endif // _debug

  cin >> row_num >> col_num >> q;

  for (int i = 1; i <= row_num; i++) {
    for (int j = 1; j <= col_num; j++) {
      cin >> A[i][j];
      pref[i][j] = A[i][j] + pref[i-1][j] + pref[i][j-1] - pref[i-1][j-1];
    }
  }

  int block_size = sqrt(row_num * col_num);
  int block_num = (q - 1) / block_size + 1;

  debug(q, block_size, block_num);

  for (int i = 1; i <= block_num; i++) {
    int start_point = (i - 1) * block_size + 1;
    int end_point = min(q, i * block_size);
    debug(start_point, end_point);
    newline;

    for (int j = start_point; j <= end_point; j++) {
      int type;
      cin >> type;
      debug(j, type);
      newline;

      if (type == 1) {
        int x, y, u, v;
        long long val;
        cin >> x >> y >> u >> v >> val;
        task[++ptr_task] = {x, y, u, v, val};
      } else if (type == 2) {
        int x, y, u, v;
        cin >> x >> y >> u >> v;

        long long res = pref[u][v] - pref[u][y-1] - pref[x-1][v] + pref[x-1][y-1];
        for (int k = 1; k <= ptr_task; k++) {

          int nx = max(task[k].x, x);
          int ny = max(task[k].y, y);
          int nu = min(task[k].u, u);
          int nv = min(task[k].v, v);

          if (nx <= nu && ny <= nv) {
            long long dx = nu - nx + 1;
            long long dy = nv - ny + 1;
            res += task[k].val * (dx * dy);
          }
        }

#if _debug == 1
        cerr << "RES: ";
#endif // _debug
        cout << res << '\n';

      }

    }

    build();

  }

}
