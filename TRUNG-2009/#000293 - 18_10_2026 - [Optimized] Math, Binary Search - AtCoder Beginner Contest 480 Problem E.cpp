#include <bits/stdc++.h>
using namespace std;

#define _debug 0
int main() {
  cin.tie(0)->sync_with_stdio(0);

  #if _debug == 1
  freopen("input.inp", "r", stdin);
  #else

  #endif // _debug

  long long n;
  cin >> n;

  auto get_val = [&](const long long& start, int len) -> long long {
    long long l = 0, r = 1e9;
    for (long long k = r - l; k > 0; k /= 2) {
      while (l + k <= r) {
        long long d = l + k;
        long long current = start;
        long long temp = n/current;
        for (int i = 2; i <= len; i++) {
          current += d;
          temp /= current;
        }
        if (temp > 0) l += k;
        else break;
      }
    }

    return l;
  };

  long long res = 0;
  for (long long start = 1; ; start++) {
    int len = 3;
    long long rem = n / start / (start + 1) / (start + 2);
    if (rem <= 0) break;

    while (rem > 0) {
      res += get_val(start, len);
      len++;
      rem /= (start + len - 1);
    }
  }

  cout << res;

}
