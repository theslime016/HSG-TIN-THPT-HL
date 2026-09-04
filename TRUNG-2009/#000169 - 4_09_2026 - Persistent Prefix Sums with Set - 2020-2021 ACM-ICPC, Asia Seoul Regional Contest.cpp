#include <bits/stdc++.h>
using namespace std;

const int maxn = 2005;
const long long inf = 1e15;
long long pref[maxn];

int main() {
  cin.tie(0)->sync_with_stdio(0);
  int n, m;
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    cin >> pref[i];
    pref[i] += pref[i - 1];
  }

  while (m--) {
    int l, r;
    long long k;
    cin >> l >> r >> k;

    long long res = -inf;
    set<long long> timeline;
    timeline.insert(pref[l - 1]);
    for (int i = l; i <= r; i++) {
      auto it = timeline.lower_bound(pref[i] - k);
      if (it != timeline.end())
        res = max(res, pref[i] - *it);
      timeline.insert(pref[i]);
    }
    if (res == -inf)
      cout << "NONE" << '\n';
    else
      cout << res << '\n';
  }
}
