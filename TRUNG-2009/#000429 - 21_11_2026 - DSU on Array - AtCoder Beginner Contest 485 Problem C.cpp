#include <bits/stdc++.h>
using namespace std;

#define _debug 0

const int maxn = 3e5 + 5;
const int inf = 1e9;

int n;
int A[maxn];

struct DSU {
  int n;
  int data[maxn];
  pair<int, int> container[maxn];

  void init(int _n) {
    n = _n;
    iota(data, data + n + 1, 0);
    fill_n(container, n + 1, make_pair(inf, 0));
  }

  int fnd(int index) {
    if (data[index] == index) return index;
    return data[index] = fnd(data[index]);
  }

  void make_union(int a, int b) {
    a = fnd(a);
    b = fnd(b);
    if (a != b) {
      data[b] = a;
      if (container[a].first == inf) {
        container[a] = {a, b};
      } else {
        container[a].second = b;
      }
    }
  }

} dsu;

int main() {
  cin.tie(0)->sync_with_stdio(0);

#if _debug == 1
  freopen("input.inp", "r", stdin);

#elif _debug == 2
  freopen("input.inp", "r", stdin);

#else

#endif // _debug

  cin >> n;
  for (int i = 1; i <= n; i++) cin >> A[i];

  dsu.init(n);

  for (int i = 2; i <= n; i++) {
    if (A[i - 1] == A[i]) dsu.make_union(i - 1, i);
  }

  for (int i = 1; i <= n; i++) {
    int fnd_index = dsu.fnd(i);
    if (dsu.container[fnd_index].first == inf) {
      cout << 1 << ' ';
      continue;
    }

    int res = inf;

    int left = dsu.container[fnd_index].first - 1;
    int right = dsu.container[fnd_index].second + 1;
    if (left >= 1) res = min(res, i - left);
    if (right <= n) res = min(res, right - i);
    cout << res << ' ';
  }

}
