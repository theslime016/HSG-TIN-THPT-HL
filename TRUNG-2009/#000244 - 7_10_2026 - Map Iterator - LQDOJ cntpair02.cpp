#include <bits/stdc++.h>
using namespace std;

#define _debug 0
int main() {
  cin.tie(0)->sync_with_stdio(0);

  #if _debug == 1
  freopen("input.inp", "r", stdin);
  #else

  #endif // _debug

  int n;
  long long k;
  cin >> n >> k;

  map<long long, int> mp;
  for (int i = 1; i <= n; i++) {
    long long x;
    cin >> x;
    mp[x]++;
  }

  auto pt1 = mp.begin();
  auto pt2 = --mp.end();
  long long res = 0;
  while (pt1 != pt2) {
    long long sum = (*pt1).first + (*pt2).first;
    if (sum > k) pt2--;
    else if (sum < k) pt1++;
    else res += (*pt1).second * (*pt2).second, pt1++;
  }

  if (k%2 == 0) {
    long long num = k/2;
    long long val = mp[num];
    res += val * (val - 1) / 2;
  }

  cout << res;
}
