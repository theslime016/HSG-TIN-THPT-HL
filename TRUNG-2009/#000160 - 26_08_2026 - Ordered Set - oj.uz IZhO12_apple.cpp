/*late in autumn*/
#include <bits/stdc++.h>
using namespace std;

set<pair<int, int>> st;

void update(int l, int r) {
  auto it = st.lower_bound({l, -1});
  auto pre = it;
  if (pre != st.begin()) {
    pre = prev(it);
    if (pre->second >= l)
      it = pre;
  }

  while (it != st.end() && it->first <= r) {
    l = min(l, it->first);
    r = max(r, it->second);
    it = st.erase(it);
  }

  st.insert({l, r});
}

int fetch(int l, int r) {
  auto it = st.lower_bound({l, -1});
  auto pre = it;
  if (pre != st.begin()) {
    pre = prev(it);
    if (pre->second >= l)
      it = pre;
  }

  int res = 0;
  while (it != st.end() && it->first <= r) {
    res += max(0, min(it->second, r) - max(it->first, l) + 1);
    it++;
  }
  return res;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  int q;
  cin >> q;

  int c = 0;
  while (q--) {
    int type, l, r;
    cin >> type >> l >> r;
    l += c;
    r += c;
    if (type == 2) {
      update(l, r);
      continue;
    }
    c = fetch(l, r);
    cout << c << '\n';
  }
}
