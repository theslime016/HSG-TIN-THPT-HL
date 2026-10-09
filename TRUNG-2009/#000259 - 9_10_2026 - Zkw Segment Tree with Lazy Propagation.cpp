#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5 + 5;
const int padding = 131072;
const int h = 17;
const long long inf = 1e18;
long long segment[maxn << 2];
long long lazy[maxn << 2];
int n, q;

void push_down(int index) {
  for (int temp = h; temp > 0; temp--) {
    int parent = index >> temp;
    if (lazy[parent]) {
      segment[parent << 1] += lazy[parent];
      lazy[parent << 1] += lazy[parent];
      segment[parent << 1 | 1] += lazy[parent];
      lazy[parent << 1 | 1] += lazy[parent];

      lazy[parent] = 0;
    }
  }
}

void push_up(int index) {
  for (index >>= 1; index > 0; index >>= 1) {
    segment[index] = max(segment[index << 1], segment[index << 1 | 1]);
  }
}

void update(int l, int r, const long long &val) {
  int s = padding + l - 1;
  int t = padding + r + 1;

  push_down(s);
  push_down(t);

  int os = s;
  int ot = t;
  for (; s ^ t ^ 1; s >>= 1, t >>= 1) {
    if (~s & 1) {
      segment[s ^ 1] += val;
      lazy[s ^ 1] += val;
    }
    if (t & 1) {
      segment[t ^ 1] += val;
      lazy[t ^ 1] += val;
    }
  }

  push_up(os);
  push_up(ot);
}

long long fetch(int l, int r) {
  int s = padding + l - 1;
  int t = padding + r + 1;
  push_down(s);
  push_down(t);

  int os = s;
  int ot = t;
  long long res = -inf;
  for (; s ^ t ^ 1; s >>= 1, t >>= 1) {
    if (~s & 1) res = max(res, segment[s ^ 1]);
    if (t & 1) res = max(res, segment[t ^ 1]);
  }

  return res;
}

#define _debug 0
int main() {
  cin.tie(0)->sync_with_stdio(0);

#if _debug == 1
  freopen("input.inp", "r", stdin);
#else

#endif // _debug

  fill_n(segment, maxn << 2, -inf);

  cin >> n;
  for (int i = 1; i <= n; i++) cin >> segment[padding + i];
  for (int i = padding - 1; i > 0; i--) segment[i] = max(segment[i << 1], segment[i << 1 | 1]);

  cin >> q;
  while (q--) {
    int type;
    cin >> type;
    if (type == 1) {
      int l, r;
      long long val;
      cin >> l >> r >> val;
      update(l, r, val);
    } else if (type == 2) {
      int l, r;
      cin >> l >> r;
      cout << fetch(l, r) << '\n';
    }
  }
}
