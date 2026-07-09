#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  string s;
  cin >> s;
  s.push_back('#');

  vector<int> lps(s.size(), 0);
  for (int i = 1, j = 0; i < (int)s.size(); i++) {
    while (j > 0 && s[i] != s[j])
      j = lps[j - 1];
    if (s[i] == s[j])
      j++;
    lps[i] = j;
  }

  vector<long long> cnt(s.size(), 1);
  for (int i = (int)s.size() - 1; i > 0; i--) {
    if (lps[i])
      cnt[lps[i] - 1] += cnt[i];
  }
  for (int x : cnt)
    cout << x << ' ';
  cout << endl;

  vector<vector<int>> automata(s.size(), vector<int>(26));
  for (int i = 0; i < (int)s.size(); i++) {
    for (int c = 0; c < 26; c++) {
      if (c + 'a' != s[i] && i > 0) {
        automata[i][c] = automata[lps[i - 1]][c];
      } else {
        automata[i][c] = i + ('a' + c == s[i]);
      }
      cout << automata[i][c] << ' ';
    }
    cout << '\n';
  }

  int k;
  cin >> k;
  vector<vector<int>> fsm(k + 1, vector<int>(s.size()));
  vector<vector<long long>> etf(k + 1, vector<long long>(s.size()));
  s.pop_back();
  for (int state = 0; state < (int)s.size(); state++) {
    fsm[1][state] = automata[state][0];
    etf[1][state] = (fsm[1][state] == s.size());
  }
  for (int i = 2; i <= k; i++) {
    int index_mid = (i - 1) % 26;
    for (int state = 0; state < (int)s.size(); state++) {
      // calc
      int aState = fsm[i - 1][state];
      int aCnt = etf[i - 1][state];

      int midState = automata[aState][index_mid];
      int midCnt = (midState == s.size());

      int bState = fsm[i - 1][midState];
      int bCnt = etf[i - 1][midState];

      // update
      fsm[i][state] = bState;
      etf[i][state] = aCnt + bCnt + midCnt;
    }
  }

  cout << etf[k][0];

  return 0;
}
