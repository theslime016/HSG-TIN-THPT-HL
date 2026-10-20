#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

typedef tree<int, int, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_map;

#define _debug 0

#if _debug == 1
#define debug(x) cerr << #x << ':' << (x) << ' ';
#define newline cerr << '\n';

#else
#define debug(x)
#define newline

#endif // _debug

long long solve_subtask2(const vector<int>& X) {
  int n = X.size();
  vector<int> dest;
  int index = 0;
  int mid = n/2;
  dest.reserve(mid+1);
  if (n%2 == 1) dest.push_back(0);
  while (index < mid) {
    dest.push_back(-X[index]);
    index++;
  }

  long long res = 0;
  int dest_index = 0;
  sort(dest.begin(), dest.end());
  while (index < n) {
    res += abs((long long)dest[dest_index] - X[index]);
    index++;
    dest_index++;
  }

  return res;
}

long long get_cost(vector<int> X, vector<int> P) {
  int n = X.size();
  int m = P.size();

  if (n == m) { /// subtask 1
    ordered_map omp;
    for (int a : X) {
      omp[a]++;
    }

    for (const auto& a : omp) {
      if (a.second != omp[-a.first]) return -1;
    }
    return 0;
  }

  if (m == 0) { /// substask 2
    return solve_subtask2(X);
  }

  /// rest

  /*
  vector<bool> mark(n, false);
  for (int i = 0; i < m; i++) {
    mark[ P[i] ] = true;
    omp[X[P[i]]]++;
  }

  for (int i = 0; i < m; i++) {
    if (omp[-X[P[i]]] > 0) {
      int cnt_pair = abs(omp[X[P[i]]] - omp[-X[P[i]]]);
      omp[X[P[i]]] -= cnt_pair;
      omp[-X[P[i]]] -= cnt_pair;
    }
  }

  vector<int> dest; /// index
  for (int i = 0; i < m; i++) {
    for (int j = 1; j <= omp[X[P[i]]]; j++) {
      dest.push_back(P[i]);
    }
  }
  */

  vector<bool> mark(n, false);
  vector<pair<int, int>> comp;
  comp.reserve(m);
  for (int i = 0; i < m; i++) {
    mark[P[i]] = true;
    if (!comp.empty() && X[comp.back().first] == X[P[i]]) comp.back().second++;
    else comp.push_back({P[i], 1});
  }

  int l = 0, r = comp.size() - 1;
  int req = m;
  while (l < r) {
    if (X[comp[l].first] == -X[comp[r].second]) {
      int diff = abs(comp[l].second - comp[r].second);
      comp[l].second -= diff;
      comp[r].second -= diff;
      l++;
      r--;

      req -= (diff << 1);

    } else if (abs(X[comp[l].first]) < abs(X[comp[r].first])) {
      r--;
    } else {
      l++;
    }
  }

  if (n - m - req < 0) return -1;

  int new_n = comp.size();
  vector<int> dest;
  dest.reserve(req);
  for (int i = 0; i < new_n; i++) {
    for (int j = 1; j <= comp[i].second; j++) {
      dest.push_back(comp[i].first);
    }
  }

  vector<int> cand, rem_cand;
  cand.reserve(req);
  rem_cand.reserve(n - m - req);
  int temp_req = req;
  for (int i = 0; i < n; i++) {
    if (mark[i]) continue;

    if (temp_req > 0) {
      cand.push_back(i);
      temp_req--;
    } else {
      rem_cand.push_back(i);
    }
  }

  long long res = 0;
  sort(dest.begin(), dest.end(), [&](int a, int b) {
    return -X[a] < -X[b];
  });

  for (int a : dest) debug(a);
  newline;
  for (int b : cand) debug(b);
  newline;

  for (int i = 0; i < req; i++) {
    res += abs(-X[dest[i]] - X[cand[i]]);
  }

  if (rem_cand.size() > 0) res += solve_subtask2(rem_cand);

  return res;

  /*
  int req = dest.size();
  int rem = n - m - req;

  if (rem < 0) return -1;

  vector<int> cand; /// index
  vector<int> rem_cand; /// index
  for (int i = 0; i < n; i++) {
    if (mark[i]) continue;

    if (req > 0) {
      cand.push_back(i);
      req--;
    } else rem_cand.push_back(i);
  }

  sort(dest.begin(), dest.end(), [&](int x, int y) {
    return -X[x] < -X[y];
  });

  long long res = 0;
  for (int i = 0; i < m; i++) {
    res += abs((long long)-X[ dest[i] ] - X[cand[i]]);
  }

  if (rem_cand.size() > 0) res += solve_subtask2(rem_cand);


  return res;

  */
}

#if _debug == 1

void test() {
  int n, m;
  cin >> n >> m;
  vector<int> x, p;
  x.reserve(n);
  p.reserve(m);
  for (int i = 1; i <= n; i++) {
    int temp;
    cin >> temp;
    x.push_back(temp);
  }

  for (int i = 1; i <= m; i++) {
    int temp;
    cin >> temp;
    p.push_back(temp);
  }

  cout << (get_cost(x, p));
}

int main() {
  cin.tie(0)->sync_with_stdio(0);

  freopen("input.inp", "r", stdin);

  test();

}

#endif
