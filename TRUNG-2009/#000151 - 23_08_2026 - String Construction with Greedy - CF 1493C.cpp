#include <bits/stdc++.h>
using namespace std;

int f[30];
int n, k;
string s;
int inline get(char x) { return (k - f[x - 'a'] % k) % k; }

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int m;
  cin >> m;
  while (m--) {
    memset(f, 0, sizeof f);

    cin >> n >> k;
    cin >> s;

    if (n % k != 0) {
      cout << -1 << '\n';
      continue;
    }

    for (char x : s) {
      f[x - 'a']++;
    }

    int req = 0;
    for (char x = 'a'; x <= 'z'; x++) {
      req += get(x);
    }

    if (req == 0) {
      cout << s << '\n';
      continue;
    }

    auto build = [&](int pos, char c) {
      s[pos] = c;
      for (int j = pos + 1; j < n; j++) {
        s[j] = 'a';
      }

      pos = n - 1;
      for (char x = 'z'; x >= 'a'; x--) {
        int xreq = get(x);
        while (xreq--) {
          s[pos] = x;
          pos--;
        }
      }

      cout << s << '\n';
    };

    int rem = 0;
    bool found = false;
    for (int i = n - 1; i >= 0; i--, rem++) {
      req -= get(s[i]);
      f[s[i] - 'a']--;
      req += get(s[i]);

      for (char x = s[i] + 1; x <= 'z'; x++) {
        int nreq = req - get(x);
        f[x - 'a']++;
        nreq += get(x);
        if (nreq <= rem && (rem - nreq) % k == 0) {
          found = true;
          build(i, x);
          break;
        }
        f[x - 'a']--;
      }
      if (found)
        break;
    }

    if (!found)
      cout << -1 << '\n';
  }
}
