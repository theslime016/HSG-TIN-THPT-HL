#include <bits/stdc++.h>
using namespace std;

/*
Có n cái lỗ nằm dọc theo một đường thẳng đánh số 1, 2, ..., n từ trái qua phải. Trong lỗ thứ i có đặt một lò xo có độ dài a_i. Nếu có một viên bi rơi vào lỗ i, nó sẽ nảy lên rơi tiếp vào lỗ i + a_i (nếu i + a_i <= n); ngược lại nếu i + a_i > n, viên bi sẽ văng ra khỏi hàng (nhảy vượt quá lỗ n). Quá trình này tiếp tục diễn ra như vậy cho đến khi viên bi nhảy ra ngoài.

Người chơi thực hiện lần lượt m thao tác thuộc một trong hai loại:

- Thay lò xo có độ dài mới b vào lỗ a.
- Bắn một viên bi vào lỗ a, xác định số hiệu của lỗ cuối cùng mà viên bi rơi vào trước khi ra khỏi hàng và tổng số lỗ viên bi đã nhảy qua.

Yêu cầu: Viết chương trình thực hiện m thao tác nói trên.

Input

- Dòng đầu tiên chứa hai số nguyên dương n, m (1 <= n, m <= 10^5).
- Dòng thứ hai chứa n số nguyên dương không vượt quá n, biểu thị độ dài ban đầu của các lò xo đặt tại các lỗ 1, 2, ..., n.
- m dòng tiếp theo, mỗi dòng mô tả một thao tác thuộc một trong hai dạng:
    - 0 a b : Đặt lại độ dài của lò xo ở lỗ a thành b (1 <= a, b <= n).
    - 1 a : Bắn một viên bi vào lỗ a (1 <= a <= n).

Output

- Với mỗi thao tác dạng 1 a, in ra trên một dòng hai số nguyên cách nhau bởi dấu cách: số thứ nhất là số hiệu của lỗ cuối cùng viên bi nhảy đến trước khi vượt qua lỗ n, số thứ hai là tổng số lỗ mà viên bi đã nhảy vào.

Example

Test 1

Input

8 5
1 1 1 1 1 2 8 2
1 1
0 1 3
1 1
0 3 4
1 2

Output

8 7
8 5
7 3
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
int n, q;

int A[maxn];

int get_block[maxn];
int lblock[maxn], rblock[maxn];
int next_index[maxn], last_index[maxn], cnt_index[maxn];

void build(int tag) {
  int l = lblock[tag];
  int r = rblock[tag];

  for (int i = r; i >= l; i--) {
    int j = A[i] + i;
    if (j > n) {
      cnt_index[i] = 1;
      next_index[i] = n + 1;
      last_index[i] = i;
      continue;
    }

    int nxt_tag = get_block[j];
    if (nxt_tag == tag) {
      cnt_index[i] = cnt_index[j] + 1;
      next_index[i] = next_index[j];
      last_index[i] = last_index[j];
    } else {
      cnt_index[i] = 1;
      next_index[i] = j;
      last_index[i] = j;
    }

  }

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

  int block_size = sqrt(n);
  int block_num = (n - 1)/block_size + 1;

  for (int i = 1; i <= n; i++) {
    cin >> A[i];
    get_block[i] = (i - 1)/block_size + 1;
  }

  for (int i = 1; i <= block_num; i++) {
    lblock[i] = (i - 1) * block_size + 1;
    rblock[i] = min(n, i*block_size);
    build(i);
  }

  while (q--) {
    int type;
    cin >> type;
    if (type == 0) {
      int index, val;
      cin >> index >> val;
      A[index] = val;
      int tag = get_block[index];
      build(tag);
    } else if (type == 1) {
      int index;
      cin >> index;

      int cnt = 0;
      int last = -1;
      while (index <= n) {
        cnt += cnt_index[index];
        last = last_index[index];


        index = next_index[index];
      }
      cout << last << ' ' << cnt << '\n';
    }
  }

}
