#include <bits/stdc++.h>
using namespace std;

#define _debug 0

#if _debug == 1
#define debug(x) cerr << #x << ':' << (x) << ' ';
#define debugn(x) cerr << #x << ':' << (x) << '\n';
#define newline cerr << '\n';

#else
#define debug(x)
#define debugn(x)
#define newline

#endif // _debug

const int maxn = 2e5 + 5;
const long long inf = 1e18;
const int padding = 262144;
const int h = 18;
long long A[maxn];
long long dp[maxn];
long long segment[maxn << 2];
long long lazy[maxn << 2];

void push_down(int index) {
  for (int i = 1, deg = h; i < padding; i <<= 1, deg--) {
    int rindex = i | (index >> deg);
    if (lazy[rindex]) {
      segment[rindex << 1] += lazy[rindex];
      segment[rindex << 1 | 1] += lazy[rindex];

      lazy[rindex << 1] += lazy[rindex];
      lazy[rindex << 1 | 1] += lazy[rindex];

      lazy[rindex] = 0;
    }
  }
}

void push_up(int index) {
  for (index >>= 1; index > 0; index >>= 1) {
    segment[index] = min(segment[index << 1], segment[index << 1 | 1]);
  }
}

void point_update(int index, const long long& val) {
  index += padding;
  push_down(index);
  segment[index] = val;
  push_up(index);
}

void range_update(int l, int r, const long long& val) {
  if (l > r) return;
  int s = padding + l - 1;
  int t = padding + r + 1;
  push_down(s);
  push_down(t);

  int os = s;
  int ot = t;
  for (; s ^ t ^ 1; s >>= 1, t >>= 1) {
    if (~s & 1) {
      segment[s ^ 1] += val;
      lazy[s ^ 1] += val;
    }
    if (t & 1) {
      segment[t ^ 1] += val;
      lazy[t ^ 1] += val;
    }
  }

  push_up(os);
  push_up(ot);
}

long long fetch(int l, int r) {
  if (l > r) return inf;
  int s = padding + l - 1;
  int t = padding + r + 1;
  push_down(s);
  push_down(t);

  long long res = inf;
  for (; s ^ t ^ 1; s >>= 1, t >>= 1) {
    if (~s & 1) {
      res = min(res, segment[s ^ 1]);
    }
    if (t & 1) {
      res = min(res, segment[t ^ 1]);
    }
  }

  return res;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);

#if _debug == 1
  freopen("input.inp", "r", stdin);

#elif _debug == 2
freopen("input.inp", "r", stdin);

#else

#endif // _debug

  fill_n(segment, maxn << 2, inf);

  int n;
  cin >> n;
  for (int i = 1; i <= n; i++) cin >> A[i];

  long long max_val = max(A[1], A[2]);
  long long min_val = min(A[1], A[2]);

  vector<int> maxst, minst;
  for (int i = 1; i <= n; i++) {
    max_val = max(max_val, A[i]);
    min_val = min(min_val, A[i]);
    dp[i] = max_val - min_val;

#if _debug == 1

    cout << "index: " << i << '\n';
    cout << "maxst: " << '\n';
    for (int x : maxst) {
      debug(x);
      debugn(A[x]);
    }

    cout << "minst: " << '\n';
    for (int x : minst) {
      debug(x);
      debugn(A[x]);
    }

#endif // _debug

    while (!maxst.empty() && A[maxst.back()] <= A[i]) {
      long long val = A[i] - A[maxst.back()];
      int ptr1 = maxst.back() - 1;
      maxst.pop_back();
      int ptr2 = maxst.empty() ? 1 : maxst.back();
      range_update(ptr2, ptr1, val);
    }

    while (!minst.empty() && A[minst.back()] >= A[i]) {
      long long val = A[minst.back()] - A[i];
      int ptr1 = minst.back() - 1;
      minst.pop_back();
      int ptr2 = minst.empty() ? 1 : minst.back();
      range_update(ptr2, ptr1, val);
    }

    maxst.push_back(i);
    minst.push_back(i);

    if (i >= 2) {
      dp[i] = min(dp[i], fetch(2, i - 2));
      point_update(i, dp[i]);

      debug(i);
      debug(fetch(2, i - 2));
      debugn(dp[i]);
      newline;
    }
  }

  #if _debug == 1
  for (int i = 1; i <= n; i++) {
    debug(i);
    debugn(dp[i]);
  }
  newline;
  for (int i = 1; i <= n; i++) {
    debug(i);
    debug(segment[i + padding]);
    newline;
  }
  #endif // _debug

  cout << dp[n];
}
