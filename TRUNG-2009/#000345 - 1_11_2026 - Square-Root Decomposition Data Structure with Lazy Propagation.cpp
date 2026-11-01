#include <bits/stdc++.h>
using namespace std;

/*
Cho mảng a1, a2, ..., an các số nguyên. Hãy thực hiện q truy vấn, mỗi truy vấn vẫn thuộc một trong hai loại:

- 1 l r val : Thực hiện a_l += val, ..., a_r += val
- 2 l r : Tính tổng a_l + a_{l+1} + ... + a_r

Input

- Dòng đầu tiên chứa số nguyên dương n (n <= 10^5).
- Dòng thứ hai chứa a1, a2, ..., an (|a_i| <= 10^9).
- Dòng thứ ba chứa số nguyên dương q (q <= 10^5).
- q dòng cuối cùng, mỗi dòng mô tả một truy vấn theo trình tự thực hiện với cách như đã trình bày ở trên (1 <= l <= r <= n; |val| <= 10^9), có ít nhất một truy vấn loại 2.

Output

- Với mỗi truy vấn loại 2, in trên một dòng số nguyên là kết quả câu trả lời.

Example

Test 1

Input

5
0 0 0 0 0
3
1 2 4 3
2 1 5
2 3 4

Output

9
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
long long A[maxn];
int get_block[maxn];

long long block[maxn], lazy[maxn];
int lblock[maxn], rblock[maxn];

int main() {
  cin.tie(0)->sync_with_stdio(0);

#if _debug == 1
  freopen("input.inp", "r", stdin);

#elif _debug == 2
  freopen("input.inp", "r", stdin);

#else

#endif // _debug

  int n;
  cin >> n;
  for (int i = 1; i <= n; i++) cin >> A[i];

  int block_size = sqrt(n);
  int block_num = (n - 1)/block_size + 1;
  for (int i = 1; i <= block_num; i++) {
    lblock[i] = (i - 1) * block_size + 1;
    rblock[i] = min(n, i * block_size);

    for (int j = lblock[i]; j <= rblock[i]; j++) {
      get_block[j] = i;
      block[i] += A[j];
    }
  }

  int q;
  cin >> q;
  while (q--) {
    int type;
    cin >> type;
    if (type == 1) {
      int l, r;
      long long val;
      cin >> l >> r >> val;

      while (l <= r) {
        int tag = get_block[l];
        if ((l - 1)%block_size == 0 && l + block_size - 1 <= r) {
          lazy[tag] += val;
          l += block_size;
        } else {
          A[l] += val;
          block[tag] += val;
          l++;
        }
      }

    } else if (type == 2) {
      int l, r;
      cin >> l >> r;

      long long res = 0;
      while (l <= r) {
        int tag = get_block[l];
        if ((l - 1)%block_size == 0 && l + block_size - 1 <= r) {
          res += block[tag] + lazy[tag] * block_size;
          l += block_size;
        } else {
          res += A[l] + lazy[tag];
          l++;
        }
      }

      cout << res << '\n';
    }

  }

  #if _debug == 1
  debug(block_size, block_num);
  newline;

  for (int i = 1; i <= n; i++) {
    debug(i, A[i]);
  }
  newline;

  for (int i = 1; i <= block_num; i++) {
    debug(i, block[i], lblock[i], rblock[i], lazy[i]);
  }


  #endif // _debug

}
