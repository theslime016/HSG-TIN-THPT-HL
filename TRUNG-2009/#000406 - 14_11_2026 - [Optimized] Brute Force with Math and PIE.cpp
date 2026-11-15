#include <bits/stdc++.h>
using namespace std;

#define _debug 0

#if _debug == 1
void log_out() {
  cerr << endl;
}
template<typename H, typename... T>
void log_out(H h, T... t) {
  cerr << h << ", ";
  log_out(t...);
}
#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:" << endl, log_out(__VA_ARGS__)
#define newline cerr << endl

#else
#define debug(...) (void(0))
#define newline (void(0))

#endif // _debug

#define popcount(x) __builtin_popcountll((x))

const int maxn = 5e5 + 5;
const int maxnum = (1LL << 12);
int n;

long long cnt[maxnum];

string num;
int get_mask() {
  int mask = 0;
  for (char c : num) {
    mask |= (1 << (c - '0'));
  }
  return mask;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);

#if _debug == 1
  freopen("input.inp", "r", stdin);

#else
  freopen("RELATIVE.INP", "r", stdin);
  freopen("RELATIVE.OUT", "w", stdout);

#endif // _debug

  cin >> n;

  for (int i = 1; i <= n; i++) {
    cin >> num;
    int mask = get_mask();
    cnt[mask]++;
  }

  long long res = 0;
  for (int mask = 1; mask < maxnum; mask++) {
    long long local = 0;
    for (int submask = 1; submask < maxnum; submask++) {
      if ((mask & submask) == mask) {
        local += cnt[submask];
      }
    }

    if (popcount(mask)%2 == 1) {
      res += local * (local - 1) / 2;
    } else {
      res -= local * (local - 1) / 2;
    }
  }

  cout << res;

}
