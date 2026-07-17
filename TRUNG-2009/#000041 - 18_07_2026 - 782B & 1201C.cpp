#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int n;
  cin >> n;
  vector<long long> x(n), v(n);
  for (int i = 0; i < n; i++)
    cin >> x[i];
  for (int i = 0; i < n; i++)
    cin >> v[i];

  auto f = [&](double t) -> bool {
    double max_l = -1e18;
    double min_r = 1e18;
    for (int i = 0; i < n; i++) {
      max_l = max(max_l, x[i] - t * v[i]);
      min_r = min(min_r, x[i] + t * v[i]);
    }
    return max_l <= min_r;
  };

  double l = 0.0, r = 1e9;
  for (int i = 0; i < 100; i++) {
    double mid = l + (r - l) / 2.0;
    if (f(mid)) {
      r = mid;
    } else {
      l = mid;
    }
  }
  cout << fixed << setprecision(9) << r;
  cout << defaultfloat << setprecision(6);

  return 0;
}





#include <bits/stdc++.h>
using namespace std;

#ifndef NDEBUG
#define NDEBUG
#endif

long long func(long long l, long long r, function<bool(long long)> f) {
  for (long long d = r - l; d > 0; d /= 2) {
    while (l + d <= r && f(l + d))
      l += d;
  }
  return l;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int n, k;
  cin >> n >> k;
  vector<long long> A(n);
  for (int i = 0; i < n; i++)
    cin >> A[i];
  sort(A.begin(), A.end());

  cout << func(-1LL, 2e9 * 1LL, [&](long long x) -> bool {
    long long r = 0;
    for (int i = (n - 1) / 2; i < n; i++) {
      r += max(0LL, x - A[i]);
    }
    return r <= k;
  });

  return 0;
}
