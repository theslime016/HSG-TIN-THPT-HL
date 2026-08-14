#include <bits/stdc++.h>
using namespace std;

// Problem: https://i.postimg.cc/Pr9n4XT2/image.png

const long long inf = 1e18;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  struct kadane {
    int start = -1;
    long long carry = -inf;

    const bool operator<(const kadane &other) const {
      return this->carry < other.carry;
    }
  };

  struct ST {
    int n;
    vector<kadane> data;

    ST(int n) {
      this->n = n;
      data.resize(2 * n + 1);
    }

    void build(const vector<kadane> &a) {
      for (int i = 0; i < n; i++) {
        data[n + i] = a[i];
      }

      for (int i = n - 1; i > 0; i--) {
        data[i] = max(data[i * 2], data[i * 2 + 1]);
      }
    }

    void process(int index, const kadane &val) {
      for (data[index += n] = val; index > 1; index >>= 1) {
        data[index >> 1] = max(data[index], data[index ^ 1]);
      }
    }

    kadane fetch(int l, int r) {
      kadane res;
      r++;
      l += n, r += n;
      for (; l < r; l >>= 1, r >>= 1) {
        if (l & 1)
          res = max(data[l++], res);
        if (r & 1)
          res = max(data[--r], res);
      }
      return res;
    }
  };

  int n;
  cin >> n;
  vector<kadane> dp(n);
  kadane last;
  for (int i = 0; i < n; i++) {
    cin >> dp[i].carry;
    dp[i].start = i;
    if (last.carry != -inf && last.carry > 0) {
      dp[i].start = last.start;
      dp[i].carry += last.carry;
    }

    last = dp[i];
  }

  ST segment(n);
  segment.build(dp);

  int m;
  cin >> m;
  while (m--) {
    int l, r;
    cin >> l >> r;
    l--, r--;
    kadane best = segment.fetch(l, r);
    if (best.start < l) {
      best.carry -= dp[l - 1].carry;
    }
    cout << best.carry << '\n';
  }
}
