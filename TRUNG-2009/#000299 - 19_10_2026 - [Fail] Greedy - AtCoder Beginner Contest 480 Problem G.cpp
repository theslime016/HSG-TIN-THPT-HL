#include <bits/stdc++.h>
using namespace std;

#define _debug 1

#if _debug == 1
#define debug(x) cerr << #x << ':' << (x) << ' ';
#define debugn(x) cerr << #x << ':' << (x) << '\n';
#define newline cerr << '\n';

#else
#define debug(x)
#define debugn(x)
#define newline

#endif // _debug

const int maxn = 2e5 + 5;
const long long inf = 1e18;
long long A[maxn];
long long pref[maxn];
long long suff[maxn];

int main() {
  cin.tie(0)->sync_with_stdio(0);

  #if _debug == 1
  freopen("input.inp", "r", stdin);

  #else

  #endif // _debug

  int n;
  cin >> n;
  for (int i = 1; i <= n; i++) cin >> A[i];

  if (n%2 == 0) {
    long long res = 0;
    for (int i = 1; i < n; i++) {
      res += max(A[i], A[i+1]) - min(A[i], A[i+1]);
    }
    cout << res;
    return 0;
  }

  long long current1 = 0;
  for (int i = 1; i < n; i+=2) {
    current1 += max(A[i], A[i+1]) - min(A[i], A[i+1]);
    pref[i] = current1;
  }

  long long current2 = 0;
  for (int i = n - 1; i >= 2; i-=2) {
    current2 += max(A[i], A[i+1]) - min(A[i], A[i+1]);
    suff[i] = current2;
  }

  long long best = inf;
  for (int i = 1; i < n; i++) {
    long long val = max({A[i], A[i+1], A[i+2]}) - min({A[i], A[i+1], A[i+2]});

    long long head = i - 2 >= 1 ? pref[i - 2] : 0;
    long long tail = i + 3 <= n ? suff[i + 3] : 0;

    best = min(best, head + val + tail);

  }

  cout << best;

}
