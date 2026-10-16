#include <bits/stdc++.h>
using namespace std;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
long long rnd(long long l, long long r) {
  return uniform_int_distribution<long long>(l, r)(rng);
}

int timer = 0;
vector<int> A;
void make_dfs(int i, int n, int k, int cnt) {
  if (cnt == n) {
    cout << n << ' ' << k << '\n';
    for (int x : A) cout << x << ' ';
    cout << '\n';
    timer++;
    return;
  }
  for (; i <= n; i++) {
    A.push_back(i);
    make_dfs(0, n, k, cnt+1);
    A.pop_back();
  }
}

int main() {
  cin.tie(0)->sync_with_stdio(0);

  freopen("input.inp", "w", stdout);

  int x = 10;
  int t = 823543;
  int n = 6;

  cout << t << '\n';
  for (int k = 0; k <= n; k++) {
    make_dfs(0, n, k, 0);
  }

  cerr << timer;

  return 0;

  for (int i = 0; i <= n; i++) {
    for (int index2 = 0; index2 <= n; index2++) {
      for (int index3 = 0; index3 <= n; index3++) {
        for (int index4 = 0; index4 <= n; index4++) {
          for (int index5 = 0; index5 <= n; index5++) {
            for (int index6 = 0; index6 <= n; index6++) {
              for (int k = 0; k <= n; k++) {
                cout << n << ' ' << k << '\n';
                cout << i << ' ' << index2 << ' ' << index3 << ' ' << index4 << ' ' << index5
                     << ' ' << index6 << '\n';
                t++;
              }
            }
          }
        }
      }
    }
  }

  cerr << t;

  return 0;


  for (int k = 0; k <= n; k++) {
    vector<int> A;
    A.assign(n+1, 0);
    iota(A.begin(), A.end(), 0);
    do {
      cout << n << ' ' << k << '\n';
      for (const int& x : A) cout << x << ' ';
      cout << '\n';
    } while (next_permutation(A.begin(), A.end()));
  }
}
