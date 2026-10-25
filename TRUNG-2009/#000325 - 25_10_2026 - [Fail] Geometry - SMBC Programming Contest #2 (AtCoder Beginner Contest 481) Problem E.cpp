#include <bits/stdc++.h>
using namespace std;

#define _debug 0

#if _debug == 1
#define debug(x) cerr << #x << ':' << (x) << ' ';
#define newline cerr << '\n';

#else
#define debug(x)
#define newline

#endif // _debug

const int maxn = 2e5 + 5;
const double pi = acos(-1.0);
const double esp = 1e-12;
int X[maxn], Y[maxn];

int main() {
  cin.tie(0)->sync_with_stdio(0);

#if _debug == 1
  freopen("input.inp", "r", stdin);

#elif _debug == 2
  freopen("input.inp", "r", stdin);

#else

#endif // _debug

  int t;
  cin >> t;
  while (t--) {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> X[i] >> Y[i];

    vector<double> angles; // radian
    angles.reserve(2*n);
    for (int i = 1; i <= n; i++) {
      double current = atan2(Y[i], X[i]);
      double copy_current = current + 2 * pi;
      angles.push_back(current);
      angles.push_back(copy_current);
    }
    sort(angles.begin(), angles.end());

    int res = 0;
    int ptr1 = 0;
    int ptr2 = 0;
    while (ptr1 < 2*n) {

      while (ptr2 + 1 < 2*n && angles[ptr2 + 1] - angles[ptr1] <= pi) ptr2++;

      res = max(res, ptr2 - ptr1 + 1);

      ptr1++;
    }

    cout << res << '\n';
  }
}
