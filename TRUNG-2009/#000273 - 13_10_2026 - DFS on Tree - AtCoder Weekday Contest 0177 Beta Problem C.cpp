#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e6 + 5;
long long cost[maxn];
vector<int> adj[maxn];
int lazy[maxn];
long long res;

bool make_dfs(int index, int parent) {
  bool ok = lazy[index];
  for (int x : adj[index]) {
    if (x == parent) continue;
    ok |= make_dfs(x, index);
  }

  if (ok) res += cost[index];
  return ok;
}

#define _debug 0
int main() {
  cin.tie(0)->sync_with_stdio(0);

  #if _debug == 1
  freopen("input.inp", "r", stdin);
  #else

  #endif // _debug

  int n, k;
  cin >> n >> k;
  for (int i = 1; i <= n; i++) cin >> cost[i];
  for (int i = 2; i <= n; i++) {
    int x;
    cin >> x;
    adj[i].push_back(x);
    adj[x].push_back(i);
  }
  for (int i = 1; i <= k; i++) {
    int x;
    cin >> x;
    lazy[x] = 1;
  }

  make_dfs(1, 0);
  cout << res;

}
