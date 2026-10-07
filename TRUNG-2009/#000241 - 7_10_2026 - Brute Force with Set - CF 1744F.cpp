#include <bits/stdc++.h>
using namespace std;

const int maxn = 2e5 + 5;
int A[maxn];

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
    for (int i = 1; i <= n; i++) cin >> A[i];

    int res = 0;
    for (int i = 1; i <= n; i++) {
      set<int> s;
      for (int j = i; j <= n; j++) {
        s.insert(A[j]);
        int mex = -1;
        for (int k = 0; k <= n; k++) {
          if (!s.count(k)) {
            mex = k;
            break;
          }
        }

        int mid = (s.size()+1)/2;
        auto it = s.begin();
        for (int k = 1; k <= mid - 1 && it != s.end(); k++, it++) {}
        int med = *it;

        if (mex > med) {
          res++;
        }
      }
    }

    cout << res << '\n';

  }
}
