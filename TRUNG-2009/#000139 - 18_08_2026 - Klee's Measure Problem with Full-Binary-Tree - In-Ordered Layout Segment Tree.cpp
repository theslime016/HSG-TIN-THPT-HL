#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5 + 5;
const int maxk = 1e6;
const long long inf = 1e15;
struct node {
  long long down, up;
  long long count;
  long long length;

  node() { down = up = count = length = 0; }
  node(long long x, long long y) {
    down = x;
    up = y;
    count = 0;
    length = 0;
  }
} segment[maxk];

vector<long long> ylevel;
void build(int index) {
  if (index & 1) {
    int jindex = index / 2;
    segment[index] = node(ylevel[jindex], ylevel[jindex + 1]);
    return;
  }

  int lindex = index - (index & -index) / 2;
  int rindex = index + (index & -index) / 2;
  build(lindex);
  build(rindex);

  segment[index] = node(segment[lindex].down, segment[rindex].up);
}

void oper(int type, int index, int ql, int qr) {
  if (segment[index].down >= qr || segment[index].up <= ql)
    return;

  if (ql <= segment[index].down && qr >= segment[index].up) {
    segment[index].count += type;

    if (segment[index].count > 0) {
      segment[index].length = segment[index].up - segment[index].down;
    } else {
      if (index & 1) {
        segment[index].length = 0;
      } else {
        int step = (index & -index) / 2;
        segment[index].length =
            segment[index - step].length + segment[index + step].length;
      }
    }
    return;
  }
  if (index & 1)
    return;

  int lindex = index - (index & -index) / 2;
  int rindex = index + (index & -index) / 2;

  oper(type, lindex, ql, qr);
  oper(type, rindex, ql, qr);

  if (segment[index].count > 0)
    segment[index].length = segment[rindex].up - segment[lindex].down;
  else
    segment[index].length = segment[lindex].length + segment[rindex].length;
}

struct line {
  int op;
  long long x;
  long long down, up;
};

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n;
  cin >> n;
  vector<line> query;
  query.reserve(2 * n);
  ylevel.reserve(2 * n);
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

  int interval = (int)ylevel.size() - 1;
  int k = 1;
  while (k < interval)
    k <<= 1;
  while (ylevel.size() - 1 < k) {
    ylevel.push_back(ylevel.back());
  }

  int root = k;
  build(root);

  sort(query.begin(), query.end(),
       [](const line &a, const line &b) { return a.x < b.x; });

  long long res = 0;
  long long last_x = query[0].x;
  for (const line &t : query) {
    long long d = t.x - last_x;
    res += d * segment[root].length;
    oper(t.op, root, t.down, t.up);

    cout << t.op << ' ' << t.x << ' ' << t.down << ' ' << t.up << '\n';

    last_x = t.x;

    for (int i = 1; i < 2 * k; i++) {
      cout << i << ':' << segment[i].down << "->" << segment[i].up << ' '
           << segment[i].count << ' ' << segment[i].length << '\n';
    }
  }
  cout << res << '\n';
}
