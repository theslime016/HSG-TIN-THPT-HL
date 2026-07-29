#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(false);

  freopen("VOLLEYBALL.INP", "r", stdin);
  freopen("VOLLEYBALL.OUT", "w", stdout);

  int n, m;
  cin >> n >> m;
  vector<long long> A(n), B(m);
  for (int i = 0; i < n; i++)
    cin >> A[i];
  for (int j = 0; j < m; j++)
    cin >> B[j];

  vector<long long> pref;
  pref.reserve(n * (n - 1) / 2);
  for (int i = 0; i < n; i++) {
    for (int j = i + 1; j < n; j++) {
      pref.push_back(A[i] + A[j]);
    }
  }

  sort(pref.begin(), pref.end());
  pref.erase(unique(pref.begin(), pref.end()), pref.end());

  sort(B.begin(), B.end());
  long long minB = B[0] + B[1];
  long long maxB = B[m - 1] + B[m - 2];

  long long res = LLONG_MAX;
  auto check = [&]() mutable {
    for (int i = 0; i < (int)pref.size(); i++) {
      long long sum = pref[i];
      if (sum > maxB || sum < minB)
        continue;
      int l = 0;
      int r = upper_bound(B.begin(), B.end(), sum - B[0]) - B.begin() - 1;

      while (l < r) {
        if (B[l] + B[r] == sum) {
          res = sum;
          return;
        }
        if (B[l] + B[r] > sum)
          r--;
        else
          l++;
      }
    }
  };
  check();
  if (res == LLONG_MAX) {
    cout << "no volleyball today";
  } else {
    cout << res;
  }

  return 0;
}
