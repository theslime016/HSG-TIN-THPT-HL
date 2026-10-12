#include <bits/stdc++.h>
using namespace std;

const int maxn = 2e5 + 5;
long long A[maxn];
long long fenwick[maxn];
void update(int index, const long long& val) {
  for (; index < maxn; index += index & -index) {
    fenwick[index] += val;
  }
}

long long fetch(int index) {
  long long res = 0;
  for (; index > 0; index -= index & -index) {
    res += fenwick[index];
  }
  return res;
}

long long get(int l, int r) {
  return fetch(r) - fetch(l - 1);
}

#define _debug 0
int main() {
  cin.tie(0)->sync_with_stdio(0);

  #if _debug == 1
  freopen("input.inp", "r", stdin);
  #else

  #endif // _debug

  int n, q;
  cin >> n >> q;
  for (int i = 1; i <= n; i++) cin >> A[i];
  for (int i = 1; i <= n; i++) {
    fenwick[i] += A[i];
    int nxt = i + (i & -i);
    if (nxt <= n) fenwick[nxt] += fenwick[i];
  }

  while (q--) {
    int type;
    cin >> type;
    if (type == 1) {
      int index;
      long long val;
      cin >> index >> val;
      update(index, val - A[index]);
      A[index] = val;


    } else if (type == 2) {
      int l;
      long long lim;
      cin >> l >> lim;

      int r = n + 1;
      for (int d = r - l; d > 0; d /= 2) {
        while (r - d >= l && get(l, r - d) >= lim) r -= d;
      }
      cout << r << '\n';


    } else if (type == 3) {
      int r;
      long long lim;
      cin >> r >> lim;

      int l = 0;
      for (int d = r - l; d > 0; d /= 2) {
        while (l + d <= r && get(l + d, r) >= lim) l += d;
      }
      cout << l << '\n';


    }
  }


}
