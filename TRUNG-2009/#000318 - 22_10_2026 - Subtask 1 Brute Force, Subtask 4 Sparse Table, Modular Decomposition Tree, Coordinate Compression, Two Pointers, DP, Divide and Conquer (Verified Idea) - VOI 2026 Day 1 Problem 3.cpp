#include <bits/stdc++.h>
using namespace std;

#define _debug 1

#if _debug == 1
#define debug(x) cerr << #x << ':' << (x) << ' ';
#define newline cerr << '\n';

#else
#define debug(x)
#define newline

#endif // _debug

int n, q;
const int maxn = 3e5 + 5;
long long A[maxn];

namespace bruteforce {

map<long long, int> cnt;
bool check(int l, int r) {
  map<long long, int> current;
  for (int i = l; i <= r; i++) {
    current[ A[i] ]++;
  }

  for (const auto& x : current) {
    if (cnt[x.first] != x.second) return false;
  }
  return true;
}

void init() {
  for (int i = 1; i <= n; i++) cnt[ A[i] ]++;
}

long long solve(int l, int r) {
  long long res = 0;
  for (int i = l; i <= r; i++) {
    for (int j = i; j <= r; j++) {
      if (check(i, j)) res++;
    }
  }
  return res;
}
}

namespace subtask4 {

map<long long, pair<int, int>> block;
vector<pair<int, int>> range;
map<long long, int> cnt;
bool check(int l, int r) {
  map<long long, int> current;
  for (int i = l; i <= r; i++) {
    current[ A[i] ]++;
  }

  for (const auto& x : current) {
    if (cnt[x.first] != x.second) return false;
  }
  return true;
}

map<long long, pair<int, int>> block;
vector<pair<int, int>> range;
vector<pair<int, int>> comp;
long long calc(int l, int r) {
  long long res = 0;

  for (int i = 1; i <= r; i++) {
    for (int j = i; j <= r; j++) {
      if (check(i, j)) res++;
    }
  }

  return res;
}

void init() {
  for (int i = 1; i <= n; i++) {
    cnt[ A[i] ]++;

    if (block[ A[i] ].first == 0) {
      block[ A[i] ] = {i, i};
    } else {
      block[ A[i] ].first = min(block[ A[i] ].first, i);
      block[ A[i] ].second = max(block[ A[i] ].second, i);
    }
  }

  for (auto it = block.begin(); it != block.end(); it++) {
    range.push_back(it->second);
  }
  sort(range.begin(), range.end());

  debug("SUBTASK4");
  newline;
  for (const pair<int, int> temp : range) {
    debug(temp.first);
    debug(temp.second);
    newline;
  }



}
long long solve() {
  long long res = 0;

  return res;

}

}

int main() {
  cin.tie(0)->sync_with_stdio(0);

#if _debug == 1
  freopen("input.inp", "r", stdin);

#elif _debug == 2
  freopen("input.inp", "r", stdin);

#else
  freopen("POST.INP", "r", stdin);
  freopen("POST.OUT", "w", stdout);

#endif // _debug

  cin >> n >> q;
  for (int i = 1; i <= n; i++) cin >> A[i];

  if (q == 1) {
    int l, r;
    cin >> l >> r;
    if (l == 1 && r == n) {
      subtask4::init();
      cout << subtask4::solve() << '\n';
    } else {
      bruteforce::init();
      cout << bruteforce::solve(l, r) << '\n';
    }
  } else {
    bruteforce::init();
    while (q--) {
      int l, r;
      cin >> l >> r;
      cout << bruteforce::solve(l, r) << '\n';
    }
  }

}
