#include <bits/stdc++.h>
using namespace std;

struct obj {
  int a, b, c;
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int n;
  cin >> n;
  vector<obj> game(n);
  for (int i = 0; i < n; i++)
    cin >> game[i].a >> game[i].b >> game[i].c;
  sort(game.begin(), game.end(),
       [](const auto &x, const auto &y) { return x.b < y.b; });

  vector<int> dp(n, 0);
  int mx = LLONG_MIN;
  for (int i = 0; i < n; i++) {
    dp[i] = game[i].c;
    for (int j = i - 1; j >= 0; j--) {
      if (game[i].a >= game[j].b) {
        dp[i] = max(dp[i], dp[j] + game[i].c);
      }
    }
    mx = max(mx, dp[i]);
  }

  cout << mx;
  return 0;
}
