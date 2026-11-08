#include <bits/stdc++.h>
using namespace std;

/*
Q. Dãy con có độ dài bị chặn

Time limit per test: 2.25 seconds
Memory limit per test: 256 megabytes
Input: standard input
Output: standard output

Nếu bạn gặp khó trong việc xem đề bài, hãy tải file maxsubseq-materials.zip trong mục Contest materials và xem các file ảnh bên trong để có bản đề đầy đủ và đẹp nhất.

Cho dãy N số nguyên A = A1, A2, ..., AN. Ta gọi dãy con của dãy A là dãy gồm một số phần tử liên tiếp của nó, tức là dãy có dạng Ai, Ai+1, ..., Aj (1 ≤ i ≤ j ≤ N). Ta gọi độ dài của dãy là số lượng phần tử của nó còn trọng số của dãy là tổng các phần tử của nó. Một dãy con được gọi là có độ dài bị chặn nếu nó có độ dài lớn hơn hoặc bằng L và nhỏ hơn hoặc bằng H.

Yêu cầu:
Cho Q cặp số nguyên (L1, H1), (L2, H2), ..., (LQ, HQ); với mỗi cặp số (Li, Hi) hãy tìm dãy con có độ dài bị chặn bởi Li và Hi với trọng số lớn nhất.

Input:
- Dòng đầu tiên chứa hai số nguyên dương N và Q được ghi cách nhau bởi dấu cách.
- Dòng thứ hai chứa N số nguyên A1, A2, ..., AN được ghi cách nhau bởi dấu cách là các phần tử của dãy số.
- Trong Q dòng cuối cùng, dòng thứ i chứa hai số nguyên Li và Hi được ghi cách nhau bởi dấu cách.

Output:
In ra Q nhóm dòng, nhóm dòng thứ i gồm hai dòng thể hiện kết quả của bài toán ứng với bộ số (Li, Hi) theo khuôn dạng sau:
- Dòng đầu tiên ghi ra trọng số lớn nhất tìm được.
- Dòng thứ hai ghi vị trí bắt đầu và kết thúc của dãy con tìm được.

Nếu có nhiều cách chọn vị trí bắt đầu và kết thúc hợp lệ, bạn được phép in ra một cách chọn bất kỳ.

Scoring:
Trong tất cả các test, Q ≤ 500.
- 35% số test có N ≤ 50.
- 35% số test có N ≤ 400.
- 20% số test có N ≤ 20000.
- 10% số test có N ≤ 300000.

Example:
Input:
6 2
3 5 -9 6 7 -4
3 4
1 6

Output:
9
2 5
13
4 5

Note:
Với L1 = 3 và H1 = 4, dãy con độ dài bị chặn có trọng số lớn nhất là dãy 5, -9, 6, 7 với trọng số bằng 9.

Với L2 = 1 và H2 = 6, dãy con độ dài bị chặn có trọng số lớn nhất là dãy 6, 7 với trọng số bằng 13.
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
#define newline cerr << endl

#else
#define debug(...) void(0)
#define newline void(0)

#endif // _debug

const int maxn = 3e5 + 5;
const int maxlog = __lg(maxn) + 1;
const long long inf = 1e18;

long long pref[maxn];
long long table[maxn][maxlog];

int main() {
  cin.tie(0)->sync_with_stdio(0);

#if _debug == 1
  freopen("input.inp", "r", stdin);

#elif _debug == 2
  freopen("input.inp", "r", stdin);

#else

#endif // _debug

  int n, q;
  cin >> n >> q;
  for (int i = 1; i <= n; i++) {
    long long val;
    cin >> val;
    pref[i] = pref[i - 1] + val;
    table[i][0] = pref[i];
  }

  for (int exp = 1; exp < maxlog; exp++) {
    for (int i = 1; i + (1 << (exp - 1)) <= n; i++) {
      table[i][exp] = max(table[i][exp - 1], table[i + (1 << (exp - 1))][exp-1]);
    }
  }

  #if _debug == 1
  cerr << "pref: ";
  for (int i = 1; i <= n; i++) {
    cerr << pref[i] << ' ';
  }
  newline;

  #endif // _debug

  while (q--) {
    int l, r;
    cin >> l >> r;
    long long res = -inf;
    int res_index = -1;
    for (int i = 1; i <= n - l + 1; i++) {
      int down_index = i + l - 1;
      int up_index = min(n, i + r - 1);

      int exp = __lg(up_index - down_index + 1);
      long long max_pref = max(table[down_index][exp], table[up_index - (1 << exp) + 1][exp]);
      debug(i, down_index, up_index, exp, max_pref);
      newline;

      long long val = max_pref - pref[i - 1];
      if (val > res) {
        res = val;
        res_index = i;
      }
    }

    debug(l, r, res, res_index);

    for (int j = res_index + l - 1; j <= min(n, res_index + r - 1); j++) {
      if (pref[j] - pref[res_index - 1] == res) {
        cout << res << '\n';
        cout << res_index << ' ' << j << '\n';
        break;
      }
    }

  }

}
