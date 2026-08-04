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
  vector<int> dist(n + 1, inf);
  stack<int> wait;
  dist[n] = 0;
  first_occur[0][0] = 0;
  for (int i = 1; i <= n; i++) {
    char c;
    cin >> c;
    pref[i] += pref[i - 1] + c - '0';
    bool parity = pref[i] % 2;
    first_occur[parity][i] = i;
    first_occur[!parity][i] = first_occur[!parity][i - 1];

    if (!wait.empty() && pref[wait.top()] % 2 != parity) {
      int cost = 1;
      while (!wait.empty()) {
        int jindex = wait.top();
        wait.pop();
        dist[jindex] = cost;
        cost++;
      }
    }
    wait.push(i);
  }

  // for (int i = 0; i < (int)dist.size(); i++) {
  //   debugr(dist[i]);
  // }
  // debugl;

  for (int m = 1; m <= n; m++) {
    int index = 0;
    bool parity = 0;
    int cost = 0;
    while (index < n) {
      int range = min(n, index + m);
      // int new_index = index;
      // for (int d = range - index; d > 0; d /= 2) {
      //   while (new_index + d <= range) {
      //     int a = first_occur[!parity][new_index + d];
      //     if (a <= index || a == 1e9)
      //       break;
      //     if (dist[a] > m)
      //       break;
      //     new_index += d;
      //   }
      // }

      // if (new_index == index)
      //   break;

      for (; range > index; range--) {
        if (first_occur[!parity][range] <= index ||
            first_occur[!parity][range] == 1e9)
          continue;
        if (dist[first_occur[!parity][range]] > m)
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
