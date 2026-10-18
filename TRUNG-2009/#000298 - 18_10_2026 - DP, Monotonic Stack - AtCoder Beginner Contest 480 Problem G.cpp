#include <bits/stdc++.h>
using namespace std;

#define _debug 1

#if _debug == 1
#define debug(x) cerr << #x << ':' << (x) << ' ';
#define debugn(x) cerr << #x << ':' << (x) << '\n';
#define new_line cerr << '\n';

#else
#define debug(x)
#define debugn(x)
#define new_line

#endif // _debug

const int maxn = 2e5 + 5;
const long long inf = 1e18;
long long A[maxn];
long long dp[maxn];

int main() {
  cin.tie(0)->sync_with_stdio(0);

  #if _debug == 1
  freopen("input.inp", "r", stdin);

  #else

  #endif // _debug

  int n;
  cin >> n;
  for (int i = 1; i <= n; i++) cin >> A[i];

  long long min_val = min(A[1], A[2]);
  long long max_val = max(A[1], A[2]);
  dp[2] = max_val - min_val;
  for (int i = 3; i <= n; i++) {
    vector<long long> mins;
    vector<long long> maxs;
    min_val = min(min_val, A[i]);
    max_val = max(max_val, A[i]);
    dp[i] = max_val - min_val;
    for (int j = i; j > 1; j--) {
      if (j < i - 1) {
        dp[i] = min(dp[i], dp[j] + maxs.front() - mins.front());
      }
      while (!mins.empty() && mins.back() >= A[j]) mins.pop_back();
      while (!maxs.empty() && maxs.back() <= A[j]) maxs.pop_back();
      mins.push_back(A[j]);
      maxs.push_back(A[j]);

    }
  }

  cout << dp[n];

}
