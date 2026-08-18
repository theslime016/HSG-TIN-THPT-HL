#include <bits/stdc++.h>
using namespace std;

// Mặc dù đúng là có thể biến cái này thành Fenwick Tree, nhưng vì Fenwick Tree lại không giải
// được những bài hình học phi tuyến tính nên gặp Klee's Measure Problem nó bó tay

const int maxn = 1e5 + 5;
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
} segment[maxn];

vector<long long> ylevel;
void build(int root) {
  for (int index = 1; index <= root; index++) {
    int low = index - (index & -index);
    if (low == 0) {
      segment[index] = node(0, ylevel[index - 1]);
    } else {
      segment[index] = node(segment[low].down, ylevel[index - 1]);
    }
  }
}

void oper(int type, int root, int ql, int qr) {
  for (int index = 1; index <= root; index++) {
    if (segment[index].down >= qr || segment[index].up <= ql)
      continue;

    int low = index - (index & -index);
    if (ql <= segment[index].down && qr >= segment[index].up) {
      segment[index].count += type;

      if (segment[index].count > 0) {
        segment[index].length = segment[index].up - segment[index].down;
      } else {
        if (low == 0) {
          segment[index].length = 0;
        } else {
          segment[index].length = segment[low].length;
        }
      }
    }

    if (segment[index].count > 0)
      segment[index].length = segment[index].up - segment[low].down;
    else
      segment[index].length = segment[low].length;
  }
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

  int root = ylevel.size();
  build(root);

  sort(query.begin(), query.end(),
       [](const line &a, const line &b) { return a.x < b.x; });

  long long res = 0;
  long long last_x = query[0].x;
  for (const line &t : query) {
    long long d = t.x - last_x;
    res += d * segment[root].length;
    oper(t.op, root, t.down, t.up);
    last_x = t.x;

    for (int i = 1; i <= ylevel.size(); i++) {
      cout << i << ':' << segment[i].up << "->" << segment[i].down << ' '
           << segment[i].count << ' ' << segment[i].length << '\n';
    }
    cout << '\n';
  }
  cout << res << '\n';
}
