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

#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:\n", log_out(__VA_ARGS__)
#define newline cerr << endl

#else
#define debug(...) void(0)
#define newline void(0)

#endif // _debug

long long n, k;
__int128_t solve(vector<pair<long long, long long>>&& task) {
  sort(task.begin(), task.end(), greater<pair<long long, long long>>());

  #if _debug == 1
  newline;
  cerr << "task: " << '\n';
  for (const auto& x : task) {
    debug(x.first, x.second);
  }
  newline;
  #endif // _debug

  __int128_t res = 0;
  int i = 0;
  while (i < (int)task.size()) {
    long long int_part = task[i].second/k + (task[i].second%k != 0 ? 1LL : 0LL);
    long long rem = task[i].second%k != 0 ? (k - task[i].second%k) : 0;

    debug(task[i].first, task[i].second, int_part, rem);

    res += (__int128_t)2 * (__int128_t)int_part * (__int128_t)task[i].first;
    i++;

    while (i < (int)task.size() && rem > 0) {
      if (rem >= task[i].second) {
        rem -= task[i].second;
        task[i].second = 0;
      } else {
        task[i].second -= rem;
        rem = 0;
      }

      if (task[i].second == 0) i++;
    }

  }

  return res;
}

int buffer[50];
void print(__int128_t x) {
  if (x == 0) {
    cout << 0;
    return;
  }

  int ptr = 0;
  while (x > 0) {
    buffer[++ptr] = x%10;
    x /= 10;
  }

  while (ptr > 0) {
    cout << buffer[ptr--];
  }
}

int main() {
  cin.tie(0)->sync_with_stdio(0);

#if _debug == 1
  freopen("input.inp", "r", stdin);

#elif _debug == 2
  freopen("input.inp", "r", stdin);

#else
  freopen("shipping.inp", "r", stdin);
  freopen("shipping.out", "w", stdout);

#endif // _debug

  cin >> n >> k;
  vector<pair<long long, long long>> pos, neg;
  pos.reserve(n);
  neg.reserve(n);
  for (int i = 1; i <= n; i++) {
    long long x, y;
    cin >> x >> y;
    if (x >= 0) pos.push_back({x, y});
    else neg.push_back({-x, y});
  }

  debug(n, k);

  __int128_t res = 0;
  res += solve(move(pos));
  res += solve(move(neg));
  print(res);
}
