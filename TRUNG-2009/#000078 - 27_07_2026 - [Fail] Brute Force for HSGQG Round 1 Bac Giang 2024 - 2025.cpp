#include <bits/stdc++.h>
using namespace std;

struct que {
  int a, b;
  long long w;
};

const long long maxn = 5e5 + 10;
bitset<maxn> visited{};

vector<vector<int>> adj(maxn);
vector<int> shops(maxn);
vector<que> query(maxn);
int n, m, k;

void bfs(int start) {
  queue<int> q;
  q.push(start);
  while (!q.empty()) {
    int a = q.front();
    q.pop();
    visited[a] = true;
    for (int x : adj[a]) {
      if (visited[x])
        continue;
      q.push(x);
    }
  }
}

long long res = LLONG_MAX;
void solve(int index, long long sum) {

  if (index == m) {
    visited.reset();
    bfs(1);
    if (visited.count() == n) {
      res = min(res, sum);
    }
    return;
  }

  long long new_sum = sum;
  for (int i = index; i < m; i++) {
    adj[query[i].a].push_back(query[i].b);
    adj[query[i].b].push_back(query[i].a);
    new_sum += query[i].w;

    solve(i + 1, new_sum);

    new_sum -= query[i].w;
    adj[query[i].a].pop_back();
    adj[query[i].b].pop_back();
  }
}

int main() {
  cin.tie(0)->sync_with_stdio(false);

  cin >> n >> m >> k;
  for (int i = 0; i < k; i++) {
    cin >> shops[i];
  }

  for (int i = 0; i < m; i++) {
    cin >> query[i].a >> query[i].b >> query[i].w;
  }

  solve(0, 0LL);
  if (res == LLONG_MAX)
    cout << -1;
  else
    cout << res;

  return 0;
}
