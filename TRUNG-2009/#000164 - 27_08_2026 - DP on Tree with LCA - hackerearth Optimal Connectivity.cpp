#include <bits/stdc++.h>
using namespace std;

const long long inf = 1e15;
const int maxn = 1e5 + 5;
const int _log = 20;
vector<pair<int, long long>> adj[maxn];
int tag[maxn];
int jump[maxn][_log];
int depth[maxn];
long long dp[maxn][_log];

int main() {
  cin.tie(0)->sync_with_stdio(0);

  // freopen("input.inp", "r", stdin);
  // freopen("output.out", "w", stdout);

  int n;
  cin >> n;
  // long long global = 0;
  for (int i = 1; i < n; i++) {
    int a, b;
    long long w;
    cin >> a >> b >> w;
    adj[a].push_back({b, w});
    adj[b].push_back({a, w});
    // global += w;
  }

  stack<int> ranker;
  stack<int> wait;
  vector<int> proc(n + 1, 0);
  wait.push(1);
  while (!wait.empty()) {
    int index = wait.top();
    wait.pop();
    if (!proc[index]) {
      proc[index] = 1;
      wait.push(index);
      for (auto &x : adj[index]) {
        if (x.first == index || proc[x.first] == 2)
          continue;
        wait.push(x.first);
      }
    } else if (proc[index] == 1) {
      proc[index] = 2;
      ranker.push(index);
    }
  }

  int timer = 1;
  while (ranker.size() > 1) {
    int a = ranker.top();
    ranker.pop();
    tag[a] = timer++;
  }
  int last = ranker.top();
  ranker.pop();
  tag[last] = timer++;

  // for (int i = 1; i <= n; i++) {
  //   cout << i << '[' << tag[i] << ']' << ' ';
  // }
  // cout << '\n';

  wait.push(last);
  depth[last] = 1;
  fill(proc.begin(), proc.end(), 0);
  while (!wait.empty()) {
    int index = wait.top();
    wait.pop();
    proc[index] = 1;
    sort(adj[index].begin(), adj[index].end(),
         [&](auto &x, auto &y) { return tag[x.first] > tag[y.first]; });
    for (auto &x : adj[index]) {
      if (x.first == index || proc[x.first])
        continue;
      jump[x.first][0] = index;
      dp[x.first][0] = x.second;
      depth[x.first] = depth[index] + 1;
      wait.push(x.first);
    }
  }

  for (int exp = 0; exp < _log; exp++) {
    dp[0][exp] = -inf;
  }

  for (int exp = 1; exp < _log; exp++) {
    for (int index = 1; index <= n; index++) {
      int next = jump[index][exp - 1];
      dp[index][exp] = -inf;
      if (next == 0)
        continue;

      jump[index][exp] = jump[next][exp - 1];
      dp[index][exp] = max(dp[index][exp - 1], dp[next][exp - 1]);
    }
  }

  // for (int index = 1; index <= n; index++) {
  //   for (int exp = 0; exp < 3; exp++) {
  //     cout << index << "jump" << jump[index][exp] << ' ';
  //   }
  //   cout << '\n';
  //   for (int exp = 0; exp < 3; exp++) {
  //     cout << index << "dp" << dp[index][exp] << ' ';
  //   }
  //   cout << '\n' << '\n';
  // }

  int q;
  cin >> q;

  auto check = [](const long long &opt, const long long &w) {
    // cout << opt << ' ' << w << '\n';

    if (opt > w) {
      cout << "YES";
    } else {
      cout << "NO";
    }
    cout << '\n';
  };

  while (q--) {
    int a, b;
    long long w;
    cin >> a >> b >> w;
    long long opt = -inf;
    if (depth[a] < depth[b])
      swap(a, b);

    int diff = depth[a] - depth[b];
    for (int j = 0; j < _log; j++) {
      if ((diff >> j) & 1) {
        opt = max(dp[a][j], opt);
        a = jump[a][j];
      }
    }
    if (a == b) {
      check(opt, w);
      continue;
    }

    for (int j = _log - 1; j >= 0; j--) {
      if (jump[a][j] != jump[b][j]) {
        opt = max({opt, dp[a][j], dp[b][j]});
        a = jump[a][j];
        b = jump[b][j];
      }
    }

    opt = max({opt, dp[a][0], dp[b][0]});
    check(opt, w);
  }
}
