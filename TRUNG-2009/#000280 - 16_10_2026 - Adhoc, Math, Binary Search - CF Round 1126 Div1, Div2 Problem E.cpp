#include <bits/stdc++.h>
using namespace std;

const int maxn = 2e5 + 5;
int A[maxn];

#define _debug 0
int main() {
  cin.tie(0)->sync_with_stdio(0);

  #if _debug == 1
  freopen("input.inp", "r", stdin);
  #else

  #endif // _debug

  int t;
  cin >> t;
  while (t--) {
    int n, k;
    cin >> n >> k;

    int max_val = 0;
    for (int i = 1; i <= n; i++) {
      cin >> A[i];
      max_val = max(max_val, A[i]);
    }

    vector<int> freq(max_val + 1, 0);
    for (int i = 1; i <= n; i++) freq[A[i]]++;

    auto check = [&](int cut) {
      int ptr = max_val;
      int rem = n;
      vector<int> cnt = freq;

      long long new_k = k + 2LL * cut + n - 1;
      while (rem > 0) {
        while (cnt[ptr] == 0) ptr--;

        if (ptr <= new_k) {
          cnt[ptr]--;
          new_k--;
          rem--;
        } else if (cut > 0) {
          cnt[ptr]--;
          cnt[(ptr+1)/2] += 2;
          cut--;
          rem++;
        } else {
          return false;
        }
      }
      return true;
    };

    int l = 0, r = max(0, max_val - k);
    for (int d = r - l; d > 0; d /= 2) {
      while (r - d >= l && check(r - d)) r -= d;
    }
    cout << (2LL * r + n) << '\n';
  }

}
