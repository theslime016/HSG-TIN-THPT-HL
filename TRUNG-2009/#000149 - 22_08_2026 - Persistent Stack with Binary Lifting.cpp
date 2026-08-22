#include <bits/stdc++.h>
using namespace std;

const int inf = 1e9;
const int _log = 20;
const int maxq = 2e5 + 5;
struct node {
  int val;
  int prevv;
  int size;
  int jmp[_log];
  int maxval[_log];
} timeline[maxq];

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int q;
  cin >> q;

  timeline[0].prevv = -1;
  timeline[0].val = -inf;
  timeline[0].size = 0;
  for (int j = 0; j < 20; j++) {
    timeline[0].maxval[j] = -inf;
    timeline[0].jmp[j] = 0;
  }

  for (int index = 1; index <= q; index++) {
    int t;
    cin >> t;
    if (t == 1) {
      int ver, x;
      cin >> ver >> x;
      timeline[index].val = x;
      timeline[index].size = timeline[ver].size + 1;
      timeline[index].prevv = ver;

      timeline[index].jmp[0] = ver;
      timeline[index].maxval[0] = x;
      for (int j = 1; j < _log; j++) {
        int half = timeline[index].jmp[j - 1];
        timeline[index].jmp[j] = timeline[half].jmp[j - 1];
        timeline[index].maxval[j] =
            max(timeline[index].maxval[j - 1], timeline[half].maxval[j - 1]);
      }
    } else if (t == 2) {
      int ver;
      cin >> ver;
      int last = timeline[ver].prevv;
      timeline[index] = timeline[last];
      cout << timeline[ver].val << '\n';
    } else if (t == 3) {
      int ver, k;
      cin >> ver >> k;
      timeline[index] = timeline[ver];

      k--;
      int current = ver;
      int exp = 0;
      while (k > 0) {
        if (k & 1) {
          current = timeline[current].jmp[exp];
        }
        exp++;
        k >>= 1;
      }
      cout << timeline[current].val << '\n';
    } else {
      int ver, k;
      cin >> ver >> k;
      timeline[index] = timeline[ver];

      k--;
      int res = timeline[ver].val;
      int current = ver;
      int exp = 0;
      while (k > 0) {
        if (k & 1) {
          res = max(res, timeline[current].maxval[exp]);
          current = timeline[current].jmp[exp];
        }
        exp++;
        k >>= 1;
      }
      cout << res << '\n';
    }
  }
}
