#include <bits/stdc++.h>
using namespace std;
#define _debug 0

#if _debug == 1
#define debugl(x) cerr << #x << ':' << (x) << ' ';
#define debugr(x) cerr << #x << ':' << (x) << '\n';

#else
#define debugl(x)
#define debugr(x)

#endif

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
  int last = 0;
  for (int i = 0; i < (int)time.size() && time[i] < t; i++) {
    if (last >= time[i]) {
      last = max(last, time[i] + k);
      continue;
    }

    int val = max(0, time[i] - last);
    int rem = val%k;
    res += val/k + (rem > 0 ? 1 : 0);
    last += (val/k) * k + (rem > 0 ? k : 0);
    debugl(i);
    debugl(time[i]);

    debugl(rem);
    debugl(val);

    debugl(last);
    last = max(last, time[i] + k);
    debugl(last);

    debugr(res);
  }

  debugr(last);
  debugr(t);

  if (last < t) {
    int val = max(0, t - last);
    int rem = val%k;
    debugl(val);
    debugr(rem);
    res += val/k + (rem > 0 ? 1 : 0);
  }

  cout << res;

}
