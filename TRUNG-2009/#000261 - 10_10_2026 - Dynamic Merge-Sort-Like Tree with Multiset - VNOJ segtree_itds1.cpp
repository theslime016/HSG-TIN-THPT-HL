#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5 + 5;
const int padding = 131072;
const long long inf = 1e18;
long long A[maxn];
multiset<long long> segment[maxn << 2];
int n, q;

void update(int index, const long long& val) {
  long long old_val = A[index];
  if (old_val == val) return;

  A[index] = val;
  index += padding;
  for (index >>= 1; index > 0; index >>= 1) {
    segment[index].erase(segment[index].find(old_val));
    segment[index].insert(val);
  }
}

long long fnd(int index, const long long& val) {
  if (index > padding) return A[index - padding] >= val ? A[index - padding] : inf;

  auto it = segment[index].lower_bound(val);
  if (it != segment[index].end()) return *it;
  else return inf;
}

long long fetch(int l, int r, const long long& k) {
  int s = padding + l - 1;
  int t = padding + r + 1;

  long long res = inf;
  for (; s ^ t ^ 1; s >>= 1, t >>= 1) {
    if (~s & 1) res = min(res, fnd(s ^ 1, k));
    if (t & 1) res = min(res, fnd(t ^ 1, k));
  }

  if (res == inf) return -1;
  else return res;
}

#define _debug 0
int main() {
  cin.tie(0)->sync_with_stdio(0);

  #if _debug == 1
  freopen("input.inp", "r", stdin);
  #else

  #endif // _debug

  cin >> n >> q;
  for (int i = 1; i <= n; i++) {
    cin >> A[i];
    segment[padding + i].insert(A[i]);
  }

  for (int i = padding - 1; i > 0; i--) {
    int lchild = i << 1;
    int rchild = i << 1 | 1;
    if (segment[lchild].size() < segment[rchild].size()) swap(lchild, rchild);

    segment[i] = segment[lchild];
    for (const auto &x : segment[rchild]) segment[i].insert(x);
  }

  while (q--) {
    int type;
    cin >> type;
    if (type == 1) {
      int index;
      long long val;
      cin >> index >> val;
      update(index, val);
    } else if (type == 2) {
      int l, r;
      long long k;
      cin >> l >> r >> k;
      cout << fetch(l, r, k) << '\n';
    }
  }

}
