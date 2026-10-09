#include <bits/stdc++.h>
using namespace std;

const int inf = 1e7 + 5;

struct POINT {
  int l, r;
  mutable int index;
  bool operator<(const POINT& other) const {
    return this->l < other.l;
  }
};

set<POINT> s;

auto split(int pos) {
  auto it = s.lower_bound({pos, 0, 0});
  if (it != s.end() && it->l == pos) return it;

  it--;
  if (it->r < pos) return s.end();

  int l = it->l, r = it->r, index = it->index;
  s.erase(it);
  s.insert({l, pos-1, index});
  return s.insert({pos, r, index}).first;
}

void proc(int l, int r, int index) {
  auto pt1 = split(r+1);
  auto pt2 = split(l);

  s.erase(pt2, pt1);
  s.insert({l, r, index});
}

#define _debug 0
int main() {
  cin.tie(0)->sync_with_stdio(0);

  #if _debug == 1
  freopen("input.inp", "r", stdin);
  #else
  freopen("POSTERS.INP", "r", stdin);
  freopen("POSTERS.OUT", "w", stdout);
  #endif // _debug

  int t;
  cin >> t;
  while (t--) {
    int n;
    cin >> n;

    s.clear();
    s.insert({1, inf, 0});

    for (int i = 1; i <= n; i++) {
      int l, r;
      cin >> l >> r;
      proc(l, r, i);
    }

    set<int> cnt;
    for (const auto& x : s) {
      if (x.index != 0) cnt.insert(x.index);
    }
    cout << cnt.size() << '\n';
  }
}
