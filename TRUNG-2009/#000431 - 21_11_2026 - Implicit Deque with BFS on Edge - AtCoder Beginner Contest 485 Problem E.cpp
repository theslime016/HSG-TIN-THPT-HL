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
int n, m;

vector<int> adj[maxn]; /// edge
int state[maxn]; /// vertex

pair<int, int> dq[maxn];

struct EDGE {
  int next_index;
  int color;
} edge[maxn];

int main() {
  cin.tie(0)->sync_with_stdio(0);

#if _debug == 1
  freopen("input.inp", "r", stdin);

#elif _debug == 2
  freopen("input.inp", "r", stdin);

#else

#endif // _debug

  cin >> n >> m;
  for (int i = 1; i <= m; i++) {
    int a, b;
    int color;
    cin >> a >> b >> color;
    adj[a].push_back(i);
    edge[i] = {b, color};
  }

  int dq_front = 1, dq_back = 0; /// edge_index - dist
  for (int x : adj[1]) {
    dq[++dq_back] = {x, 1};
  }
  state[1] = -1;

  while (dq_front <= dq_back) {
    int edge_index = dq[dq_front].first;
    int dist = dq[dq_front].second;
    dq_front++;

    int nxt = edge[edge_index].next_index;
    int color = edge[edge_index].color;

    if (nxt == n) {
      cout << dist << '\n';
      return 0;
    }

    if (state[nxt] == -1)
      continue;
    if (state[nxt] != 0 && state[nxt] == color)
      continue;

    int type = (state[nxt] == 0) ? 1 : 2;

    for (int x : adj[nxt]) {
      if (type == 1) {
        if (edge[x].color == color)
          continue;
      } else if (type == 2) {
        if (edge[x].color != state[nxt])
          continue;
      }

      dq[++dq_back] = {x, dist + 1};
    }

    if (type == 1)
      state[nxt] = color;

    if (type == 2)
      state[nxt] = -1;
  }

  cout << -1;
}
