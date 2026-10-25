#include <bits/stdc++.h>
using namespace std;

#define _debug 0

#if _debug == 1
#define debug(x) cerr << #x << ':' << (x) << ' ';
#define newline cerr << '\n';

#else
#define debug(x)
#define newline

#endif // _debug

const int maxn = 2e5 + 5;
const long long inf = 1e18;
const long long mod = 998244353;

struct DIST {
  long long rem = inf;
  long long coefficient = inf;

  friend bool operator<(const DIST& a, const DIST& b) {
    return a.coefficient < b.coefficient || (a.coefficient == b.coefficient && a.rem < b.rem);
  }


} dist[maxn];

vector<pair<int, int>> adj[maxn];

DIST get_cost(const DIST& d, int c) {
  if (d.rem == inf) return d;

  DIST res = d;
  res.rem = (res.rem * 10) + c;
  res.coefficient = res.coefficient * 10;
  while (res.rem >= mod) {
    res.coefficient++;
    res.rem -= mod;
  }
  return res;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);

  #if _debug == 1
  freopen("input.inp", "r", stdin);

  #else

  #endif // _debug

  int n, m;
  cin >> n >> m;
  for (int i = 1; i <= m; i++) {
    int a, b;
    int w;
    cin >> a >> b >> w;
    adj[a].push_back({b, w});
  }

  priority_queue<pair<DIST, int>, vector<pair<DIST, int>>,
                 greater<pair<DIST, int>>> pq;

  dist[1] = {0, 0};
  pq.push({ {0, 0}, 1});
  while (!pq.empty()) {
    DIST d = pq.top().first;
    int index = pq.top().second;
    pq.pop();

    debug(index);
    debug(d.coefficient);
    debug(d.rem);
    newline;

    if (dist[index] < d) continue;

    for (const auto& x : adj[index]) {
      DIST cost = get_cost(d, x.second);

      debug(x.first);
      debug(x.second);
      debug(cost.coefficient);
      debug(cost.rem);
      debug(dist[x.first].coefficient);
      debug(dist[x.first].rem);
      newline;

      if (cost < dist[x.first]) {
        dist[x.first] = cost;
        pq.push({cost, x.first});
      }
    }

    newline;
    newline;
  }

  for (int i = 2; i <= n; i++) {
    if (dist[i].rem == inf) cout << -1 << '\n';
    else cout << dist[i].rem << '\n';
  }

}
