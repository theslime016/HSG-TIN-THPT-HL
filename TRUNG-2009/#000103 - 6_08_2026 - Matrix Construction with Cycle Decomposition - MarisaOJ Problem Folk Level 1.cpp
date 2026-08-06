#include <bits/stdc++.h>
using namespace std;

#define debugr(x) cout << #x << " = " << (x) << '\n'
#define debugl cout << '\n'

const int maxn = 5e5 + 5;
const int maxk = 15;
int A[maxk][maxn]{0};

int main() {
  cin.tie(0)->sync_with_stdio(false);

  freopen("input.inp", "r", stdin);
  freopen("output.out", "w", stdout);

  int n, k, d;
  cin >> n >> k >> d;
  if (abs(d) > k || (n % 2 == 0 && k % 2 != abs(d) % 2) || (k < 2 && d == 0)) {
    cout << -1;
    return 0;
  }

  int s1_x2 = k * (n + 1) - d * (n - 1);
  if (abs(s1_x2) % 2 != 0) {
    cout << -1;
    return 0;
  }

  for (int i = 1; i <= k; i++) {
    for (int j = 1; j <= n; j++) {
      cin >> A[i][j];
    }
  }

  vector<vector<int>> B(k + 1, vector<int>(n + 1));
  int current_row = 1;
  int rem_k = k, rem_d = d;
  if (k % 2 != abs(d) % 2) {
    int m = (n + 1) / 2;
    int x = 1, y = m;
    int s = 1;
    for (int i = 1; i <= n; i++) {
      B[current_row][i] = x;
      B[current_row + 1][i] = y;
      if (y == n)
        s = -1;
      y += s;
      swap(x, y);
    }

    if (d > 0) {
      rem_d--;
    } else {
      reverse(B[current_row].begin() + 1, B[current_row].end());
      reverse(B[current_row + 1].begin() + 1, B[current_row + 1].end());
      rem_d++;
    }
    rem_k -= 2;
    current_row += 2;
  }

  int x = (rem_k + rem_d) / 2, y = x - rem_d;
  for (int i = 0; i < x; i++, current_row++) {
    iota(B[current_row].begin() + 1, B[current_row].end(), 1);
  }
  for (int i = 0; i < y; i++, current_row++) {
    iota(B[current_row].rbegin(), B[current_row].rend(), 1);
  }

  struct oper {
    int r, i, j;
  };
  vector<oper> res;

  vector<int> orin(n + 1, 0);
  int op = 0;
  for (int i = 1; i <= k; i++) {
    for (int j = 1; j <= n; j++) {
      orin[A[i][j]] = j;
    }
    for (int j = 1; j <= n; j++) {
      while (orin[B[i][j]] != j) {
        res.push_back({i, orin[B[i][j]], j});
        op++;
        swap(B[i][j], B[i][orin[B[i][j]]]);
      }
    }
  }

  cout << op << '\n';
  for (int i = res.size() - 1; i >= 0; i--) {
    cout << res[i].r << ' ' << res[i].i << ' ' << res[i].j << '\n';
  }

  return 0;
}
