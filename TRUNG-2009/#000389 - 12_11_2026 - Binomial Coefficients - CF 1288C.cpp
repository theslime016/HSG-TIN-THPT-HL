#include <bits/stdc++.h>
using namespace std;

#define _debug 0

const int maxn = 1005;
const int maxk = 25;
const long long mod = 1e9 + 7;
long long C[maxk][maxn];

int main() {
  cin.tie(0)->sync_with_stdio(0);

  #if _debug == 1
  freopen("input.inp", "r", stdin);

  #else

  #endif // _debug

  int n, m;
  cin >> n >> m;
  int select = 2 * m;
  int base = (n - 1) + 2 * m;
  for (int i = 0; i <= base; i++) {
    C[0][i] = 1;
    for (int j = 1; j <= select; j++) {
      C[j][i] = (C[j - 1][i - 1] + C[j][i - 1]) % mod;
    }
  }

  cout << C[select][base];

}
