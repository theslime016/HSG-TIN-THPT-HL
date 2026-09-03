#include <bits/stdc++.h>
using namespace std;

const int maxchar = 105;
char temp[maxchar];

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int t;
  cin >> t;
  string s;
  int x, y;
  while (t--) {
    cin >> s >> x >> y;
    if (x > y)
      swap(x, y);

    int h = s.size() + ((int)s.size() % 2);
    if (h == (int)s.size()) {
      auto solve = [&](int pos, int rem_a, int rem_b, int proc,
                       auto &self) -> bool {
        if (pos == (int)s.size())
          return true;

        if (proc) {
          if (s[pos] - '0' <= x && rem_a &&
              self(pos + 1, rem_a - 1, rem_b, proc & (s[pos] - '0' == x), self))
            return temp[pos] = x + '0', true;
          else if (s[pos] - '0' <= y && rem_b &&
                   self(pos + 1, rem_a, rem_b - 1, proc & (s[pos] - '0' == y),
                        self))
            return temp[pos] = y + '0', true;
          else {
            return false;
          }
        } else {
          if (rem_a)
            return temp[pos] = x + '0',
                   self(pos + 1, rem_a - 1, rem_b, proc, self);
          else if (rem_b)
            return temp[pos] = y + '0',
                   self(pos + 1, rem_a, rem_b - 1, proc, self);
        }
        return false;
      };
      if (solve(0, h / 2, h / 2, 1, solve)) {
        for (int i = 0; i < (int)s.size(); i++)
          cout << temp[i];
        cout << '\n';
        continue;
      } else {
        h += 2;
      }
    }

    int rem_a = h / 2;
    int rem_b = rem_a;
    if (x == 0) {
      cout << y << x;
      rem_a--;
      rem_b--;
    }
    while (rem_a--)
      cout << x;
    while (rem_b--)
      cout << y;
    cout << '\n';
  }
}
