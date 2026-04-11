#include <bits/stdc++.h>
using namespace std;
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int n;
  long long t;
  cin >> n >> t;
  string mode, s;
  cin >> mode >> s;
  int j = t % n;

  if (mode == "LEFT") {
    rotate(s.begin(), s.begin() + j, s.end());
  } else if (mode == "RIGHT") {
    rotate(s.begin(), s.end() - j, s.end());
  }

  cout << s;
  return 0;
}
