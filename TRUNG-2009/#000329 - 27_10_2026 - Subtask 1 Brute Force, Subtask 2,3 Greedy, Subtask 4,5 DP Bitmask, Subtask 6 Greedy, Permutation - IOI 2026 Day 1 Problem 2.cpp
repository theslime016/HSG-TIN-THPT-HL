#include <bits/stdc++.h>
using namespace std;

#if defined(__has_include) && __has_include("slime_debug_016.h")
#include "slime_debug_016.h"

#else
#define _debug 0

#endif // defined

/// DEBUG MACRO
#if _debug == 1
#define debug(x) cerr << #x << ':' << (x) << ' ';
#define newline cerr << '\n';

#else
#define debug(x)
#define newline

#endif // _debug


const int maxn = 5e5 + 5;
const long long inf = 1e18;
#define popcount(x) __builtin_popcountll(x)



struct SUBTASK1 { /// SUBTASK 1
  int n, m;
  vector<int> X;
  vector<int> P;
  map<long long, int> mp; // value - cnt

  void init(int n, int m, vector<int>&& X, vector<int>&& P) {
    this->n = n;
    this->m = m;

    this->X = move(X);
    this->P = move(P);
  }

  long long solve() {
    for (int i = 0; i < n; i++) {
      mp[ X[i] ]++;
    }
    for (const auto& x : mp) {
      if (mp[-x.first] != x.second) return -1;
    }
    return 0;
  }

} subtask1;




struct SUBTASK2 { /// SUBTASK 2
  int n;
  int m;
  vector<int> X;
  vector<int> P;

  void init(int n, int m, vector<int>&& X, vector<int>&& P) {
    this->n = n;
    this->m = m;
    this->X = move(X);
    this->P = move(P);
  }

  long long solve() {
    sort(X.begin(), X.end());

    long long res = 0;

    int l = 0, r = n - 1;
    while (l <= r) {
      if (l == r) {
        res += abs(X[l]);
        break;
      }

      res += abs(X[r] + X[l]);

      l++;
      r--;
    }

    return res;
  }

} subtask2;




struct SUBTASK3 { /// SUBTASK 3
  int n;
  int m;
  vector<int> X;
  vector<int> P;
  vector<int> dest, cand;
  vector<int> mark;

  void init(int n, int m, vector<int>&& X, vector<int>&& P) {
    this->n = n;
    this->m = m;

    this->X = move(X);
    this->P = move(P);
    this->dest.reserve(n/2 + 1);
    this->cand.reserve(n/2 + 1);
    this->mark.assign(n+1, 0);
  }

  long long solve() {
    if ((m << 1) > n) return -1;

    for (int i = 0; i < m; i++) {
      mark[ P[i] ] = 1;
    }

    int req = n/2 - m;
    for (int i = 0; i < n; i++) {
      if (mark[i]) {
        dest.push_back(-X[i]);
        continue;
      }

      if (req > 0) {
        dest.push_back(-X[i]);
        req--;
      } else {
        cand.push_back(X[i]);
      }
    }

    if (dest.size() < cand.size()) dest.push_back(0);
    sort(dest.begin(), dest.end());
    sort(cand.begin(), cand.end());

    long long res = 0;
    for (int i = 0; i < dest.size(); i++) {
      res += abs(dest[i] - cand[i]);
    }
    return res;
  }

} subtask3;


struct SUBTASK45 { /// SUBTASK 4,5
  int n, m;
  vector<int> X, P;
  vector<int> mark;
  vector<long long> dp;

  void init(int n, int m, vector<int>&& X, vector<int>&& P) {
    this->n = n;
    this->m = m;

    this->X = move(X);
    this->P = move(P);
    this->mark.assign(n, 0);
    this->dp.assign(1LL << n, -1);
  }

  long long cost_pair(int i, int j) {
    if (mark[i] && mark[j]) {
      if (X[i] == -X[j]) return 0;
      else return inf;
    }
    return abs(X[i] + X[j]);
  }

  long long cost_single(int i) {
    if (mark[i]) {
      if (X[i] == 0) return 0;
      else return inf;
    } else return abs(X[i]);
  }

  long long make_dp(int mask) {
    if (dp[mask] != -1) return dp[mask];
    if (popcount(mask) == n) return 0;

    int index = 0;
    for (; index < n; index++) {
      if ((mask >> index) & 1) continue;
      break;
    }

    long long res = inf;
    for (int nxt = index + 1; nxt < n; nxt++) {
      if ((mask >> nxt) & 1) continue;


      long long cost = cost_pair(index, nxt);
      if (cost == inf) continue;

      int new_mask = mask | (1LL << index) | (1LL << nxt);
      long long next_cost = make_dp(new_mask);


      if (next_cost == inf) continue;

      res = min(res, cost + next_cost);
    }

    int rem = n - popcount(mask);
    if (rem%2 == 1) {
      long long cost = cost_single(index);
      if (cost != inf) {
        int new_mask = mask | (1LL << index);
        long long next_cost = make_dp(new_mask);
        if (next_cost != inf) res = min(res, cost + next_cost);
      }
    }

    return dp[mask] = res;
  }

  long long solve() {
    for (int i = 0; i < m; i++) {
      mark[ P[i] ] = 1;
    }

    long long res = make_dp(0);
    if (res == inf) return -1;
    else return res;
  }
} subtask45;


struct SUBTASK6 { /// SUBTASK 6
  int n;
  int m;
  vector<int> red; // fixed
  vector<int> blue;

  void init(int n, int m, vector<int>&& X, vector<int>&& P) {
    map<int, int> cnt;
    vector<int> color(n, 0);
    for (int i = 0; i < m; i++) {
      cnt[ X[ P[i] ] ]++;
      color[ P[i] ] = 1;
    }

    for (auto& x : cnt) {
      if (x.first > 0) break;
      if (x.first == 0) {
        x.second = 0;
        continue;
      }

      int rem = min(x.second, cnt[ -x.first ]);
      x.second -= rem;
      cnt[ -x.first ] -= rem;
    }

    for (auto& x : cnt) {
      while (x.second--) {
        red.push_back(x.first);
      }
    }

    for (int i = 0; i < n; i++) {
      if (!color[i]) blue.push_back(X[i]);
    }

    this->n = red.size();
    this->m = blue.size();
  }

  long long solve() {
    if (n > m) return -1;

    vector<int> mark(m, 0);
    fill(mark.end() - n, mark.end(), 1);

    sort(red.begin(), red.end());
    sort(blue.begin(), blue.end());

    long long res = inf;

    do {
      vector<int> red_blue, blue_blue;
      for (int i = 0; i < m; i++) {
        if (mark[i]) {
          red_blue.push_back(blue[i]);
        } else {
          blue_blue.push_back(blue[i]);
        }
      }

      long long local = 0;
      for (int i = 0; i < n; i++) {
        local += abs(red[i] + red_blue[n - i - 1]);
      }

      int i = 0;
      int j = m - n - 1;
      while (i < j) {
        local += abs(blue_blue[i] + blue_blue[j]);
        i++;
        j--;
      }
      if (i == j) local += abs(blue_blue[i]);

      res = min(res, local);

    } while (next_permutation(mark.begin(), mark.end()));

    if (res == inf) return -1;
    else return res;
  }

} subtask6;

long long get_cost(vector<int> X, vector<int> P) { /// MAIN
  int n = X.size();
  int m = P.size();


  if (n == m) {
    debug("SUBTASK1");
    newline;

    subtask1.init(n, m, move(X), move(P));
    return subtask1.solve();
  }

  if (m == 0) {
    debug("SUBTASK2");
    newline;

    subtask2.init(n, m, move(X), move(P));
    return subtask2.solve();
  }

  bool flag_subtask3 = true;
  for (int temp : P) {
    if (X[temp] >= 0) flag_subtask3 = false;
  }

  if (flag_subtask3) {
    debug("SUBTASK3");
    newline;

    subtask3.init(n, m, move(X), move(P));
    return subtask3.solve();
  }

  if (n <= 19) {
    debug("SUBTASK45");
    newline;

    subtask45.init(n, m, move(X), move(P));
    return subtask45.solve();
  }

  if (n <= 32) {
    debug("SUBTASK6");
    newline;

    subtask6.init(n, m, move(X), move(P));
    return subtask6.solve();
  }

  return -1;
}


#if _debug == 1

void test() {
  int n, m;
  cin >> n >> m;
  vector<int> X(n);
  vector<int> P(m);
  for (int i = 0; i < n; i++) cin >> X[i];
  for (int i = 0; i < m; i++) cin >> P[i];

  cout << get_cost(X, P);
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  freopen("input.inp", "r", stdin);
  test();


}
#endif // _debug
