#include <bits/stdc++.h>
using namespace std;

const int maxn = 2e5 + 5;
const long long inf = 1e15;
struct node {
  long long data;
  int l, r;
  int left, right;
} segment[4 * maxn];
int node_count = 1;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n, q;
  cin >> n >> q;
  vector<long long> A(n + 1, 0);
  for (int i = 1; i <= n; i++)
    cin >> A[i];

  segment[0].data = inf;
  segment[0].l = segment[0].r = 0;
  segment[0].left = segment[0].right = 0;

  auto merge = [](const long long &x, const long long &y) { return min(x, y); };

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

  int root = build(build, 1, n);

  auto update = [&](auto &self, int index, int k, const long long &val) {
    if (segment[index].l == segment[index].r) {
      segment[index].data = val;
      return;
    }

    int lindex = segment[index].left;
    int rindex = segment[index].right;
    int mid = segment[index].l + (segment[index].r - segment[index].l) / 2;
    if (k <= mid) {
      self(self, lindex, k, val);
    } else {
      self(self, rindex, k, val);
    }
    segment[index].data = merge(segment[lindex].data, segment[rindex].data);
  };

  auto fetch = [&](auto &self, int index, int l, int r) {
    if (segment[index].l > r || segment[index].r < l)
      return segment[0].data;
    if (segment[index].l >= l && segment[index].r <= r) {
      return segment[index].data;
    }

    return min(self(self, segment[index].left, l, r),
               self(self, segment[index].right, l, r));
  };

  while (q--) {
    int t;
    cin >> t;
    if (t == 1) {
      int index;
      long long val;
      cin >> index >> val;
      update(update, root, index, val);
    } else {
      int l, r;
      cin >> l >> r;
      cout << fetch(fetch, root, l, r) << '\n';
    }
  }
}
