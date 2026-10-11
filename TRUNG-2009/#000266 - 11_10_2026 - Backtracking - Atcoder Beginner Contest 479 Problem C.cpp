#include <bits/stdc++.h>
using namespace std;
#define _debug 0

const int maxn = 30;
long long A[maxn];
long long B[maxn];
int n;
long long lim;
long long best_s;

void make_dfs(int index, long long w, long long s) {
  if (w > lim) return;
  if (index == n + 1) {
    best_s = max(best_s, s);
    return;
  }

  make_dfs(index+1, w, s);
  make_dfs(index+1, w + B[index], s + A[index]);
}

int main() {
  cin.tie(0)->sync_with_stdio(0);

  #if _debug == 1
  freopen("input.inp", "r", stdin);
  #else

  #endif // _debug

  cin >> n >> lim;
  for (int i = 1; i <= n; i++) cin >> A[i] >> B[i];
  make_dfs(2, 0LL, 0LL);
  make_dfs(2, B[1], A[1]);
  cout << best_s;

}
