#include <bits/stdc++.h>
using namespace std;

struct FWT {
  int n;
  vector<long long> data;
  FWT(int num) {
    this->n = num;
    this->data.assign(num + 1, 0);
  }

  FWT(vector<long long> const A) : n(A.size()), data(A) {
    for (int i = 0; i < n; i++) {
      int p = i + (i & (-i));
      if (p <= n) {
        data[p] += data[i];
      }
    }
  }

  void process(int index, long long val) {
    for (; index <= n; index += index & (-index)) {
      data[index] += val;
    }
  }

  long long fetch(int index) {
    long long pref = 0;
    for (; index > 0; index -= index & (-index)) {
      pref += data[index];
    }
    return pref;
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int n, k;
  cin >> n >> k;
  vector<int> A(n + 1, 0);
  for (int i = 1; i <= n; i++) {
    cin >> A[i];
    A[i]++;
  }
  vector<FWT> dp(k + 2, FWT(n + 1));
  dp[0].process(1, 1);

  for (int i = 1; i <= n; i++) {
    for (int j = k + 1; j > 0; j--) {
      dp[j].process(A[i], dp[j - 1].fetch(A[i] - 1));
    }
  }

  for (int j = 0; j <= k + 1; j++) {
    for (int i = 0; i <= n + 1; i++) {
      cout << dp[j].data[i] << ' ';
    }
    cout << '\n';
  }

  cout << dp[k + 1].fetch(n + 1);

  return 0;
}
