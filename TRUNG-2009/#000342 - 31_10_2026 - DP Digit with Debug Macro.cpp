#include <bits/stdc++.h>
using namespace std;

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

#define debug(...) cerr << '[' << #__VA_ARGS__ << "]:\n", log_out(__VA_ARGS__)
#define newline cerr << '\n'

#else
#define debug(...) void(0)
#define newline void(0)

#endif // _debug

long long dp[100][100]; /// pos - last_char
string num;

long long make_dp(int pos, int last_char, int flag_tight, int flag_head) {
  if (pos == (int)num.size()) {
    return !flag_head;
  }

  if (!flag_tight && !flag_head && dp[pos][last_char] != -1) return dp[pos][last_char];

  int lim = flag_tight ? (num[pos] - '0') : 9;
  long long res = 0;
  for (int c = 0; c <= lim; c++) {
    if (!flag_head && abs(last_char - c) < 2) continue;

    int new_flag_tight = flag_tight && (c == lim);
    int new_flag_head = flag_head && (c == 0);
    long long val = make_dp(pos + 1, c, new_flag_tight, new_flag_head);
    res += val;

    debug(last_char, c, new_flag_tight, new_flag_head, val);

  }

  debug(pos, last_char, lim);
  debug(flag_tight, flag_head, res);
  newline;

  if (!flag_tight && !flag_head) dp[pos][last_char] = res;
  return res;
}

long long fetch(long long x) {
  if (x <= 0) return 0;

  memset(dp, -1, sizeof dp);
  num = to_string(x);

  int lim_char = num[0] - '0';
  long long res = 0;
  for (int i = 0; i <= lim_char; i++) {
    int flag_tight = (i == lim_char);
    int flag_head = (i == 0);
    long long val = make_dp(1, i, flag_tight, flag_head);
    res += val;

    debug(i, flag_tight, flag_head, val);
    newline;
    newline;
  }

  return res;
}

long long query_fetch(long long l, long long r) {
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

  long long l, r;
  cin >> l >> r;
  cout << query_fetch(l, r) << '\n';

}
