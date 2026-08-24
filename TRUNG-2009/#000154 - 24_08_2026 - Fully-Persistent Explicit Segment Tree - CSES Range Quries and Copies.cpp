/*late in autumn*/

#include <bits/stdc++.h>
using namespace std;

const int maxn = 2e5 + 5;
struct node {
  long long data;
  int l, r;
  int left, right;
} segment[40 * maxn];
int root[maxn];
int node_count = 1;
int root_count = 1;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n, q;
  cin >> n >> q;
  vector<long long> A(n + 1, 0);
  for (int i = 1; i <= n; i++)
    cin >> A[i];

  segment[0].data = 0;
  segment[0].l = segment[0].r = 0;
  segment[0].left = segment[0].right = 0;

  auto merge = [](const long long &x, const long long &y) { return x + y; };

  auto build = [&](auto &self, int l, int r) -> int {
    if (l < 1 || r > n)
      return 0;
    int index = node_count++;
    if (l == r) {
      segment[index].data = A[l];
      segment[index].l = segment[index].r = l;
      segment[index].left = segment[index].right = 0;
      return index;
    }

    int mid = l + (r - l) / 2;
    int lindex = self(self, l, mid);
    int rindex = self(self, mid + 1, r);
    segment[index].data = merge(segment[lindex].data, segment[rindex].data);
    segment[index].l = l;
    segment[index].r = r;
    segment[index].left = lindex;
    segment[index].right = rindex;
    return index;
  };

  root[root_count++] = build(build, 1, n);

  auto update = [&](auto &self, int index, int k, const long long &val) {
    int new_index = node_count++;
    segment[new_index] = segment[index];
    if (segment[new_index].l == segment[new_index].r) {
      segment[new_index].data = val;
      return new_index;
    }

    int mid = segment[new_index].l +
              (segment[new_index].r - segment[new_index].l) / 2;
    if (k <= mid) {
      segment[new_index].left = self(self, segment[new_index].left, k, val);
    } else {
      segment[new_index].right = self(self, segment[new_index].right, k, val);
    }
    segment[new_index].data = merge(segment[segment[new_index].left].data,
                                    segment[segment[new_index].right].data);
    return new_index;
  };

  auto fetch = [&](auto &self, int index, int l, int r) {
    if (segment[index].l > r || segment[index].r < l)
      return segment[0].data;
    if (segment[index].l >= l && segment[index].r <= r) {
      return segment[index].data;
    }

    return merge(self(self, segment[index].left, l, r),
                 self(self, segment[index].right, l, r));
  };

  while (q--) {
    int t;
    cin >> t;
    if (t == 1) {
      int ver, index;
      long long val;
      cin >> ver >> index >> val;
      root[ver] = update(update, root[ver], index, val);
    } else if (t == 2) {
      int ver, l, r;
      cin >> ver >> l >> r;
      cout << fetch(fetch, root[ver], l, r) << '\n';
    } else {
      int ver;
      cin >> ver;
      root[root_count++] = root[ver];
    }
  }
}
