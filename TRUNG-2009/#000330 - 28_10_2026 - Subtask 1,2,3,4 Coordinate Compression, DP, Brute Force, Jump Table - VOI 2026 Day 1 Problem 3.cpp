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


    for (int i = n; i >= 1; i--) {
      int fnd_index = rindex[i];
      int lbound = first_occur[fnd_index];
      int rbound = last_occur[fnd_index];

      int j = i + 1;
      while (j <= rbound) {
        fnd_index = rindex[j];
        if (nxt[j] != inf) j = nxt[j] + 1;
        else {
          lbound = min(lbound, first_occur[fnd_index]);
          rbound = max(rbound, last_occur[fnd_index]);
          j++;
        }

        if (lbound < i) break;
      }

#if _debug
      debug(i);
      debug(j);
      debug(lbound);
      debug(rbound);
      newline;

#endif // _debug

      if (lbound < i) nxt[i] = inf;
      else nxt[i] = j - 1;
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
