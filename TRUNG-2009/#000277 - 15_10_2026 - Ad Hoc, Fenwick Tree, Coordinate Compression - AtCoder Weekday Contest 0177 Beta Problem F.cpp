#include <bits/stdc++.h>
using namespace std;

struct FENWICK {
  int n;
  vector<int> data;

  FENWICK(int n) {
    this->n = n;
    data.assign(n+1, 0);
  }

  void update(int index, int val) {
    for (; index <= n; index += index & -index) {
      data[index] += val;
    }
  }

  int fetch(int index) {
    int res = 0;
    for (; index > 0; index -= index & -index) {
      res += data[index];
    }
    return res;
  }
};

const int maxn = 2e5 + 5;
struct PERSON {
  long long s, t;

  friend bool operator<(const PERSON& a, const PERSON& b) {
    return a.s < b.s;
  }
} A[maxn];

int T[maxn];

#define _debug 0
int main() {
  cin.tie(0)->sync_with_stdio(0);

  #if _debug == 1
  freopen("input.inp", "r", stdin);
  #else

  #endif // _debug

  int n;
  cin >> n;
  for (int i = 1; i <= n; i++) cin >> A[i].s;
  for (int i = 1; i <= n; i++) cin >> A[i].t;

  sort(A + 1, A + n + 1);
  iota(T + 1, T + n + 1, 1LL);
  sort(T + 1, T + n + 1, [&](const int x, const int y) {
    return A[x].t < A[y].t;
  });

  long long res = 0;

  FENWICK fenwick(n);
  for (int i = 1; i <= n; i++) {
    int rindex = T[i];

    int cnt = fenwick.fetch(rindex);

    int right_to_left = rindex - cnt - 1;
    int left_to_right = i - cnt - 1;

    A[rindex].s += left_to_right - right_to_left;
    res += left_to_right;

    fenwick.update(rindex, 1);
  }

  for (int i = 1; i <= n; i++) {
    res += abs(A[i].s - A[i].t);
  }

  cout << res;

}
