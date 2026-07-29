#include <bits/stdc++.h>
using namespace std;

#define popcount __builtin_popcount

int main() {
  cin.tie(0)->sync_with_stdio(false);

  freopen("VOLLEYBALL.INP", "r", stdin);
  freopen("VOLLEYBALL.ANS", "w", stdout);

  int n, m;
  cin >> n >> m;
  vector<long long> A(n), B(m);
  for (int i = 0; i < n; i++)
    cin >> A[i];
  for (int j = 0; j < m; j++)
    cin >> B[j];

  auto check = [&](int a, int b) {
    long long sum1 = 0, sum2 = 0;
    for (int i = 0; i < n; i++) {
      if ((1 << i) & a) {
        sum1 += A[i];
      }
    }
    for (int j = 0; j < m; j++) {
      if ((1 << j) & b) {
        sum2 += B[j];
      }
    }
    return sum1 == sum2 ? sum1 : -1;
  };

  long long res = LLONG_MAX;
  for (int m1 = 0; m1 < (1 << n); m1++) {
    for (int m2 = 0; m2 < (1 << m); m2++) {
      if (popcount(m1) == 2 && popcount(m2) == 2) {
        long long t = check(m1, m2);
        if (t != -1)
          res = min(res, t);
      }
    }
  }

  if (res == LLONG_MAX) {
    cout << "no volleyball today";
  } else {
    cout << res;
  }

  return 0;
}
