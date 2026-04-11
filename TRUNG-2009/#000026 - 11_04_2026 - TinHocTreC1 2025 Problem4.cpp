#include <bits/stdc++.h>
using namespace std;
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int m, n;
  cin >> m >> n;
  vector<int> a(m, 0);
  for (int j = 0; j < n; j++) {
    for (int i = 0; i < m; i++) {
      char c;
      cin >> c;
      a[i] += (c == 'X');
    }
  }

  int mx = INT_MIN;
  int count = 0;
  for (int i = 0; i < m; i++) {
    if (a[i] > mx) {
      mx = a[i];
      count = 1;
    } else if (a[i] == mx) {
      count++;
    }
  }

  cout << count << ' ' << mx << '\n';
  for (int i = 0; i < m; i++) {
    if (mx == a[i])
      cout << i + 1 << ' ';
  }
  return 0;
}
