#include <bits/stdc++.h>
using namespace std;

const int maxn = 2e5 + 5;
const long long inf = 1e15;
struct node {
  long long data;
  int l, r;
  int left, right;
};
int node_count = 1;

struct query {
  int t;
  int a, b;
  long long c;
};

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n, q;
  cin >> n >> q;
  vector<long long> A(n + 1, 0);
  for (int i = 1; i <= n; i++)
    cin >> A[i];

  vector<vector<node>> timeline(2, vector<node>(4 * n));

  auto merge = [](const long long &x, const long long &y) { return x + y; };

  auto build = [&](auto &self, int l, int r, vector<node> &segment) -> int {
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
    int lindex = self(self, l, mid, segment);
    int rindex = self(self, mid + 1, r, segment);
    segment[index].data = merge(segment[lindex].data, segment[rindex].data);
    segment[index].l = l;
    segment[index].r = r;
    segment[index].left = lindex;
    segment[index].right = rindex;
    return index;
  };

  int root = build(build, 1, n, timeline[1]);

  auto update = [&](auto &self, int index, int k, const long long &val,
                    vector<node> &segment) {
    if (segment[index].l == segment[index].r) {
      segment[index].data = val;
      return;
    }

    int lindex = segment[index].left;
    int rindex = segment[index].right;
    int mid = segment[index].l + (segment[index].r - segment[index].l) / 2;
    if (k <= mid) {
      self(self, lindex, k, val, segment);
    } else {
      self(self, rindex, k, val, segment);
    }
    segment[index].data = merge(segment[lindex].data, segment[rindex].data);
  };

  auto fetch = [&](auto &self, int index, int l, int r, vector<node> &segment) {
    if (segment[index].l > r || segment[index].r < l)
      return segment[0].data;
    if (segment[index].l >= l && segment[index].r <= r) {
      return segment[index].data;
    }

    return merge(self(self, segment[index].left, l, r, segment),
                 self(self, segment[index].right, l, r, segment));
  };

  while (q--) {
    int t;
    cin >> t;
    if (t == 1) {
      int ver, index;
      long long val;
      cin >> ver >> index >> val;
      update(update, root, index, val, timeline[ver]);
    } else if (t == 2) {
      int ver, l, r;
      cin >> ver >> l >> r;
      cout << fetch(fetch, root, l, r, timeline[ver]) << '\n';
    } else {
      int ver;
      cin >> ver;
      timeline.push_back(timeline[ver]);
    }
  }
}
