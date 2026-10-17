#include <bits/stdc++.h>
using namespace std;

const int maxn = 2e5 + 5;
const int inf = 1e9;
int A[maxn];
int n;

bool verify() {
  stack<int> s; // index;
  vector<int> diff(n+2, 0);
  for (int i = 1; i <= n; i++) {
    while (!s.empty() && A[s.top()] < A[i]) s.pop();
    if (!s.empty() && A[s.top()] == A[i]) diff[s.top()]++, diff[i+1]--;
    else s.push(i);
  }

  int current = 0;
  for (int i = 1; i <= n; i++) {
    current += diff[i];
    if (current == 0) return false;
  }
  return true;
}

bool check(int index, int new_val) {
  int old_val = A[index];
  A[index] = new_val;
  bool res = verify();
  if (res) {
    cout << 1 << '\n';
    cout << index << ' ' << new_val << '\n';
  }
  A[index] = old_val;
  return res;
}

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
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> A[i];

    if (verify()) {
      cout << 0 << '\n';
      continue;
    }

    int index = 0;
    for (int i = 1; i <= n; i++) {
      if (A[i] > A[index]) index = i;
    }

    if (check(1, A[index])) continue;
    if (check(n, A[index])) continue;
    if (check(index, 1)) continue;

    cout << 2 << '\n';
    cout << 1 << ' ' << inf << '\n';
    cout << n << ' ' << inf << '\n';
  }

}
