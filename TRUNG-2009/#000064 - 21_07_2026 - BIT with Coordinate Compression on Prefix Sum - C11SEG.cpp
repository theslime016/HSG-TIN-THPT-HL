#include <bits/stdc++.h>
using namespace std;

vector<long long> vals;
struct FWT {
  int n;
  vector<long long> data;
  FWT(int n) {
    this->n = n;
    data.assign(n + 1, 0);
  }

  int rindex(long long x) {
    return lower_bound(vals.begin(), vals.end(), x) - vals.begin() + 1;
  }

  void process(int index, long long value) {
    for (; index <= n; index += index & -index) {
      data[index] += value;
    }
  }

  long long fetch(int index) {
    long long pref = 0;
    for (; index > 0; index -= index & -index) {
      pref += data[index];
    }
    return pref;
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  freopen("input.inp", "r", stdin);
  freopen("output.ans", "w", stdout);

  int n;
  cin >> n;
  long long l, r;
  cin >> l >> r;
  vals.reserve(3 * n);
  vals.push_back(0);
  // vals.push_back(-l);
  // vals.push_back(-r);

  vector<long long> pref(n + 1, 0);
  for (int i = 1; i <= n; i++) {
    long long temp;
    cin >> temp;
    pref[i] = pref[i - 1] + temp;
    vals.push_back(pref[i]);
    vals.push_back(pref[i] - l);
    vals.push_back(pref[i] - r);
  }

  // for (int i = 0; i < (int)pref.size(); i++)
  //   cout << pref[i] << ' ';
  // cout << '\n';

  sort(vals.begin(), vals.end());
  vals.erase(unique(vals.begin(), vals.end()), vals.end());

  // for (int i = 0; i < (int)vals.size(); i++)
  //   cout << vals[i] << ' ';
  // cout << '\n';

  FWT BIT(vals.size());
  BIT.process(BIT.rindex(0), 1);
  long long res = 0;
  for (int i = 1; i <= n; i++) {
    res += BIT.fetch(BIT.rindex(pref[i] - l)) -
           BIT.fetch(BIT.rindex(pref[i] - r) - 1);
    BIT.process(BIT.rindex(pref[i]), 1);
  }

  cout << res;

  return 0;
}
