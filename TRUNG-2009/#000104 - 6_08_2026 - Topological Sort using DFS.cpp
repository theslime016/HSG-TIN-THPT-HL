#include <bits/stdc++.h>
using namespace std;

int n, m;
const int maxn = 105;
vector<int> adj[maxn];
int state[maxn]{0}, ans[maxn]{0};
stack<int> ranks;

void dfs(int index) {
  state[index] = 1;
  for (int x : adj[index]) {
    if (!state[x])
      dfs(x);
  }
  ranks.push(index);
}

int main() {
  cin.tie(0)->sync_with_stdio(false);

  cin >> n >> m;
  while (m--) {
    int a, b;
    cin >> a >> b;
    adj[a].push_back(b);
  }

  for (int i = 1; i <= n; i++) {
    if (!state[i]) {
      dfs(i);
    }
  }

  int timer = 1;
  while (!ranks.empty()) {
    ans[ranks.top()] = timer++;
    ranks.pop();
  }

  for (int i = 1; i <= n; i++)
    cout << ans[i] << ' ';

  return 0;
}
