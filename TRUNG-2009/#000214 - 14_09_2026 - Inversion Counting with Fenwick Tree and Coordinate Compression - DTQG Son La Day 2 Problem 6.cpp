#include <bits/stdc++.h>
using namespace std;

const int maxn = 5e4 + 5;
long long fenwick[maxn];
long long A[maxn];
long long C[maxn];

int main() {
  cin.tie(0)->sync_with_stdio(0);

  freopen("CHECKINV.inp", "r", stdin);
  freopen("CHECKINV.out", "w", stdout);

  int n, q;
  cin >> n >> q;
  vector<long long> B;
  B.reserve(n);
  for (int i = 1; i <= n; i++) {
    cin >> A[i];
    B.push_back(A[i]);
  }

  sort(B.begin(), B.end());
  B.erase(unique(B.begin(), B.end()), B.end());
  for (int i = 1; i <= n; i++) {
    int fnd = lower_bound(B.begin(), B.end(), A[i]) - B.begin() + 1;
    C[i] = fnd;
  }

  while (q--) {
    memset(fenwick, 0, sizeof fenwick);
    int l, r;
    cin >> l >> r;
    long long res = 0;
    for (int index = r; index >= l; index--) {
      int fnd = C[index];

      long long cnt = 0;
      for (int j = fnd - 1; j > 0; j -= j & -j) {
        cnt += fenwick[j];
      }

      res += cnt;
      for (int j = fnd; j < maxn; j += j & -j) {
        fenwick[j] += 1;
      }
    }
    cout << res << '\n';
  }
}
