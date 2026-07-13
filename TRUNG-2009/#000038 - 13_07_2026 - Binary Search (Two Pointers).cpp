#include <bits/stdc++.h>
using namespace std;

#ifndef NDEBUG
#define NDEBUG
#endif

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int n, m;
  cin >> n >> m;
  vector<long long> A(n), B(m);
  for (int i = 0; i < n; i++)
    cin >> A[i];
  for (int i = 0; i < m; i++)
    cin >> B[i];

  A.erase(unique(A.begin(), A.end()), A.end());
  B.erase(unique(B.begin(), B.end()), B.end());
  n = A.size();
  m = B.size();
  for (long long x : A)
    cout << x << ' ';
  cout << '\n';
  for (long long y : B)
    cout << y << ' ';
  cout << '\n';

  int l = 0, r = m - 1;
  long long res = 0;
  for (long long x : A) {
    long long g = abs(x - B[l]);
    while (l <= r && abs(x - B[l + 1]) <= abs(x - B[l])) {
      assert(l <= r);
      g = abs(x - B[l + 1]);
      l++;
    }
    cout << x << '-' << g << '\n';
    res = max(res, g);
  }
  cout << res;

  return 0;
}
