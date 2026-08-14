#include <bits/stdc++.h>
using namespace std;

// Problem: https://i.postimg.cc/Df6NC2PF/image.png

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n, k;
  cin >> n >> k;

  deque<pair<int, long long>> dq; // index
  long long res = LLONG_MIN;
  for (int i = 1; i <= n; i++) {
    // i-k -> i-1 (last update)
    while (!dq.empty() && dq.front().first < i - k)
      dq.pop_front();

    long long val;
    cin >> val;

    if (!dq.empty() && dq.front().second > 0)
      val += dq.front().second;

    while (!dq.empty() && dq.back().second <= val)
      dq.pop_back();
    dq.push_back({i, val});
    res = max(res, val);
  }
  cout << res;
}
