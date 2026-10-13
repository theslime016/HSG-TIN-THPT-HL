#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5 + 5;
int fenwick[maxn];

void update(int index, int val) {
  for (; index > 0; index -= index & -index) {
    fenwick[index] += val;
  }
}

int fetch(int index) {
  int res = 0;
  for (; index < maxn; index += index & -index) {
    res += fenwick[index];
  }
  return res;
}

struct POINT {
  long long x, y;

  friend bool operator<(const POINT& a, const POINT& b) {
    return a.x < b.x || (a.x == b.x && a.y > b.y);
  }
} point[maxn];

#define _debug 0
int main() {
  cin.tie(0)->sync_with_stdio(0);

  #if _debug == 1
  freopen("input.inp", "r", stdin);
  #else

  #endif // _debug

  int n;
  long long A, B;
  cin >> n >> A >> B;

  vector<long long> bcoor;
  bcoor.reserve(n);
  for (int i = 1; i <= n; i++) {
    long long x, y;
    cin >> x >> y;
    point[i] = {A * x - y, B * x - y};
    bcoor.push_back(B * x - y);
  }

  sort(bcoor.begin(), bcoor.end());
  bcoor.erase(unique(bcoor.begin(), bcoor.end()), bcoor.end());

  sort(point + 1, point + n + 1);
  long long res = 0;
  for (int i = 1; i <= n; i++) {
    int fnd = lower_bound(bcoor.begin(), bcoor.end(), point[i].y) - bcoor.begin() + 1;
    res += fetch(fnd);
    update(fnd, 1);
  }

  cout << res;

}
