#include <bits/stdc++.h>
using namespace std;

/**
O. Trồng hoa
giới hạn thời gian mỗi test: 3 seconds
giới hạn bộ nhớ mỗi test: 256 megabytes
đầu vào: flowers.inp
đầu ra: flowers.out

Ở Hải Phòng không ai là không biết đến giáo sư NTH giấu tên. Ngoài đam mê đào tạo nhân tài tin học cấp quốc tế, giáo sư còn sở hữu vườn hoa siêu to khổng lồ với vô số các loài hoa: Phượng, Bạch Dương, Lan, Huệ, Thủy Dương,...

Mùa xuân sắp đến, giáo sư NTH muốn quy hoạch lại khu vườn của mình. Theo đó, khu vườn sẽ gồm n khóm hoa được xếp trên một hàng thẳng. Có m loài hoa có thể trồng, mỗi khóm hoa chỉ trồng 1 loài hoa. Để tránh sự đơn điệu, giáo sư quyết định khu vườn có k khóm hoa mà loại hoa được trồng ở đó khác với loại hoa được trồng ở khóm liền kề bên trái.

Giáo sư muốn biết có bao nhiêu cách trồng các loài hoa trong khu vườn thỏa mãn mọi điều kiện trên. Do kết quả rất lớn, các bạn chỉ cần tính kết quả theo modulo p cho trước.

Đầu vào
- Dòng đầu tiên chứa hai số nguyên t và p, lần lượt là số bộ test và modulo mà các bạn cần tính kết quả.
- t dòng tiếp theo mô tả các bộ test, mỗi dòng gồm ba số nguyên n, m, k (0 ≤ k ≤ n-1, 1 ≤ m ≤ 10^9), lần lượt là số khóm hoa trong khu vườn, số loài hoa có thể được trồng và số khóm hoa có loài hoa khác với khóm liền kề bên trái.

Đầu ra
Với mỗi test, in ra kết quả trên một dòng.

Ghi điểm
- Subtask 1 (21 điểm): t = 10^6, p = 998244353, n ≤ 2000
- Subtask 2 (26 điểm): t = 10^6, p = 998244353, n ≤ 10^6
- Subtask 3 (24 điểm): t = 50, p = 998244353, n ≤ 10^9, k ≤ 10^6
- Subtask 4 (29 điểm): t = 50, p = 220797, n ≤ 10^6

Ví dụ

input
2 998244353
3 3 0
3 2 1

output
3
4
**/

#define _debug 0

#if _debug == 1
void logout() {
  cerr << endl;
}
template<typename H, typename... T>
void logout(H h, T... t) {
  cerr << h << ", ";
  logout(t...);
}
#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:" << endl, logout(__VA_ARGS__)
#define debugtitle cerr << __PRETTY_FUNCTION__ << " line: " << __LINE__ << endl
#define newline cerr << endl

#else
#define debug(...) (void(0))
#define debugtitle (void(0))
#define newline (void(0))

#endif // _debug

const int maxtest = 1e6 + 5;
int t;
long long mod;

long long binary_exp(long long base, long long exp) {
  long long res = 1;
  while (exp > 0) {
    if (exp & 1) {
      res = (res * base) % mod;
    }
    base = (base * base) % mod;
    exp >>= 1;
  }
  return res;
}

struct SUB12 {
  static const int maxn = 1e6 + 5;
  long long fact[maxn];
  long long inv_fact[maxn];

  long long get_comb(int k, int n) {
    return ((fact[n] * inv_fact[k])%mod * inv_fact[n - k])%mod;
  }

  void make_fact() {
    fact[0] = 1;
    for (int i = 1; i < maxn; i++) {
      fact[i] = (fact[i - 1] * i) % mod;
    }
    inv_fact[maxn - 1] = binary_exp(fact[maxn - 1], mod - 2);
    for (int i = maxn - 2; i >= 0; i--) {
      inv_fact[i] = (inv_fact[i + 1] * (i + 1)) % mod;
    }
  }

  void solve() {
    make_fact();

    long long n, m, k;
    for (int i = 1; i <= t; i++) {
      cin >> n >> m >> k;
      long long res = ((get_comb(k, n - 1) * m)%mod * binary_exp(m - 1, k))%mod;
      cout << res << '\n';
    }

  }

  bool is_subtask() {
    return t <= maxn && mod == 998244353;
  }

} sub12;

struct SUB3 : SUB12 {

  long long make_f(long long k, long long n, long long m) {
    long long res = 1;
    for (long long i = n; i >= max(1LL, n - k + 1); i--) {
      res = (res * i) % mod;
    }
    res = (res * inv_fact[k]) % mod;
    res = (res * m) % mod;
    res = (res * binary_exp(m - 1, k)) % mod;
    return res;
  }

  void solve() {
    SUB12::make_fact();

    long long n, m, k;
    for (int i = 1; i <= t; i++) {
      cin >> n >> m >> k;
      long long res = make_f(k, n - 1, m);
      cout << res << '\n';
    }
  }

  bool is_subtask() {
    return t <= 50 && mod == 998244353;
  }
} sub3;

struct SUB4 {
  static const int maxn = 1e6 + 5;
  bitset<maxn> is_prime;
  vector<int> prime;

  vector<pair<int, int>> get_factor(const int fact) {
    vector<pair<int, int>> res; /// value - exp

    for (int x : prime) {
      if (x > fact)
        break;

      int exp = 0;
      int temp = fact;
      while (temp >= x) {
        exp += temp / x;
        temp /= x;
      }
      res.push_back({x, exp});
    }
    return res;
  }

  void solve() {
    is_prime.set();
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i*i < maxn; i++) {
      if (!is_prime[i])
        continue;
      for (long long j = 1LL * i * i; j < maxn; j += i) {
        is_prime[j] = false;
      }
    }

    for (int i = 2; i < maxn; i++) {
      if (is_prime[i])
        prime.push_back(i);
    }

    for (int i = 1; i <= t; i++) {
      long long n, m, k;
      cin >> n >> m >> k;

      vector<pair<int, int>> up = get_factor(n - 1), down1 = get_factor(k), down2 = get_factor(n - k - 1);

      long long res = 1;
      for (int i = 0; i < (int)up.size(); i++) {
        int base = up[i].first;
        int exp = up[i].second;
        if (i < (int)down1.size())
          exp -= down1[i].second;
        if (i < (int)down2.size())
          exp -= down2[i].second;

        long long val = binary_exp(base, exp);
        res = (res * val) % mod;
      }

      res = (res * m) % mod;
      res = (res * binary_exp(m - 1, k)) % mod;
      cout << res << '\n';
    }
  }

  bool is_subtask() {
    return t <= 50 && mod == 220797;
  }

} sub4;

int main() {
  cin.tie(0)->sync_with_stdio(0);

#if _debug == 1
  freopen("input.inp", "r", stdin);

#elif _debug == 2
  freopen("input.inp", "r", stdin);

#else
  freopen("flowers.inp", "r", stdin);
  freopen("flowers.out", "w", stdout);

#endif // _debug

  cin >> t >> mod;

  if (sub4.is_subtask())
    return sub4.solve(), 0;
  if (sub3.is_subtask())
    return sub3.solve(), 0;
  if (sub12.is_subtask())
    return sub12.solve(), 0;
}
