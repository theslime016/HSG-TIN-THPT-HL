#include <bits/stdc++.h>
using namespace std;
 
const int maxn = 2e5 + 10;
bool visited[maxn]{};
 
int main() {
  cin.tie(0)->sync_with_stdio(false);
 
  int n;
  cin >> n;
  vector<long long> A(n);
  vector<long long> B(n);
  for (int i = 0; i < n; i++) {
    cin >> A[i];
    B[i] = A[i];
  }
 
  sort(B.begin(), B.end());
  B.erase(unique(B.begin(), B.end()), B.end());
 
  auto fnd = [&](long long val) {
    return lower_bound(B.begin(), B.end(), val) - B.begin();
  };
 
  int l = 0, r = 0;
  int res = -1;
  while (r < n) {
    int index = fnd(A[r]);
    while (visited[index]) {
      visited[fnd(A[l])] = false;
      l++;
    }
    visited[index] = true;
    res = max(res, r - l + 1);
    r++;
  }
  cout << res;
 
  return 0;
}
