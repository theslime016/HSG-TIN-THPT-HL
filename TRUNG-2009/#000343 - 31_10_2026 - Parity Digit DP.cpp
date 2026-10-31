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

#if _debug == 1
void log_out() {cerr << '\n';}
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


unsigned long long dp[22][(1 << 10)][(1 << 10)]; // rem - occur - parity
string num;
unsigned long long make_dp(int pos, int occur_mask, int parity_mask, int flag_tight, int flag_head) {
  int rem = (int)num.size() - pos;

  if (rem == 0) {
    int ok = !flag_head;
    for (int c = 0; c <= 9; c++) {
      int occur = (occur_mask >> c) & 1;
      int parity = (parity_mask >> c) & 1;
      if (occur && (c%2 == parity)) ok = 0;
    }
    return ok;
  }

  if (!flag_tight && !flag_head && dp[rem][occur_mask][parity_mask] != -1)
    return dp[rem][occur_mask][parity_mask];

  int lim = flag_tight ? (num[pos] - '0') : 9;
  unsigned long long res = 0;
  for (int c = 0; c <= lim; c++) {
    int new_flag_tight = flag_tight && (c == lim);
    int new_flag_head = flag_head && (c == 0);
    int new_occur_mask = new_flag_head ? occur_mask : (occur_mask | (1 << c));
    int new_parity_mask = new_flag_head ? parity_mask : (parity_mask ^ (1 << c));
    unsigned long long val = make_dp(pos + 1, new_occur_mask, new_parity_mask,
                            new_flag_tight, new_flag_head);
    res += val;
  }

  if (!flag_tight && !flag_head) dp[rem][occur_mask][parity_mask] = res;
  return res;
}

unsigned long long fetch(unsigned long long x) {
  if (x <= 0) return 0;

  num = to_string(x);
  return make_dp(0, 0, 0, 1, 1);
}

int main() {
  cin.tie(0)->sync_with_stdio(0);

  #if _debug == 1
  freopen("input.inp", "r", stdin);

  #elif _debug == 2
  freopen("input.inp", "r", stdin);

  #else

  #endif // _debug

  memset(dp, -1, sizeof dp);

  int t;
  cin >> t;
  while (t--) {
    unsigned long long l, r;
    cin >> l >> r;
    cout << fetch(r) - fetch(l - 1) << '\n';
  }

}
