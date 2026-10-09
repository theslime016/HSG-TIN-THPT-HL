#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5 + 5;
const long long inf = 1e18;
long long A[maxn];
long long B[maxn];

int get_index[maxn];
int lblock[maxn], rblock[maxn];
int n, q, sz, num_block;

void proc(int index, const long long& val) {
  A[index] = val;
  int tag = get_index[index];
  copy(A + lblock[tag], A + rblock[tag] + 1, B + lblock[tag]);
  sort(B + lblock[tag], B + rblock[tag] + 1);
}

#define _debug 0
int main() {
  cin.tie(0)->sync_with_stdio(0);

  #if _debug == 1
  freopen("input.inp", "r", stdin);
  #else

  #endif // _debug

  cin >> n >> q;
  sz = sqrt(n);
  num_block = (n-1)/sz + 1;
  for (int i = 1; i <= n; i++) {
    cin >> A[i];
    B[i] = A[i];
    get_index[i] = (i-1)/sz + 1;
  }

  for (int i = 1; i <= num_block; i++) {
    lblock[i] = (i-1)*sz + 1;
    rblock[i] = i*sz;
    sort(B + lblock[i], B + rblock[i] + 1);
  }

  for (int i = 1; i <= q; i++) {
    int type;
    cin >> type;
    if (type == 1) {
      int index;
      long long val;
      cin >> index >> val;
      proc(index, val);
    } else if (type == 2) {
      int l, r;
      long long k;
      cin >> l >> r >> k;
      long long res = inf;

      while (l <= r) {
        int tag = get_index[l];
        if ((l - 1)%sz == 0 && l + sz < r) {
          int index = lower_bound(B + lblock[tag], B + rblock[tag] + 1, k) - (B + lblock[tag]);
          index += lblock[tag];
          if (index <= rblock[tag]) res = min(res, B[index]);
          l += sz;
        } else {
          if (A[l] >= k) res = min(res, A[l]);
          l++;
        }
      }

      if (res == inf) cout << -1 << '\n';
      else cout << res << '\n';
    }
  }


}
