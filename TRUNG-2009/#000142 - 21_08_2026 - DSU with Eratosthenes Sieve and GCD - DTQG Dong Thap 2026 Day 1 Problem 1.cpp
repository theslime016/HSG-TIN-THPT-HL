#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e6 + 5;
int freq[maxn];
long long res = 0;
int proc = 0;

struct uf {
  int n;
  vector<int> data;

  uf(int n) {
    this->n = n;
    data.resize(n + 1);
    iota(data.begin(), data.end(), 0);
  }

  int find(int index) {
    if (data[index] == index)
      return index;
    else
      return data[index] = find(data[index]);
  }

  void compress(int a, int b, long long w) {
    a = find(a);
    b = find(b);
    if (a != b) {
      data[a] = b;
      res += w;
      proc++;
    }
  }
};

int main() {
  cin.tie(0)->sync_with_stdio(0);

  // freopen("input.inp", "r", stdin);
  // freopen("output.out", "w", stdout);

  int n;
  cin >> n;

  int m = -1;
  for (int i = 1; i <= n; i++) {
    int x;
    cin >> x;
    m = max(m, x);
    if (freq[x] > 0) {
      res += x;
    } else {
      freq[x]++;
    }
  }

  uf dsu(m);
  auto run = [&]() {
    for (int d = m; d > 0; d--) {
      int first = -1;
      for (int j = d; j <= m; j += d) {
        if (freq[j]) {
          if (first != -1)
            dsu.compress(j, first, d);
          else
            first = j;
        }
        if (proc == n - 1)
          return;
      }
    }
  };
  run();
  cout << res;
}
