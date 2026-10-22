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

const int maxn = 2e5 + 5;
const long long inf = 1e18;
long long A[maxn];
int n, q;
long long c;

struct NODE {
  long long max_val = -inf;
  long long sum_val;

  int cnt;
  int left;
  int right;

  map<long long, int> container;

} segment[maxn << 2];
long long lazy[maxn << 2];

NODE proc(const NODE& a, const NODE& b) {
  NODE res;
  res.max_val = max(a.max_val, b.max_val);
  res.sum_val = a.sum_val + b.sum_val;

  res.cnt = a.cnt + b.cnt;
  res.left = a.left;
  res.right = b.right;
  if (a.left && b.right) res.cnt--;

  res.container = a.container;
  for (const auto& x : b.container) {
    res.container[x.first] += x.second;
  }

  return res;
}

void apply(int index, long long val) {
  if (val < c) {
    segment[index].left = segment[index].right = 0;
    segment[index].cnt = 0;
  }

  while (!segment[index].container.empty()) {
    auto it = --segment[index].container.end();
    if (it->first <= val) break;

    segment[index].sum_val -= it->first * it->second;

    int cnt = it->second;
    it = segment[index].container.erase(it);

    segment[index].container[val] += cnt;
    segment[index].sum_val += cnt * val;
  }
  segment[index].max_val = min(segment[index].max_val, val);
}

void push_down(int index) {
  if (lazy[index] == -1) return;

  apply(index << 1, lazy[index]);
  apply(index << 1 | 1, lazy[index]);

  lazy[index] = -1;
}

void build(int index, int l, int r) {
  if (r < l) return;
  if (l == r) {
    segment[index].max_val = A[l];
    segment[index].sum_val = A[l];

    segment[index].left = segment[index].right = (segment[index].max_val >= c);
    segment[index].cnt = segment[index].left;

    segment[index].container[A[l]] = 1;

    return;
  }

  int mid = l + ((r - l) >> 1);
  build(index << 1, l, mid);
  build(index << 1 | 1, mid + 1, r);
  segment[index] = proc(segment[index << 1], segment[index << 1 | 1]);
}

void update(int index, int l, int r, int ql, int qr, long long val) {
  if (l > qr || r < ql) return;
  if (l >= ql && r <= qr) {
    apply(index, val);
    if (lazy[index] == -1) lazy[index] = val;
    else lazy[index] = min(lazy[index], val);
    return;
  }

  push_down(index);

  int mid = l + ((r - l) >> 1);
  update(index << 1, l, mid, ql, qr, val);
  update(index << 1 | 1, mid + 1, r, ql, qr, val);
  segment[index] = proc(segment[index << 1], segment[index << 1 | 1]);
}

NODE query(int index, int l, int r, int ql, int qr) {
  if (l > qr || r < ql) return NODE();
  else if (l >= ql && r <= qr) return segment[index];

  push_down(index);

  int mid = l + ((r - l) >> 1);
  return proc(query(index << 1, l, mid, ql, qr),
              query(index << 1 | 1, mid + 1, r, ql, qr));
}

void solve_subtask1() {
  while (q--) {
    int type;
    cin >> type;

    if (type == 1) {
      int l, r;
      long long h;
      cin >> l >> r >> h;
      for (int i = l; i <= r; i++) {
        A[i] = min(A[i], h);
      }

    } else if (type == 2) {
      int l, r;
      cin >> l >> r;
      long long res = 0;
      for (int i = l; i <= r; i++) {
        res += A[i];
      }
      cout << res << '\n';



    } else if (type == 3) {
      int l, r;
      cin >> l >> r;
      long long res = -inf;
      for (int i = l; i <= r; i++) {
        res = max(res, A[i]);
      }
      cout << res << '\n';



    } else if (type == 4) {
      int l, r;
      cin >> l >> r;
      long long res = 0;

      int current = 0;
      for (int i = l; i <= r; i++) {
        if (current == 0 && A[i] >= c) {
          current = 1;
          res++;
        } else if (current == 1 && A[i] < c) {
          current = 0;
        }
      }
      cout << res << '\n';


    }

  }
}


int main() {
  cin.tie(0)->sync_with_stdio(0);

#if _debug == 1
  freopen("input.inp", "r", stdin);

#elif _debug == 2
  freopen("input.inp", "r", stdin);

#else
  freopen("BARIER.INP", "r", stdin);
  freopen("BARIER.OUT", "w", stdout);

#endif // _debug

  cin >> n >> q >> c;
  for (int i = 1; i <= n; i++) cin >> A[i];

  memset(lazy, -1, sizeof lazy);
  build(1, 1, n);

  while (q--) {
    int type;
    cin >> type;
    if (type == 1) {
      int l, r;
      long long h;
      cin >> l >> r >> h;
      update(1, 1, n, l, r, h);
    } else {
      int l, r;
      cin >> l >> r;
      NODE res = query(1, 1, n, l, r);
      if (type == 2) cout << res.sum_val << '\n';
      if (type == 3) cout << res.max_val << '\n';
      if (type == 4) cout << res.cnt << '\n';
    }
  }

  #if _debug == 1

  for (const auto& x : segment[1].container) {
    debug(x.first);
    debug(x.second);
    newline;
  }

  #endif // _debug

}
