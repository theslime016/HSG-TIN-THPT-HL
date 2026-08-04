#include <bits/stdc++.h>
using namespace std;

const int inf = 1e9;

#define debugr(x) cout << #x << " = " << (x) << '\n'
#define debugl cout << '\n'

int main() {
  cin.tie(0)->sync_with_stdio(false);

  freopen("SUMODD.INP", "r", stdin);
  freopen("SUMODD.OUT", "w", stdout);

  int n;
  cin >> n;

  vector<int> pref(n + 1, 0);
  vector<vector<int>> first_occur(2, vector<int>(n + 1, inf));
  first_occur[0][0] = 0;
  for (int i = 1; i <= n; i++) {
    char c;
    cin >> c;
    pref[i] += pref[i - 1] + c - '0';
    bool parity = pref[i] % 2;
    first_occur[parity][i] = i;
    first_occur[!parity][i] = first_occur[!parity][i - 1];
  }

  vector<int> req(n + 1, inf);
  req[n] = 1;
  for (int i = n - 1; i >= 0; i--) {
    for (int j = i + 1; j <= n; j++) {
      if (pref[i] % 2 == pref[j] % 2)
        continue;
      req[i] = min(req[i], max(j - i, req[j]));
    }
  }

  for (int m = 1; m <= n; m++) {
    int index = 0;
    bool parity = 0;
    int cost = 0;
    while (index < n) {
      int range = min(n, index + m);

      for (; range > index; range--) {
        int a = first_occur[!parity][range];
        if (a <= index || a == inf)
          continue;
        if (req[a] > m)
          continue;
        break;
      }
      if (range == index)
        break;

      index = first_occur[!parity][range];
      parity = !parity;
      cost++;
    }

    if (index == n)
      cout << cost << ' ';
    else
      cout << -1 << ' ';
  }

  return 0;
}
