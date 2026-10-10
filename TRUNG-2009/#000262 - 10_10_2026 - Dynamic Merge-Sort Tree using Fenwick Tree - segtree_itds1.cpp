#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5 + 5;
const int inf = 2e9;
int A[maxn];
multiset<int> fenwick[maxn];

#define _debug 0
int main() {
  cin.tie(0)->sync_with_stdio(0);

  #if _debug == 1
  freopen("input.inp", "r", stdin);
  #else

  #endif // _debug

  int n, q;
  cin >> n >> q;
  for (int i = 1; i <= n; i++) {
    cin >> A[i];
    for (int j = i; j < maxn; j += j & -j) fenwick[j].insert(A[i]);
  }

  while (q--) {
    int type;
    cin >> type;
    if (type == 1) {
      int index, val;
      cin >> index >> val;
      int old_val = A[index];
      if (old_val == val) continue;
      A[index] = val;
      for (; index < maxn; index += index & -index) {
        fenwick[index].erase(fenwick[index].find(old_val));
        fenwick[index].insert(val);
      }
    } else if (type == 2) {
      int l, r, k;
      cin >> l >> r >> k;

      int res = inf;
      int pt = r;
      while (pt >= l) {
        int prev = pt - (pt & -pt);
        if (prev >= l) {
          auto it = fenwick[pt].lower_bound(k);
          if (it != fenwick[pt].end() && *it >= k) res = min(res, *it);
          pt = prev;
        } else {
          if (A[pt] >= k) res = min(res, A[pt]);
          pt--;
        }
      }

      if (res == inf) cout << -1 << '\n';
      else cout << res << '\n';
    }
  }

}
