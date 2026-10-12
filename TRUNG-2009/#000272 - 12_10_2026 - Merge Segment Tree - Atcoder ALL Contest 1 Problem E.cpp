#include <bits/stdc++.h>
using namespace std;

const int maxn = 2e5 + 5;
const int padding = 262144;
const long long mod = 998244353;
long long A[maxn];
int tag[maxn];

struct NODE {
  long long sum;
  long long color[3];
  long long RG;
  long long GB;
};

NODE segment[maxn << 2];

NODE proc(const NODE& a, const NODE& b) {
  NODE res{};

  res.sum = (a.sum + b.sum) % mod;
  res.sum = ( res.sum +
              ( (a.RG*b.color[2])%mod
                +
                (a.color[0]*b.GB)%mod
              ) % mod
            ) % mod;

  for (int index = 0; index < 3; index++) {
    res.color[index] = (a.color[index] + b.color[index]) % mod;
  }

  res.RG = ((a.RG + b.RG) % mod + (a.color[0] * b.color[1]) % mod)%mod;
  res.GB = ((a.GB + b.GB) % mod + (a.color[1] * b.color[2]) % mod)%mod;

  return res;
}

void update(int index, const long long& val) {
  segment[index + padding].color[tag[index]] = val;
  index += padding;

  for (index >>= 1; index > 0; index >>= 1) {
    segment[index] = proc(segment[index << 1], segment[index << 1 | 1]);
  }
}

long long fetch(int l, int r) {
  int s = padding + l - 1;
  int t = padding + r + 1;

  NODE left{}, right{};
  for (; s ^ t ^ 1; s >>= 1, t >>= 1) {
    if (~s & 1) left = proc(left, segment[s ^ 1]);
    if (t & 1) right = proc(segment[t ^ 1], right);
  }

  return proc(left, right).sum;
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
  for (int i = 1; i <= n; i++) cin >> A[i];
  for (int i = 1; i <= n; i++) {
    char x;
    cin >> x;
    if (x == 'R') tag[i] = 0;
    else if (x == 'G') tag[i] = 1;
    else if (x == 'B') tag[i] = 2;
  }

  for (int index = 1; index <= n; index++) {
    segment[padding + index].color[tag[index]] = A[index];
  }

  for (int index = padding - 1; index > 0; index--) {
    segment[index] = proc(segment[index << 1], segment[index << 1 | 1]);
  }

  while (q--) {
    int type;
    cin >> type;
    if (type == 1) {
      int index;
      long long val;
      cin >> index >> val;
      update(index, val);
    } else if (type == 2) {
      int l, r;
      cin >> l >> r;
      cout << fetch(l, r) << '\n';
    }
  }

}
