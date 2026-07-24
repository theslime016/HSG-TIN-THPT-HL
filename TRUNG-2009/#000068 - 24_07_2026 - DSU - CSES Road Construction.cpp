#include <bits/stdc++.h>
using namespace std;

const long long MAXN = 1e5 + 10;
long long bucket[MAXN];
int len[MAXN];
int group = -1;
int mx_sz = 1;

long long fnd(int v) {
  if (v == bucket[v])
    return v;

  return bucket[v] = fnd(bucket[v]);
}

void collect(int v, int u) {
  v = fnd(v);
  u = fnd(u);
  if (v != u) {
    if (len[v] < len[u])
      swap(v, u);
    bucket[u] = v;
    len[v] += len[u];
    mx_sz = max(mx_sz, len[v]);
    group--;
  }
}

int sz(int v) { return len[fnd(v)]; }

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int n, m;
  cin >> n >> m;
  group = n;
  fill(len, len + MAXN, 1);
  iota(bucket, bucket + MAXN, 0LL);
  for (int i = 0; i < m; i++) {
    int u, v;
    cin >> u >> v;
    collect(u, v);
    cout << group << ' ' << mx_sz << '\n';
  }

  return 0;
}
