#include <bits/stdc++.h>
using namespace std;
#define _debug 1

int main() {
  cin.tie(0)->sync_with_stdio(0);

#if _debug == 1
  freopen("input.inp", "r", stdin);
#elif _debug == 2
  freopen("input.inp", "r", stdin);
  freopen("output.out", "w", stdout);
#else

#endif // _debug

  int t;
  cin >> t;
  while (t--) {
    int n, k;
    cin >> n >> k;

    int start = k;
    vector<int> A;
    A.reserve(n);
    for (int i = 1; i <= n; i++) {
      int x;
      cin >> x;
      A.push_back(x);
    }

    sort(A.rbegin(), A.rend());
    stack<int> odd, even;
    for (int x : A) {
      if (x%2) odd.push(x);
      else even.push(x);
    }

    while (!odd.empty() || !even.empty()) {
      bool eat = true;
      while (eat) {
        eat = false;
        while (!odd.empty() && odd.top() <= k) {
          k++;
          odd.pop();
          eat = true;
        }

        while (!even.empty() && even.top() <= k) {
          k++;
          even.pop();
          eat = true;
        }
      }

      if (!even.empty()) {
        k++;
        int val = even.top();
        even.pop();
        even.push(val/2);
        even.push(val/2);
      } else if (!odd.empty()) {
        k++;
        int val = odd.top();
        odd.pop();
        odd.push((val + 1)/2);
        odd.push((val + 1)/2);
      }
    }

    cout << k - start << '\n';

  }
}
