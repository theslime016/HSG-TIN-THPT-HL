#include <bits/stdc++.h>
using namespace std;

const int maxn = 2e5 + 5;
const int inf = 1e9;
int A[maxn];
pair<int, int> B[maxn];
int n;

bool verify() {
  stack<int> s; // index
  int ptr = 1;
  int pair1 = 0, pairn = 0;
  for (int i = 1; i <= n; i++) {
    while (!s.empty() && A[s.top()] < A[i]) s.pop();
    if (!s.empty() && A[s.top()] == A[i]) {
      B[ptr++] = {s.top(), i};
      if (s.top() == 1) pair1 = 1;
      if (i == n) pairn = 1;
    } else {
      s.push(i);
    }
  }

  sort(B + 1, B + ptr);
  int best_l = inf, best_r = 0;
  int ok = 1;
  for (int i = 1; i < ptr - 1; i++) {
    if (B[i].second + 1 < B[i+1].first) {
      ok = false;
      break;
    } else {
      best_l = min(best_l, B[i].first);
      best_r = max(best_r, B[i].second);
    }
  }

  best_l = min(best_l, B[1].first);
  best_r = max(best_r, B[1].second);
  best_l = min(best_l, B[ptr-1].first);
  best_r = max(best_r, B[ptr-1].second);
  return ok && best_l == 1 && best_r == n;
}

bool test(int index, int old_val, int new_val) {
  A[index] = new_val;
  if (verify()) {
    cout << 1 << '\n';
    cout << index << ' ' << new_val << '\n';
    return true;
  }
  A[index] = old_val;
  return false;
}

#define _debug 0
int main() {
  cin.tie(0)->sync_with_stdio(0);

#if _debug == 1
  freopen("input.inp", "r", stdin);
#else

#endif // _debug

  int t;
  cin >> t;
  while (t--) {
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> A[i];

    if (verify()) {
      cout << 0 << '\n';
      continue;
    }

    pair<int, long long> object_1 = {-1, -1LL}, object_n = {-1, -1LL}; // index - old_val
    int head = max(A[1], A[n]);
    for (int i = 1; i <= n; i++) {
      if (A[i] > head) {
        if (object_1.first == -1) object_1 = {i, A[i]};
        object_n = {i, A[i]};
      }
    }

    if (object_1.first == -1) {
      cout << 1 << '\n';
      cout << (&min(A[1], A[n]) - &A[0]) << ' ' << max(A[1], A[n]) << '\n';
      continue;
    }

    if (test(object_1.first, object_1.second, A[1])) continue;
    if (test(object_1.first, object_1.second, A[n])) continue;
    if (test(object_n.first, object_n.second, A[1])) continue;
    if (test(object_n.first, object_n.second, A[n])) continue;

    if (test(1, A[1], object_1.second)) continue;
    if (test(1, A[1], object_n.second)) continue;
    if (test(n, A[n], object_1.second)) continue;
    if (test(n, A[n], object_n.second)) continue;

    cout << 2 << '\n';
    cout << 1 << ' ' << inf << '\n';
    cout << n << ' ' << inf << '\n';
  }
}
