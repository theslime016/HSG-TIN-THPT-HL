#include <bits/stdc++.h>
using namespace std;

#define _debug 0

#if _debug == 1
void logout() {
  cerr << endl;
}
template<typename H, typename... T>
void logout(H h, T... t) {
  cerr << h << ", ";
  logout(t...);
}
#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:" << endl, logout(__VA_ARGS__)
#define debugtitle cerr << __PRETTY_FUNCTION__ << " line: " << __LINE__ << endl
#define newline cerr << endl

#else
#define debug(...) (void(0))
#define debugtitle (void(0))
#define newline (void(0))

#endif // _debug

const int maxn = 105;
const int maxval = 1e4 + 5;

int n, m;

pair<int, long long> container[maxn];
long long dp[maxval];

int main() {
  cin.tie(0)->sync_with_stdio(0);

#if _debug == 1
  freopen("input.inp", "r", stdin);

#elif _debug == 2
  freopen("input.inp", "r", stdin);

#else

#endif // _debug

  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    cin >> container[i].first >> container[i].second;
  }

  sort(container + 1, container + n + 1);

  long long base = 0;
  int base_index = 1;
  for (int j = 0; j <= m; j++) {
    for (int k = 0; k <= m; k++)
      dp[k] = -1;
    dp[m] = 0;

    long long res = base;
    long long best = 0;
    for (int i = base_index; i <= n; i++) {
      for (int k = container[i].first; k <= m; k++) {
        if (dp[k] != -1) {
          int rem = k - container[i].first;
          dp[rem] = max(dp[rem], dp[k] + container[i].second);
          best = max(best, dp[rem]);
        }
      }

      if (!--container[i].first) {
        base += container[base_index].second;
        base_index++;
      }
    }

    res += best;
    cout << res << ' ';
  }

}
