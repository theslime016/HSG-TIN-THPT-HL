#include <bits/stdc++.h>
using namespace std;

const int maxn = 5e4 + 5;
long long A[maxn];
long long pref[maxn];

#define _debug 0
int main() {
  cin.tie(0)->sync_with_stdio(0);

  #if _debug == 1
  freopen("input.inp", "r", stdin);
  #else

  #endif // _debug

  int n;
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> A[i];
    pref[i] = A[i] + pref[i-1];
  }

  int res = 0;
  for (int k = 1; k <= n; k++) {
    long long val = 2 * pref[k];
    int l = 1;
    int r = n;
    while (l < r && l <= k && r >= k) {
      long long other_val = pref[l-1] + pref[r];
      if (other_val > val) r--;
      else if (other_val < val) l++;
      else {
        res = max(res, r - l + 1);
        break;
      }
    }
  }

  cout << res;

}
