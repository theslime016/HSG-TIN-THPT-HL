#include <bits/stdc++.h>
using namespace std;

/*
MAXLEN
Points: 100 (p) | Time limit: 1.0s | Memory limit: 1G | Input: stdin | Output: stdout

Cho dãy số nguyên a1, a2, ..., an. Hãy thực hiện Q yêu cầu, mỗi yêu cầu được cho bởi hai số nguyên L, R (1 <= L <= R <= n) với ý nghĩa tính:
max{|x - y| : L <= x, y <= R, ax = ay}

Input

- Dòng 1: Chứa hai số nguyên dương n, Q (1 <= n, Q <= 10^5).
- Dòng 2: Chứa n số nguyên a1, a2, ..., an (|ai| <= 10^9).
- Q dòng tiếp theo, dòng thứ i mô tả yêu cầu thứ i gồm hai số nguyên Li, Ri (1 <= Li <= Ri <= n).

Output

- In ra Q dòng, dòng thứ i ghi một số nguyên là câu trả lời của yêu cầu thứ i (in 0 nếu tất cả các giá trị trong yêu cầu tương ứng khác nhau).

Example

Test 1

Input

7 5
4 5 6 6 5 7 4
6 6
5 6
3 5
3 7
1 7

Output

0
0
1
1
6
*/

#if defined(__has_include) && __has_include("slime_debug_016.h")
#include "slime_debug_016.h"

#else
#define _debug 0

#endif // defined

/// MACRO
#if _debug == 1
void log_out() {cerr << '\n';}
template<typename H, typename... T>
void log_out(H h, T... t) {
  cerr << h << ", ";
  log_out(t...);
}
#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:\n", log_out(__VA_ARGS__)
#define newline cerr << '\n'

#else
#define debug(...) void(0)
#define newline void(0)

#endif // _debug

const int maxn = 1e5 + 5;
const long long inf = 1e18;
int n, q;

long long A[maxn];
int get_block[maxn];
int get_rindex[maxn];
deque<int> dq[maxn]; // index

long long query_res[maxn];

const int padding = 131072;
long long segment[maxn << 2];
void update(int index, long long val) {
  index += padding;
  segment[index] = val;
  for (index >>= 1; index > 0; index >>= 1) {
    segment[index] = max(segment[index << 1], segment[index << 1 | 1]);
  }
}

long long fetch(int l, int r) {
  int s = padding + l - 1;
  int t = padding + r + 1;

  long long res = 0;
  for (; s ^ t ^ 1; s >>= 1, t >>= 1) {
    if (~s & 1) res = max(res, segment[s ^ 1]);
    if (t & 1) res = max(res, segment[t ^ 1]);
  }

  return res;
}

struct QUERY {
  int l, r;
  int index;

  friend bool operator<(const QUERY& a, const QUERY& b) {
    int tag_a = get_block[a.l];
    int tag_b = get_block[b.l];

    if (tag_a != tag_b) return tag_a < tag_b;
    else return (tag_a & 1) ? a.r < b.r : a.r > b.r;
  }

} query[maxn];

void add(int index, int type) {
  int fnd = get_rindex[index];

  if (type == 1) {
    dq[fnd].push_front(index);
  } else if (type == 2) {
    dq[fnd].push_back(index);
  }

  long long val = abs(dq[fnd].back() - dq[fnd].front());
  update(fnd, val);
}

void rem(int index, int type) {
  int fnd = get_rindex[index];

  if (type == 1) {
    dq[fnd].pop_front();
  } else if (type == 2) {
    dq[fnd].pop_back();
  }

  long long val = dq[fnd].empty() ? 0 : abs(dq[fnd].back() - dq[fnd].front());
  update(fnd, val);
}


int main() {
  cin.tie(0)->sync_with_stdio(0);

  #if _debug == 1
  freopen("input.inp", "r", stdin);

  #elif _debu == 2
  freopen("input.inp", "r", stdin);

  #else

  #endif // _debug

  cin >> n >> q;

  vector<long long> comp;
  comp.reserve(n);

  for (int i = 1; i <= n; i++) {
    cin >> A[i];
    comp.push_back(A[i]);
  }

  sort(comp.begin(), comp.end());
  comp.erase(unique(comp.begin(), comp.end()), comp.end());

  int block_size = max(1, n / (int)sqrt(q));

  for (int i = 1; i <= n; i++) {
    int fnd = lower_bound(comp.begin(), comp.end(), A[i]) - comp.begin() + 1;
    get_rindex[i] = fnd;
    get_block[i] = (i - 1)/block_size + 1;
  }

  for (int i = 1; i <= q; i++) {
    cin >> query[i].l >> query[i].r;
    query[i].index = i;
  }

  sort(query + 1, query + q + 1);

  int l = 1, r = 0;
  for (int i = 1; i <= q; i++) {
    int ql = query[i].l;
    int qr = query[i].r;
    while (l > ql) {
      l--;
      add(l, 1);
    }
    while (r < qr) {
      r++;
      add(r, 2);
    }

    while (l < ql) {
      rem(l, 1);
      l++;
    }
    while (r > qr) {
      rem(r, 2);
      r--;
    }

    query_res[query[i].index] = fetch(1, n);
  }

  for (int i = 1; i <= q; i++) cout << query_res[i] << '\n';
}
