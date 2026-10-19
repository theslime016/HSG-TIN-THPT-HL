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
int n, q;

long long A[maxn];
long long B[maxn];
long long segment[maxn << 2];

void make_segment(int index, int l, int r) {
  if (l > r) return;
  if (l == r) {
    segment[index] = B[l];
    return;
  }

  int mid = l + ((r - l) >> 1);
  make_segment(index << 1, l, mid);
  make_segment(index << 1 | 1, mid + 1, r);
  segment[index] = segment[index << 1] + segment[index << 1 | 1];
}

void update(int index, int l, int r, int qindex, const long long& val) {
  if (l == r) {
    segment[index] = val;
    return;
  }

  int mid = l + ((r - l) >> 1);
  if (qindex <= mid) {
    update(index << 1, l, mid, qindex, val);
  } else {
    update(index << 1 | 1, mid + 1, r, qindex, val);
  }

  segment[index] = segment[index << 1] + segment[index << 1 | 1];
}

long long fetch(int index, int l, int r, int ql, int qr) {
  if (l > qr || r < ql) return 0;
  if (l >= ql && r <= qr) return segment[index];

  int mid = l + ((r - l) >> 1);
  return fetch(index << 1, l, mid, ql, qr) + fetch(index << 1 | 1, mid + 1, r, ql, qr);
}

vector<int> adj[maxn];
int child[maxn], parent[maxn];
int depth[maxn];

int timein[maxn], timeout[maxn];
int head[maxn];
int timer = 1;

int make_dfs(int index, int p, int d) {
  parent[index] = p;
  depth[index] = d;
  child[index] = 1;

  for (int x : adj[index]) {
    if (x == p) continue;
    child[index] += make_dfs(x, index, d + 1);
  }

  return child[index];
}

void build(int index, int p, int head_index) {
  timein[index] = timer++;
  head[index] = head_index;
  int best_index = -1;
  for (int x : adj[index]) {
    if (x == p) continue;

    if (best_index == -1) best_index = x;
    else if (child[x] > child[best_index]) best_index = x;
  }

  if (best_index == -1) return;

  build(best_index, index, head_index);
  for (int x : adj[index]) {
    if (x == p || x == best_index) continue;
    build(x, index, x);
  }

  timeout[index] = timer - 1;
}

long long query_fetch(int a, int b) {
  long long res = 0;
  while (head[a] != head[b]) {
    if (depth[head[a]] < depth[head[b]]) swap(a, b);
    res += fetch(1, 1, n, timein[head[a]], timein[a]);
    a = parent[head[a]];
  }

  if (depth[a] < depth[b]) swap(a, b);
  res += fetch(1, 1, n, timein[b], timein[a]);
  return res;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);

#if _debug == 1
  freopen("input.inp", "r", stdin);

#elif _debug == 2
  freopen("input.inp", "r", stdin);
  freopen("output.out", "w", stdout);

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

  make_dfs(1, 0, 1);
  build(1, 0, 1);

  for (int i = 1; i <= n; i++) {
    B[timein[i]] = A[i];
  }
  make_segment(1, 1, n);

  while (q--) {
    int type;
    cin >> type;
    if (type == 1) {
      int index;
      long long val;
      cin >> index >> val;
      update(1, 1, n, timein[index], val);
    } else if (type == 2) {
      int index;
      cin >> index;
      cout << query_fetch(1, index) << '\n';
    }
  }

}
