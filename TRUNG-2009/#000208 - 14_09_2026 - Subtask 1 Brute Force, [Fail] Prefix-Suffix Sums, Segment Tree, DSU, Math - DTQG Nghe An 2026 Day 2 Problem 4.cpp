#include <bits/stdc++.h>
using namespace std;

int n, q;
long long m;
const int maxn = 2e5 + 5;
pair<long long, long long> A[maxn];

namespace brute {
void solve() {
  cin >> q;
  while (q--) {
    int l, r;
    cin >> l >> r;
    int flag = 1;
    for (int i = l; i <= r && flag; i++) {
      for (int j = i + 1; j <= r && flag; j++) {
        if (A[i].first == A[j].first || A[i].second == A[j].second ||
            abs(A[i].first - A[j].first) == abs(A[i].second - A[j].second)) {
          flag = 0;
          break;
        }
      }
    }
    if (!flag)
      cout << "No" << '\n';
    else
      cout << "Yes" << '\n';
  }
}
} // namespace brute

namespace fallback {
int dsu[5][maxn];
struct node {
  int valid;
  int maxl, maxr;
} segment[maxn];
void solve() {
  vector<long long> X, Y, cheo1x, cheo2y, cheo3x;
  X.reserve(n);
  Y.reserve(n);
  cheo1x.reserve(n);
  cheo2y.reserve(n);
  cheo3x.reserve(n);

  int l[maxn], r[maxn];
  for (int i = 1; i <= n; i++) {
    X.push_back(A[i].first);
    Y.push_back(A[i].second);
    long long x = A[i].first;
    long long y = A[i].second;
    if (x >= y) {
      cheo1x.push_back(x - y + 1);
    } else {
      cheo2y.push_back(y - x + 1);
    }
    cheo3x.push_back(x + y - 1);
  }

  sort(X.begin(), X.end());
  X.erase(unique(X.begin(), X.end()), X.end());
  sort(Y.begin(), Y.end());
  Y.erase(unique(Y.begin(), Y.end()), Y.end());

  sort(cheo1x.begin(), cheo1x.end());
  cheo1x.erase(unique(cheo1x.begin(), cheo1x.end()), cheo1x.end());
  sort(cheo2y.begin(), cheo2y.end());
  cheo2y.erase(unique(cheo2y.begin(), cheo2y.end()), cheo2y.end());
  sort(cheo3x.begin(), cheo3x.end());
  cheo3x.erase(unique(cheo3x.begin(), cheo3x.end()), cheo1x.end());

  for (int i = 1; i <= n; i++) {
  }
}

} // namespace fallback

#define _debug 0

int main() {
  cin.tie(0)->sync_with_stdio(0);

#if _debug == 1
  freopen("input.inp", "r", stdin);
#else

#endif // _debug

  cin >> n >> m;

  for (int i = 1; i <= n; i++) {
    cin >> A[i].first >> A[i].second;
  }

  /// SUB1
  brute::solve();
}
