#include <bits/stdc++.h>
using namespace std;

char S[105][105]{};
// 0 -> 9
// # -> Skip

vector<pair<int, int>> adj[105];
// index - value
int indeg[105]{};
int dp[10005]{};

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n, m;
  cin >> n >> m;

  auto flat = [&](int a, int b) { return (a - 1) * m + b; };
  auto fetch = [&](int x, int y, int index, int jindex) {
    if (!(index >= 1 && index <= n && jindex >= 1 && jindex <= m))
      return;
    int val = isdigit(S[index][jindex]) ? (S[index][jindex] - '0') : 0;
    int nindex = flat(index, jindex);
    int oIndex = flat(x, y);
    indeg[nindex]++;
    adj[oIndex].push_back({nindex, val});
  };

  char c;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      cin >> S[i][j];
    }
  }

  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      char c = S[i][j];
      if (c == '#')
        continue;
      fetch(i, j, i + 1, j);
      fetch(i, j, i, j + 1);
    }
  }

  int mx = flat(n, m);
  deque<int> q;
  for (int i = 1; i <= mx; i++) {
    if (!indeg[i]) {
      q.push_back(i);
    }
  }

  memset(dp, -1, sizeof dp);
  dp[1] = isdigit(S[1][1]) ? (S[1][1] - '0') : 0;
  int res = 0;
  while (!q.empty()) {
    int a = q.front();
    q.pop_front();

    for (auto &x : adj[a]) {
      if (dp[a] != -1) {
        dp[x.first] = max(dp[x.first], dp[a] + x.second);
        res = max(res, dp[x.first]);
      }
      indeg[x.first]--;
      if (!indeg[x.first])
        q.push_back(x.first);
    }
  }

  cout << res;
}
