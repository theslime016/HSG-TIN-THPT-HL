#include <bits/stdc++.h>
using namespace std;

#if defined(__has_include) && __has_include("slime_debug_016.h")
#include "slime_debug_016.h"

#else
#define _debug 0

#endif // defined

/// MACRO
#if _debug == 1
void log_out() {
  cerr << '\n';
}
template<typename H, typename... T>
void log_out(H h, T... t) {
  cerr << h << ", ";
  log_out(t...);
}
#define debug(...) cerr << "(" << #__VA_ARGS__ << "):\n", log_out(__VA_ARGS__)
#define newline cerr << endl

#else
#define debug(...) void(0)
#define newline void(0)

#endif // _debug

const int maxn = 1e5 + 5;
long long V[maxn], T[maxn];

int main() {
  cin.tie(0)->sync_with_stdio(0);

#if _debug == 1
  freopen("input.inp", "r", stdin);

#elif _debug == 2
  freopen("input.inp", "r", stdin);

#else

#endif // _debug

  int n;
  cin >> n;
  for (int i = 1; i <= n; i++) cin >> V[i];
  for (int i = 1; i <= n; i++) cin >> T[i];

  priority_queue<long long, vector<long long>, greater<long long>> task;
  long long water_level = 0;
  for (int i = 1; i <= n; i++) {
    long long res = 0;
    while (!task.empty()) {
      long long val = task.top();
      long long real_val = val - water_level;
      long long new_val = real_val - T[i];

      task.pop();

      if (new_val <= 0) {
        res += real_val;
      } else {
        task.push(val);
        break;
      }
    }


    res += T[i] * (long long)(task.size());

    long long val = V[i] - T[i];
    if (val > 0) {
      task.push(V[i] + water_level);
      res += T[i];
    } else {
      res += V[i];
    }

    water_level += T[i];

#if _debug == 1
    newline;
    debug(i, val);
    newline;
#endif

    cout << res << ' ';

  }
}
