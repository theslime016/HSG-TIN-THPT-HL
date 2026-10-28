#include <bits/stdc++.h>
using namespace std;

#if defined(__has_include) && __has_include("slime_debug_016.h")
#include "slime_debug_016.h"

#else
#define _debug 0

#endif // defined

/// DEBUG MACRO
#if _debug
#define debug(x) cerr << #x << ':' << (x) << ' ';
#define newline cerr << '\n';

#else
#define debug(x) 42
#define newline 42

#endif // _debug



const int maxn = 3e5 + 5;
const int inf = 1e9;

struct SEGMENT {
  int n;
  int type; /// 1 min | 2 max
  int null_val;
  vector<int> data;

  SEGMENT(int _n, int _type) {
    n = _n;
    type = _type;
    if (type == 1) null_val = inf;
    else if (type == 2) null_val = -inf;

    data.assign(n << 2, null_val);
  }

  int proc(int a, int b) {
    if (type == 1) return min(a, b);
    else if (type == 2) return max(a, b);
  }

  void update(int index, int l, int r, int qindex, int val) {
    if (l == r) {
      data[index] = val;
      return;
    }

    int mid = l + ((r - l) >> 1);
    if (qindex <= mid) {
      update(index << 1, l, mid, qindex, val);
    } else {
      update(index << 1 | 1, mid + 1, r, qindex, val);
    }
    data[index] = proc(data[index << 1], data[index << 1 | 1]);
  }

  int fetch(int index, int l, int r, int ql, int qr) {
    if (l > qr || r < ql) return null_val;
    if (l >= ql && r <= qr) return data[index];

    int mid = l + ((r - l) >> 1);
    return proc(fetch(index << 1, l, mid, ql, qr),
                fetch(index << 1 | 1, mid + 1, r, ql, qr));
  }

};


struct SUBTASK1234 {
  int n, q;
  vector<int> A;
  vector<int> nxt;
  vector<int> dp;
  vector<int> comp;
  vector<int> first_occur, last_occur;
  vector<int> rindex;

  void init(int _n, int _q, vector<int>&& _A) {
    n = _n;
    q = _q;

    A = move(_A);

    first_occur.assign(n + 1, inf);
    last_occur.assign(n + 1, -1);

    nxt.assign(n + 1, inf);
    rindex.assign(n + 1, 0);

    comp.reserve(n);

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

#if _debug
    debug("comp");
    for (int x : comp) cout << x << ' ';
    newline;

    for (int i = 1; i <= n; i++) {
      debug(i);
      debug(A[i]);
      debug(rindex[i]);
      newline;
    }

    newline;
    for (int i = 1; i <= comp.size(); i++) {
      debug(i);
      debug(comp[i - 1]);
      debug(first_occur[i]);
      debug(last_occur[i]);
      newline;
    }


#endif // _debug

    SEGMENT segment_min(n, 1), segment_max(n, 2);
    for (int i = n; i >= 1; i--) {
      int fnd_index = rindex[i];

      segment_min.update(1, 1, n, i, first_occur[fnd_index]);

      int lim_down = segment_min.fetch(1, 1, n, i, last_occur[fnd_index]);
      if (lim_down < i) {
        nxt[i] = inf;
        continue;
      }

      nxt[i] = max(last_occur[fnd_index], segment_max.fetch(1, 1, n, i + 1, last_occur[fnd_index] - 1));

      segment_max.update(1, 1, n, i, nxt[i]);
    }

#if _debug
    for (int i = 1; i <= n; i++) {
      debug(i);
      debug(nxt[i]);
      newline;
    }
    newline;
#endif // _debug

  }

  long long solve(int l, int r) {
    dp.assign(n + 1, 0);
    long long res = 0;
    for (int i = r; i >= l; i--) {
      dp[i] = nxt[i] <= r;
      if (nxt[i] + 1 <= r) dp[i] += dp[nxt[i] + 1];

      res += dp[i];
    }

#if _debug
    for (int i = l; i <= r; i++) {
      debug(i);
      debug(dp[i]);
      newline;
    }
#endif // _debug

    return res;
  }



} subtask1234;

int main() {
  cin.tie(0)->sync_with_stdio(0);

#if _debug
  freopen("input.inp", "r", stdin);

#else
  freopen("POST.INP", "r", stdin);
  freopen("POST.OUT", "w", stdout);

#endif // _debug

  int n, q;
  cin >> n >> q;
  vector<int> A(n + 1, 0);
  for (int i = 1; i <= n; i++) cin >> A[i];

  if (n <= 5000 || q == 1) {
    debug("SUBTASK1234");
    subtask1234.init(n, q, move(A));

    while (q--) {
      int l, r;
      cin >> l >> r;
      cout << subtask1234.solve(l, r) << '\n';
    }

    return 0;
  }

}
