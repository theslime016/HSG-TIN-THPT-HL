#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

typedef tree<int, int, less<int>, rb_tree_tag,
        tree_order_statistics_node_update> ordered_map;

const int inf = 1e9;
const int maxn = 1e6;
int A[maxn];
pair<int, int> B[maxn];

#define _debug 1
int main() {
  cin.tie(0)->sync_with_stdio(0);

#if _debug == 1
  freopen("input.inp", "r", stdin);
#else

#endif // _debug

  int t;
  cin >> t;
  while (t--) {
    int n;
    cin >> n;

    stack<int> s; // index
    int ptr = 1;
    int pair1 = 0, pairn = 0;
    for (int i = 1; i <= n; i++) {
      cin >> A[i];
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

    if (ok && best_l == 1 && best_r == n) {
      cout << 0 << '\n';
      continue;
    }

    long long head = max(A[1], A[n]);
    long long cnt = 0;
    long long index = -1;
    for (int i = 2; i < n; i++) {
      if (A[i] > head) {
        cnt++;
        index = i;
      }
    }

    if (cnt == 0) {
      cout << (A[1] != A[n]) << '\n';
      if (A[1] != A[n]) cout << (&min(A[1], A[n]) - &A[0]) << ' ' << max(A[1], A[n]) << '\n';
    } else if (cnt == 1 && (A[1] == A[n] || pair1 || pairn)) {
      cout << 1 << '\n';
      if (!pair1) cout << index << ' ' << A[1] << '\n';
      else cout << index << ' ' << A[n] << '\n';
    } else {
      cout << 2 << '\n';
      cout << 1 << ' ' << inf << '\n';
      cout << n << ' ' << inf << '\n';
    }
  }
}
