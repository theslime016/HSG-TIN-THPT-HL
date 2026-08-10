#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int t;
  cin >> t;
  for (int time = 1; time <= t; time++) {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> boss(n);
    while (m--) {
      int a, b;
      cin >> a >> b;
      boss[a].push_back(b);
    }

    vector<int> rank(n);
    auto dfs = [&](auto &self, int index) {
      if (rank[index])
        return rank[index];
      int val = 0;
      for (int x : boss[index])
        val = max(val, self(self, x));
      return rank[index] = val + 1;
    };

    vector<pair<int, int>> top(n);
    for (int i = 0; i < n; i++)
      top[i] = {dfs(dfs, i), i};
    sort(top.begin(), top.end());

    cout << "Scenario #" << time << ":\n";
    for (auto &x : top)
      cout << x.first << ' ' << x.second << '\n';
  }
}
