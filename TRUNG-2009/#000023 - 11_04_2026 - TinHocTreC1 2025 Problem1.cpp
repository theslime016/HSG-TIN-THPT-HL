#include <bits/stdc++.h>
using namespace std;
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  long long s1, v1;
  cin >> s1 >> v1;

  long long s2, v2;
  cin >> s2 >> v2;

  long long l;
  cin >> l;

  if (v1 == v2) {
    cout << -1;
  } else {
    double t = double(s2 - s1) / (v1 - v2);
    if (t < 0 || t * v1 + s1 > l || t * v2 + s2 > l) {
      cout << -1;
    } else {
      cout << (long long)t;
    }
  }
  return 0;
}
