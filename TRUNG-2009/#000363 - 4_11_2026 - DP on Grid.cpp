#include <bits/stdc++.h>
using namespace std;

/*
Cho một lưới ô vuông gồm $r$ hàng và $c$ cột. Các hàng được đánh số từ 1 tới $r$ theo thứ tự từ trên xuống dưới, các cột được đánh số từ 1 tới $c$ theo thứ tự từ trái qua phải. Trên bảng có một số ô cấm.



Bạn cần đi từ góc trái trên — ô $(1, 1)$ tới góc phải dưới — ô $(r, c)$. Tại mỗi bước, bạn được đi theo một trong năm hướng (tương đương với việc cộng thêm vào tọa độ $(x, y)$ các giá trị):

- Sang phải 1 ô: $(0, 1)$

- Xuống dưới 1 ô: $(1, 0)$

- Chéo xuống 1 ô: $(1, 1)$

- Đi kiểu mã: $(2, 1)$ và $(1, 2)$



Một đường đi được gọi là *đường đi đẹp* khi và chỉ khi đường đi có những tính chất sau:

- Mọi bước đi đều đi theo một trong năm hướng nêu trên.

- Hai bước đi liên tiếp nhau phải đi theo hai hướng khác nhau.

- Đường đi không đi qua ô cấm nào.



Hãy đếm số đường đi đẹp từ ô $(1, 1)$ tới ô $(r, c)$.



**Input**

Dòng đầu tiên chứa hai số nguyên $r$ và $c$ ($1 \le r, c \le 2207$) — số hàng và số cột của bảng.

$r$ dòng tiếp theo, mỗi dòng chứa $c$ kí tự mô tả bảng. Ký tự `.` thể hiện ô không cấm và ký tự `#` thể hiện ô cấm.

Dữ liệu vào đảm bảo hai ô $(1, 1)$ và $(r, c)$ đều không phải ô cấm.



**Output**

In ra một số nguyên duy nhất là số đường đi đẹp modulo 998244353.



**Scoring**

- Subtask 1 (50 điểm): $r, c \le 7$

- Subtask 2 (50 điểm): $r, c \le 2207$



**Examples**

Input:

3 3

...

.#.

...



Output:

6
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

char table[maxn][maxn];
int dp[maxn][maxn][6]; // row - col - (5) last_move
int row, col;

const int max_move = 5;
const int dx[] = {0, 1, 1, 2, 1};
const int dy[] = {1, 0, 1, 1, 2};

int main() {
  cin.tie(0)->sync_with_stdio(0);

#if _debug == 1
  freopen("input.inp", "r", stdin);

#elif _debug == 2
  freopen("input.inp", "r", stdin);
  freopen("output.out", "w", stdout);

#else
  freopen("changedir.inp", "r", stdin);
  freopen("changedir.out", "w", stdout);

#endif // _debug

  cin >> row >> col;
  for (int i = 1; i <= row; i++) {
    for (int j = 1; j <= col; j++) {
      cin >> table[i][j];
    }
  }

  if (row == 1 && col == 1) {
    cout << 1;
    return 0;
  }


  auto can_go = [&](int i, int j) {
    return i >= 1 && i <= row && j >= 1 && j <= col && table[i][j] != '#';
  };

  auto add = [&](int& a, int b) {
    a = a + b;
    while (a >= mod) a = a - mod;
  };

  for (int k = 0; k < max_move; k++) {
    int new_row = dx[k] + 1;
    int new_col = dy[k] + 1;
    if (can_go(new_row, new_col)) dp[new_row][new_col][k] = (table[1][1] == '.');
  }

  for (int i = 1; i <= row; i++) {
    for (int j = 1; j <= col; j++) {
      if (i == 1 && j == 1) continue;
      if (table[i][j] == '#') continue;

      int sum = 0;
      for (int k = 0; k < max_move; k++) {
        sum = sum + dp[i][j][k];
        while (sum >= mod) sum = sum - mod;
      }
      if (sum == 0) continue;

      for (int m = 0; m < max_move; m++) {
        int new_row = i + dx[m];
        int new_col = j + dy[m];
        int val = sum - dp[i][j][m];
        if (val < 0) val = val + mod;

        if (can_go(new_row, new_col)) add(dp[new_row][new_col][m], val);
      }

    }
  }

  int res = 0;
  for (int k = 0; k < max_move; k++) {
    add(res, dp[row][col][k]);
  }

  cout << res;
}
