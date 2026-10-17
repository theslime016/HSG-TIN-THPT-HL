#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e3 + 5;
int cnt[maxn];

#define _debug 0
int main() {
  cin.tie(0)->sync_with_stdio(0);

  #if _debug == 1
  freopen("input.inp", "r", stdin);
  #else

  #endif // _debug

  map<string, int> mp; // string - index
  int n, m;
  cin >> n >> m;
  string s;
  for (int i = 1; i <= n; i++) {
    cin >> s;
    mp.insert({s, i});
  }

  for (int i = 1; i <= m; i++) {
    cin >> s;
    if (mp.count(s)) cnt[mp[s]]++;
    else {
      int index = -1;
      int ok = 1;
      for (char &c : s) {
      char old_val = c;
        for (char t = 'a'; t <= 'z'; t++) {
          c = t;
          if (mp.count(s)) {
            if (index == -1) index = mp[s];
            else {
              ok = 0;
              break;
            }
          }
        }
        c = old_val;
      }

      if (ok && index != -1) cnt[index]++;
    }
  }

  for (int i = 1; i <= n; i++) cout << cnt[i] << '\n';

}
