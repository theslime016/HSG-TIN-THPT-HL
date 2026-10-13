#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5 + 5;
struct POINT {
  long long val;
  long long cnt;

  friend bool operator<(const POINT& a, const POINT& b) {
    return a.val > b.val;
  }
} point[maxn];

#define _debug 0
int main() {
  cin.tie(0)->sync_with_stdio(0);

  #if _debug == 1
  freopen("input.inp", "r", stdin);
  #else

  #endif // _debug

  long long n, m;
  int k;
  cin >> n >> m >> k;

  for (int i = 1; i <= k; i++) cin >> point[i].val >> point[i].cnt;
  sort(point + 1, point + k + 1);

  long long lim = (n * m + 1) / 2;
  long long proc = 0;
  long long res = 0;
  for (int i = 1; i <= k; i++) {
    if (proc >= n * m) break;

    long long valid = min({lim, point[i].cnt, n * m - proc});
    res += valid * point[i].val;
    proc += valid;
  }

  cout << res;

}
