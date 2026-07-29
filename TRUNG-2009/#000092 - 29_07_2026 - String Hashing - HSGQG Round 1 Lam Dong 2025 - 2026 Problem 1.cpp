#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
typedef pair<long long, long long> pairll;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
long long rnd(long long l, long long r) {
  return uniform_int_distribution<>(l, r)(rng);
}

const int base = rnd(300, 1000);
const long long mod = 1e9 + 7;
const long long mod2 = 1e9 + 9;
const long long maxn = 1e6 + 5;
long long power[maxn]{};
long long power2[maxn]{};
long long hashB[maxn]{};
long long hashS[maxn]{};

int main() {
  cin.tie(0)->sync_with_stdio(false);

  power[0] = power2[0] = 1;
  for (int i = 1; i < maxn; i++) {
    power[i] = (power[i - 1] * base) % mod;
    power2[i] = (power2[i - 1] * base) % mod2;
  }

  long long t;
  cin >> t;
  string A, B;
  while (t--) {
    cin >> A >> B;
    int n = A.size();
    int m = B.size();
    A = '-' + A;
    B = '#' + B;

    for (int i = 1; i <= m; i++) {
      hashB[i] = (hashB[i - 1] * base + (B[i] - 'a' + 1)) % mod;
      hashS[i] = (hashS[i - 1] * base + (B[i] - 'a' + 1)) % mod2;
    }

    auto gethash = [&](int l, int r) -> pairll {
      int len = r - l + 1;
      long long hash1 =
          (hashB[r] - hashB[l - 1] * power[len] % mod + mod) % mod;
      long long hash2 =
          (hashS[r] - hashS[l - 1] * power2[len] % mod2 + mod2) % mod2;
      return {hash1, hash2};
    };

    int x = 0, y = 0;
    for (char c : A) {
      if (c == '0')
        x++;
      else if (c == '1')
        y++;
    }

    char s1 = '0', s2 = '1';
    if (x < y) {
      swap(s1, s2);
      swap(x, y);
    }
    // x >= y
    // x-> s1, y->s2

    // int k = 0;
    // for (int i = 1; i <= n; i++) {
    //   if (A[i] == s2)
    //     k++;
    // }

    int l_min = 1;
    int l_max = (m - y) / x;
    long long res = 0;
    for (int l = l_min; l <= l_max; l++) {
      long long rem = (m - l * x);
      if (rem % y != 0 || rem <= 0)
        continue;
      int d = rem / y;
      int start = 1;
      bool found = true;
      pairll hashp = {-1, -1}, hashq = {-1, -1};

      for (int i = 1; i <= n; i++) {
        char c = A[i];
        if (c == s1) {
          pairll current_hash = gethash(start, start + l - 1);
          if (hashp.first == -1) {
            hashp = current_hash;
          } else if (hashp != current_hash) {
            found = false;
            break;
          }
          start += l;
        }
        if (c == s2) {
          pairll current_hash = gethash(start, start + d - 1);
          if (hashq.first == -1) {
            hashq = current_hash;
          } else if (hashq != current_hash) {
            found = false;
            break;
          }
          start += d;
        }
      }
      if (found) {
        if (l == d && hashp == hashq)
          continue;
        res++;
      }
    }
    cout << res << '\n';
  }

  return 0;
}
