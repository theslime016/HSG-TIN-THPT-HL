#include <bits/stdc++.h>
using namespace std;

const int maxn = 2e5 + 10;
long long S[maxn]{};

auto combine = [](long long x, long long y) { return min(x, y); };
const long long ninf = -1e18;
struct TWDQ {
  stack<pair<long long, long long>> s1, s2;
  long long get() {
    if (s1.empty() && s2.empty())
      return ninf;
    else if (s1.empty() || s2.empty())
      return s1.empty() ? s2.top().second : s1.top().second;
    else
      return combine(s1.top().second, s2.top().second);
  }

  void enqueue(long long val) {
    long long second = s1.empty() ? val : combine(val, s1.top().second);
    s1.push({val, second});
  }

  void dequeue() {
    if (s1.empty() && s2.empty())
      return;
    if (s2.empty()) {
      while (!s1.empty()) {
        long long val = s1.top().first;
        long long second = s2.empty() ? val : combine(val, s2.top().second);
        s2.push({val, second});
        s1.pop();
      }
    }
    s2.pop();
  }
};

int main() {
  cin.tie(0)->sync_with_stdio(false);

  int n, a, b;
  cin >> n >> a >> b;
  for (int i = 1; i <= n; i++) {
    cin >> S[i];
    S[i] += S[i - 1];
  }

  TWDQ dql;
  long long res = ninf;
  for (int i = 1; i <= n; i++) {
    if (i >= a) {
      dql.enqueue(S[i - a]);
    }

    if (i > b) {
      dql.dequeue();
    }

    if (i >= a) {
      res = max(res, S[i] - dql.get());
    }
  }

  cout << res;

  return 0;
}
