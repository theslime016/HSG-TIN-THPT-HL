#include <bits/stdc++.h>
using namespace std;

const int maxn = 2005;
char A[maxn][maxn];
int m, n;
int cnt_M;
int cnt_T;

/// sub1
namespace sub1 {
long long solve() {
  if (cnt_M) {
    return -1;
  } else {
    int dist[2];
    int pos = 0;
    for (int i = 1; i <= n; i++) {
      if (A[m][i] == 'T')
        dist[pos++] = i;
    }
    int range = dist[1] - dist[0] + 1;
    if (range % 2 == 0)
      return -1;
    else
      return range / 2;
  }
}
}

int main() {
  cin.tie(0)->sync_with_stdio(0);

  freopen("GATHER.INP", "r", stdin);
  freopen("GATHER.OUT", "w", stdout);

  int m, n;
  cin >> m >> n;
  for (int i = 1; i <= m; i++) {
    for (int j = 1; j <= n; j++) {
      cin >> A[i][j];
      if (A[i][j] == 'M')
        cnt_M++;
      if (A[i][j] == 'T')
        cnt_T++;
    }
  }

  if (cnt_T + cnt_M == 2) {
    if (m == 1) {
      cout << sub1::solve();
      return 0;
    }
    // cout << sub2::solve();
    // return 0;
  }

  cout << -1;
  /// fallback
}
