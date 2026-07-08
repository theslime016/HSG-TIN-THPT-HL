#include <bits/stdc++.h>
using namespace std;

long long cont = 0;
bitset<1'000000'20> duplicate1;
bitset<1'000000'20> duplicate2;
bitset<1'000000'20> duplicate3;
bitset<1'000000'20> duplicate4;
vector<long long> hhash;
vector<long long> bbase;
vector<long long> hhash2;
vector<long long> bbase2;
vector<long long> hhash3;
vector<long long> bbase3;
vector<long long> hhash4;
vector<long long> bbase4;
string s;
int k;
int table[26];
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
const long long mod = 1e8 + 7;
const long long mod2 = 1e8 + 9;
const long long mod3 = 1e8 + 1;
const long long mod4 = 1e8 + 3;
const long long base = 31;

void f(int left, int right) {
  while (left <= right) {
    long long h =
        (hhash[right] - hhash[left - 1] * bbase[right - left + 1] % mod + mod) %
        mod;
    long long h2 = (hhash2[right] -
                    hhash2[left - 1] * bbase2[right - left + 1] % mod2 + mod2) %
                   mod2;
    long long h3 = (hhash3[right] -
                    hhash3[left - 1] * bbase3[right - left + 1] % mod3 + mod3) %
                   mod3;
    long long h4 = (hhash4[right] -
                    hhash4[left - 1] * bbase4[right - left + 1] % mod4 + mod4) %
                   mod4;
    if (duplicate1[h] && duplicate2[h2] && duplicate3[h3] && duplicate4[h4]) {
      break;
    }
    duplicate1[h] = duplicate2[h2] = duplicate3[h3] = duplicate4[h4] = true;
    // cout << s.substr(left - 1, right - left + 1) << '\n';
    cont++;
    left++;
  }
  return;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  // freopen("input.inp", "r", stdin);

  cin >> s;
  for (int i = 0; i < 26; i++) {
    char c;
    cin >> c;
    table[i] = c == '0' ? 1 : 0;
  }
  cin >> k;

  hhash.resize(s.size() + 1);
  bbase.resize(s.size() + 1);
  hhash[0] = 0;
  bbase[0] = 1;
  hhash2.resize(s.size() + 1);
  bbase2.resize(s.size() + 1);
  hhash2[0] = 0;
  bbase2[0] = 1;
  hhash3.resize(s.size() + 1);
  bbase3.resize(s.size() + 1);
  hhash3[0] = 0;
  bbase3[0] = 1;
  hhash4.resize(s.size() + 1);
  bbase4.resize(s.size() + 1);
  hhash4[0] = 0;
  bbase4[0] = 1;
  for (int i = 1; i <= (int)s.size(); i++) {
    hhash[i] = ((hhash[i - 1] * base) % mod + s[i - 1] - 'a' + 1) % mod;
    bbase[i] = (bbase[i - 1] * base) % mod;
    hhash2[i] = ((hhash2[i - 1] * base) % mod2 + s[i - 1] - 'a' + 1) % mod2;
    bbase2[i] = (bbase2[i - 1] * base) % mod2;
    hhash3[i] = ((hhash3[i - 1] * base) % mod3 + s[i - 1] - 'a' + 1) % mod3;
    bbase3[i] = (bbase3[i - 1] * base) % mod3;
    hhash4[i] = ((hhash4[i - 1] * base) % mod4 + s[i - 1] - 'a' + 1) % mod4;
    bbase4[i] = (bbase4[i - 1] * base) % mod4;
  }

  int l = 1, r = 1;
  long long g = 0;
  while (l <= r && r <= (int)s.size()) {
    g += table[s[r - 1] - 'a'];
    while (l <= r && g > k) {
      g -= table[s[l - 1] - 'a'];
      l++;
    }
    while (g > k && r <= (int)s.size()) {
      g = table[s[r - 1] - 'a'];
      r++;
      l++;
    }
    if (g <= k)
      f(l, r);
    r++;
  }

  cout << cont;

  return 0;
}
