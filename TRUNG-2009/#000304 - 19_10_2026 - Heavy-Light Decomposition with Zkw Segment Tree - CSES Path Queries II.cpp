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
const int padding = 262144;
const long long inf = 1e18;
long long A[maxn], B[maxn];
long long segment[maxn << 2];
int n, q;

void update(int index, const long long& val) {
  index += padding;
  segment[index] = val;
  for (index >>= 1; index > 0; index >>= 1) {
    segment[index] = max(segment[index << 1], segment[index << 1 | 1]);
  }
}

long long fetch(int l, int r) {
  int s = padding + l - 1;
  int t = padding + r + 1;

  long long res = -inf;
  for (; s ^ t ^ 1; s >>= 1, t >>= 1) {
    if (~s & 1) res = max(res, segment[s ^ 1]);
    if (t & 1) res = max(res, segment[t ^ 1]);
  }

  return res;
}

vector<int> adj[maxn];
int child[maxn], parent[maxn], depth[maxn];
int timein[maxn], timeout[maxn], head[maxn];
int timer = 1;

int make_dfs(int index, int parent_index) {
  child[index] = 1;
  depth[index] = depth[parent_index] + 1;
  parent[index] = parent_index;

  for (int x : adj[index]) {
    if (x == parent_index) continue;
    child[index] += make_dfs(x, index);
  }

  return child[index];
}

void make_hld(int index, int parent_index, int head_index) {
  timein[index] = timer++;
  head[index] = head_index;

  int best_index = -1;
  for (int x : adj[index]) {
    if (x == parent_index) continue;

    if (best_index == - 1 || child[x] > child[best_index]) best_index = x;
  }

  if (best_index != -1) {
    make_hld(best_index, index, head_index);
    for (int x : adj[index]) {
      if (x == parent_index || x == best_index) continue;
      make_hld(x, index, x);
    }
  }

  timeout[index] = timer - 1;
}

long long query_fetch(int a, int b) {
  long long res = -inf;
  while (head[a] != head[b]) {
    if (depth[head[a]] < depth[head[b]]) swap(a, b);
    res = max(res, fetch(timein[head[a]], timein[a]));
    a = parent[head[a]];
  }

  if (depth[a] < depth[b]) swap(a, b);
  res = max(res, fetch(timein[b], timein[a]));
  return res;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);

  #if _debug == 1
  freopen("input.inp", "r", stdin);

  #elif _debug == 2
  freopen("input.inp", "r", stdin);

  #else

  #endif // _debug

  cin >> n >> q;
  for (int i = 1; i <= n; i++) cin >> A[i];
  for (int i = 1; i < n; i++) {
    int a, b;
    cin >> a >> b;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }

  make_dfs(1, 0);

  #if _debug == 1

  for (int i = 1; i <= n; i++) {
    debug(i);
    debug(child[i]);
    debug(parent[i]);
    debug(depth[i]);
    newline;
  }
  newline;

  #endif // _debug

  make_hld(1, 0, 1);

  #if _debug == 1

  for (int i = 1; i <= n; i++) {
    debug(i);
    debug(timein[i]);
    debug(timeout[i]);
    debug(head[i]);
    newline;
  }
  newline;

  #endif // _debug

  for (int i = 1; i <= n; i++) {
    B[timein[i]] = A[i];
  }
  for (int i = 1; i <= n; i++) {
    segment[padding + i] = B[i];
  }
  for (int i = padding - 1; i > 0; i--) {
    segment[i] = max(segment[i << 1], segment[i << 1 | 1]);
  }

  while (q--) {
    int type;
    cin >> type;
    if (type == 1) {
      int index;
      long long val;
      cin >> index >> val;
      update(timein[index], val);
    } else if (type == 2) {
      int a, b;
      cin >> a >> b;
      cout << query_fetch(a, b) << ' ';
    }
  }

  #if _debug == 1

  newline;
  for (int i = 1; i <= n; i++) {
    debug(i);
    debug(fetch(timein[i], timein[i]));
    newline;
  }

  #endif // _debug

}
