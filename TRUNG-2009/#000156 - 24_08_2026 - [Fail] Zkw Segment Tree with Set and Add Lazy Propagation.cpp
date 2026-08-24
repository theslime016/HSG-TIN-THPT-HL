#include <bits/stdc++.h>
using namespace std;

const long long inf = 1e15;
const int maxnode = 2e5 + 5;
const int _log = 20;
struct node {
  int l, r;
  long long sum;
  long long maxval;
  long long lazyset;
  long long lazysum;
} segment[(1 << _log)];
// zkw

struct query {
  int t;
  int l, r;
  long long val;
};

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n, q;
  cin >> n >> q;
  vector<long long> interval = {1, n};
  interval.reserve(2 * q);
  vector<query> task(q);
  for (int i = 0; i < q; i++) {
    cin >> task[i].t >> task[i].l >> task[i].r;
    if (task[i].t == 1 || task[i].t == 2)
      cin >> task[i].val;

    interval.push_back(task[i].l);
    interval.push_back(task[i].r);
  }

  sort(interval.begin(), interval.end());
  interval.erase(unique(interval.begin(), interval.end()), interval.end());

  int sn = (int)interval.size() - 1;
  int m = 1;
  int h = 0;
  while (m <= n + 1) {
    m <<= 1;
    h++;
  }

  for (long long x : interval)
    cerr << x << ' ';
  cerr << '\n';

  for (int i = 0; i <= m + 1; i++) {
    if (i < sn) {
      segment[i + 1 + m].l = interval[i];
      segment[i + 1 + m].r = interval[i + 1];
    } else {
      segment[i + 1 + m].l = segment[i + 1 + m].r = interval.back();
    }
  }

  segment[m].l = segment[m].r = 1;

  for (int i = m - 1; i > 0; i--) {
    segment[i].l = segment[i << 1].l;
    segment[i].r = segment[i << 1 | 1].r;
  }
  cerr << segment[1].l << ' ' << segment[1].r << '\n';

  auto pushup = [&](int index) {
    for (index >>= 1; index > 0; index >>= 1) {
      segment[index].sum =
          segment[index << 1].sum + segment[index << 1 | 1].sum;
      segment[index].maxval =
          max(segment[index << 1].maxval, segment[index << 1 | 1].maxval);
    }
  };

  auto apply = [&](int index, int type, const long long &val) {
    // 1 = sum
    // 2 = set
    int len = segment[index].r - segment[index].l + 1;
    if (type == 1) {
      segment[index].sum += val * len;
      segment[index].maxval += val;
      if (index < m) {
        segment[index].lazysum += val;
      }
    } else {
      segment[index].sum = val * len;
      segment[index].maxval = val;
      if (index < m) {
        segment[index].lazysum = 0;
        segment[index].lazyset = val;
      }
    }
  };

  auto pushdown = [&](int index) {
    for (int rank = h; rank > 0; rank--) {
      int rindex = index >> rank;
      if (!segment[rindex].lazyset) {
        apply(rindex << 1, 2, segment[rindex].lazyset);
        apply(rindex << 1 | 1, 2, segment[rindex].lazyset);
        segment[rindex].lazyset = 0;
      }

      if (!segment[rindex].lazysum) {
        apply(rindex << 1, 1, segment[rindex].lazysum);
        apply(rindex << 1 | 1, 1, segment[rindex].lazysum);
        segment[rindex].lazysum = 0;
      }
    }
  };

  auto update = [&](int type, int l, int r, const long long &val) {
    int s = m + l - 1;
    int t = m + r + 1;
    pushdown(s);
    pushdown(t);

    int os = s;
    int ot = t;
    int len = 1;
    for (; s ^ t ^ 1; s >>= 1, t >>= 1, len <<= 1) {
      if (~s ^ 1)
        apply(s ^ 1, type, val);
      if (t ^ 1)
        apply(t ^ 1, type, val);
    }
    pushup(os);
    pushup(ot);
  };

  auto merge = [&](int type, const long long &x, const node &y) {
    if (type == 3)
      return x + y.sum;
    else
      return max(x, y.maxval);
  };

  auto fetch = [&](int type, int l, int r) {
    int s = m + l - 1;
    int t = m + r + 1;
    pushdown(s);
    pushdown(t);

    long long res = type == 3 ? 0 : -inf;
    for (; s ^ t ^ 1; s >>= 1, t >>= 1) {
      if (~s ^ 1)
        res = merge(type, res, segment[s ^ 1]);
      if (t ^ 1)
        res = merge(type, res, segment[t ^ 1]);
    }
    return res;
  };

  auto fnd = [&](int val) {
    return lower_bound(interval.begin(), interval.end(), val) -
           interval.begin();
  };

  for (auto &lp : task) {
    if (lp.t == 1 || lp.t == 2) {
      update(lp.t, fnd(lp.l), fnd(lp.r), lp.val);
      break;
    } else {
      cout << fetch(lp.t, fnd(lp.l), fnd(lp.r)) << '\n';
    }
  }

  for (int i = 0; i < 2 * m; i++) {
    cout << segment[i].sum << ' ' << segment[i].maxval << ' '
         << segment[i].lazyset << ' ' << segment[i].lazysum << ' '
         << segment[i].l << ' ' << segment[i].r << '\n';
  }
}
