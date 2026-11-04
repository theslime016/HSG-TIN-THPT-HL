#include <bits/stdc++.h>
using namespace std;

/*
K. Tổng đường đi
time limit per test: 0.5 seconds
memory limit per test: 256 megabytes
input: sumpath.inp
output: sumpath.out

Cho lưới ô vuông gồm m hàng và n cột. Các hàng được đánh số từ 1 đến m theo thứ tự từ trên xuống dưới, các cột được đánh số từ 1 đến n theo thứ tự từ trái qua phải. Trên mỗi ô của lưới có ghi một chữ số từ 0 đến 9. Ta gọi một đường đi là đường đi đẹp khi và chỉ khi đường đi có đầy đủ các tính chất sau:

- Đường đi xuất phát ở ô (1, 1) (ô góc trái trên).
- Đường đi kết thúc ở ô (m, n) (ô góc phải dưới).
- Với mỗi bước, ta chỉ đi từ vị trí hiện tại (gọi là ô (x, y)) tới một trong ba ô (x, y + 1), (x + 1, y) và (x + 1, y + 1).

Giá trị của một đường đi đẹp là tổng số ghi trên các ô mà đường đi đó đi qua. Hãy tính tổng giá trị tất cả các đường đi đẹp có trên lưới.

Input
Dòng đầu tiên gồm hai số nguyên m và n (1 <= m, n <= 2207) lần lượt là số hàng và số cột của lưới.
m dòng tiếp theo mô tả các chữ số ghi trên lưới, mỗi dòng có n chữ số.

Output
In ra một số nguyên duy nhất là tổng giá trị của tất cả các đường đi đẹp có trên lưới. Do kết quả có thể rất lớn, hãy in ra tổng này theo modulo 998244353.

Scoring
- Subtask 1 (20 điểm): m = 1
- Subtask 2 (35 điểm): m, n <= 7
- Subtask 3 (45 điểm): m, n <= 2207

Examples

input
2 2
22
07

output
29


input
3 3
123
456
789

output
285


input
2 4
2207
1997

output
153
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

const int maxn = 2300;
const int mod = 998244353;

int table[maxn][maxn];
int way[maxn][maxn];
int dp[maxn][maxn];

int row, col;

const int max_move = 3;
const int dx[] = {1, 0, 1};
const int dy[] = {0, 1, 1};

int main() {
  cin.tie(0)->sync_with_stdio(0);

#if _debug == 1
  freopen("input.inp", "r", stdin);

#elif _debug == 2
  freopen("input.inp", "r", stdin);

#else
  freopen("sumpath.inp", "r", stdin);
  freopen("sumpath.out", "w", stdout);

#endif // _debug

  cin >> row >> col;

  way[1][1] = 1;
  for (int i = 1; i <= row; i++) {
    for (int j = 1; j <= col; j++) {
      char c;
      cin >> c;
      table[i][j] = (c - '0');

      for (int k = 0; k < max_move; k++) {
        way[i][j] = (way[i][j] + way[i - dx[k]][j - dy[k]])%mod;
      }

#if _debug == 1
      debug(i, j, way[i][j]);
#endif // _debug

    }
  }

  dp[1][1] = table[1][1];

  for (int i = 1; i <= row; i++) {
    for (int j = 1; j <= col; j++) {

      for (int k = 0; k < max_move; k++) {
        int nx = dx[k] + i;
        int ny = dy[k] + j;
        if (nx >= 1 && nx <= row && ny >= 1 && ny <= col) {
          int val = (long long)way[i][j] * (long long)table[nx][ny] % mod;
          dp[nx][ny] = (dp[nx][ny] + dp[i][j]) % mod;
          dp[nx][ny] = (dp[nx][ny] + val) % mod;
        }

      }

    }
  }

  cout << dp[row][col];

}
