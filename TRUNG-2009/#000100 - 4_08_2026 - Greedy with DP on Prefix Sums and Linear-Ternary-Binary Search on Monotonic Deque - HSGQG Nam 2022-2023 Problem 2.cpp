#include <bits/stdc++.h>
using namespace std;

const int inf = 1e9;

// Upsolve: https://i.postimg.cc/NFdT7w3j/tset.png

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
  deque<int> dq[2]; // deque req - index
  req[n] = 1;
  dq[pref[n] % 2].push_back(n);
  for (int i = n - 1; i >= 0; i--) {
    bool parity = pref[i] % 2;
    bool tParity = !parity;

    // Binary Search
    if (!dq[tParity].empty()) {
      int l = 0, r = (int)dq[tParity].size() - 1;
      int best = r;
      while (l <= r) {
        int mid = l + (r - l) / 2;
        int up = dq[tParity][mid] - i;
        int down = req[dq[tParity][mid]];
        if (up >= down) {
          best = mid;
          r = mid - 1;
        } else {
          l = mid + 1;
        }
      }
      req[i] = min(req[i], max(dq[tParity][best] - i, req[dq[tParity][best]]));
      if (best > 0)
        req[i] = min(
            req[i], max(dq[tParity][best - 1] - i, req[dq[tParity][best - 1]]));
    }

    // Ternary Search
    // if (!dq[tParity].empty()) {
    //   int l = 0, r = (int)dq[tParity].size() - 1;
    //   while (r - l > 3) {
    //     int p = (r - l) / 3;
    //     int m1 = l + p;
    //     int m2 = r - p;

    //     int index1 = dq[tParity][m1];
    //     int index2 = dq[tParity][m2];

    //     int val1 = max(index1 - i, req[index1]);
    //     int val2 = max(index2 - i, req[index2]);
    //     if (val1 == val2) {
    //       l = m1;
    //       r = m2;
    //     } else if (val1 > val2) {
    //       l = m1;
    //     } else {
    //       r = m2;
    //     }
    //   }

    //   while (l <= r) {
    //     req[i] = min(req[i], max(dq[tParity][l] - i, req[dq[tParity][l]]));
    //     l++;
    //   }
    // }

    // Linear Search:
    // for (int j = 0; j < (int)dq[tParity].size(); j++) {
    //   req[i] = min(req[i], max(dq[tParity][j] - i, req[dq[tParity][j]]));
    // }

    while (!dq[parity].empty() && req[dq[parity].front()] >= req[i])
      dq[parity].pop_front();
    dq[parity].push_front(i);
  }

  // for (int i = 0; i < (int)req.size(); i++) {
  //   debugr(req[i]);
  // }

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
