#include <bits/stdc++.h>
using namespace std;

/*
SUBSETSUM

Điểm: 100
Thời gian: 1.0s
Bộ nhớ: 1G
Input: stdin
Output: stdout
Tác giả: lethanhbinh

Bạn được cho một dãy số A1, A2, ..., An và m tập hợp S1, S2, ..., Sm các chỉ số của mảng này. Gọi Sk = {S_{k,i}}, 1 ≤ i ≤ |Sk|. Nói cách khác, S_{k,i} là một phần tử bất kỳ từ tập hợp Sk.

Trong bài này bạn sẽ phải trả lời q truy vấn có 2 dạng sau:

- "? k": Tính tổng ∑_{i=1}^{|Sk|} A_{S_{k,i}}, hay tổng các phần tử có vị trí thuộc tập Sk của dãy A.
- "+ k x": Cộng x vào các phần tử của dãy A có chỉ số trong tập Sk. Phần tử A_{S_{k,i}} được thay bằng A_{S_{k,i}} + x với mọi i ∈ [1, |Sk|].

Với mỗi truy vấn loại đầu tiên hãy in tổng đã tính.

Input:
- Dòng đầu tiên gồm 3 số n, m, q (1 ≤ n, m, q ≤ 10^5).
- Dòng thứ hai gồm n phần tử A1, A2, ..., An (|Ai| ≤ 10^8), các phần tử của dãy A.
- m dòng tiếp theo, dòng thứ k gồm một số nguyên dương ở đầu cho biết số lượng phần tử của tập Sk, theo sau bởi |Sk| số nguyên dương phân biệt S_{k,1}, S_{k,2}, ..., S_{k,|Sk|} (1 ≤ S_{k,i} ≤ n).
- q dòng tiếp theo, mỗi dòng có dạng "? k" hoặc "+ k x". Với mọi truy vấn có 1 ≤ k ≤ m, |x| ≤ 10^8. Các truy vấn được cho theo thứ tự chúng cần được trả lời.
- Đề đảm bảo tổng của kích thước mọi tập Sk không quá 10^5.

Output:
- Sau mỗi truy vấn dạng đầu tiên hãy in tổng đã tính trên một dòng.

Example:
Test 1
Input:
5 3 5
5 -5 5 1 -4
2 1 2
4 2 1 4 5
2 2 5
? 2

+ 3 4
? 1
+ 2 1
? 2

Output:
-3
4
9

Note:
Giải thích:
Ở truy vấn đầu tiên, tập Sk là S2 có 4 phần tử {2, 1, 4, 5}. Tổng của 4 phần tử có vị trí trong tập S2 là:
A2 + A1 + A4 + A5 = -5 + 5 + 1 + (-4) = -3
*/

#if defined(__has_include) && __has_include("slime_debug_016.h")
#include "slime_debug_016.h"

#else
#define _debug 0

#endif // defined

/// MACRO
#if _debug == 1
void log_out() {
  cerr << endl;
}
template<typename H, typename... T>
void log_out(H h, T... t) {
  cerr << h << ", ";
  log_out(t...);
}

#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:" << endl, log_out(__VA_ARGS__)
#define newline cerr << endl

#else
#define debug(...) void(0)
#define newline void(0)

#endif // _debug

const int maxn = 1e5 + 5;
const int block_size = 400;

int n, m, q;

long long A[maxn];
vector<int> S[maxn];
int intersect[maxn][block_size];

int get_index[maxn];
int get_rev_index[maxn];
int heavy_cnt = 0;

long long sum_heavy[block_size];
long long lazy_heavy[block_size];
int mark[maxn];

void build() {
  memset(get_index, -1, sizeof get_index);
  memset(get_rev_index, -1, sizeof get_rev_index);

  for (int i = 1; i <= m; i++) {
    if ((int)S[i].size() >= block_size) {
      heavy_cnt++;
      get_index[i] = heavy_cnt;
      get_rev_index[heavy_cnt] = i;

      for (int j : S[i]) {
        sum_heavy[heavy_cnt] += A[j];
      }
    }
  }

  for (int i = 1; i <= heavy_cnt; i++) {
    int fnd = get_rev_index[i];
    for (int j : S[fnd]) {
      mark[j] = 1;
    }

    for (int k = 1; k <= m; k++) {
      for (int j : S[k]) {
        if (mark[j]) intersect[k][i]++;
      }
    }

    for (int j : S[fnd]) {
      mark[j] = 0;
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

#endif // _debug

  cin >> n >> m >> q;
  for (int i = 1; i <= n; i++) cin >> A[i];
  for (int i = 1; i <= m; i++) {
    int sz;
    cin >> sz;

    S[i].reserve(sz);
    for (int j = 1; j <= sz; j++) {
      int x;
      cin >> x;
      S[i].push_back(x);
    }

  }

  build();

  while (q--) {
    char type;
    cin >> type;

    if (type == '+') {
      int index;
      long long val;
      cin >> index >> val;
      if (get_index[index] != -1) {
        int fnd = get_index[index];

        lazy_heavy[fnd] += val;
      } else {
        for (int j : S[index]) {
          A[j] += val;
        }
        for (int heavy_index = 1; heavy_index <= heavy_cnt; heavy_index++) {
          sum_heavy[heavy_index] += val * intersect[index][heavy_index];
        }
      }

    } else if (type == '?') {
      int index;
      cin >> index;

      long long res = 0;

      if (get_index[index] != -1) {
        int fnd = get_index[index];
        res += sum_heavy[fnd];
      } else {
        for (int j : S[index]) res += A[j];
      }

      for (int heavy_index = 1; heavy_index <= heavy_cnt; heavy_index++) {
        res += lazy_heavy[heavy_index] * intersect[index][heavy_index];
      }

      cout << res << '\n';

    }

  }

}
