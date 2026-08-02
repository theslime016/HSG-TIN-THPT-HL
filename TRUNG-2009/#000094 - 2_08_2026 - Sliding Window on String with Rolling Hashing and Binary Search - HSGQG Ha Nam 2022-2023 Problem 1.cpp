#include <bits/stdc++.h>
using namespace std;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
long long rnd(long long l, long long r) {
  return uniform_int_distribution<long long>(l, r)(rng);
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  freopen("CANDIES.INP", "r", stdin);
  freopen("CANDIES.OUT", "w", stdout);

  const int base = rnd(300, 1000);
  const long long mod = 1e9 + 7;
  const long long mod2 = 1e9 + 9;

  int n, k;
  cin >> n >> k;

  if (n == k) {
    long long sum = 0;
    for (int i = 0; i < n; i++) {
      char c;
      cin >> c;
      sum += c - '0';
    }
    cout << sum;
    return 0;
  }

  vector<long long> hashS(n + 1, 0);
  vector<long long> pow(n + 1, 1);

  vector<long long> hash2(n + 1, 0);
  vector<long long> pow2(n + 1, 1);
  string S;
  S.resize(n + 1);
  for (int i = 1; i <= n; i++) {
    char c;
    cin >> c;
    S[i] = c;
    int val = c - '0';
    hashS[i] = (hashS[i - 1] * base % mod + val) % mod;
    pow[i] = (pow[i - 1] * base) % mod;
    hash2[i] = (hash2[i - 1] * base % mod2 + val) % mod2;
    pow2[i] = (pow2[i - 1] * base) % mod2;
  }

  int len = n - k + 1;
  int l = 1, r = len;

  long long bestl = 0, bestr = 0;

  auto calc = [&](int left, int right) {
    return (hashS[right] - (hashS[left - 1] * pow[right - left + 1]) % mod +
            mod) %
           mod;
  };

  auto calc2 = [&](int left, int right) {
    return (hash2[right] - (hash2[left - 1] * pow2[right - left + 1] % mod2) +
            mod2) %
           mod2;
  };

  for (; r <= n; l++, r++) {
    if (len > 1 && S[l] == '0')
      continue;

    if (bestr == 0 || bestl == 0) {
      bestl = l;
      bestr = r;
      continue;
    }

    int new_r = r;
    int new_bestr = bestr;
    for (int d = len; d > 0; d /= 2) {
      while (new_r - d >= l && new_bestr - d >= bestl) {
        long long s1 = calc(bestl, new_bestr - d);
        long long s2 = calc(l, new_r - d);
        long long s3 = calc2(bestl, new_bestr - d);
        long long s4 = calc2(l, new_r - d);
        if (s1 == s2 && s3 == s4)
          break;
        new_r -= d;
        new_bestr -= d;
      }
    }

    if (S[new_r] > S[new_bestr]) {
      bestl = l;
      bestr = r;
    }
  }

  long long otherSum = 0;
  for (int i = 1; i < bestl; i++) {
    otherSum += S[i] - '0';
  }

  for (int j = bestr + 1; j <= n; j++) {
    otherSum += S[j] - '0';
  }

  int carry = 0;
  string res = S.substr(bestl, len);
  int pos = len - 1;
  while ((otherSum > 0 || carry > 0) && pos >= 0) {
    int val = (res[pos] - '0') + otherSum % 10 + carry;
    carry = (val >= 10);
    res[pos] = (val) % 10 + '0';
    otherSum /= 10;
    pos--;
  }

  if (carry > 0)
    otherSum += carry;
  if (otherSum > 0)
    cout << otherSum;
  cout << res;

  return 0;
}
