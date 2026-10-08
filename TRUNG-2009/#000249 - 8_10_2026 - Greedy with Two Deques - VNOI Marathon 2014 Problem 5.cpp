#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e6 + 5;
int A[maxn];

#define _debug 0
int main() {
  cin.tie(0)->sync_with_stdio(0);

#if _debug == 1
  freopen("input.inp", "r", stdin);
#else

#endif // _debug

  int n, l, d;
  cin >> n >> l >> d;
  for (int i = 1; i <= n; i++) cin >> A[i];

  long long res = 0;
  deque<int> dmax, dmin; // index
  int pt = 0;
  for (int i = 1; i <= n; i++) {
    while (!dmax.empty() && A[dmax.back()] <= A[i]) dmax.pop_back();
    while (!dmin.empty() && A[dmin.back()] >= A[i]) dmin.pop_back();
    dmax.push_back(i);
    dmin.push_back(i);

    while (A[dmax.front()] - A[dmin.front()] > d) {
      pt = min(dmax.front(), dmin.front());
      if (dmax.front() > dmin.front()) dmin.pop_front();
      else dmax.pop_front();
    }

    if (i - pt - l > 0) res += i - pt - l;
  }

  cout << res;

}
