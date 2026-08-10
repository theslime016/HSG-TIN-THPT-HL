#include <bits/stdc++.h>
using namespace std;

#define debugr(x) cout << #x << " = " << (x) << '\n'
#define debugl cout << '\n'

const long long mod = 1e9;
const long long hmod = 1e10;
const int maxn = 1e4 + 5;
vector<int> adj[maxn];
vector<int> radj[maxn];
int valid[maxn];
int indeg[maxn];
long long dp[maxn];
int n, m;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  cin >> n >> m;

  while (m--) {
    int a, b;
    cin >> a >> b;
    adj[a].push_back(b);
    radj[b].push_back(a);
  }

  auto dfs = [&](auto &self, int index, vector<int> *graph,
                 int flag) mutable -> void {
    valid[index] |= flag;
    for (int x : graph[index]) {
      if (valid[x] & flag)
        continue;
      self(self, x, graph, flag);
    }
  };

  int flag1 = 0b1;
  int flag2 = 0b10;
  int vflag = 0b11;

  dfs(dfs, 1, adj, flag1);
  dfs(dfs, 2, radj, flag2);

  for (int i = 1; i <= n; i++) {
    if (valid[i] == vflag)
      for (int x : adj[i]) {
        if (valid[x] == vflag)
          indeg[x]++;
      }
  }

  deque<int> q;
  for (int i = 1; i <= n; i++) {
    if (valid[i] == vflag && !indeg[i])
      q.push_back(i);
  }

  dp[1] = 1;
  while (!q.empty()) {
    int a = q.front();
    q.pop_front();

    for (int x : adj[a]) {
      if (valid[x] == vflag) {
        dp[x] += dp[a];
        if (dp[x] > mod)
          dp[x] = hmod + dp[x] % mod;

        indeg[x]--;
        if (!indeg[x])
          q.push_back(x);
      }
    }
  }

  for (int i = 1; i <= n; i++) {
    if (valid[i] == vflag && indeg[i] > 0)
      return cout << "inf", 0;
  }

  int buffer[15]{0};
  int pos = 1;
  for (; pos <= 9 && dp[2] > 0; pos++) {
    buffer[pos] = dp[2] % 10;
    dp[2] /= 10;
  }
  while (--pos)
    cout << buffer[pos];
}
