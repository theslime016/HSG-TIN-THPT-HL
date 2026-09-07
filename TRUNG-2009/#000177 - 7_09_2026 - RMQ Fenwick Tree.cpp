#include <bits/stdc++.h>
using namespace std;

const long long inf = 1e18;
const int maxn = 2e5 + 5;
long long A[maxn];
long long fenwick[maxn];
int n, q;

void proc(int index, const long long &val) {
  A[index] = val;
  for (; index <= n; index += index & -index) {
    fenwick[index] = A[index];
    int c = index - (index & -index);
    for (int jindex = index - 1; jindex > c; jindex -= jindex & -jindex) {
      fenwick[index] = min(fenwick[index], fenwick[jindex]);
    }
  }
}

long long fetch(int l, int r) {
  long long res = A[r];
  while (l <= r) {
    int next = r - (r & -r);
    if (next >= l) {
      res = min(res, fenwick[r]);
      r = next;
    } else {
      res = min(res, A[r]);
      r--;
    }
  }
  return res;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);

  cin >> n >> q;
  for (int i = 1; i <= n; i++) {
    cin >> A[i];
    fenwick[i] = A[i];
  }

  for (int i = 1; i <= n; i++) {
    int p = i + (i & -i);
    if (p <= n)
      fenwick[p] = min(fenwick[p], fenwick[i]);
  }

  while (q--) {
    int t;
    cin >> t;
    if (t == 1) {
      int index;
      long long val;
      cin >> index >> val;
      proc(index, val);
    } else {
      int l, r;
      cin >> l >> r;
      cout << fetch(l, r) << '\n';
    }
  }
}
