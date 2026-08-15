#include <bits/stdc++.h>
using namespace std;

// Bui Dinh Trung

const long long inf = 1e18;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  freopen("input.inp", "r", stdin);
  freopen("output.out", "w", stdout);

  struct kadane {
    int start = -1;
    int end = -1;
    int tag = -1;
    long long carry = -inf;

    bool operator<(const kadane &other) const {
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
  vector<kadane> block;
  vector<long long> A(n);
  kadane last;
  int block_count = -1;
  for (int i = 0; i < n; i++) {
    cin >> A[i];
    dp[i].start = dp[i].end = i;
    dp[i].carry = A[i];
    if (last.carry != -inf && last.carry > 0) {
      dp[i].start = last.start;
      dp[i].carry += last.carry;
      dp[i].tag = last.tag;
      block[last.tag].end = i;
    } else {
      dp[i].tag = ++block_count;
      block.push_back({i, i});
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
    long long opt = -inf;
    if (best.start < l) {
      long long current = -inf;
      for (int i = l; i <= min(block[best.tag].end, r); i++) {
        current = max(current + A[i], A[i]);
        opt = max(opt, current);
      }

      if (block[best.tag].end + 1 <= r)
        opt = max(opt, segment.fetch(block[best.tag].end + 1, r).carry);
    } else {
      opt = best.carry;
    }

    cout << opt << '\n';
  }
}
