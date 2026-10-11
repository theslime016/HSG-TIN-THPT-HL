#include <bits/stdc++.h>
using namespace std;
#define _debug 0

const int maxn = 1e6;
const long long inf = 1e15;
int n, q;
long long L[maxn], R[maxn];
long long best_l[maxn], best_r[maxn];

int main() {
  cin.tie(0)->sync_with_stdio(0);

  #if _debug == 1
  freopen("input.inp", "r", stdin);
  #else

  #endif // _debug

  cin >> n >> q;
  for (int i = 2; i <= n; i++) cin >> L[i];
  for (int i = 1; i < n; i++) cin >> R[i];

  best_l[n] = L[n];
  best_r[1] = R[1];
  best_l[1] = best_r[n] = inf;
  for (int i = n-1; i >= 1; i--) best_l[i] = min(best_l[i+1], L[i]);
  for (int i = 2; i < n; i++) best_r[i] = min(best_r[i-1], R[i]);

  while (q--) {
    int s, t;
    cin >> s >> t;
    if (s < t) {
      cout << min(L[s] + best_r[s], R[s]) << '\n';
    } else {
      cout << min(R[s] + best_l[s], L[s]) << '\n';
    }
  }
}
