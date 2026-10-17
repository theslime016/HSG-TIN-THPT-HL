#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5 + 5;
long long A[maxn];
long long pref[maxn];
int lblock[maxn], rblock[maxn];

#define _debug 0
int main() {
  cin.tie(0)->sync_with_stdio(0);

#if _debug == 1
  freopen("input.inp", "r", stdin);
#else

#endif // _debug

  int n, q;
  cin >> n >> q;
  int timer = 1;
  for (int i = 1; i <= n; i++) {
    cin >> A[i];
    pref[i] = pref[i-1] + A[i];
    lblock[i] = timer;
    rblock[i] = timer + i - 1;
    timer += i;
  }

  auto get_tag = [&] (int a, int b) -> pair<int, int> {
    int tag_l = upper_bound(lblock + 1, lblock + n + 1, a) - lblock - 1;
    int tag_r = upper_bound(lblock + 1, lblock + n + 1, b) - lblock - 1;
    return {tag_l, tag_r};
  };

  while (q--) {
    int l, r;
    cin >> l >> r;
    pair<int, int> tag = get_tag(l, r);

    int start_l = l - lblock[tag.first] + 1;
    int start_r = r - lblock[tag.second] + 1;

    if (tag.first == tag.second) {
      cout << pref[start_r] - pref[start_l - 1] << '\n';
      continue;
    }

    //cout << tag.first << ' ' << tag.second << '\n';
    //cout << start_l << ' ' << start_r << '\n';
    long long res = pref[tag.first] - pref[start_l - 1] + pref[start_r];

    for (int index = tag.first + 1; index < tag.second; index++) {
      res += pref[index];
    }
    cout << res << '\n';
  }

}
