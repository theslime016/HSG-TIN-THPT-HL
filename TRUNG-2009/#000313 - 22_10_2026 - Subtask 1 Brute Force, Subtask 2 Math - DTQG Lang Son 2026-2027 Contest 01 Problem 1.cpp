#include <bits/stdc++.h>
using namespace std;

/*
Cho 1 dãy n phần tử số nguyên A (n <= 10^6, Ai <= 10^9).
Tìm số lượng các cặp chỉ số (i, j) sao cho:
1 <= i < j <= n
và
j - i = Ai * Aj.
*/

#define _debug 0

#if _debug == 1
#define debug(x) cerr << #x << ':' << (x) << ' ';
#define newline cerr << '\n';

#else
#define debug(x)
#define newline

#endif // _debug

const int maxn = 2e5 + 5;
long long A[maxn];
int n;

long long solve_subtask1() {
  long long res = 0;

  for (int i = 1; i <= n; i++) {
      if (A[i] > n) continue;
    for (int j = i; j <= n; j++) {
      if (A[i] * A[j] == j - i) res++;
    }
  }
  return res;
}

long long solve_full() {
  long long res = 0;
  long long sz = sqrt(n);
  for (long long x = 1; x <= sz; x++) {
    for (int j = 1; j <= n; j++) {
      int i = j - x * A[j];
      if (i >= 1 && A[i] == x) {
        res++;
      }
    }
  }

  for (long long y = 1; y <= sz; y++) {
    for (int i = 1; i <= n; i++) {
      if (A[i] == sz) continue;

      int j = i + A[i] * y;
      if (j <= n && A[j] == y) res++;
    }
  }

  return res;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);

  #if _debug == 1
  freopen("input.inp", "r", stdin);

  #elif _debug == 2
  freopen("input.inp", "r", stdin);

  #else
  freopen("BEAUPAIRS.INP", "r", stdin);
  freopen("BEAUPAIRS.OUT", "w", stdout);

  #endif // _debug

  int t;
  cin >> t;
  while (t--) {
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> A[i];

    cout << solve_subtask1() << '\n';

  }

}
