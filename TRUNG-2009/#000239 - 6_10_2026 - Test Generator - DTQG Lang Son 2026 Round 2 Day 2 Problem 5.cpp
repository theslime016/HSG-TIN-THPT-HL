#include <bits/stdc++.h>
using namespace std;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
long long rnd(long long l, long long r) {
  return uniform_int_distribution<long long>(l, r)(rng);
}

int main(int argc, char* argv[]) {
  cin.tie(0)->sync_with_stdio(0);

  freopen("input.inp", "w", stdout);

  int x = 10;
  int n = rnd(1, x);
  int q = rnd(1, x);
  cout << n << ' ' << q << '\n';
  long long y = 100;
  for (int i = 1; i <= n; i++) cout << rnd(1, y) << ' ';
  cout << '\n';

  vector<int> perm(n+1);
  iota(perm.begin(), perm.end(), 0);
  shuffle(perm.begin() + 1, perm.end(), rng);
  int bias = argc > 1 ? atoi(argv[1]) : rnd(1, n);
  for (int i = 2; i <= n; i++) {
    cout << perm[i] << ' ' << perm[rnd(max(1, i - bias), i - 1)] << '\n';
  }

  for (int i = 1; i <= q; i++) {
    int type = rnd(1, 2);
    cout << type << ' ';
    if (type == 1) {
      cout << rnd(1, n) << ' ' << rnd(1, y) << '\n';
    } else if (type == 2) {
      cout << rnd(1, n) << '\n';
    }
  }
}
