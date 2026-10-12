#include <bits/stdc++.h>
using namespace std;

const int maxn = 2e5 + 5;
const int padding = 262144;
int A[maxn];

struct NODE {
  int best;
  int same;
  int head, tail;
  int head_color, tail_color;
};

NODE segment[maxn << 2];

NODE proc(const NODE& a, const NODE& b) {
  if (!a.best) return b;
  if (!b.best) return a;
  NODE res{};
  res.best = max(a.best, b.best);

  res.head_color = a.head_color;
  res.tail_color = b.tail_color;

  res.head = a.head;
  res.tail = b.tail;

  if (a.tail_color == b.head_color) {
    res.best = max(res.best, a.tail + b.head);
    res.same = a.same && b.same;
    if (a.same) res.head += b.head;
    if (b.same) res.tail += a.tail;
  }

  return res;
}

void update(int index, int val) {
  index += padding;
  segment[index].head_color = segment[index].tail_color = val;

  for (index >>= 1; index > 0; index >>= 1) {
    segment[index] = proc(segment[index << 1], segment[index << 1 | 1]);
  }
}

int fetch(int l, int r) {
  int s = padding + l - 1;
  int t = padding + r + 1;

  NODE left{}, right{};
  for (; s ^ t ^ 1; s >>= 1, t >>= 1) {
    if (~s & 1) left = proc(left, segment[s ^ 1]);
    if (t & 1) right = proc(segment[t ^ 1], right);
  }
  return proc(left, right).best;
}

#define _debug 0
int main() {
  cin.tie(0)->sync_with_stdio(0);

  #if _debug == 1
  freopen("input.inp", "r", stdin);
  #else

  #endif // _debug

  int n, q;
  cin >> n >> q;
  for (int i = 1; i <= n; i++) {
    cin >> A[i];
  }

  for (int i = 1; i <= n; i++) {
    segment[padding + i] = {1, 1, 1, 1, A[i], A[i]};
  }

  for (int i = padding - 1; i > 0; i--) {
    segment[i] = proc(segment[i << 1], segment[i << 1 | 1]);
  }

  while (q--) {
    int type;
    cin >> type;
    if (type == 1) {
      int index;
      int val;
      cin >> index >> val;
      update(index, val);
    } else if (type == 2) {
      int l, r;
      cin >> l >> r;
      cout << fetch(l, r) << endl;
    }
  }
}
