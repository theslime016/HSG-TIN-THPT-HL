#include <bits/stdc++.h>
using namespace std;

const int maxn = 30;
long long A[maxn], B[maxn];

#define _debug 0
int main() {
  cin.tie(0)->sync_with_stdio(0);

  #if _debug == 1
  freopen("input.inp", "r", stdin);
  #else

  #endif // _debug

  int n;
  long long lim;
  cin >> n >> lim;

  for (int i = 1; i <= n; i++) cin >> A[i] >> B[i];

  long long best_sum = 0;
  for (int mask = 1; mask < (1LL << n); mask++) {
    long long sum = 0;
    long long w = 0;
    for (int i = 1; i <= n; i++) {
      if ((1 << (i-1)) & mask) {
        sum += A[i];
        w += B[i];
      }
    }
    if (w <= lim) best_sum = max(best_sum, sum);
  }
  cout << best_sum;

}
