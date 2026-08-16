#include <bits/stdc++.h>
using namespace std;

const long long inf = 1e9;
struct fenwick {
  int n;
  vector<int> data;
  vector<int> lazy;

  fenwick(int n) {
    this->n = n;
    data.assign(n + 1, -inf);
    lazy.assign(n + 1, -inf);
  }

  void process(int index, const int &val) {
    for (; index <= n; index += index & -index) {
      data[index] = max(data[index], val);
    }
  }

  void prefetch(int index, const int &val) {
    lazy[index] = max(lazy[index], val);
  }
  void preprocess(int start, int end) {
    int propagation = lazy[start];
    for (int index = start; index <= n && index <= end;
         index += index & -index) {
      data[index] = max(data[index], propagation);
      int next = index + (index & -index);
      if (next <= n)
        lazy[next] = max(lazy[next], propagation);
      lazy[index] = -inf;
    }
  }

  int fetch(int index) {
    int res = -inf;

    for (int jindex = 1; jindex <= index; jindex++) {
      if (lazy[jindex] != -inf) {
        preprocess(jindex, index);
      }
    }

    for (; index > 0; index -= index & -index) {
      res = max(res, data[index]);
    }
    return res;
  }
};

int main() {
  cin.tie(0)->sync_with_stdio(0);
}
