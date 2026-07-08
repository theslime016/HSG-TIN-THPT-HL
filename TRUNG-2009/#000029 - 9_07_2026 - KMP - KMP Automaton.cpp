#include <bits/stdc++.h>
using namespace std;

// test:
// aba
// aabaxxaba
// abaxxxababbaabax

vector<int> lps;
void build_lps(string &s) {
  for (int i = 1, j = 0; i < (int)s.size(); i++) {
    while (s[i] != s[j] && j > 0)
      j = lps[j - 1];
    if (s[i] == s[j]) {
      j++;
    }
    lps[i] = j;
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  string s;
  getline(cin, s);
  s.push_back('#');
  char c;
  int i = 1, j = 0;
  lps.resize(s.size());
  build_lps(s);
  string t;
  // cin.ignore(257, '\n');
  cin >> t;
  stringstream ss;
  ss << t;

  while (i++) {
    if (i >= s.size() && !(ss >> c))
      break;
    while (j > 0) {
      if ((i < s.size() && s[i] != s[j]) || (i >= s.size() && c != s[j]))
        j = lps[j - 1];
      else
        break;
    }
    if ((i < s.size() && s[i] == s[j]) || (i >= s.size() && c == s[j])) {
      if (j == s.size() - 2) {
        cout << i - (int)s.size() * 2 + 3 << '\n';
        j = lps[j];
      } else {
        j++;
      }
    }
    if (i < s.size() - 1)
      lps[i] = j;
  }

  s.pop_back();

  int n = s.size();
  vector<int> ans(s.size() + 1);
  for (int i = 0; i < n; i++) {
    ans[lps[i]]++;
  }
  for (int i = n - 1; i > 0; i--) {
    ans[lps[i - 1]] += ans[i];
  }
  for (int x : ans) {
    x++;
    cout << x << ' ';
  }

  cout << ((lps[n - 1] > 0 && n % (n - lps[n - 1]) == 0) ? "YES" : "NO");

  vector<vector<int>> automata;
  s += '#';
  n = s.size();
  automata.assign(n, vector<int>(26));
  cout << '\n';
  for (int i = 0; i < n; i++) {
    for (int c = 0; c < 26; c++) {
      if (i > 0 && 'a' + c != s[i])
        automata[i][c] = automata[lps[i - 1]][c];
      else
        automata[i][c] = i + ('a' + c == s[i]);
      cout << automata[i][c];
    }
    cout << '\n';
  }

  int state = 0;
  int index = 1;
  char current_char;
  while ((current_char = cin.get()) != EOF) {
    if (!isalpha(current_char))
      continue;
    index++;
    state = automata[state][current_char - 'a'];
    if (state == n - 1)
      cout << index - n + 1 << ' ';
  }

  return 0;
}
