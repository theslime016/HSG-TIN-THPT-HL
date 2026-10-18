#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;

#define _debug 0

#if _debug == 1
#define debugl(x) cerr << #x << ':' << (x) << ' ';
#define debugr(x) cerr << #x << ':' << (x) << '\n';

#else
#define debugl(x)
#define debugr(x)

#endif // _debug

const long long maxd = 8e8;
const int maxlen = 20;
const int maxstart = 1e6 + 5;
long long res = 0;
long long n;

/// voi moi start va len, tim ra max d con hop le bang binary search
/// -> khoang hop le se la [1 -> d], tuc la cong d vao res

bool check(const long long& start, int len, const long long& d) {
  long long res = n/start;
  long long current = start;
  for (int i = 2; i <= len; i++) {
    current += d;
    res /= current;
    if (res < 0) return false;
  }
  return res > 0;
}

long long make_binary_search(const long long& start, int len) {
  long long l = 0LL, r = maxd;
  for (long long k = r - l; k > 0; k /= 2) {
    while (l + k < r && check(start, len, l + k)) l += k;
  }
  return l;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);

  #if _debug == 1
  freopen("input.inp", "r", stdin);
  #else

  #endif // _debug

  cin >> n;

  for (long long start = 1; start <= maxstart; start++) {
    int ok = 0;
    for (int len = 3; len <= maxlen; len++) {
      long long val = make_binary_search(start, len);
      if (val != 0) res += val, ok = 1;
      else break;
    }
    if (!ok) break;
  }

  cout << res;

}
