#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  string t, s;
  cin >> t >> s;
  s.push_back('#');

  vector<int> lps(s.size(), 0);
  for (int i = 1, j = 0; i < (int)s.size(); i++) {
    while (j > 0 && s[i] != s[j])
      j = lps[j - 1];
    if (s[i] == s[j])
      j++;
    lps[i] = j;
  }

  vector<vector<int>> automata(s.size(), vector<int>(26));
  for (int i = 0; i < (int)s.size(); i++) {
    for (int c = 0; c < 26; c++) {
      if (c + 'a' != s[i] && i > 0) {
        automata[i][c] = automata[lps[i - 1]][c];
      } else {
        automata[i][c] = i + ('a' + c == s[i]);
      }
    }
  }

  vector<pair<bool, long long>> last(s.size() + 1, {false, 0});
  vector<pair<bool, long long>> current(s.size() + 1, {false, 0});
  s.pop_back();
  last[0] = {true, 0};
  if (s[0] == t[0] || t[0] == '?')
    last[1] = {true, (s.size() == 1)};
  for (int i = 1; i < t.size(); i++) {
    for (int j = 0; j <= s.size(); j++) {
      if (!last[j].first)
        continue;
      if (t[i] == '?') {
        for (int c = 0; c < 26; c++) {
          current[automata[j][c]].first = true;
          current[automata[j][c]].second =
              max(current[automata[j][c]].second,
                  last[j].second + (automata[j][c] == s.size()));
        }
      } else {
        current[automata[j][t[i] - 'a']].first = true;
        current[automata[j][t[i] - 'a']].second =
            max(current[automata[j][t[i] - 'a']].second,
                last[j].second + (automata[j][t[i] - 'a'] == s.size()));
      }
    }
    swap(last, current);
    current.assign(s.size() + 1, {false, 0});
  }

  long long mx = 0;
  for (auto &x : last) {
    mx = max(mx, x.second);
  }
  cout << mx;

  return 0;
}
