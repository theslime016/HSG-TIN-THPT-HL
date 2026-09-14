#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5 + 5;
const int inf = 1e6;
vector<int> adj[maxn];
long long dp[maxn][3];
int n;

void make_dp(int index, int parent) {
  dp[index][0] = 1;
  dp[index][1] = inf;
  dp[index][2] = 0;

  long long diff = inf;
  long long sum = 0;
  for (int x : adj[index]) {
    if (x == parent)
      continue;
    make_dp(x, index);
    dp[index][0] += min({dp[x][0], dp[x][1], dp[x][2]});
    dp[index][2] += dp[x][1];

    sum += min(dp[x][0], dp[x][1]);
    diff = min(diff, dp[x][0] - min(dp[x][0], dp[x][1]));
  }
  dp[index][1] = sum + diff;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);

  freopen("CAMERA.inp", "r", stdin);
  freopen("CAMERA.out", "w", stdout);

  cin >> n;
  for (int i = 1; i < n; i++) {
    int a, b;
    cin >> a >> b;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }

  make_dp(1, 0);
  cout << min(dp[1][0], dp[1][1]);
}
