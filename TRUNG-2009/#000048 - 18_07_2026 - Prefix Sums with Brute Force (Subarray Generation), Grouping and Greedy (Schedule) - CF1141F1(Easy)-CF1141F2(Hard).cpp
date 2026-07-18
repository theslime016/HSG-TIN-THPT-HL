#include <bits/stdc++.h>
using namespace std;

struct coor {
  int x = -1, y = -1;
  long long val;
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int n;
  cin >> n;
  vector<long long> pref(n + 1, 0);
  for (int i = 1; i <= n; i++) {
    cin >> pref[i];
    pref[i] += pref[i - 1];
  }

  vector<coor> S;
  S.reserve(n * (n + 1) / 2);
  for (int i = 1; i <= n; i++) {
    for (int j = 0; j < i; j++) {
      if (i <= j + 1)
        S.push_back({i, j + 1, (pref[i] - pref[j])});
      else
        S.push_back({j + 1, i, (pref[i] - pref[j])});
    }
  }

  sort(S.begin(), S.end(), [](auto &a, auto &b) { return a.val < b.val; });
  // for (int i = 0; i < S.size(); i++) {
  //   cout << S[i].x << ' ' << S[i].y << ' ' << S[i].val << '\n';
  // }
  // sort(S.begin() + 1, S.begin() + 2,
  //      [](auto &a, auto &b) { return a.y < b.y || (a.y == b.y && a.x > b.x);
  //      });

  int k = 0;
  stack<pair<int, int>> res;
  for (int i = 0, j = i; i < S.size(); i = j) {
    while (j < S.size() && S[i].val == S[j].val) {
      j++;
    }
    sort(S.begin() + i, S.begin() + j, [](auto &a, auto &b) {
      return a.y < b.y || (a.y == b.y && a.x > b.x);
    });
    int count = 0;
    int last = -1;
    stack<pair<int, int>> temp;
    for (int l = i; l < j; l++) {
      if (S[l].x > last) {
        count++;
        last = S[l].y;
        temp.push({S[l].x, S[l].y});
      }
    }
    if (count > k) {
      k = count;
      swap(temp, res);
      // cout << S[i].val << '\n';
    }
  }

  cout << k << '\n';
  while (!res.empty()) {
    cout << res.top().first << ' ' << res.top().second << '\n';
    res.pop();
  }

  return 0;
}
