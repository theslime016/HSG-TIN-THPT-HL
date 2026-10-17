#include <bits/stdc++.h>
using namespace std;

const long long inf = 1e16;
const int maxn = 2e5 + 5;
pair<long long, long long> range[maxn];
long long pref[maxn];

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
    long long m, k;
    cin >> n >> m >> k;
    for (int i = 1; i <= n; i++) cin >> range[i].first >> range[i].second;
    sort(range + 1, range + n + 1);

    for (int i = 1; i <= n; i++) {
      pref[i] = pref[i-1] + range[i].second - range[i].first + 1;
    }


    auto f = [&](long long val) {
      int l = upper_bound(range + 1, range + n + 1, make_pair(val, inf)) - range - 1;
      int r = upper_bound(range + 1, range + n + 1, make_pair(val + m, inf)) - range - 1;
      long long res_left = l > 0 ? (pref[l-1] + min(range[l].second, val - 1)
                                    - range[l].first + 1) : 0;
      long long res_right = r > 0 ? (pref[r-1] + min(range[r].second, val + m - 1)
                                     - range[r].first + 1) : 0;
      return res_right - res_left;
    };

    long long opt = -1;
    long long ptr1 = -1;
    for (int i = 1; i <= n; i++) {
      long long val = f(range[i].first);
      if (val >= opt) {
        opt = val;
        ptr1 = range[i].first;
      }
    }

    if (opt < k) {
      cout << -1 << '\n';
      continue;
    }

    long long ptr2 = inf;
    while (ptr1 <= ptr2) {
      long long mid = ptr1 + ((ptr2 - ptr1) >> 1);
      long long val = f(mid);
      if (val == k) {
        cout << mid << '\n';
        break;
      } else if (val > k) {
        ptr1 = mid + 1;
      } else {
        ptr2 = mid - 1;
      }
    }
  }
}
