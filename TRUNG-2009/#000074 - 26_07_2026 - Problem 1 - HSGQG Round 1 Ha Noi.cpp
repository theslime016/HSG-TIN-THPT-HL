#include <bits/stdc++.h>
using namespace std;

#ifndef NDEBUG
#define NDEBUG
#endif

#define endl '\n'

const int maxn = 1e5 + 10;
int A[maxn]{};
int pref[3][maxn]{};

int main() {
  cin.tie(0)->sync_with_stdio(false);

  freopen("input.inp", "r", stdin);
  freopen("output.out", "w", stdout);

  auto get = [&](int l, int r, const int *p) {
    return *(p + r) - *(p + l - 1);
  };

  int n, k;
  cin >> n >> k;
  for (int i = 1; i <= n; i++) {
    cin >> A[i];
    pref[0][i] += pref[0][i - 1] + (A[i] != 0);
    pref[1][i] += pref[1][i - 1] + (A[i] != 1);
    pref[2][i] += pref[2][i - 1] + (A[i] != 2);
  }

  auto check = [&](int index, int dist) mutable -> bool {
    static int f[6][2] = {{0, 1}, {1, 0}, {0, 2}, {2, 0}, {1, 2}, {2, 1}};
    for (int i = 0; i < 6; i++) {
      int cost1 = get(index - dist, index, &pref[f[i][0]][0]);
      int cost2 = get(index + 1, index + dist + 1, &pref[f[i][1]][0]);
      if (cost1 + cost2 <= k)
        return true;
    }
    return false;
  };

  int res = 0;
  for (int i = 1; i <= n; i++) {
    int r = min(i - 1, n - i - 1);
    int l = -1;
    for (int d = r - l; d > 0; d /= 2) {
      while (l + d <= r && check(i, l + d))
        l += d;
    }
    res = max(res, (l + 1) * 2);
  }

  cout << res;

  return 0;
}
