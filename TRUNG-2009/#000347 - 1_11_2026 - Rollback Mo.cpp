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
void log_out() {
  cerr << '\n';
}
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
const int inf = 1e9;
int n, q;

long long A[maxn];
int get_block[maxn];
int get_rindex[maxn];

int lblock[maxn], rblock[maxn];

long long query_res[maxn];
int first_occur[maxn], last_occur[maxn];

struct HISTORY {
  int index;
  int first_occur_val;
  int last_occur_val;
} rollback[maxn];

struct QUERY {
  int l, r;
  int index;

  friend bool operator<(const QUERY& a, const QUERY& b) {
    int tag_a = get_block[a.l];
    int tag_b = get_block[b.l];

    if (tag_a != tag_b) return tag_a < tag_b;
    else return a.r < b.r;
  }

} query[maxn];

int make_local(int l, int r) {
  int res = 0;
  int ptr = 1;
  for (int i = min(r, rblock[ get_block[l] ]); i >= l; i--) {
    int fnd = get_rindex[i];
    rollback[ptr++] = {fnd, first_occur[fnd], last_occur[fnd]};
    first_occur[fnd] = min(first_occur[fnd], i);
    last_occur[fnd] = max(last_occur[fnd], i);

    debug(i, fnd, first_occur[fnd], last_occur[fnd]);

    res = max(res, abs(last_occur[fnd] - first_occur[fnd]));
  }

  for (int j = ptr - 1; j > 0; j--) {
    first_occur[ rollback[j].index ] = rollback[j].first_occur_val;
    last_occur[ rollback[j].index ] = rollback[j].last_occur_val;
  }

  return res;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);

#if _debug == 1
  freopen("input.inp", "r", stdin);

#elif _debug == 2
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
  int block_num = (n - 1)/block_size + 1;

  for (int i = 1; i <= block_num; i++) {
    lblock[i] = (i - 1)*block_size + 1;
    rblock[i] = min(n, i * block_size);
  }

  for (int i = 1; i <= n; i++) {
    int fnd = lower_bound(comp.begin(), comp.end(), A[i]) - comp.begin() + 1;
    get_rindex[i] = fnd;
    get_block[i] = (i - 1)/block_size + 1;
  }

#if _debug == 1
  debug(block_size, block_num);
  for (int i = 1; i <= block_num; i++) {
    debug(i, lblock[i], rblock[i]);
  }

  newline;
  for (int i = 1; i <= n; i++) {
    debug(i, get_rindex[i], get_block[i]);
  }

#endif // _debug


  for (int i = 1; i <= q; i++) {
    cin >> query[i].l >> query[i].r;
    query[i].index = i;
  }

  sort(query + 1, query + q + 1);

#if _debug == 1
  for (int i = 1; i <= q; i++) {
    debug(i, query[i].index, query[i].l, query[i].r);
  }

#endif // _debug

  int r = 0;
  int last_tag = -1;
  int res = 0;
  for (int i = 1; i <= q; i++) {
    int ql = query[i].l;
    int qr = query[i].r;
    int tag_l = get_block[ql];
    int tag_r = get_block[qr];

    if (tag_l != last_tag) {
      fill_n(first_occur, maxn, inf);
      fill_n(last_occur, maxn, -inf);

      last_tag = tag_l;
      r = rblock[tag_l];
      res = 0;
    }


    if (tag_l == tag_r) {
      query_res[ query[i].index ] = max(res, make_local(ql, qr));
      continue;
    }

    while (r < qr) {
      r++;
      int fnd = get_rindex[r];
      first_occur[fnd] = min(first_occur[fnd], r);
      last_occur[fnd] = max(last_occur[fnd], r);
      res = max(res, abs((last_occur[fnd] - first_occur[fnd])));
    }

    query_res[ query[i].index ] = max(res, make_local(ql, qr));
  }

  for (int i = 1; i <= q; i++) cout << query_res[i] << '\n';
}
