#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n, q;
  cin >> n >> q;
  vector<vector<long long>> timeline(1, {0});
  vector<long long> init(n + 1, 0);
  for (int i = 1; i <= n; i++)
    cin >> init[i];
  for (int index = 1; index <= n; index++) {
    int nxt = index + (index & -index);
    if (nxt <= n)
      init[nxt] += init[index];
  }

  timeline.push_back(init);
  while (q--) {
    int t;
    cin >> t;
    if (t == 1) {
      int ver, index;
      long long val;
      cin >> ver >> index >> val;

      long long old_val = timeline[ver][index];
      for (int jindex = index - 1; jindex > (index - (index & -index));
           jindex -= jindex & -jindex) {
        old_val -= timeline[ver][jindex];
      }
      long long diff = -old_val + val;
      for (; index <= n; index += index & -index) {
        timeline[ver][index] += diff;
      }
    } else if (t == 2) {
      int ver, l, r;
      cin >> ver >> l >> r;
      long long val = 0;
      for (int index = r; index > 0; index -= index & -index) {
        val += timeline[ver][index];
      }
      for (int index = l - 1; index > 0; index -= index & -index) {
        val -= timeline[ver][index];
      }
      cout << val << '\n';
    } else {
      int ver;
      cin >> ver;
      timeline.push_back(timeline[ver]);
    }
  }
}
