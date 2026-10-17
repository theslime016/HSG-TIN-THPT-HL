#include <bits/stdc++.h>
using namespace std;

#define _debug 0
int main() {
  cin.tie(0)->sync_with_stdio(0);

  #if _debug == 1
  freopen("input.inp", "r", stdin);
  #else

  #endif // _debug

  int n;
  int k, t;
  cin >> n >> k >> t;
  vector<int> time;
  time.reserve(n+2);
  for (int i = 1; i <= n; i++) {
    int x;
    cin >> x;
    time.push_back(x);
  }
  sort(time.begin(), time.end());
  time.erase(unique(time.begin(), time.end()), time.end());

  int res = 0;
  int last = -1;
  for (int i = 0; i < (int)time.size() && last <= t; i++) {
    if (last > time[i]) {
      last = max(last, time[i] + k);
      continue;
    }

    int val = max(0, time[i] - last - 1);
    int rem = val%k;
    res += val/k + (rem > 0 ? 1 : 0);
    last += (val/k) * k + (rem > 0 ? k : 0);
    last = max(last, time[i] + k);
    //cout << i << ' ' << res << ' ' << last << '\n';
  }

  if (last < t) {
    int val = max(0, t - last);
    int rem = val%k;
    res += val/k + (rem > 0 ? 1 : 1);
  }

  cout << res;

}
