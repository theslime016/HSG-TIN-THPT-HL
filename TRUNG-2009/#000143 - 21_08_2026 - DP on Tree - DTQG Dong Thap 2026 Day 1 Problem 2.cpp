#include <bits/stdc++.h>
using namespace std;

const int maxn = 2e5 + 5;
char gparity[maxn];
vector<int> adj[maxn];
int indeg[maxn];
int proc[maxn];
int n;

namespace subtask2 {
void solve() {
  vector<char> block;
  block.push_back('#');
  block.reserve(n);

  stack<int> st;
  st.push(1);
  while (!st.empty()) {
    int a = st.top();
    st.pop();

    if (proc[a]) {
      block.push_back(gparity[a]);
      for (int x : adj[a]) {
        if (!proc[x])
          st.push(x);
      }
    } else {
      proc[a] = 1;
      st.push(a);
      for (int x : adj[a]) {
        if (!proc[x]) {
          st.push(x);
          break;
        }
      }
    }
  }

  block.push_back('#');

  // for (char x : block)
  //   cout << x;
  // cout << '\n';

  long long op = 0;
  for (int i = 1; i <= n; i++) {
    if (block[i] != block[i - 1] && block[i] != block[i + 1]) {
      int x = block[i] - '0';
      x = !x;
      block[i] = x + '0';
      op++;
    }
  }

  for (int i = 1; i <= n; i++) {
    if (block[i] != block[i - 1])
      op++;
  }

  cout << op;
}
} // namespace subtask2

namespace fb {
long long res = 0;
vector<array<long long, 2>> dp;

void dfs(int index) {
  proc[index] = 1;

  int index_parity = gparity[index] - '0';
  dp[index][index_parity] = 0;
  dp[index][!index_parity] = 1;

  for (int c : adj[index]) {
    if (proc[c])
      continue;
    dfs(c);

    dp[index][0] += min(dp[c][0], dp[c][1] + 1);
    dp[index][1] += min(dp[c][1], dp[c][0] + 1);
  }
}

void solve() {
  dp.assign(n + 5, {0, 0});
  for (int i = 1; i <= n; i++) {
    if (!proc[i])
      dfs(i);
  }
  for (int i = 1; i <= n; i++) {
    res = max(res, min(dp[i][0], dp[i][1]) + 1);
  }
  cout << res;
}
} // namespace fb

namespace subtask3 {
void solve() {
  int root = -1;
  int parity = -1;
  int red, blue; // 0/1;
  red = blue = 0;
  for (int i = 1; i <= n; i++) {
    if (indeg[i] == n - 1) {
      root = i;
      parity = gparity[root] - '0';
    } else if (gparity[i] - '0') {
      blue++;
    } else {
      red++;
    }
  }

  // parity = red
  if (parity == 1)
    swap(red, blue);

  cout << min(blue, red + 1) + 1;
}
} // namespace subtask3

int main() {
  cin.tie(0)->sync_with_stdio(0);

  cin >> n;
  cin.ignore(256, '\n');
  cin.read(&gparity[1], n);

  for (int i = 1; i <= n - 1; i++) {
    int a, b;
    cin >> a >> b;
    adj[a].push_back(b);
    adj[b].push_back(a);
    indeg[a]++;
    indeg[b]++;
  }

  bool sub2 = true;
  bool sub3 = false;
  int checksub3 = 0;
  for (int i = 1; i <= n; i++) {

    if (indeg[i] == n - 1) {
      sub3 = true;
      checksub3++;
    }

    if (indeg[i] > 2) {
      sub2 = false;
    }
  }
  // if (sub2)
  //   subtask2::solve();
  if (sub3 && checksub3 == 1)
    subtask3::solve();

  else
    fb::solve();
}
