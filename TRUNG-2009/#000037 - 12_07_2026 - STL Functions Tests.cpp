#include <bits/stdc++.h>
using namespace std;

#ifndef NDEBUG
#define NDEBUG
#endif

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  vector<long long> a = {1, 2, 2, 2, 3, 3, 2, 4, 5};
  sort(a.begin(), a.end());
  a.erase(unique(a.begin(), a.end()), a.end());
  assert(a.size() > 0);
  for (int i : a)
    cout << i << ' ';
  cout << '\n';
  long long sum = accumulate(a.begin(), a.end(), 0LL);
  cout << sum << '\n';
  partial_sum(a.begin(), a.end(), a.begin());
  for (int i : a)
    cout << i << ' ';
  cout << '\n';

  int n;
  cin >> n;
  vector<int> per(n);
  iota(per.begin(), per.end(), 1);
  do {
    for (int x : per)
      cout << x << ' ';
    cout << '\n';
  } while (next_permutation(per.begin(), per.end()));

  return 0;
}
