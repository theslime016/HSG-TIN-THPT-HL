#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;

#define _debug 0

#if _debug == 1
#define debugl(x) cerr << #x << ':' << (x) << ' '
#define debugr(x) cerr << #x << ':' << (x) << '\n'

#else
#define debugl(x)
#define debugr(x)

#endif // _debug

int main() {
  cin.tie(0)->sync_with_stdio(0);

  #if _debug == 1
  freopen("input.inp", "r", stdin);
  #else

  #endif // _debug

  int n, m;
  cin >> n >> m;
  vector<string> s(n + 1);
  vector<int> cnt(n+1, 0);
  for (int i = 1; i <= n; i++) cin >> s[i];

  string t;
  for (int i = 1; i <= m; i++) {
    cin >> t;
    int found = 0;
    for (int j = 1; j <= n; j++) {
      if (s[j] == t) {
        cnt[j]++;
        found = 1;
        break;
      }
    }

    if (!found) {
      int ok = 1;
      int index = -1;
      for (int j = 0; j <= n; j++) {
        if (s[j].size() != t.size()) continue;
        int diff = 0;
        for (int k = 0; k < (int)t.size(); k++) {
          if (s[j][k] != t[k]) diff++;
        }

        if (diff == 1) {
          if (index != -1) {
            ok = 0;
            break;
          } else {
            index = j;
          }
        }

      }

      if (ok && index != -1) cnt[index]++;

    }

  }

  for (int i = 1; i <= n; i++) cout << cnt[i] << '\n';

}
