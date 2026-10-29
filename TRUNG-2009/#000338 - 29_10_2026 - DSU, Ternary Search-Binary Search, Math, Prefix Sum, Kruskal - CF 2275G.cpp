#include <bits/stdc++.h>
using namespace std;

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

const int maxn = 1e5 + 5;
const int maxedge = 2e5 + 5;
const long long inf = 1e18;
int n, m, q;

struct EDGE {
  int a, b;
  long long val;

  friend bool operator<(const EDGE& a, const EDGE& b) {
    return a.val < b.val;
  }
} edge[maxedge];

struct DSU {
  int n;
  long long rem;
  vector<int> data;
  vector<int> bucket;
  vector<long long> selected; // val

  DSU(int _n) {
    n = _n;
    rem = n - 1;
    data.assign(n + 1, 0);
    iota(data.begin(), data.end(), 0);
    bucket.assign(n + 1, 1);
    selected.reserve(n + 1);
  }

  int fnd(int index) {
    if (data[index] == index) return index;
    return data[index] = fnd(data[index]);
  }

  bool proc(int a, int b, long long val) {
    a = fnd(a);
    b = fnd(b);
    if (a != b) {
      if (bucket[a] < bucket[b]) swap(a, b);
      bucket[a] += b;
      data[b] = a;

      rem--;
      selected.push_back(val);
      return true;
    }
    return false;
  }

};

int main() {
  cin.tie(0)->sync_with_stdio(0);

#if _debug
  freopen("input.inp", "r", stdin);

#else

#endif // _debug

  int t;
  cin >> t;
  while (t--) {
    cin >> n >> m >> q;
    for (int i = 1; i <= m; i++) {
      int a, b;
      long long val;
      cin >> a >> b >> val;
      edge[i] = {a, b, val};
    }

    sort(edge + 1, edge + m + 1);

    #if _debug == 1
    for (int i = 1; i <= m; i++) {
      debug(i);
      debug(edge[i].a);
      debug(edge[i].b);
      debug(edge[i].val);
      newline;
    }

    #endif // _debug

    DSU dsu(n);
    long long base_profit = 0;
    for (int i = 1; i <= m; i++) {
      if (!dsu.proc(edge[i].a, edge[i].b, edge[i].val)) {
        base_profit += edge[i].val;
      }
    }

    sort(dsu.selected.begin(), dsu.selected.end(), greater<long long>());
    int s = dsu.selected.size();
    vector<long long> pref(s + 1, 0);
    for (int i = 1; i <= s; i++) pref[i] = pref[i-1] + dsu.selected[i-1];

    #if _debug == 1
    debug("selected");
    newline;
    for (long long x : dsu.selected) cerr << x << ' ';
    newline;

    #endif // _debug

    while (q--) {
      long long cost;
      cin >> cost;

      long long res = base_profit - cost * (dsu.rem * (dsu.rem + 1)/2);
      long long best_profit = 0LL;

      auto get_profit = [&](long long len) {
        if (len < 1) return -inf;
        long long nxt = dsu.rem + len;
        long long val = ( (nxt * (nxt + 1)) - (dsu.rem * (dsu.rem + 1)) )/2;
        return pref[len] - val * cost;
      };

      #if _debug == 1
      for (int i = 0; i <= s; i++) {
        debug(i);
        debug(pref[i]);
        newline;
      }
      debug(cost);
      debug(dsu.rem);
      debug(base_profit);
      debug(res);
      newline;

      #endif // _debug

      int l = 1;
      int r = s;
      while (l <= r) {
        if (r - l + 1 <= 10) {
          while (l <= r) {
            best_profit = max(best_profit, get_profit(l));
            l++;
          }
          break;
        }

        int mid1 = l + (r - l)/3;
        int mid2 = r - (r - l)/3;

        long long profit1 = get_profit(mid1);
        long long profit2 = get_profit(mid2);
        if (profit1 < profit2) {
          l = mid1;
        } else {
          r = mid2;
        }

      }

      cout << res + best_profit << ' ';
    }
    cout << '\n';

  }

}
