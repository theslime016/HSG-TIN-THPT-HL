#include <bits/stdc++.h>
using namespace std;

#ifndef NDEBUG
#define NDEBUG
#endif

#define all(x) x.begin(), x.end()
typedef pair<int, int> pairll;
const long long INF = 1e9;
struct FWT {
  int n;
  vector<pairll> data;
  void reset(int n) {
    this->n = n;
    data.assign(n + 1, {-INF, INF});
  }

  void process(int index, const pairll &val) {
    for (; index <= n; index += index & -index) {
      data[index].first = max(data[index].first, val.first);
      data[index].second = min(data[index].second, val.second);
    }
  }

  pairll fetch(int index) {
    pairll pref = {-INF, INF};
    for (; index > 0; index -= index & -index) {
      pref.first = max(data[index].first, pref.first);
      pref.second = min(data[index].second, pref.second);
    }
    return pref;
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int n, k;
  cin >> n >> k;
  vector<long long> pref(n + 1, 0);
  long long sABS = 0;
  for (int i = 1; i <= n; i++) {
    long long x;
    cin >> x;
    sABS += abs(x);
    pref[i] = pref[i - 1] + x;
  }

  vector<long long> vals = pref;
  sort(all(vals), greater<long long>());
  vals.erase(unique(all(vals)), vals.end());

  auto search = [&](long long x) {
    return upper_bound(all(vals), x, greater<long long>()) - vals.begin();
  };

  vector<int> jump(n + 1);
  for (int i = 0; i <= n; i++) {
    jump[i] = search(pref[i]);
  }

  // for (auto a : pref)
  //   cout << a << ' ';
  // cout << '\n';

  // for (auto a : vals)
  //   cout << a << ' ';
  // cout << '\n';

  // for (auto &b : jump)
  //   cout << b << ' ';
  // cout << '\n';

  FWT BIT;
  auto check = [&](long long m) mutable -> bool {
    BIT.reset(vals.size());
    BIT.process(jump[0], {0, 0});

    vector<pairll> dp(pref.size(), {-INF, INF});
    for (int i = 1; i <= n; i++) {
      int id = search(pref[i] - m);
      pairll prev_dp = BIT.fetch(id);
      if (prev_dp.first != -INF && prev_dp.second != INF) {
        dp[i].first = prev_dp.first + 1;
        dp[i].second = prev_dp.second + 1;
        BIT.process(jump[i], dp[i]);
      }
      // cout << id << ' ';
    }
    // cout << '\n';
    // for (auto &s : dp)
    //   cout << s.first << ' ' << s.second << '\n';
    // cout << '\n';
    return dp[n].first >= k && dp[n].second <= k;
  };

  long long L = -sABS, R = sABS;
  for (long long D = R - L; D > 0; D /= 2) {
    while (R - D >= L && check(R - D))
      R -= D;
  }

  cout << R;

  return 0;
}
