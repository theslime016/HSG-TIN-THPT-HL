#include <bits/stdc++.h>
using namespace std;

#define _debug 0

#if _debug == 1
void log_out() {
  cerr << endl;
}
template<typename H, typename... T>
void log_out(H h, T... t) {
  cerr << h << ", ";
  log_out(t...);
}
#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:" << endl, log_out(__VA_ARGS__)
#define newline cerr << endl

#else
#define debug(...) (void(0))
#define newline (void(0))

#endif // _debug

const int maxn = 1e5 + 5;
const int maxedge = 2e5 + 5;
int n, m;

int color[maxn];
vector<int> adj[maxn];

void make_dfs(int index, int parent) {
  for (int x : adj[index]) {
    if (x == parent)
      continue;
    if (color[x] != -1) {
      if (color[x] == color[index]) {
        cout << "IMPOSSIBLE";
        exit(0);
      } else {
        continue;
      }
    }

    color[x] = !color[index];
    make_dfs(x, index);
  }
}

int main() {
  cin.tie(0)->sync_with_stdio(0);

#if _debug == 1
  freopen("input.inp", "r", stdin);

#else

#endif // _debug

  cin >> n >> m;
  for (int i = 1; i <= m; i++) {
    int a, b;
    cin >> a >> b;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }

  memset(color, -1, sizeof color);
  for (int i = 1; i <= n; i++) {
    if (color[i] == -1) {
      color[i] = 1;
      make_dfs(i, 0);
    }
  }

  for (int i = 1; i <= n; i++) {
    cout << color[i] + 1 << ' ';
  }

}
