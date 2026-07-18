#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int n, q;
  cin >> n >> q;
  vector<long long> B(n + 2, 0);

  while (q--) {
    int x;
    int l, r;
    cin >> x >> l >> r;
    if (x == 0) {
      int k;
      cin >> k;
      B[l] += k;
      B[r + 1] -= k;
    } else {
      long long last = 0;
      long long pref = 0;
      long long h = 0;
      for (int i = 1; i <= r; i++) {
        pref += B[i];
        h += i * B[i];
        if (i == l - 1) {
          last = pref * l - h;
        }
      }
      cout << pref * (r + 1) - h - last << '\n';
    }
  }

  return 0;
}
