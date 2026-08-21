#include <bits/stdc++.h>
using namespace std;

const int maxn = 2e5 + 5;
bool gparity[maxn];
long long dp[maxn][2];

const long long inf = 1e15;

vector<int> adj[maxn];
int proc[maxn];
long long res = 0;

void dfs(int index) {
  proc[index] = 1;

  int index_parity = gparity[index];
  dp[index][index_parity] = 0;
  dp[index][!index_parity] = 1;

  for (int c : adj[index]) {
    if (proc[c])
      continue;
    dfs(c);

    dp[index][0] += dp[c][0];
    dp[index][1] += dp[c][1];
  }
}

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n;
  cin >> n;

  for (int i = 1; i <= n; i++) {
    char s;
    cin >> s;
    gparity[i] = s - '0';
  }

  for (int i = 1; i < n; i++) {
    int a, b;
    cin >> a >> b;
    // cout << a << ' ' << b << '\n';
    adj[a].push_back(b);
  }

  for (int i = 1; i <= n; i++) {
    if (!proc[i])
      dfs(i);
  }

  for (int i = 1; i <= n; i++) {
    // cout << i << ':' << dp[i][0] << ' ' << dp[i][1] << '\n';
    res = max(res, min(dp[i][0], dp[i][1]) + 1);
  }

  cout << res;
}
