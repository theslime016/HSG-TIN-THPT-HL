#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5 + 5;
const long long inf = 1e15;
struct node {
  long long down, up;
  long long count;
  long long length;

  node() { down = up = count = length = -inf; }
  node(long long x, long long y) {
    down = x;
    up = y;
    count = 0;
    length = 0;
  }
} segment[2 * maxn];

int n;
int mx;
int build(int x, int y, int l, int r, const vector<long long> &A) {
  int index = (y - x) / 2 + x;

  if (l + 1 == r) {
    segment[index] = node(A[l], A[r]);
    return index;
  }

  segment[index] = node(A[l], A[r]);
  int mid = l + (r - l) / 2;
  build(x, index, l, mid, A);
  build(index + 1, y, mid, r, A);
  return index;
}

long long oper(int type, int x, int y, int l, int r) {
  int index = x + (y - x) / 2;
  if (segment[index].count == -inf)
    return 0;
  if (l <= segment[index].down && r >= segment[index].up) {
    segment[index].count += type;
    if (segment[index].count == 0)
      segment[index].length = 0;
    else
      segment[index].length = segment[index].up - segment[index].down;
    return segment[index].length;
  }
  if (index % 2 == 1)
    return 0;

  segment[index].length = 0;
  segment[index].length += oper(type, x, index, l, r);
  segment[index].length += oper(type, index + 1, y, l, r);
  return segment[index].length;
}

struct line {
  int op;
  long long x;
  long long down, up;
};

int main() {
  cin.tie(0)->sync_with_stdio(0);

  // freopen("input.inp", "r", stdin);

  int n;
  cin >> n;
  vector<line> query;
  vector<long long> ylevel;
  query.reserve(2 * n);
  ylevel.reserve(n);
  for (int i = 1; i <= n; i++) {
    long long a, b, c, d;
    cin >> a >> b >> c >> d;
    query.push_back({1, a, b, d});
    query.push_back({-1, c, b, d});
    ylevel.push_back(b);
    ylevel.push_back(d);
  }

  sort(ylevel.begin(), ylevel.end());
  ylevel.erase(unique(ylevel.begin(), ylevel.end()), ylevel.end());

  for (int x : ylevel)
    cout << x << ' ';
  cout << '\n';

  deque<pair<int, int>> wait;
  wait.push_back({0, (int)ylevel.size() - 1});
  while (!wait.empty()) {
    auto [x, y] = wait.front();
    wait.pop_front();
    cout << '[' << ylevel[x] << ';' << ylevel[y] << ']' << endl;
    if (x + 1 == y)
      continue;

    int mid = x + (y - x) / 2;
    wait.push_back({x, mid});
    wait.push_back({mid, y});
  }

  mx = 2 * ylevel.size() - 1;
  int root = build(1, mx, 0, (int)ylevel.size() - 1, ylevel);
  cout << mx << '\n';
  cout << root << '\n';
  for (int i = 0; i <= mx + 1; i++) {
    cout << i << ':' << segment[i].down << ' ' << segment[i].up << '\n';
  }

  long long last_x = -inf;
  long long res = 0;
  for (const line &t : query) {
    if (t.op == -1)
      continue;
    if (last_x != -inf) {
      long long d = t.x - last_x;
      res += d * segment[root].length;
    }

    oper(t.op, 1, mx, t.down, t.up);
    last_x = t.x;
  }
  cout << res;
}
