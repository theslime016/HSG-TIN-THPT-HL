#include <bits/stdc++.h>
using namespace std;

/*
Cho T truy vấn. Mỗi truy vấn gồm hai số nguyên dương L, R và số nguyên dương K. Hãy đếm xem trong đoạn [L, R] có bao nhiêu số nguyên chia hết cho K mà tổng các chữ số của nó cũng chia hết cho K?

Input
- Dòng đầu tiên chứa số nguyên dương T (T <= 100).
- T dòng tiếp theo, mỗi dòng chứa ba số nguyên L, R, K (1 <= L <= R <= 10^12; 1 <= K <= 90).

Output
- Với mỗi truy vấn in một số nguyên trên một dòng là kết quả tìm được.

Example
Test 1

Input
3
1 20 2
1 100 7
10 50 4

Output
5
3
3
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



long long l, r;
int k;

long long dp[20][100][100]; /// position - num%k - sum_char%k
string s;
long long make_dp(int pos, int num, int sum_char, int flag_tight, int flag_head) {
  if (pos == s.size()) {
    return num == 0 && sum_char == 0 && !flag_head;
  }

  if (!flag_tight && !flag_head && dp[pos][num][sum_char] != -1) return dp[pos][num][sum_char];

  int lim = flag_tight ? (s[pos] - '0') : 9;
  long long res = 0;
  for (int c = 0; c <= lim; c++) {
    int new_num = ((num * 10) % k + c) % k;
    int new_sum_char = (sum_char + c) % k;
    int new_flag_tight = flag_tight && (c == lim);
    int new_flag_head = flag_head && (c == 0);
    long long val = make_dp(pos + 1, new_num, new_sum_char, new_flag_tight, new_flag_head);
    res += val;

    debug(c);
    debug(new_num);
    debug(new_sum_char);
    debug(new_flag_tight);
    debug(new_flag_head);
    newline;
  }

  debug(pos);
  debug(num);
  debug(sum_char);
  debug(flag_tight);
  debug(flag_head);
  debug(lim);
  debug(res);
  newline;

  if (!flag_tight && !flag_head) dp[pos][num][sum_char] = res;
  return res;
}

long long fetch(long long x) {
  if (x <= 0) return 0;

  memset(dp, -1, sizeof dp);
  s = to_string(x);

  long long res = 0;
  int lim_char = s[0] - '0';
  for (int i = 0; i <= lim_char; i++) {
    int nxt_pos = 1;
    int current_num = i%k;
    int current_sum_char = i%k;
    int flag_tight = (i == lim_char);
    int flag_head = (i == 0);

    long long val = make_dp(nxt_pos, current_num, current_sum_char, flag_tight, flag_head);
    res += val;

    newline;
    debug("make_dp");
    debug(i);
    debug(val);
    debug(current_num);
    debug(current_sum_char);
    debug(flag_tight);
    debug(flag_head);

    newline;
    newline;
  }
  return res;
}

long long query_get(long long l, long long r) {
  return fetch(r) - fetch(l - 1);
}

int main() {
  cin.tie(0)->sync_with_stdio(0);

#if _debug == 1
  freopen("input.inp", "r", stdin);

#elif _debug == 2
  freopen("input.inp", "r", stdin);

#else

#endif // _debug

  int t;
  cin >> t;
  while (t--) {
    cin >> l >> r >> k;
    long long res = query_get(l, r);
    debug("QUERY");
    cout << res << '\n';
  }
}
