#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_map;

const int maxn = 2e5 + 5;

#define _debug 0
int main() {
  cin.tie(0)->sync_with_stdio(0);

  #if _debug == 1
  freopen("input.inp", "r", stdin);
  #else

  #endif // _debug

  int t;
  cin >> t;
  while (t--) {
    int n;
    cin >> n;

    int x = 1;
    while ((x << 1) <= n) {
      x <<= 1;
    }

    vector<int> pref;
    pref.reserve(4 * x);
    for (int i = 0; i <= x - 1; i++) pref.push_back(i);
    for (int i = x - 1; i >= 0; i--) pref.push_back(i);
    for (int i = x; i <= (x << 1) - 1; i++) pref.push_back(i);
    for (int i = (x << 1) - 1; i >= x; i--) pref.push_back(i);

    cout << (int)pref.size() - 1 << '\n';
    for (int i = 1; i < (int)pref.size(); i++) {
      cout << (pref[i] ^ pref[i-1]) << ' ';
    } cout << '\n';
  }

}
