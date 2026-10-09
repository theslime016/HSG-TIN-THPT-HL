#include <bits/stdc++.h>
using namespace std;

const int maxn = 2e4 + 5;
int A[maxn];
vector<int> occur[maxn];
int get_index[maxn];
pair<int, int> block[maxn];
int lblock[maxn], rblock[maxn];
int n, q;
int sz, num_block;

pair<int, int> proc(pair<int, int> x, pair<int, int> y) {
  if (x.first == y.first) return {x.first, x.second + y.second};
  else if (x.second >= y.second) return {x.first, x.second - y.second};
  else return {y.first, y.second - x.second};
}

int cnt_freq(int val, int l, int r) {
  int start = lower_bound(occur[val].begin(), occur[val].end(), l) - occur[val].begin();
  int stop = upper_bound(occur[val].begin(), occur[val].end(), r) - occur[val].begin() - 1;
  return stop - start + 1;
}

#define _debug 1
int main() {
  cin.tie(0)->sync_with_stdio(0);

  #if _debug == 1
  freopen("input.inp", "r", stdin);
  #else

  #endif // _debug

  cin >> n >> q;
  sz = max(1, n / (int)sqrt(q));
  num_block = (n-1)/sz + 1;
  for (int i = 1; i <= n; i++) {
    cin >> A[i];
    get_index[i] = (i-1)/sz + 1;
    block[ get_index[i] ] = proc(block[ get_index[i] ], {A[i], 1});
    occur[ A[i] ].push_back(i);
  }

  for (int i = 1; i <= num_block; i++) {
    lblock[i] = (i-1)*sz + 1;
    rblock[i] = i*sz;
  }

  while (q--) {
    int l, r, lim;
    cin >> l >> r >> lim;
    int ql = l;
    int qr = r;
    pair<int, int> res = {0, 0};
    while (l <= r) {
      if ((l-1)%sz == 0 && l + sz - 1 <= r) {
        res = proc(res, block[get_index[l]]);
        l += sz;
      } else {
        res = proc(res, {A[l], 1});
        l++;
      }
    }

    int cnt = cnt_freq(res.first, ql, qr);
    if (cnt >= lim) cout << res.first << '\n';
    else cout << -1 << '\n';
  }

}
