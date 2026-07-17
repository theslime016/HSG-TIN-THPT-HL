#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int n, k;
  cin >> n >> k;
  vector<long long> A(n);
  long long l = 0, r = 0;
  for (int i = 0; i < n; i++) {
    cin >> A[i];
    r += A[i];
  }

  auto f = [&](long long a) -> bool {
    int d = k;
    long long current = 0;
    for (int i = 0; i < n && d >= 0; i++) {
      if (A[i] > a)
        return false;
      if (current == 0) {
        d--;
        current += A[i];
      } else if (current + A[i] > a) {
        d--;
        current = A[i];
      } else {
        current += A[i];
      }
    }
    return d >= 0;
  };

  r++;
  for (long long d = r - l; d > 0; d /= 2) {
    while (r - d >= l && f(r - d))
      r -= d;
  }
  cout << r;

  return 0;
}




#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int n, k;
  cin >> n >> k;
  vector<pair<long long, long>> A(n);
  for (int i = 0; i < n; i++) {
    cin >> A[i].first >> A[i].second;
  }

  sort(A.begin(), A.end(),
       [](auto &x, auto &y) { return x.second < y.second; });
  multiset<int> rel;
  for (int i = 0; i < k; i++) {
    rel.insert(0);
  }
  long long mov = 0;
  for (const auto &x : A) {
    auto it = rel.lower_bound(x.first);
    if (it == rel.end() || *it > x.first) {
      if (it != rel.begin())
        it--;
      else
        continue;
    }
    rel.erase(it);
    rel.insert(x.second);
    mov++;
  }
  cout << mov;

  return 0;
}
