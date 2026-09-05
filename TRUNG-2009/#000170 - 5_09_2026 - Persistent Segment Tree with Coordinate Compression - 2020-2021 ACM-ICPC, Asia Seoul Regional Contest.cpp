#include <bits/stdc++.h>
using namespace std;

const int maxn = 2005;
const int maxq = 2e5;
const int _log = 20;
const long long maxsz = maxq * _log;
const long long inf = 1e18;

int root[maxn];
int lc[maxsz], rc[maxsz];
int segment[maxsz]; // sorted val - index
// 1 index

int node_count = 0;
// stack<int> wait; // index

int build(int oindex, int l, int r, int vindex, int rindex) {
  // rindex -> sorted
  // vindex -> raw
  int nindex = node_count++;
  lc[nindex] = lc[oindex];
  rc[nindex] = rc[oindex];
  segment[nindex] = max(segment[oindex], rindex);
  if (l == r)
    return nindex;

  int mid = l + (r - l) / 2;

  if (vindex <= mid) {
    lc[nindex] = build(lc[oindex], l, mid, vindex, rindex);
  } else {
    rc[nindex] = build(rc[oindex], mid + 1, r, vindex, rindex);
  }
  return nindex;
}

int fetch(int node, int l, int r, int tvindex, int lrindex) {
  if (!node || lrindex > segment[node])
    return -1;

  if (l == r) {
    if (l >= tvindex)
      return l;
    return -1;
  }

  int mid = l + (r - l) / 2;

  int res = -1;
  if (lc[node] && tvindex <= mid && segment[lc[node]] >= lrindex) {
    res = max(res, fetch(lc[node], l, mid, tvindex, lrindex));
  }

  if (res == -1) {
    res = max(res, fetch(rc[node], mid + 1, r, tvindex, lrindex));
  }

  return res;
}

long long A[maxn], pref[maxn];
int main() {
  cin.tie(0)->sync_with_stdio(0);

  // freopen("input.inp", "r", stdin);

  int n, m;
  cin >> n >> m;

  vector<long long> proc;
  proc.reserve(n + 1);
  proc.push_back(0);
  for (int i = 1; i <= n; i++) {
    cin >> A[i];
    pref[i] = A[i] + pref[i - 1];
    proc.push_back(pref[i]);
  }

  sort(proc.begin(), proc.end());
  proc.erase(unique(proc.begin(), proc.end()), proc.end());

  auto get_index = [&](const long long &val) {
    return lower_bound(proc.begin(), proc.end(), val) - proc.begin() + 1;
  };

  // for (long long x : proc)
  //   cerr << x << ' ';
  // cerr << '\n';
  // for (int i = 0; i <= n; i++)
  //   cerr << pref[i] << ' ';
  // cerr << '\n';

  root[0] = node_count++;
  segment[0] = -1;
  // null
  for (int ver = 0; ver <= n; ver++) {
    root[ver] = (ver == 0) ? 0 : root[ver - 1];

    root[ver] = build(root[ver], 1, proc.size(), get_index(pref[ver]), ver);
  }

  while (m--) {
    int l, r;
    long long k;
    cin >> l >> r >> k;

    long long res = -inf;
    for (int ver = l; ver <= r; ver++) {
      long long tar = pref[ver] - k;
      int tvindex = get_index(tar);

      if (tvindex <= proc.size()) {
        int resindex = fetch(root[ver - 1], 1, proc.size(), tvindex, l - 1);
        // cerr << ver << ' ' << tar << ' ' << resindex << '\n';
        if (resindex != -1)
          res = max(res, pref[ver] - proc[resindex - 1]);
      }
    }
    if (res == -inf)
      cout << "NONE" << '\n';
    else
      cout << res << '\n';
  }
}
