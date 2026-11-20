#include <bits/stdc++.h>
using namespace std;

#define _debug 0

#if _debug == 1
void logout() {
  cerr << endl;
}
template<typename H, typename... T>
void logout(H h, T... t) {
  cerr << h << ", ";
  logout(t...);
}
#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:" << endl, logout(__VA_ARGS__)
#define debugtitle cerr << __PRETTY_FUNCTION__ << " line: " << __LINE__ << endl
#define newline cerr << endl

#else
#define debug(...) (void(0))
#define debugtitle (void(0))
#define newline (void(0))

#endif // _debug

const int maxn = 2e5 + 5;
const long long inf = 1e18;
int n;

vector<int> adj[maxn];
int dist[maxn];
int best[maxn];

void make_dist(int index, int parent) {
  for (int x : adj[index]) {
    if (x == parent)
      continue;
    make_dist(x, index);
    dist[index] = max(dist[index], dist[x] + 1);
  }
}

void make_dfs(int index, int parent, int new_dist) {
  best[index] = max(dist[index], new_dist);
  int best1 = 0, best2 = 0;
  for (int x : adj[index]) {
    if (x == parent)
      continue;

    if (dist[x] + 1 >= best1) {
      best2 = best1;
      best1 = dist[x] + 1;
    } else if (dist[x] + 1 > best2) {
      best2 = dist[x] + 1;
    }
  }

  for (int x : adj[index]) {
    if (x == parent)
      continue;
    int best_adj = (dist[x] + 1 == best1) ? best2 : best1;
    int next_dist = max(best_adj, new_dist) + 1;
    make_dfs(x, index, next_dist);
  }
}

int main() {
  cin.tie(0)->sync_with_stdio(0);

#if _debug == 1
  freopen("input.inp", "r", stdin);

#elif _debug == 2
  freopen("input.inp", "r", stdin);

#else

#endif // _debug

  cin >> n;
  for (int i = 1; i < n; i++) {
    int a, b;
    cin >> a >> b;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }

  make_dist(1, 0);
  make_dfs(1, 0, 0);

  for (int i = 1; i <= n; i++)
    cout << best[i] << ' ';
}
