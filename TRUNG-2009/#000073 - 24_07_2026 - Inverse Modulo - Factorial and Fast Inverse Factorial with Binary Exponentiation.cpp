#include <bits/stdc++.h>
using namespace std;

long long binpow(long long val, long long exp, long long mod) {
  long long res = 1;
  while (exp) {
    if (exp & 1) {
      res = (res * val) % mod;
    }
    val = (val * val) % mod;
    exp >>= 1;
  }
  return res;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  long long a, m;
  cin >> a >> m;
  a = binpow(a, m - 2, m);
  cout << a << '\n';

  int f;
  cin >> f;
  vector<long long> fact(f + 1, 0);
  fact[0] = fact[1] = 1;
  for (int i = 2; i <= f; i++) {
    fact[i] = ((fact[i - 1] * i) % m + m) % m;
  }

  for (int x : fact)
    cout << x << ' ';
  cout << '\n';

  vector<long long> invFact(f + 1, 0);
  invFact[f] = binpow(fact[f], m - 2, m);
  for (int j = f - 1; j >= 0; j--) {
    invFact[j] = (invFact[j + 1] * (j + 1)) % m;
  }

  for (int x : invFact)
    cout << x << ' ';
  cout << '\n';

  vector<long long> Arrangement(f + 1, 0);
  for (int k = 0; k <= f; k++) {
    Arrangement[k] = (fact[f] * invFact[f - k]) % m;
    cout << Arrangement[k] << ' ';
  }
  cout << '\n';

  vector<long long> Combination(f + 1, 0);
  for (int k = 0; k <= f; k++) {
    Combination[k] = (Arrangement[k] * invFact[k]) % m;
    cout << Combination[k] << ' ';
  }
  cout << '\n';

  return 0;
}
