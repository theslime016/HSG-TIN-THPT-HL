#include <bits/stdc++.h>
using namespace std;

const int maxn = 3e5 + 5;
int jump[maxn];
int dp[maxn][30];
int indeg[maxn];
deque<int> dq;
vector<int> adj[maxn];

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n, m;
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    // Ánh xạ từ char trên mỗi node về 1 value
    char c;
    cin >> c;
    int val = c - 'a';
    jump[i] = val;
  }

  while (m--) {
    int a, b;
    cin >> a >> b;
    adj[a].push_back(b);
    indeg[b]++;
  }

  for (int i = 1; i <= n; i++) {
    if (!indeg[i]) {
      dp[i][jump[i]]++;
      dq.push_back(i);
    }
  }

  while (!dq.empty()) {
    int a = dq.front();
    dq.pop_front();

    for (int x : adj[a]) {
      for (int i = 0; i < 26; i++) {
        dp[x][i] = max(dp[x][i], dp[a][i]);
      }
      if (!--indeg[x]) {
        dp[x][jump[x]]++;
        dq.push_back(x);
      }
    }
  }

  if (any_of(indeg + 1, indeg + n + 1, [](int x) { return x > 0; }))
    return cout << -1, 0;

  int res = 0;
  for (int i = 1; i <= n; i++) {
    for (int c = 0; c < 26; c++) {
      res = max(res, dp[i][c]);
    }
  }

  cout << res;
}
