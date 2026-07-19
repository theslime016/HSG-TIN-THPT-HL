#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
#ifndef NDEBUG
#define NDEBUG
#endif

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int n;
  cin >> n;
  int A[n * n];
  memset(A, 0, sizeof(A));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      cin >> A[i * n + j];
    }
  }

  for (int x : A)
    cout << x << ' ';
  cout << endl << endl;

  vector<vector<int>> B(n, vector<int>(n));
  for (int i = 0; i < n * n; i++) {
    int r = i / n;
    int c = i % n;
    B[r][c] = A[i];
  }

  for (auto &x : B) {
    for (auto &y : x) {
      cout << y << ' ';
    }
    cout << '\n';
  }
  cout << endl;

  int mask = 5;
  for (int i = mask; i > 0; i = (i - 1) & mask) {
    cout << i << ' ';
  }

  return 0;
}
