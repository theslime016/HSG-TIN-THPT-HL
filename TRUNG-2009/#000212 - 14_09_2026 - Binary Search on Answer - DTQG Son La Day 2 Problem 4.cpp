#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5 + 5;
long long A[maxn];

int n, k;
bool check(long long val) {
  long long sum = 0;
  long long used = 1;
  for (int i = 1; i <= n; i++) {
    if (sum + A[i] > val) {
      if (used < k) {
        used++;
        sum = A[i];
      } else {
        return false;
      }
    } else {
      sum += A[i];
    }
  }
  return true;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);

  freopen("BOOKS.inp", "r", stdin);
  freopen("BOOKS.out", "w", stdout);

  cin >> n >> k;
  long long L = 0;
  long long R = 0;
  for (int i = 1; i <= n; i++) {
    cin >> A[i];
    L = max(L, A[i]);
    R += A[i];
  }

  for (long long diff = R - L; diff > 0; diff /= 2) {
    while (R - diff >= L && check(R - diff)) {
      R -= diff;
    }
  }

  cout << R;
}
