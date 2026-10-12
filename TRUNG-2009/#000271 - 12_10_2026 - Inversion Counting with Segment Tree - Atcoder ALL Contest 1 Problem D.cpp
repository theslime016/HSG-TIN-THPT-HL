#include <bits/stdc++.h>
using namespace std;

const int maxn = 2e5 + 5;
const int padding = 262144;
struct NODE {
  long long inv;
  long long cnt[3];
};
NODE segment[maxn << 2];
int A[maxn];

void proc(const NODE& a, const NODE& b, NODE& res) {
  res.inv = a.inv + b.inv;
  res.inv += b.cnt[0] * (a.cnt[1] + a.cnt[2]);
  res.inv += b.cnt[1] * a.cnt[2];

  for (int i = 0; i < 3; i++) {
    res.cnt[i] = a.cnt[i] + b.cnt[i];
  }
}

NODE proc2(const NODE& a, const NODE& b) {
  NODE res{};
  res.inv = a.inv + b.inv;
  res.inv += b.cnt[0] * (a.cnt[1] + a.cnt[2]);
  res.inv += b.cnt[1] * a.cnt[2];

  for (int i = 0; i < 3; i++) {
    res.cnt[i] = a.cnt[i] + b.cnt[i];
  }

  return res;
}

void update(int index, int val) {
  index += padding;
  segment[index].cnt[A[index - padding]] = 0;
  A[index - padding] = val;
  segment[index].cnt[val] = 1;

  for (index >>= 1; index > 0; index >>= 1) {
    proc(segment[index << 1], segment[index << 1 | 1], segment[index]);
  }
}

long long fetch(int l, int r) {
  int s = padding + l - 1;
  int t = padding + r + 1;
  NODE left {},
       right {};

  for (; s ^ t ^ 1; s >>= 1, t >>= 1) {
    if (~s & 1) {
      left = proc2(left, segment[s ^ 1]);
    }
    if (t & 1) {
      right = proc2(segment[t ^ 1], right);
    }
  }

  return proc2(left, right).inv;
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
    segment[padding + i].cnt[A[i]] = 1;
  }

  for (int index = padding - 1; index > 0; index--) {
    proc(segment[index << 1], segment[index << 1 | 1], segment[index]);
  }

  while (q--) {
    int type;
    cin >> type;
    if (type == 1) {
      int index, val;
      cin >> index >> val;
      update(index, val);
    } else if (type == 2) {
      int l, r;
      cin >> l >> r;
      cout << fetch(l, r) << endl;
    }
  }
}
