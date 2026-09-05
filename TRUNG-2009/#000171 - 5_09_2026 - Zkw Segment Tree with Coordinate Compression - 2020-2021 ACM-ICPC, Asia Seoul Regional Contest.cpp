#include <bits/stdc++.h>
using namespace std;

const int maxn = 2e5 + 5;
const long long inf = 1e18;
const int padding = (1 << 21);

long long segment[padding * 2]; // index - sorted sum
// zkw 0 index
// max - sum index
long long A[maxn];

inline void update(int index, const long long &val) {
  index += padding;
  segment[index] = max(segment[index], val);
  for (index >>= 1; index > 0; index >>= 1) {
    segment[index] = max(segment[index << 1], segment[index << 1 | 1]);
  }
}

int fetch(int index, int l, int r, int target, int limit) {
  if (segment[index] < limit || l > target)
    return -1;

  if (l == r)
    return l;

  int mid = l + (r - l) / 2;
  int res = -1;
  if (mid + 1 <= target) {
    res = fetch(index << 1 | 1, mid + 1, r, target, limit);
  }

  if (res == -1)
    res = fetch(index << 1, l, mid, target, limit);
  return res;
}

struct query {
  int limit;
  long long k;
  int rank;
};
vector<query> task[maxn];
long long res[maxn];

int main() {
  cin.tie(0)->sync_with_stdio(0);

  memset(segment, -1, sizeof segment);

  int n, m;
  cin >> n >> m;

  for (int i = 1; i <= n; i++)
    cin >> A[i];

  vector<long long> proc;
  proc.reserve(n * (n + 1) / 2);
  for (int i = 1; i <= n; i++) {
    long long sum = 0;
    for (int j = i; j <= n; j++) {
      sum += A[j];
      proc.push_back(sum);
    }
  }

  sort(proc.begin(), proc.end());
  proc.erase(unique(proc.begin(), proc.end()), proc.end());

  auto get_index = [&](const long long &val) {
    return upper_bound(proc.begin(), proc.end(), val) - proc.begin() - 1;
  };

  for (int i = 1; i <= m; i++) {
    int l, r;
    long long k;
    cin >> l >> r >> k;
    task[r].push_back({l, k, i});
  }

  for (int R = 1; R <= n; R++) {
    long long sum = 0;
    for (int L = R; L >= 1; L--) {
      sum += A[L];
      int rindex = get_index(sum);
      update(rindex, L);
    }

    for (const auto &s : task[R]) {
      res[s.rank] = -inf;
      int target = get_index(s.k);
      if (target == -1)
        continue;

      int resindex = fetch(1, 0, padding - 1, target, s.limit);
      if (resindex != -1)
        res[s.rank] = proc[resindex];
    }
  }

  for (int i = 1; i <= m; i++) {
    if (res[i] == -inf)
      cout << "NONE" << '\n';
    else
      cout << res[i] << '\n';
  }
}
