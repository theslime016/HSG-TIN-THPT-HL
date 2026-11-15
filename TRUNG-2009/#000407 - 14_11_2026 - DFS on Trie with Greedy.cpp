#include <bits/stdc++.h>
using namespace std;

#define _debug 0

#if _debug == 1
void log_out() {cerr << endl;}
template<typename H, typename... T>
void log_out(H h, T... t) {
  cerr << h << ", ";
  log_out(t...);
}
#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:" << endl, log_out(__VA_ARGS__)
#define newline cerr << endl

#else
#define debug(...) (void(0))
#define newline (void(0))

#endif // _debug

const int maxn = 30'000;
const int maxlen = 30;
const int maxchar = 30;

int trie[maxn * maxlen][maxchar];
int mark[maxn * maxlen];
int container[maxn * maxlen];
int trie_cnt = 0;

void add_trie(const string& s) {
  int index = 0;
  for (int i = 0; i < s.size(); i++) {
    int c = s[i] - 'a';
    int flag = (i + 1 == s.size());
    if (trie[index][c] == 0) {
      trie[index][c] = ++trie_cnt;
    }
    index = trie[index][c];
    if (flag) container[index]++;
  }
}

string longest;
void make_longest() {
  int index = 0;
  for (char c : longest) {
    index = trie[index][c - 'a'];
    mark[index] = 1;
  }
}

char oper[(maxn * maxlen) << 2];
int oper_cnt = 0;
int word_cnt;
void make_dfs(int index) {
  int longest_char = -1;
  for (int c = 0; c < maxchar; c++) {
    if (trie[index][c]) {
      if (mark[ trie[index][c] ]) {
        longest_char = c;
        continue;
      }

      oper[++oper_cnt] = c + 'a';
      while (container[ trie[index][c] ]--) {
        oper[++oper_cnt] = 'P';
        word_cnt--;
      }
      make_dfs(trie[index][c]);
    }
  }

  if (longest_char != -1) {
    oper[++oper_cnt] = longest_char + 'a';
    while(container[ trie[index][longest_char] ]--) {
      oper[++oper_cnt] = 'P';
      word_cnt--;
    }
    make_dfs(trie[index][longest_char]);
  }

  if (word_cnt > 0) oper[++oper_cnt] = '-';
}

int main() {
  cin.tie(0)->sync_with_stdio(0);

  #if _debug == 1
  freopen("input.inp", "r", stdin);

  #else

  #endif // _debug

  int n;
  cin >> n;
  word_cnt = n;

  string s;
  for (int i = 1; i <= n; i++) {
    cin >> s;
    add_trie(s);
    if (s.size() > longest.size()) longest = s;
  }
  make_longest();

  make_dfs(0);

  cout << oper_cnt << '\n';
  for (int i = 1; i <= oper_cnt; i++) cout << oper[i] << '\n';

}
