#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5 + 5;
const long long inf = 1e18;
long long fenwick[maxn];
long long A[maxn];

void update(int index, const long long& val) {
  for (; index > 0; index -= index & -index) {
    fenwick[index] = max(fenwick[index], val);
  }
}

long long fetch(int index) {
  long long res = -inf;
  for (; index < maxn; index += index & -index) {
    res = max(res, fenwick[index]);
  }
  return res;
}

#define _debug 1
int main() {
  cin.tie(0)->sync_with_stdio(0);

  #if _debug == 1
  freopen("input.inp", "r", stdin);
  #else

  #endif // _debug

  int n;
  long long d;
  cin >> n >> d;
  vector<long long> B;
  B.reserve(n);
  for (int i = 1; i <= n; i++) {
    cin >> A[i];
    B.push_back(A[i]);
  }

  sort(B.begin(), B.end());
  B.erase(unique(B.begin(), B.end()), B.end());
  auto get_index = [&](const long long& val) {
    return lower_bound(B.begin(), B.end(), val) - B.begin() + 1;
  };

  long long res = 0;
  for (int i = n; i >= 1; i--) {
    int fnd = get_index( A[i] + max(1LL, d) );
    long long val = fetch( fnd ) + 1;
    res = max(res, val);
    update(get_index(A[i]), val);
  }
  cout << res;
}
