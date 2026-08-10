#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e3 + 5;
int indeg[maxn];
int ranks[maxn];
vector<int> adj[maxn];

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int t;
  cin >> t;
  for (int timer = 1; timer <= t; timer++) {
    cout << "Scenario #" << timer << ":\n";

    int n, r;
    cin >> n >> r;

    for (int i = 0; i < n; i++) {
      adj[i].clear();
      indeg[i] = 0;
      ranks[i] = 0;
    }

    while (r--) {
      int a, b;
      cin >> a >> b;
      adj[b].push_back(a);
      indeg[a]++;
    }

    deque<int> dq;
    for (int i = 0; i < n; i++) {
      if (!indeg[i]) {
        dq.push_back(i);
        ranks[i] = 1;
      }
    }

    while (!dq.empty()) {
      int index = dq.front();
      dq.pop_front();

      for (int x : adj[index]) {
        if (!--indeg[x]) {
          dq.push_back(x);
          ranks[x] = ranks[index] + 1;
        }
      }
    }

    vector<int> ind(n);
    iota(ind.begin(), ind.end(), 0);
    sort(ind.begin(), ind.end(), [&](int x, int y) {
      if (ranks[x] != ranks[y])
        return ranks[x] < ranks[y];
      return x < y;
    });
    for (int x : ind)
      cout << ranks[x] << ' ' << x << '\n';
  }
}
