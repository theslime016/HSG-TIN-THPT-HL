#include <bits/stdc++.h>
using namespace std;

/*
E. DNA
time limit per test: 0.25 seconds
memory limit per test: 8 megabytes
input: adn.inp
output: adn.out

Như các bạn đã biết, một chuỗi DNA có thể được biểu diễn bởi một xâu kí tự mà trong đó mỗi tự là một trong bốn chữ cái in hoa A, T, G hay C.

Có ba phép làm thay đổi chuỗi gen thường gặp:

- Thêm: Thêm một kí tự vào trong chuỗi DNA. Kí tự được thêm vào phải là một trong bốn chữ cái in hoa A, T, G hay C.
- Xóa: Xóa một kí tự đang có trong chuỗi DNA.
- Sửa: Thay thế một kí tự đang có trong chuỗi DNA bằng một kí tự khác. Kí tự mới phải là một trong bốn chữ cái in hoa A, T, G hay C.

Cho hai chuỗi DNA s và t, hãy cho biết có thể biến đổi từ s thành t qua không quá hai phép biến đổi hay không.

Input
Dòng đầu tiên chứa xâu s, dòng thứ hai chứa xâu t. Cả hai xâu s và t đều có độ dài từ 1 đến 50, và chỉ chứa các kí tự A, T, G và C.

Output
In ra Yes nếu có thể biến đổi từ s sang t trong không quá hai phép biến đổi, No nếu điều này là không khả thi.

Example
input
AAAAA
AACAACA

output
Yes
*/

#if defined(__has_include) && __has_include("slime_debug_016.h")
#include "slime_debug_016.h"

#else
#define _debug 0

#endif // defined

/// MACRO
#if _debug == 1
void log_out() {cerr << '\n';}
template<typename H, typename... T>
void log_out(H h, T... t) {
  cerr << h << ", ";
  log_out(t...);
}

#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:\n", log_out(__VA_ARGS__)
#define newline cerr << endl

#else
#define debug(...) void(0)
#define newline void(0)

#endif // _debug

int dp[100][100];

int main() {
  cin.tie(0)->sync_with_stdio(0);

  #if _debug == 1
  freopen("input.inp", "r", stdin);

  #elif _debug == 2
  freopen("input.inp", "r", stdin);

  #else
  freopen("adn.inp", "r", stdin);
  freopen("adn.out", "w", stdout);

  #endif // _debug


  string A, B;
  cin >> A >> B;

  int n = A.size();
  int m = B.size();

  A = '#' + A;
  B = '#' + B;

  dp[0][0] = 0;
  for (int i = 1; i <= n; i++) dp[i][0] = i;
  for (int j = 1; j <= m; j++) dp[0][j] = j;

  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      if (A[i] == B[j]) {
        dp[i][j] = dp[i-1][j-1];
      } else {
        dp[i][j] = min({dp[i-1][j-1], dp[i][j-1], dp[i-1][j]}) + 1;
      }
    }
  }

  if (dp[n][m] <= 2) cout << "Yes";
  else cout << "No";

}
