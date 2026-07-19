#include <bits/stdc++.h>
using namespace std;

int k;
string N;
long long key[20][2][200];
long long dp(int index, int lim, int pref) {
  if (pref > k)
    return 0;
  if (index == (int)N.size()) {
    return pref == k;
  }
  if (key[index][lim][pref] != -1) {
    return key[index][lim][pref];
  }

  int de_lim = lim == 0 ? 9 : (N[index] - '0');
  long long current = 0;
  for (int c = 0; c <= de_lim; c++) {
    int ne_lim = lim && (c == de_lim);
    current += dp(index + 1, ne_lim, pref + c);
  }
  return key[index][lim][pref] = current;
}

long long solve(long long a) {
  assert(a >= 0);
  N = to_string(a);
  memset(key, -1, sizeof(key));
  return dp(0, 1, 0);
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  freopen("input.inp", "r", stdin);
  freopen("output.out", "w", stdout);

  long long l, r;
  cin >> l >> r >> k;
  cout << solve(r) - solve(l - 1);

  return 0;
}
