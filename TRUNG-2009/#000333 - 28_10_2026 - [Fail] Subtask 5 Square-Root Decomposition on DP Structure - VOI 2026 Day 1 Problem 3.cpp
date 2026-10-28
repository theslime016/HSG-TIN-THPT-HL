#include <bits/stdc++.h>
using namespace std;

#if defined(__has_include) && __has_include("slime_debug_016.h")
#include "slime_debug_016.h"

#else
#define _debug 0

#endif // defined

#if _debug == 1
#define debug(x) cerr << #x << ':' << (x) << ' ';
#define newline cerr << '\n';

#else
#define debug(x) 42
#define newline 42

#endif // _debug

const int maxn = 3e5 + 5;
const int inf = 1e9;

int n, q;
int A[maxn];
pair<int, int> query[maxn];

struct SUB1 { /// SUB 1
  map<int, int> cnt;
  void init() {
    for (int i = 1; i <= n; i++) cnt[ A[i] ]++;
  }

  bool check(int l, int r) {
    map<int, int> temp;
    for (int i = l; i <= r; i++) {
      temp[ A[i] ]++;
    }

    for (const auto& x : temp) {
      if (cnt[ x.first ] != x.second) return false;
    }
    return true;
  }

  long long solve(int l, int r) {
    long long res = 0;
    for (int i = l; i <= r; i++) {
      for (int j = i; j <= r; j++) {
        res += check(i, j);
      }
    }
    return res;
  }
} sub1;

struct SUB4 { /// SUB 4
  vector<int> comp;
  vector<int> rindex;
  vector<int> first_occur, last_occur;

  void build_occur() {
    comp.reserve(n);
    rindex.assign(n+1, 0);
    first_occur.assign(n+1, inf);
    last_occur.assign(n+1, -inf);

    for (int i = 1; i <= n; i++) {
      comp.push_back(A[i]);
    }

    sort(comp.begin(), comp.end());
    comp.erase(unique(comp.begin(), comp.end()), comp.end());
    auto fnd = [&](int val) {
      return lower_bound(comp.begin(), comp.end(), val) - comp.begin() + 1;
    };

    for (int i = 1; i <= n; i++) {
      int fnd_index = fnd(A[i]);
      rindex[i] = fnd_index;

      first_occur[fnd_index] = min(first_occur[fnd_index], i);
      last_occur[fnd_index] = max(last_occur[fnd_index], i);
    }

#if _debug == 1
    debug("comp");
    for (int x : comp) cout << x << ' ';
    newline;
    for (int i = 1; i <= n; i++) {
      debug(i);
      debug(rindex[i]);
      debug(first_occur[rindex[i]]);
      debug(last_occur[rindex[i]]);
      newline;
    }
#endif // _debug
  }

  vector<int> nxt;
  void build_nxt() {
    nxt.assign(n+1, 0);

    struct BLOCK {
      int index;
      int left, right;
    };
    vector<BLOCK> st;

    for (int i = n; i >= 1; i--) {
      int fnd_index = rindex[i];

      int lbound = first_occur[fnd_index];
      int rbound = last_occur[fnd_index];

      while (!st.empty() && st.back().index <= rbound) {
        lbound = min(lbound, st.back().left);
        rbound = max(rbound, st.back().right);
        st.pop_back();
      }

      if (lbound < i) nxt[i] = inf;
      else nxt[i] = rbound;

      st.push_back({i, lbound, rbound});
    }

#if _debug == 1
    for (int i = 1; i <= n; i++) {
      debug(i);
      debug(nxt[i]);
      newline;
    }
#endif // _debug
  }

  vector<int> dp;
  void init() {
    build_occur();
    build_nxt();
    dp.assign(n + 1, 0);
  }

  long long solve(int l, int r) {
    long long res = 0;
    for (int i = r; i >= l; i--) {
      dp[i] = (nxt[i] <= r);
      if (nxt[i] + 1 <= r) dp[i] += dp[ nxt[i] + 1];

      res += dp[i];
    }

#if _debug == 1
    for (int i = 1; i <= n; i++) {
      debug(i);
      debug(dp[i]);
      newline;
    }
#endif // _debug

    return res;
  }
} sub4;


struct SUB3 : SUB4 { /// SUB 3
  vector<vector<bool>> is_valid;
  vector<vector<int>> dp;

  void init() {
    is_valid.assign(n+2, vector<bool>(n+2, false));
    dp.assign(n+2, vector<int>(n+2, 0));

    SUB4::build_occur();

    for (int i = 1; i <= n; i++) {
      int lbound = inf;
      int rbound = -inf;
      for (int j = i; j <= n; j++) {
        int fnd_index = rindex[j];
        lbound = min(lbound, first_occur[fnd_index]);
        rbound = max(rbound, last_occur[fnd_index]);

        if (lbound >= i && rbound == j) is_valid[i][j] = 1;
      }
    }

    for (int len = 1; len <= n; len++) {
      for (int l = 1; l <= n - len + 1; l++) {
        int r = l + len - 1;

        dp[l][r] = is_valid[l][r] + dp[l + 1][r] + dp[l][r - 1] - dp[l + 1][r - 1];
      }
    }
  }

  long long solve(int l, int r) {
    return dp[l][r];
  }

} sub3;

struct SUB2 : SUB4 { /// SUB 2
  vector<vector<long long>> table;
  void init() {
    SUB4::init();

    table.assign(n+1, vector<long long>(n + 1, 0));
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= n; j++) {
        table[i][j] = SUB4::solve(i, j);
      }
    }
  }

  long long solve(int l, int r) {
    return table[l][r];
  }
} sub2;

struct SUB5 : SUB4 { /// SUB 5
  int block_size;
  int block_cnt;

  struct BLOCK {
    int total_dp;
    int left_cnt;
    int right_cnt;
  };
  vector<BLOCK> block;

  BLOCK merge_block(const BLOCK& x, const BLOCK& y) {
    BLOCK res;
    res.total_dp = x.total_dp + y.total_dp;
    res.left_cnt = x.left_cnt;
    res.right_cnt = y.right_cnt;
    if (x.right_cnt && y.left_cnt) {
      res.total_dp -= x.right_cnt * (x.right_cnt - 1) / 2;
      res.total_dp -= y.left_cnt * (y.left_cnt - 1) / 2;
      long long sum_cnt = x.right_cnt + y.left_cnt;
      res.total_dp += sum_cnt * (sum_cnt - 1) / 2;

      if (x.left_cnt == x.right_cnt) res.left_cnt += y.left_cnt;
      if (y.left_cnt == y.right_cnt) res.right_cnt += x.right_cnt;
    }
    return res;
  }

  void init() {
    SUB4::init();

    block_size = max(1, n / (int)sqrt(q));
    block_cnt = n / block_size + 1;

    for (int i = 1; i <= block_cnt; i++) {
      int start_index = (i - 1) * block_size + 1;
      int end_index = i * block_size;
      int ok = 1;
      for (int j = end_index; j >= start_index; j--) {
        dp[j] = (nxt[j] <= end_index);
        if (nxt[j] + 1 <= end_index) dp[j] += dp[nxt[j] + 1];
        block[i].total_dp += dp[j];


        if (nxt[j] + 1 <= end_index) {
          if (ok) block[i].right_cnt++;
          block[i].left_cnt++;
        } else {
          ok = 0;
          block[i].left_cnt = (nxt[j] <= end_index);
        }

      }
      #if _debug == 1
      debug(i);
      debug(block[i].total_dp);
      debug(block[i].left_cnt);
      debug(block[i].right_cnt);
      newline;
      #endif // _debug
    }

    for (int i = 1; i <= n; i++) {
      debug(i);
      debug(dp[i]);
      newline;
    }
  }

} sub5;

int main() {
  cin.tie(0)->sync_with_stdio(0);

#if _debug == 1
  freopen("input.inp", "r", stdin);

#else
  freopen("POST.INP", "r", stdin);
  freopen("POST.OUT", "w", stdout);

#endif // _debug

  cin >> n >> q;
  for (int i = 1; i <= n; i++) cin >> A[i];
  for (int i = 1; i <= q; i++) cin >> query[i].first >> query[i].second;
//
//  if (n <= 50 && q <= 50) {
//    debug("SUB1");
//    newline;
//
//    sub1.init();
//    for (int i = 1; i <= q; i++) {
//      cout << sub1.solve(query[i].first, query[i].second) << '\n';
//    }
//    return 0;
//  }
//
//  if (n <= 500) {
//    debug("SUB2");
//    newline;
//
//    sub2.init();
//    for (int i = 1; i <= q; i++) {
//      cout << sub2.solve(query[i].first, query[i].second) << '\n';
//    }
//    return 0;
//  }
//
//  if (n <= 5000) {
//    debug("SUB3");
//    newline;
//
//    sub3.init();
//    for (int i = 1; i <= q; i++) {
//      cout << sub3.solve(query[i].first, query[i].second) << '\n';
//    }
//    return 0;
//  }
//
//  if (q == 1 && query[1].first == 1 && query[1].second == n) {
//    debug("SUB4");
//    newline;
//
//    sub4.init();
//    for (int i = 1; i <= q; i++) {
//      cout << sub4.solve(query[i].first, query[i].second) << '\n';
//    }
//    return 0;
//  }

  if (q <= 30'000) {
    debug("SUB5");
    newline;

    sub5.init();
  }

}
