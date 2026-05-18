#include <bits/stdc++.h>
using namespace std;
// Problem: https://postimg.cc/CBsr0RNq
#define popcount __builtin_popcountll

bool check(long long m1, long long m2) {
  if (m1 == m2)
    return false;
  return m1 & ((m1 ^ m2) & -(m1 ^ m2));
}

struct item {
  long long sum = 0;
  long long mask = 0;

  bool operator<(const item &other) const {
    if (other.sum != sum)
      return sum < other.sum;
    int c1 = popcount(mask);
    int c2 = popcount(other.mask);
    if (c1 != c2)
      return c1 < c2;
    return check(mask, other.mask);
  }
};

int n;
long long W;
vector<long long> Q;
vector<item> bX;
long long bmask = -1;

void y(const long long value, const long long v1) {
  item A = {value, 0};
  vector<item>::iterator iter = lower_bound(bX.begin(), bX.end(), A);
  if (iter == bX.end() || iter->sum != value)
    return;

  long long cmask = (v1 | iter->mask);
  int cpop = popcount(cmask);
  int bpop = popcount(bmask);

  if (cpop < bpop || (cpop == bpop && check(cmask, bmask)))
    bmask = cmask;
}

void f(int start, const int &end) {
  int len = end - start;
  int mx = 1 << len;

  for (int i = 1; i < mx; i++) {
    long long sum = 0;
    long long rmask = i << start;
    for (int j = 0; j < len; j++) {
      if ((i >> j) & 1) {
        sum += Q[j + start];
      }
    }

    if (start == 0) {
      y(W - sum, rmask);
    } else {
      bX.push_back({sum, rmask});
    }
  }

  if (start == 0) {
    y(W, 0);
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  cin >> n >> W;
  if (n == 1) {
    int a;
    cin >> a;
    if (a == W)
      cout << "1\n1";
    else
      cout << "KHONGTHE";
    return 0;
  }

  Q.resize(n);
  for (int i = 0; i < n; i++)
    cin >> Q[i];

  int mid = n / 2;
  bX.reserve((1LL << mid));
  bX.push_back({0, 0});

  f(mid, n);
  stable_sort(bX.begin(), bX.end());
  f(0, mid);

  if (bmask == -1) {
    cout << "KHONGTHE";
    return 0;
  }

  cout << popcount(bmask) << '\n';
  for (int i = 0; i < n; i++) {
    if ((bmask >> i) & 1)
      cout << i + 1 << ' ';
  }

  return 0;
}
