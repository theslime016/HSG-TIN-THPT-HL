#include <bits/stdc++.h>
using namespace std;

#define _debug 0

#if _debug == 1
void logout() {
  cerr << endl;
}
template<typename H, typename... T>
void logout(H h, T... t) {
  cerr << h << ", ";
  logout(t...);
}
#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:" << endl, logout(__VA_ARGS__)
#define debugtitle cerr << __PRETTY_FUNCTION__ << " line: " << __LINE__ << endl
#define newline cerr << endl

#else
#define debug(...) (void(0))
#define debugtitle (void(0))
#define newline (void(0))

#endif // _debug

const int maxn = 2e5 + 5;
const int maxlog = 20;
int n, k;

long long A[maxn];
vector<int> adj[maxn]; /// index - value

int timein[maxn], timeout[maxn];
int timer = 0;

int up[maxn][maxlog];
long long table[maxn][maxlog];

void make_lca(int index, int parent) {
  up[index][0] = parent;
  table[index][0] = max(A[index], A[parent]);
  timein[index] = ++timer;

  for (int exp = 1; exp < maxlog; exp++) {
    up[index][exp] = up[ up[index][exp - 1] ][exp-1];
    table[index][exp] = max(table[index][exp-1], table[ up[index][exp-1] ][exp-1]);
  }

  for (const auto& x : adj[index]) {
    if (x == parent)
      continue;
    make_lca(x, index);
  }
  timeout[index] = timer;
}

bool is_lca(int a, int b) {
  return timein[a] <= timein[b] && timeout[a] >= timeout[b];
}

long long walk_lca(int a, int b) {
  if (a == b)
    return A[a];

  long long res = 0;
  for (int exp = maxlog - 1; exp >= 0; exp--) {
    int index = up[a][exp];
    if (index != 0 && !is_lca(index, b)) {
      res = max(res, table[a][exp]);
      a = index;
    }
  }

  for (int exp = maxlog - 1; exp >= 0; exp--) {
    int index = up[b][exp];
    if (index != 0 && !is_lca(index, a)) {
      res = max(res, table[b][exp]);
      b = index;
    }
  }

  if (up[a][0] != 0 && !is_lca(a, b))
    res = max(res, table[a][0]);
  if (up[b][0] != 0 && !is_lca(b, a))
    res = max(res, table[b][0]);
  return res;
}

pair<int, int> task[maxn]; /// index -> index
long long profit[maxn];

long long dp[maxn]; /// max value with a task end at index

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

#if _debug == 1
  freopen("input.inp", "r", stdin);

#elif _debug == 2
  freopen("input.inp", "r", stdin);

#else
  freopen("SHIP.INP", "r", stdin);
  freopen("SHIP.OUT", "w", stdout);

#endif // _debug

  cin >> n;
  for (int i = 1; i <= n; i++)
    cin >> A[i];
  for (int i = 1; i < n; i++) {
    int a, b;
    cin >> a >> b;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }

  make_lca(1, 0);

  cin >> k;
  for (int i = 1; i <= k; i++) {
    cin >> task[i].first >> task[i].second;
    profit[i] = walk_lca(task[i].first, task[i].second);
  }

  long long res = 0;
  memset(dp, -1, sizeof dp);
  dp[1] = 0;
  for (int i = 1; i <= k; i++) {
    int start = task[i].first;
    int end = task[i].second;

    if (dp[start] != -1) {
      dp[end] = max(dp[end], dp[start] + profit[i]);
    }
    res = max(dp[end], res);
  }

//  #if _debug == 1
//  cerr << "profit: ";
//  newline;
//  for (int i = 1; i <= k; i++) cerr << profit[i] << ' ';
//  newline;
//
//  cerr << "dp: ";
//  newline;
//  for (int i = 1; i <= n; i++) cerr << dp[i] << ' ';
//  newline;
//
//  for (int i = 1; i <= k; i++) {
//    debug(i, task[i].first, task[i].second);
//  }
//
//  #endif // _debug

  cout << res;
}
