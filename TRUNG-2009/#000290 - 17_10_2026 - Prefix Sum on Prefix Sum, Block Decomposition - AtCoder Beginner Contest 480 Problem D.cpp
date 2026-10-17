#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;

#define _debug 0

#if _debug == 1
#define debugl(x) cerr << #x << ':' << (x) << ' '
#define debugr(x) cerr << #x << ':' << (x) << '\n'

#else
#define debugl(x)
#define debugr(x)

#endif // _debug

const int maxn = 1e5 + 5;
long long A[maxn];
long long pref[maxn];
long long pref_block[maxn];
long long lblock[maxn], rblock[maxn];

int main() {
  cin.tie(0)->sync_with_stdio(0);

#if _debug == 1
  freopen("input.inp", "r", stdin);
#else

#endif // _debug

  int n, q;
  cin >> n >> q;
  long long timer = 1;
  for (int i = 1; i <= n; i++) {
    cin >> A[i];
    pref[i] = pref[i-1] + A[i];
    pref_block[i] = pref_block[i-1] + pref[i];
    lblock[i] = timer;
    rblock[i] = timer + i - 1;
    timer += i;
  }

  auto get_tag = [&] (long long a, long long b) -> pair<int, int> {
    int tag_l = upper_bound(lblock + 1, lblock + n + 1, a) - lblock - 1;
    int tag_r = upper_bound(lblock + 1, lblock + n + 1, b) - lblock - 1;
    return {tag_l, tag_r};
  };

  while (q--) {
    long long l, r;
    cin >> l >> r;
    pair<int, int> tag = get_tag(l, r);

    int start_l = l - lblock[tag.first] + 1;
    int start_r = r - lblock[tag.second] + 1;

    if (tag.first == tag.second) {
      cout << pref[start_r] - pref[start_l - 1] << '\n';
      continue;
    }

    debugl(tag.first);
    debugl(tag.second);

    debugl(start_l);
    debugr(start_r);

    long long res = pref[tag.first] - pref[start_l - 1] + pref[start_r];

    if (tag.first + 1 < tag.second) {
      res += pref_block[tag.second - 1] - pref_block[tag.first];
    }

    cout << res << '\n';
  }

}
