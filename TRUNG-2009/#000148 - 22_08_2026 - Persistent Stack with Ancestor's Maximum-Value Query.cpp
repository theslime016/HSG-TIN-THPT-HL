#include <bits/stdc++.h>
using namespace std;

const int inf = 1e9;
const int _log = 20;
const int maxq = 2e5 + 5;
struct node {
  int val;
  // int maxval = -inf;
  int prevv;
  int size;
} timeline[maxq];

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int q;
  cin >> q;

  for (int i = 1; i <= q; i++) {
    int t;
    cin >> t;
    if (t == 1) { // push
      int ver;
      int x;
      cin >> ver >> x;
      timeline[i].val = x;
      timeline[i].prevv = ver;
      // timeline[i].maxval = max(timeline[i].maxval, x);
      timeline[i].size = timeline[ver].size + 1;
    } else if (t == 2) { // pop
      int ver;
      cin >> ver;
      int last = timeline[ver].prevv;
      timeline[i] = timeline[last];
      cout << timeline[ver].val << '\n';
    } else if (t == 3) { // print kth-element
      int ver;
      int k;
      cin >> ver >> k;
      k = timeline[ver].size - k + 1;
      timeline[i] = timeline[ver];
      while (timeline[ver].size > k)
        ver = timeline[ver].prevv;
      cout << timeline[ver].val << '\n';
    } else { // print max
      int ver;
      int k;
      cin >> ver >> k;
      timeline[i] = timeline[ver];
      k = timeline[ver].size - k + 1;
      int res = -inf;
      while (timeline[ver].size >= k) {
        res = max(res, timeline[ver].val);
        ver = timeline[ver].prevv;
      }
      cout << res << '\n';
    }
  }

  for (int i = 0; i < q; i++) {
    cerr << 'v' << i << ' ' << timeline[i].val << ' ' << timeline[i].size
         << '\n';
  }
}
