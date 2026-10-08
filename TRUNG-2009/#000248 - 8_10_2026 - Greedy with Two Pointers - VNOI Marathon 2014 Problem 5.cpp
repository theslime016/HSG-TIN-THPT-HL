#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e6 + 5;
int A[maxn];

#define _debug 0
int main() {
  cin.tie(0)->sync_with_stdio(0);

#if _debug == 1
  freopen("input.inp", "r", stdin);
#else

#endif // _debug

  int n, l, d;
  cin >> n >> l >> d;
  l++;
  for (int i = 1; i <= n; i++) cin >> A[i];

  long long res = 0;
  int pt1 = 1;
  multiset<int> ms;
  for (int pt2 = 1; pt2 <= n; pt2++) {
    ms.insert(A[pt2]);
    while (pt1 <= pt2 && abs(*(ms.begin()) - *(--ms.end())) > d) ms.erase(ms.find(A[pt1++]));
    if (ms.size() >= l) res += (int)ms.size() - l + 1;
  }
  cout << res;

}
