#include <bits/stdc++.h>
using namespace std;

// Count unique elements in a range

const int maxn = 5e4 + 5;
const int maxnum = 1e6 + 5;
const int maxnode = 250;
int A[maxn];
int n, q, sz;
bitset<maxnum> block[maxnode];

#define _debug 1
int main() {
  cin.tie(0)->sync_with_stdio(0);

#if _debug == 1
  freopen("input.inp", "r", stdin);
#else
#endif //_debug

  cin >> n;
  for (int i = 1; i <= n; i++)
    cin >> A[i];
  sz = sqrt(n);
  for (int i = 1; (i - 1) * sz + 1 <= n; i++) {
    int start = (i - 1) * sz + 1;
    int end = start + sz - 1;
    while (start <= end) {
      block[i][A[start]] = true;
      start++;
    }
  }
  bitset<maxnum> res;
  cin >> q;
  while (q--) {
    res.reset();
    int l, r;
    cin >> l >> r;
    while (l <= r) {
      if ((l - 1) % sz == 0 && r >= (l - 1) + sz) {
        int index = (l - 1) / sz + 1;
        res |= block[index];
        l += sz;
      } else {
        res[A[l]] = true;
        l++;
      }
    }
    cout << res.count() << '\n';
  }
}
