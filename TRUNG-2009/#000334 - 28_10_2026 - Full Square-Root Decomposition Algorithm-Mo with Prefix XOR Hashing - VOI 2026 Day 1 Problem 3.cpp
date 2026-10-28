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

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

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

struct SUB56 { /// SUB 5,6
  int block_size;
  int block_cnt;
  vector<long long> xor_hashing;
  vector<long long> pref_xor;
  vector<long long> comp;
  vector<int> get_block;
  vector<int> rindex;
  vector<int> old_index;

  void build_xor() {
    xor_hashing.assign(n+1, 0);
    pref_xor.assign(n + 1, 0);

    vector<int> cnt(n + 1, 0);
    vector<long long> total_xor(n + 1, 0);

    vector<int> comp_A;
    comp_A.reserve(n);
    for (int i = 1; i <= n; i++) comp_A.push_back(A[i]);
    sort(comp_A.begin(), comp_A.end());
    comp_A.erase(unique(comp_A.begin(), comp_A.end()), comp_A.end());

    vector<int> get_index(n + 1, 0);
    for (int i = 1; i <= n; i++) {
      get_index[i] = lower_bound(comp_A.begin(), comp_A.end(), A[i]) - comp_A.begin() + 1;
    }

    for (int i = 1; i <= n; i++) {
      int fnd_index = get_index[i];
      cnt[fnd_index]++;
    }

    for (int i = 1; i <= n; i++) {
      int fnd_index = get_index[i];
      if (cnt[ fnd_index ] > 1) {
        xor_hashing[i] = rng();
        if (!total_xor[ fnd_index ]) total_xor[ fnd_index ] = xor_hashing[i];
        else total_xor[ fnd_index ] ^= xor_hashing[i];
        cnt[ fnd_index ]--;
      } else if (cnt[ fnd_index ] == 1) {
        xor_hashing[i] = total_xor[ fnd_index ];
        cnt[ fnd_index ]--;
      }
      pref_xor[i] ^= xor_hashing[i];
      pref_xor[i] ^= pref_xor[i-1];
    }

#if _debug == 1
    for (int i = 1; i <= n; i++) {
      debug(i);
      debug(A[i]);
      debug(xor_hashing[i]);
      debug(pref_xor[i]);
      newline;
    }
#endif // _debug
  }

  void build_query() {
    block_size = max(1, n / (int)sqrt(q));
    block_cnt = (n - 1) / block_size + 1;

    get_block.assign(n + 1, 0);
    for (int i = 1; i <= n; i++) {
      get_block[i] = (i - 1) / block_size + 1;
    }

    for (int i = 1; i <= q; i++) {
      query[i].first--;
    }

    auto cmp = [&](const pair<int, int>& a, const pair<int, int>& b) {
      int tag_a = get_block[a.first];
      int tag_b = get_block[b.first];
      if (tag_a != tag_b) return tag_a < tag_b;

      if (tag_a & 1) return a.second < b.second;
      else return a.second > b.second;
    };

    old_index.assign(q + 1, 0);
    iota(old_index.begin(), old_index.end(), 0);
    sort(old_index.begin() + 1, old_index.end(), [&](const int x, const int y) {
      return cmp(query[x], query[y]);
    });
    sort(query + 1, query + q + 1, cmp);

#if _debug == 1
    for (int i = 1; i <= q; i++) {
      debug(i);
      debug(query[i].first);
      debug(query[i].second);
      newline;
    }
#endif // _debug
  }

  void build_rindex_xor() {
    rindex.assign(n + 1, 0);
    comp.reserve(n);
    for (int i = 1; i <= n; i++) comp.push_back(pref_xor[i]);

    sort(comp.begin(), comp.end());
    comp.erase(unique(comp.begin(), comp.end()), comp.end());
    for (int i = 0; i <= n; i++) {
      rindex[i] = lower_bound(comp.begin(), comp.end(), pref_xor[i]) - comp.begin() + 1;
    }

#if _debug == 1
    for (int i = 1; i <= n; i++) {
      debug(i);
      debug(rindex[i]);
      newline;
    }
#endif // _debug
  }

  void init() {
    build_xor();
    build_query();
    build_rindex_xor();
  }

  vector<int> cnt;
  vector<long long> res_query;
  int add(int index) {
    int fnd_index = rindex[index];
    int diff = cnt[fnd_index];
    cnt[fnd_index]++;
    return diff;
  }

  int rem(int index) {
    int fnd_index = rindex[index];
    cnt[fnd_index]--;
    int diff = -cnt[fnd_index];
    return diff;
  }

  void solve() {
    cnt.assign(n + 1, 0);
    res_query.assign(q + 1, 0);

    int l = 1, r = 0;
    long long res = 0;

    cnt[0] = 1;

    for (int i = 1; i <= q; i++) {
      int ql = query[i].first;
      int qr = query[i].second;
      while (l > ql) {
        l--;
        res += add(l);
      }
      while (r < qr) {
        r++;
        res += add(r);
      }

      while (l < ql) {
        res += rem(l);
        l++;
      }
      while (r > qr) {
        res += rem(r);
        r--;
      }

      int query_index = old_index[i];
      res_query[query_index] = res;

#if _debug == 1
      debug(i);
      newline;
      for (int j = 1; j <= (int)comp.size(); j++) {
        debug(comp[j - 1]);
        debug(cnt[j]);
        newline;
      }

#endif // _debug

    }

    for (int i = 1; i <= q; i++) {
      cout << res_query[i] << '\n';
    }
  }

} sub56;

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

  if (n <= 50 && q <= 50) {
    debug("SUB1");
    newline;

    sub1.init();
    for (int i = 1; i <= q; i++) {
      cout << sub1.solve(query[i].first, query[i].second) << '\n';
    }
    return 0;
  }

  if (n <= 500) {
    debug("SUB2");
    newline;

    sub2.init();
    for (int i = 1; i <= q; i++) {
      cout << sub2.solve(query[i].first, query[i].second) << '\n';
    }
    return 0;
  }

  if (n <= 5000) {
    debug("SUB3");
    newline;

    sub3.init();
    for (int i = 1; i <= q; i++) {
      cout << sub3.solve(query[i].first, query[i].second) << '\n';
    }
    return 0;
  }

  if (q == 1 && query[1].first == 1 && query[1].second == n) {
    debug("SUB4");
    newline;

    sub4.init();
    for (int i = 1; i <= q; i++) {
      cout << sub4.solve(query[i].first, query[i].second) << '\n';
    }
    return 0;
  }

  debug("SUB56");
  newline;

  sub56.init();
  sub56.solve();
}
