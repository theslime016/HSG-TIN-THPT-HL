#include <bits/stdc++.h>
using namespace std;

struct trp {
  int l, r;
  long long d;
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int n, m, k;
  cin >> n >> m >> k;
  vector<long long> A(n + 2, 0);
  for (int i = 1; i <= n; i++)
    cin >> A[i];
  vector<long long> D(n + 2, 0);
  vector<long long> S(m + 2, 0);
  vector<trp> op(m + 2);
  for (int i = 1; i <= m; i++)
    cin >> op[i].l >> op[i].r >> op[i].d;
  while (k--) {
    int x, y;
    cin >> x >> y;
    S[x]++;
    S[y + 1]--;
  }

  long long comp = 0;
  for (int i = 1; i <= m; i++) {
    comp += S[i];
    D[op[i].l] += comp * op[i].d;
    D[op[i].r + 1] -= comp * op[i].d;
  }

  long long current = 0;
  for (int i = 1; i <= n; i++) {
    current += D[i];
    A[i] += current;
    cout << A[i] << ' ';
  }

  return 0;
}
