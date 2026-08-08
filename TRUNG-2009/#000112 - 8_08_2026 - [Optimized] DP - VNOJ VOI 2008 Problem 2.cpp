#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n;
  cin >> n;

  vector<int> A(n);
  vector<int> dp(n, 1);
  for (int i = 0; i < n; i++) {
    cin >> A[i];
  }

  sort(A.begin(), A.end());
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < i; j++) {
      int val = A[i] + A[j];
      int index_val = upper_bound(A.begin(), A.end(), val) - A.begin() - 1;
      if (index_val < 0 || A[index_val] != val)
        continue;
      dp[index_val] = max({dp[index_val], dp[i] + 1, dp[j] + 1});
    }
  }

  cout << *max_element(dp.begin(), dp.end());
}
