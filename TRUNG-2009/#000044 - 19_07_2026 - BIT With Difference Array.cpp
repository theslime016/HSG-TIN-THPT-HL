#include <bits/stdc++.h>
using namespace std;
// problem: https://lqdoj.edu.vn/problem/sumq

struct FWT {
  int n;
  vector<long long> data;
  FWT(int num) {
    this->n = num;
    this->data.assign(num + 1, 0);
  }

  void add(int i, long long value) {
    for (; i <= n; i += i & (-i)) {
      data[i] += value;
    }
  }

  long long query(int i) {
    long long pref = 0;
    for (; i > 0; i -= i & (-i)) {
      pref += data[i];
    }
    return pref;
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int n, q;
  cin >> n >> q;
  FWT bit1(n + 1);
  FWT bit2(n + 1);

  while (q--) {
    int x;
    int l, r;
    cin >> x >> l >> r;
    if (x == 0) {
      long long k;
      cin >> k;
      bit1.add(l, k);
      bit1.add(r + 1, -k);

      bit2.add(l, l * k);
      bit2.add(r + 1, -(r + 1) * k);
    } else {
      auto prefix = [&](int x) -> long long {
        return (x + 1) * bit1.query(x) - bit2.query(x);
      };
      cout << prefix(r) - prefix(l - 1) << '\n';
    }
  }

  return 0;
}
