#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5 + 10;
int A[maxn], B[maxn];
int n, k;
int res = 0;
void backtrack(int index, int rem) {
  if (index == n && rem >= 0) {
    for (int a = 0; a < n - 1; a++) {
      int b = a + 1;
      int l1 = B[a];
      int l2 = B[b];
      if (B[a] == B[b])
        continue;
      int len = 2;
      for (int j = 1; j < n; j++) {
        if (a - j < 0 || b + j >= n)
          break;
        if (B[a - j] != l1 || B[b + j] != l2)
          break;
        len += 2;
      }
      res = max(res, len);
    }
    return;
  }
  if (index >= n || rem < 0)
    return;
  if (rem > 0) {
    for (int i = 0; i < 3; i++) {
      if (A[index] == i)
        continue;
      B[index] = i;
      backtrack(index + 1, rem - 1);
    }
  }
  B[index] = A[index];
  backtrack(index + 1, rem);
}

int main() {
  cin.tie(0)->sync_with_stdio(false);

  freopen("input.inp", "r", stdin);
  freopen("output.ans", "w", stdout);

  cin >> n >> k;
  for (int i = 0; i < n; i++)
    cin >> A[i];

  memcpy(B, A, sizeof(A));
  backtrack(0, k);
  cout << res;

  return 0;
}
