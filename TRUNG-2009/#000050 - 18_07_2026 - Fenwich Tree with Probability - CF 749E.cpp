#include <bits/stdc++.h>
using namespace std;

struct FWT {
  int n;
  vector<long long> data;
  FWT(int n) {
    this->n = n;
    data.assign(n + 1, 0);
  }
  void process(int index, long long value) {
    for (; index <= n; index += index & -index) {
      data[index] += value;
    }
  }
  long long fetch(int index) {
    long long pref = 0;
    for (; index > 0; index -= index & -index) {
      pref += data[index];
    }
    return pref;
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int n;
  cin >> n;
  vector<int> A(n + 1);
  for (int i = 1; i <= n; i++) {
    cin >> A[i];
  }

  double H = 0;
  for (double L = 1; L <= n; L++) {
    H += (n - L + 1) * L * (L - 1) / 4.0;
  }

  FWT BIT(n);
  FWT reBIT(n);
  long long I = 0;
  long long C = 0;
  long long pre = 1LL * n * (n + 1) / 2;
  for (int i = n; i > 0; i--) {
    I += BIT.fetch(A[i] - 1);
    C += i * reBIT.fetch(A[i] - 1);
    BIT.process(A[i], 1);
    reBIT.process(A[i], n - i + 1);
  }

  double res = double(I) - (double)C / pre + (double)H / pre;
  cout << fixed << setprecision(15) << res;

  return 0;
}
