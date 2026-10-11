#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e6;
int n;

struct EDGE {
  int a, b;
} task[maxn];
vector<int> adj[maxn];
long long lazy[maxn];
int timein[maxn], timeout[maxn];
int cnt[maxn];
int timer = 1;

void make_dfs(int index, int parent) {
  timein[index] = timer++;
  cnt[index] = 1;
  for (int x : adj[index]) {
    if (x == parent) continue;
    make_dfs(x, index);
    cnt[index] += cnt[x];
  }

  timeout[index] = timer - 1;
}

bool is_lca(int a, int b) {
  return timein[a] <= timein[b] && timeout[a] >= timeout[b];
}

void push_lazy(int index, int parent, long long val) {
  for (int x : adj[index]) {
    if (x == parent) continue;
    push_lazy(x, index, val + lazy[index]);
  }
  lazy[index] += val;
}

#define _debug 0
int main() {
  cin.tie(0)->sync_with_stdio(0);

  #if _debug == 1
  freopen("input.inp", "r", stdin);
  #else

  #endif // _debug

  int n;
  cin >> n;
  for (int i = 1; i < n; i++) {
    int a, b;
    cin >> a >> b;
    adj[a].push_back(b);
    adj[b].push_back(a);
    task[i] = {a, b};
  }

  make_dfs(1, 0);
  for (int i = 1; i < n; i++) {
    auto [x, y] = task[i];
    if (is_lca(y, x)) swap(x, y);
    if (is_lca(x, y)) {
      int cnt_x = cnt[1] - cnt[y];
      int cnt_y = cnt[y];
      if (cnt_x > cnt_y) {
        lazy[1] += i;
        lazy[y] -= i;
      } else {
        lazy[y] += i;
      }
    } else {
      if (cnt[x] > cnt[y]) {
        lazy[x] += i;
      } else {
        lazy[y] += i;
      }
    }
  }

  push_lazy(1, 0, 0LL);
  for (int i = 1; i <= n; i++) cout << lazy[i] << ' ';

}
