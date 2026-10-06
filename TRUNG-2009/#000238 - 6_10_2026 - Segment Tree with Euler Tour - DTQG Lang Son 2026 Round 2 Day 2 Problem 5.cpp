#include <bits/stdc++.h>
using namespace std;

const int maxn = 2e5 + 5;
const int padding = 262144;
const long long inf = 1e18;
vector<int> adj[maxn];
long long W[maxn];
long long segment[maxn << 2];
int timein[maxn], timeout[maxn];
int timer = 1;

void make_dfs(int index, int parent) {
  timein[index] = timer;
  segment[timer + padding] = W[index];
  timer++;

  for (int x : adj[index]) {
    if (x == parent) continue;
    make_dfs(x, index);
  }

  timeout[index] = timer - 1;
}

void build() {
  for (int index = padding - 1; index > 0; index--) {
    segment[index] = max(segment[index << 1], segment[index << 1 | 1]);
  }
}

void update(int index, const long long& val) {
  index += padding;
  segment[index] = val;
  for (index >>= 1; index > 0; index >>= 1) {
    segment[index] = max(segment[index << 1], segment[index << 1 | 1]);
  }
}

long long fetch(int l, int r) {
  int s = l + padding - 1;
  int t = r + padding + 1;

  long long res = -inf;
  for (; s ^ t ^ 1; s >>= 1, t >>= 1) {
    if (~s & 1) res = max(res, segment[s ^ 1]);
    if (t & 1) res = max(res, segment[t ^ 1]);
  }
  return res;
}

#define _debug 1
int main() {
  cin.tie(0)->sync_with_stdio(0);

  #if _debug == 1
  freopen("input.inp", "r", stdin);
  freopen("output.out", "w", stdout);
  #else

  #endif // _debug

  int n, q;
  cin >> n >> q;
  for (int i = 1; i <= n; i++) cin >> W[i];
  for (int i = 1; i < n; i++) {
    int a, b;
    cin >> a >> b;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }

  fill(segment, segment + (maxn << 2), -inf);
  make_dfs(1, 0);
  build();
  for (int i = 1; i <= q; i++) {
    int type;
    cin >> type;
    if (type == 1) {
      int index;
      long long val;
      cin >> index >> val;
      update(timein[index], val);
    } else if (type == 2) {
      int index;
      cin >> index;
      cout << fetch(timein[index], timeout[index]) << '\n';
    }
  }

}
