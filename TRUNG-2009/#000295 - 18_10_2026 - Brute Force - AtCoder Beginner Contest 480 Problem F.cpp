#include <bits/stdc++.h>
using namespace std;

#define _debug 2
int main() {
  cin.tie(0)->sync_with_stdio(0);

  #if _debug == 1
  freopen("input.inp", "r", stdin);

  #elif _debug == 2
  freopen("input.inp", "r", stdin);
  freopen("output.ans", "w", stdout);

  #else

  #endif // _debug

  int n;
  int m;
  cin >> n >> m;

  vector<long long> B;
  B.reserve(n);
  long long s = 0;
  for (int i = 1; i <= n; i++) {
    int x;
    cin >> x;
    B.push_back(x);
    s += x;
  }

  sort(B.begin(), B.end());
  long long res = 1e9;
  do {
    long long current = 0;
    long long op = m - 1;
    for (int i = 0; i < n - 1; i++) {
      current += B[i];
      if (current * m % s == 0) op--;
    }
    res = min(res, op);
  } while (next_permutation(B.begin(), B.end()));

  cout << res;

}
