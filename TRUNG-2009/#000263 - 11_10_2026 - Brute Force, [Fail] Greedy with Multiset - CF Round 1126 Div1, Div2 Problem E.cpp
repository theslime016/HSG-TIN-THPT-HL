#include <bits/stdc++.h>
using namespace std;
#define _debug 1

const int maxn = 2e5 + 5;
const int inf = 2e9;
int best_k = inf;

void make_test(multiset<int> s, int k) {

#if _debug == 1
  cout << "START" << ' ' << k << '\n';
  for (const int& x : s) cout << x << ' ';
  cout << '\n';
#endif // _debug

  while (!s.empty() && k >= *(s.begin())) {
    k++;
    s.erase(s.begin());
  }

#if _debug == 1
  cout << "STOP" << ' ' << k << '\n';
  for (const int &x : s) cout << x << ' ';
  cout << '\n';
  cout << '\n';
#endif

  if (s.empty()) {
    best_k = min(best_k, k);
#if _debug == 1
    cerr << k << '\n';
#endif // _debug
    return;
  }

  for (auto it = s.begin(); it != s.end(); it++) {
    multiset<int> new_set = s;
    new_set.erase(new_set.find(*it));
    if (*it > k) {
      int val = ((*it)+1)/2;
      new_set.insert(val);
      new_set.insert(val);
    }
    make_test(new_set, k+1);
  }
}

void make_dfs(int val, int& k) {
  if (val <= k) {
    k++;
    return;
  }

  k++;
  make_dfs((val+1)/2, k);
  make_dfs((val+1)/2, k);
}

int make_A(multiset<int> s, int k) {
  while (!s.empty()) {
    while (!s.empty() && k >= (*s.begin())) {
      k++;
      s.erase(s.begin());
    }

    if (!s.empty()) {
      k++;
      long long val = ((*(--s.end()))+1)/2;
      s.erase((--s.end()));
      s.insert(val);
      s.insert(val);
    }
  }
  return k;
}

int make_B(multiset<int> s, int k) {
  while (!s.empty()) {
    while (!s.empty() && k >= (*s.begin())) {
      k++;
      s.erase(s.begin());
    }

    if (!s.empty()) {
      k++;
      auto it = s.begin();
      while (*it == 1 && (++it) != s.end()) {
      }
      if (it == s.end()) it--;
      long long val = (*(it)+1)/2;
      s.erase(it);
      s.insert(val);
      s.insert(val);
    }
  }
  return k;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);

#if _debug == 1
  freopen("input.inp", "r", stdin);
#elif _debug == 2
  freopen("input.inp", "r", stdin);
  freopen("output.ans", "w", stdout);
#else

#endif // _debug

  int t;
  cin >> t;
  for (int tt = 1; tt <= t; tt++) {
    int n, k;
    cin >> n >> k;

    multiset<int> s;
    for (int i = 1; i <= n; i++) {
      int x;
      cin >> x;
      s.insert(x);
    }

    //make_test(s, k);
    //cout << best_k - k << '\n';

#if _debug == 1
    best_k = inf;
    make_test(s, k);
    int res1 = best_k;
    int res2 = min(make_A(s, k), make_B(s, k));
    if (res1 != res2) {
      cerr << "TEST" << tt << "!!!!" << '\n';
      cerr << res1 << ' ' << res2 << '\n';
      cerr << k << '\n';
      for (const int& x : s) cerr << x << ' ';
      cerr << '\n';
      return 0;
    } else {
      cerr << "TEST" << tt << "+++" << '\n';
    }

#endif // _debug

#if _debug != 1
    best_k = inf;
    make_test(s, k);
    cout << best_k - k << '\n';
    //cout << min(make_A(s, k), make_B(s, k)) - k << '\n';
#endif // _debug
  }
}
