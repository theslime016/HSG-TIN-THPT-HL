#include <bits/stdc++.h>
using namespace std;

#define debugr(x) cout << #x << " = " << (x) << '\n'
#define debugl cout < '\n'

constexpr int mxsz = 55;
struct bigint {
  long long data[mxsz]{}; // 32-bit
  int sz = 0;
  bool neg = false;

  bigint() = default;

  bigint(int type) {
    // 1 -> max positive
    // -1 -> min negative
    data[mxsz - 1] = 1;
    neg = type == -1 ? true : false;
  }

  void convert(long long val) {
    sz = 0;
    neg = false;
    memset(data, 0, sizeof data);

    if (val < 0) {
      neg = true;
      val = -val;
    }

    while (val > 0) {
      data[sz] = (uint32_t)val;
      val >>= 32;
      sz++;
    }
  }

  int cmp_abs(const bigint &other) const {
    if (sz != other.sz)
      return sz > other.sz ? 1 : -1;
    for (int index = sz - 1; index >= 0; index--) {
      if (data[index] != other.data[index]) {
        return data[index] > other.data[index] ? 1 : -1;
      }
    }
    return 0;
  }

  bool operator>(const bigint &other) const {
    if (neg != other.neg)
      return !neg;

    int c = cmp_abs(other);
    return neg ? (c < 0) : (c > 0);
  }

  bool operator<(const bigint &other) const {
    if (neg != other.neg)
      return neg;

    int c = cmp_abs(other);
    return neg ? (c > 0) : (c < 0);
  }

  void update_max(bigint &res, const bigint &val) {
    if (val > res)
      res = val;
  }

  void update_min(bigint &res, const bigint &val) {
    if (val < res)
      res = val;
  }

  friend ostream &operator<<(ostream &os, bigint val) {
    if (val.sz == 0)
      return os << 0;

    string res = "";
    while (val.sz > 0) {
      long long carry = 0;
      for (int index = val.sz - 1; index >= 0; index--) {
        long long current = (carry << 32) + val.data[index];
        val.data[index] = current / 10;
        carry = current % 10;
      }
      res.push_back(char(carry + '0'));

      while (val.sz > 0 && val.data[val.sz - 1] == 0)
        val.sz--;
    }

    if (val.neg)
      res.push_back('-');
    reverse(res.begin(), res.end());

    return os << res;
  }

  bigint add_abs(const bigint &other) const {
    bigint res;
    res.sz = max(sz, other.sz);

    long long carry = 0;
    for (int index = 0; index < res.sz; index++) {
      long long sum = carry;
      if (index < sz)
        sum += data[index];
      if (index < other.sz)
        sum += other.data[index];

      res.data[index] = (uint32_t)sum;
      carry = (sum >> 32);
    }
    if (carry)
      res.data[res.sz++] = carry;
    return res;
  }

  bigint sub_abs(const bigint &other) const {
    // *this >= other
    bigint res;
    res.sz = sz;

    long long borrow = 0;
    for (int index = 0; index < sz; index++) {
      long long diff = data[index] - borrow;
      if (index < other.sz)
        diff -= other.data[index];

      if (diff < 0) {
        diff += (1LL << 32);
        borrow = 1;
      } else {
        borrow = 0;
      }
      res.data[index] = (uint32_t)diff;
    }
    while (res.sz > 0 && res.data[res.sz - 1] == 0)
      res.sz--;
    return res;
  }

  bigint operator+(const bigint &other) const {
    // ++ --
    if (neg == other.neg) {
      bigint res = add_abs(other);
      res.neg = neg;
      return res;
    }

    // +-
    if (cmp_abs(other) >= 0) {
      bigint res = sub_abs(other);
      res.neg = neg;
      return res;
    } else {
      // -+
      bigint res = other.sub_abs(*this);
      res.neg = other.neg;
      return res;
    }
  }

  bigint operator-(const bigint &other) const {
    bigint tmp = other;
    if (tmp.sz > 0)
      tmp.neg = !tmp.neg;
    return *this + tmp;
  }

  bigint operator*(const bigint &other) const {
    bigint res;
    if (sz == 0 || other.sz == 0)
      return res;
    if (data[mxsz - 1] == 1) {
      int rneg = (neg | other.neg) ? -1 : 1;
      return bigint(rneg);
    }

    res.sz = sz + other.sz;
    for (int index = 0; index < sz; index++) {
      long long carry = 0;
      for (int jindex = 0; jindex < other.sz || carry > 0; jindex++) {
        long long current =
            res.data[index + jindex] + carry +
            1ULL * data[index] * (jindex < other.sz ? other.data[jindex] : 0);
        res.data[index + jindex] = (uint32_t)current;
        carry = current >> 32;
      }
    }

    while (res.sz > 0 && res.data[res.sz - 1] == 0)
      res.sz--;
    res.neg = (neg != other.neg);
    return res;
  }
};

const int maxn = 105;
int A[maxn];
char oper[maxn];

bigint maxit[maxn][maxn];
bigint minit[maxn][maxn];

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n;
  cin >> n;

  for (int i = 1; i <= n; i++) {
    cin >> A[i];
  }

  for (int i = 1; i <= n - 1; i++) {
    cin >> oper[i];
  }

  // A bắt đầu từ index 1
  // oper bắt đầu từ index 1
  // -> [index] oper = A
  // i j [index] A -> [index] oper = i -> j-1

  fill_n(&maxit[0][0], maxn * maxn, bigint(1));
  fill_n(&minit[0][0], maxn * maxn, bigint(-1));

  for (int i = 1; i <= n; i++) {
    maxit[i][i].convert(A[i]);
    minit[i][i].convert(A[i]);
  }

  auto fetch = [](const bigint &x, const bigint &y, char op) -> bigint {
    if (op == '+')
      return x + y;
    if (op == '-')
      return x - y;
    return x * y;
  };

  for (int len = 2; len <= n; len++) {
    for (int start = 1; start <= n; start++) {
      int end = start + len - 1;
      if (end > n)
        break;
      for (int k = start; k < end; k++) {
        bigint v1 = fetch(maxit[start][k], maxit[k + 1][end], oper[k]);
        bigint v2 = fetch(minit[start][k], minit[k + 1][end], oper[k]);
        bigint v3 = fetch(maxit[start][k], minit[k + 1][end], oper[k]);
        bigint v4 = fetch(minit[start][k], maxit[k + 1][end], oper[k]);

        maxit[start][end].update_max(maxit[start][end], max({v1, v2, v3, v4}));

        minit[start][end].update_min(minit[start][end], min({v1, v2, v3, v4}));
      }
    }
  }

  cout << maxit[1][n];
}
