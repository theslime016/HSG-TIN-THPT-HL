#include <bits/stdc++.h>
using namespace std;

const int maxn = 2005;
const long long inf = 1e18;

struct fenwick {
  int n;
  vector<vector<long long>> data;

  fenwick(int n) {
    this->n = n;
    data.assign(n + 1, vector<long long>(n + 1, -inf));
  }

  void update(int x, int y, const long long &val) {
    for (int index = x; index <= n; index += index & -index) {
      for (int jindex = y; jindex <= n; jindex += jindex & -jindex) {
        data[index][jindex] = max(data[index][jindex], val);
      }
    }
  }

  long long fetch(int x, int y) {
    long long res = -inf;
    for (int index = x; index > 0; index -= index & -index) {
      for (int jindex = y; jindex > 0; jindex -= jindex & -jindex) {
        res = max(res, data[index][jindex]);
      }
    }
    return res;
  }
};

long long A[maxn];

struct item {
  int l, r;
  long long data;
  int rank;
  bool operator<(const item &other) const { return this->data < other.data; }
};

int main() {
  cin.tie(0)->sync_with_stdio(0);
  int n, q;
  cin >> n >> q;

  for (int i = 1; i <= n; i++)
    cin >> A[i];

  vector<item> proc;
  proc.reserve(n * (n + 1) / 2);
  for (int i = 1; i <= n; i++) {
    long long pref = 0;
    for (int j = i; j <= n; j++) {
      pref += A[j];
      proc.push_back({i, j, pref});
    }
  }

  sort(proc.begin(), proc.end());

  // for (const auto &x : proc)
  //   cout << x.l << ' ' << x.r << ' ' << x.data << '\n';
  // cout << '\n';

  int m = proc.size();
  fenwick bit(n);

  vector<item> task;
  task.reserve(q);
  for (int i = 1; i <= q; i++) {
    int l, r;
    long long k;
    cin >> l >> r >> k;
    task.push_back({l, r, k, i});
  }

  sort(task.begin(), task.end());

  // for (const auto &x : task)
  //   cout << x.l << ' ' << x.r << ' ' << x.data << '\n';
  // cout << '\n';

  int pos = 0;
  for (auto &x : task) {
    while (pos < m && proc[pos].data <= x.data) {
      bit.update(n - proc[pos].l + 1, proc[pos].r, proc[pos].data);
      pos++;
    }
    long long res = bit.fetch(n - x.l + 1, x.r);
    x.data = res;
  }

  sort(task.begin(), task.end(),
       [](const item &x, const item &y) { return x.rank < y.rank; });

  for (const auto &x : task) {
    if (x.data == -inf)
      cout << "NONE" << '\n';
    else
      cout << x.data << '\n';
  }
}
