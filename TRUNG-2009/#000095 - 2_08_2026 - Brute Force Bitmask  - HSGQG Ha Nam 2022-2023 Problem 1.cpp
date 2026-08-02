#include <bits/stdc++.h>
using namespace std;

#define popcount __builtin_popcountll

int main() {
  cin.tie(0)->sync_with_stdio(false);

  freopen("CANDIES.INP", "r", stdin);
  freopen("CANDIES.ANS", "w", stdout);

  int n, k;
  cin >> n >> k;
  string S;
  cin >> S;
  long long res = -1;
  for (long long bitmask = 0; bitmask < (1 << (n - 1)); bitmask++) {
    if (popcount(bitmask) != k - 1)
      continue;
    long long sum = 0;
    long long current = S[0] - '0';
    bool pass = true;
    char last = S[0];
    for (int j = 0; j < n - 1; j++) {
      if ((bitmask >> j) & 1) {
        sum += current;
        current = (S[j + 1] - '0');
        last = S[j + 1];
      } else {
        if (last == '0') {
          pass = false;
          break;
        }
        current = current * 10 + (S[j + 1] - '0');
      }
    }
    if (!pass)
      continue;
    sum += current;
    res = max(res, sum);
  }

  cout << res;

  return 0;
}
