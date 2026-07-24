#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

constexpr long long MAXN = 1e5 + 10;
bitset<MAXN> trace;
vector<int> bucket[MAXN];

bool dfs(int index) {
  if (trace[index])
    return false;
  trace[index] = true;
  if (bucket[index].empty())
    return true;
  for (int v : bucket[index]) {
    dfs(v);
  }
  return true;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  freopen("input.inp", "r", stdin);
  freopen("output.out", "w", stdout);

  trace.reset();
  int n, m;
  cin >> n >> m;
  if (n == 1) {
    cout << "YES" << endl << 1;
    return 0;
  }
  for (int i = 0; i < m; i++) {
    int a, b;
    cin >> a >> b;
    bucket[a].push_back(b);
    bucket[b].push_back(a);
  }
  int group = 0;
  for (int index = 1; index <= n; index++) {
    if (dfs(index))
      group++;
  }
  if (group > 1)
    cout << "NO" << endl << group;
  else
    cout << "YES" << endl << 1;

  return 0;
}
