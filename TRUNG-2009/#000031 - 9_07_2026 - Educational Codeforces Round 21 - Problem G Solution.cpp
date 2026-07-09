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

  vector<vector<pair<bool, long long>>> dp(
      t.size(), vector<pair<bool, long long>>(s.size() + 2, {false, 0}));
  s.pop_back();
  // TODO: BỎ T, cin.get, dùng 2 vector pair xong swap
  dp[0][0] = {true, 0};
  if (s[0] == t[0] || t[0] == '?')
    dp[0][1] = {true, (s.size() == 1)};
  for (int i = 1; i < t.size(); i++) {
    for (int j = 0; j <= s.size(); j++) {
      if (!dp[i - 1][j].first)
        continue;
      if (t[i] == '?') {
        for (int c = 0; c < 26; c++) {
          dp[i][automata[j][c]].first = true;
          dp[i][automata[j][c]].second =
              max(dp[i][automata[j][c]].second,
                  dp[i - 1][j].second + (automata[j][c] == s.size()));
        }
      } else {
        dp[i][automata[j][t[i] - 'a']].first = true;
        dp[i][automata[j][t[i] - 'a']].second =
            max(dp[i][automata[j][t[i] - 'a']].second,
                dp[i - 1][j].second + (automata[j][t[i] - 'a'] == s.size()));
        // ????
      }
    }
  }

  long long mx = 0;
  for (int i = 0; i < t.size(); i++) {
    for (int j = 0; j <= s.size(); j++) {
      // cout << dp[i][j].second << ' ';
      mx = max(mx, dp[i][j].second);
    }
    // cout << '\n';
  }

  cout << mx;

  return 0;
}
