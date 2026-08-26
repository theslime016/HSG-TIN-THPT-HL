#include <bits/stdc++.h>
using namespace std;

const int maxnode = 6e6;
struct node {
  int left, right;
  int sum;
  bool lazy;
} segment[maxnode];

const int __start_ = 1;
const int __end_ = 1e9;
int root = 1;
int node_count = 2;

inline void apply(int index, int len) {
  segment[index].sum = len;
  segment[index].lazy = true;
}

void pushup(int index) {
  segment[index].sum = 0;
  if (segment[index].left)
    segment[index].sum += segment[segment[index].left].sum;
  if (segment[index].right)
    segment[index].sum += segment[segment[index].right].sum;
}

void pushdown(int index, int l, int r) {
  if (!segment[index].lazy)
    return;

  if (!segment[index].left)
    segment[index].left = node_count++;
  if (!segment[index].right)
    segment[index].right = node_count++;

  int mid = l + (r - l) / 2;
  apply(segment[index].left, mid - l + 1);
  apply(segment[index].right, r - mid);

  segment[index].lazy = false;
}

void update(int &index, int l, int r, int u, int v) {
  if (!index)
    index = node_count++;

  if (l > v || r < u)
    return;
  if (l >= u && r <= v) {
    apply(index, r - l + 1);
    return;
  }

  pushdown(index, l, r);

  int mid = l + (r - l) / 2;
  update(segment[index].left, l, mid, u, v);
  update(segment[index].right, mid + 1, r, u, v);

  pushup(index);
}

int query(int index, int l, int r, int u, int v) {
  if (!index)
    return 0;
  if (l > v || r < u)
    return 0;
  if (l >= u && r <= v)
    return segment[index].sum;

  pushdown(index, l, r);
  int mid = l + (r - l) / 2;
  return query(segment[index].left, l, mid, u, v) +
         query(segment[index].right, mid + 1, r, u, v);
}

void ranker() {
  deque<pair<int, int>> wait;
  wait.push_back({root, 1});

  int last_rank = 0;
  while (!wait.empty()) {
    auto [index, depth] = wait.front();
    wait.pop_front();
    if (last_rank != depth) {
      cout << "\nrank " << depth << ':';
      last_rank = depth;
    }

    cout << segment[index].sum << ' ';
    if (segment[index].left)
      wait.push_back({segment[index].left, depth + 1});
    if (segment[index].right)
      wait.push_back({segment[index].right, depth + 1});
  }
}

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
long long rnd(long long l, long long r) {
  return uniform_int_distribution<long long>(l, r)(rng);
}

void stress() {
  int n = 100;
  int q = 10;
  vector<bool> temp(n + 1, false);
  for (int i = 0; i < q; i++) {
    int l = rnd(1, n);
    int r = rnd(l, n);
    update(root, __start_, __end_, l, r);

    for (int j = l; j <= r; j++)
      temp[j] = 1;
  }

  for (int i = 1; i <= n; i++) {
    for (int j = i; j <= n; j++) {
      int t = query(root, __start_, __end_, i, j);

      for (int rindex = i; rindex <= j; rindex++)
        t -= temp[rindex];

      if (t != 0) {
        cout << "oaiwjwioajfoa";
        exit(0);
      }
    }
  }
}

int main() {
  cin.tie(0)->sync_with_stdio(0);

  // stress();
  // return 0;

  int c = 0;
  int q;
  cin >> q;
  while (q--) {
    int type, x, y;
    cin >> type >> x >> y;
    x += c;
    y += c;
    if (type == 1) {
      c = query(root, __start_, __end_, x, y);
      cout << c << '\n';
    } else {
      update(root, __start_, __end_, x, y);
    }
  }

  // ranker();
}
