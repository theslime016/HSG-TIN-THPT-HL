#include <bits/stdc++.h>
using namespace std;

// Problem: https://i.postimg.cc/c4VBhjjD/image.png

const long long inf = 1e18;
struct fenwick {
  int n;
  vector<long long> data;

  fenwick(int n) {
    this->n = n;
    data.assign(n + 1, -inf);
    // fenwick tag index - dp max
  }

  void process(int index, long long val) {
    for (; index <= n; index += index & -index) {
      data[index] = max(data[index], val);
    }
  }

  long long fetch(int index) {
    long long res = -inf;
    for (; index > 0; index -= index & -index) {
      res = max(res, data[index]);
    }
    return res;
  }
};

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n;
  cin >> n;
  vector<pair<int, long long>> A(n + 1);
  vector<int> rindex(n + 1);
  fenwick bit(n);
  for (int i = 1; i <= n; i++) {
    int tag;
    long long val;
    cin >> tag >> val;
    A[i] = {tag, val};
    rindex[i] = tag;
  }

  sort(rindex.begin() + 1, rindex.end());
  rindex.erase(unique(rindex.begin(), rindex.end()), rindex.end());

  auto get_index = [&](int tag) -> int {
    return upper_bound(rindex.begin() + 1, rindex.end(), tag) - rindex.begin() -
           1;
  };

  long long res = -inf;
  for (int i = 1; i <= n; i++) {
    int tag = A[i].first;
    int index = get_index(tag);
    long long val = A[i].second;
    long long dp = bit.fetch(index - 1);
    val += dp != -inf ? dp : 0;

    res = max(res, val);
    bit.process(index, val);
  }

  cout << res;
}
