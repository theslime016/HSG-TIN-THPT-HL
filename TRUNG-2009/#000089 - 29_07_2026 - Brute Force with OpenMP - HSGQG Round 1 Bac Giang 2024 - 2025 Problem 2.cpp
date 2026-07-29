#include <bits/stdc++.h>
using namespace std;

const int maxn = 510;
bool A[maxn][maxn]{};

int main() {
  cin.tie(0)->sync_with_stdio(false);

  freopen("REDSTONE.INP", "r", stdin);
  freopen("REDSTONE.ANS", "w", stdout);

  int n, m, k, q;
  cin >> n >> m >> k >> q;
  long long count = 0;
  for (int i = 0; i < q; i++) {
    int a, b;
    cin >> a >> b;
    int start_r = max(1, a - k);
    int end_r = min(n, a + k);

    int sum = 0;
#pragma omp parallel for reduction(+ : sum) schedule(dynamic)
    for (int i = start_r; i <= end_r; i++) {
      int x = abs(a - i);
      int start_c = max(1, b - k + x);
      int end_c = min(m, b + k - x);
      for (int j = start_c; j <= end_c; j++) {
        if (A[i][j] == 0) {
          A[i][j] = 1;
          sum++;
        }
      }
    }

    // for (int i = 1; i <= n; i++) {
    //   for (int j = 1; j <= m; j++) {
    //     cout << A[i][j] << ' ';
    //   }
    //   cout << '\n';
    // }

    count += sum;
    cout << count << '\n';
  }

  return 0;
}
