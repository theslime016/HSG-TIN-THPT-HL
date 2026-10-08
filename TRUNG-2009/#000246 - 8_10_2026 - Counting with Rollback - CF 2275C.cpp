#pragma GCC optimize("O3,unroll-loops")
#include <bits/stdc++.h>
using namespace std;

const int maxn = 2e5 + 5;
const int padding = 1e5;
const int inf = 1e9;
const int maxnum = 1e6 + 5;
int A[maxn];
long long cnt[maxn];
int rollback[maxn]; // index

inline int proc(int index, int n) {
  if (index < 1 || index + 4 > n) return inf;
  return A[index] + A[index + 2] - A[index + 4] + padding;
}

#define _debug 0
int main() {
  cin.tie(0)->sync_with_stdio(0);

#if _debug == 1
  freopen("input.inp", "r", stdin);
#else

#endif // _debug

  int t;
  cin >> t;
  while (t--) {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
      cin >> A[i];
    }

    long long res = 0;
    int pt = 0;
    for (int i = 1; i <= n; i++) {
      int v1 = proc(i, n);
      if (v1 == inf) continue;
      res += cnt[v1];
      int v2 = proc(i-2, n);
      int v3 = proc(i-4, n);
      if (v2 == v1) res--;
      if (v3 == v1) res--;
      if (cnt[v1] == 0) {
        rollback[pt++] = v1;
      }
      cnt[v1]++;
    }

    while (pt > 0) {
      cnt[ rollback[--pt] ] = 0;
    }

    cout << res << '\n';
  }

}
