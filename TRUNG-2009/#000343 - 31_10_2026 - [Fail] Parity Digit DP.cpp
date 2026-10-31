#include <bits/stdc++.h>
using namespace std;

/*
BALANCED

Points: 100 (p) | Time limit: 1.0s | Memory limit: 1G | Input: stdin | Output: stdout

Một số nguyên dương được gọi là số cân bằng nếu trong biểu diễn thập phân của nó mọi chữ số CHẴN đều xuất hiện một số LẺ lần và mọi chữ số LẺ có mặt trong số đó đều xuất hiện một số CHẴN lần.

Yêu cầu: Cho T truy vấn, mỗi truy vấn gồm hai số nguyên dương L, R. Hãy đếm số lượng số cân bằng nằm trong đoạn [L, R].

Input
- Dòng đầu chứa số nguyên dương T (1 <= T <= 1000) là số lượng truy vấn.
- Tiếp theo là T dòng, mỗi dòng mô tả một truy vấn gồm hai số nguyên dương L, R (1 <= L <= R <= 10^10).

Output
- Với mỗi truy vấn trên một dòng một số nguyên là số lượng số cân bằng tìm được.

Example
Test 1:
Input:
2
1 20
21 50

Output:
6
8
*/

#if defined(__has_include) && __has_include("slime_debug_016.h")
#include "slime_debug_016.h"

#else
#define _debug 0

#endif // defined

/// MACRO
#if _debug == 1
void log_out() {
  cerr << '\n';
}
template<typename H, typename... T>
void log_out(H h, T... t) {
  cerr << h << ", ";
  log_out(t...);
}
#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:\n", log_out(__VA_ARGS__)
#define newline cerr << '\n'

#else
#define debug(...) void(0)
#define newline void(0)

#endif // _debug


long long dp[50][50][50]; // pos - parity_odd - parity_even
string num;

#if _debug == 1
string temp;
#endif // _debug

long long make_dp(int pos, int parity_odd, int parity_even, int flag_tight, int flag_head,
                  int flag_even) {
  if (pos == num.size()) {
    return !parity_odd && (flag_even || parity_even) && !flag_head;
  }

  if (!flag_tight && !flag_head && !flag_even && dp[pos][parity_odd][parity_even] != -1)
    return dp[pos][parity_odd][parity_even];

  long long res = 0;
  int lim = flag_tight ? (num[pos] - '0') : 9;
  for (int c = 0; c <= lim; c++) {
    int new_flag_tight = flag_tight && (c == lim);
    int new_flag_head = flag_head && (c == 0);
    int new_flag_even = flag_even && (c%2 == 1);
    int new_parity_odd = (c%2 == 1) ? !parity_odd : parity_odd;
    int new_parity_even = (c%2 == 0 && !new_flag_even) ? !parity_even : parity_even;

#if _debug == 1
    temp.push_back(c + '0');
#endif // _debug

    long long val = make_dp(pos + 1, new_parity_odd, new_parity_even,
                            new_flag_tight, new_flag_head, new_flag_even);
    res += val;


#if _debug == 1
    debug("START");
    debug(pos, c, temp);
    debug(parity_odd, parity_even, flag_tight, flag_head);
    newline;
    debug(new_parity_odd, new_parity_even);
    debug(new_flag_tight, new_flag_head, new_flag_even);
    debug(val);
    newline;
    newline;
#endif

#if _debug == 1
    temp.pop_back();
#endif // _debug
  }

  if (!flag_tight && !flag_head) dp[pos][parity_odd][parity_even] = res;
  return res;
}

long long fetch(long long x) {
  if (x <= 0) return 0;

  memset(dp, -1, sizeof dp);
  num = to_string(x);

  return make_dp(0, 0, 0, 1, 1, 1);
}

int main() {
  cin.tie(0)->sync_with_stdio(0);

#if _debug == 1
  freopen("input.inp", "r", stdin);

#elif _debug == 2
  freopen("input.inp", "r", stdin);

#else

#endif // _debug

  fetch(20);
  return 0;

  int t;
  cin >> t;
  while (t--) {
    long long l, r;
    cin >> l >> r;
    cout << fetch(r) - fetch(l - 1) << '\n';
  }

}
