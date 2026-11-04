#include <bits/stdc++.h>
using namespace std;

/*
G. Đếm số cây khung
time limit per test: 0.25 seconds
memory limit per test: 8 megabytes
input: cntmst.inp
output: cntmst.out

Nếu bạn gặp khó trong việc xem đề bài, hãy tải file cntmst-materials.zip trong mục Contest materials và xem các file ảnh bên trong để có bản đề đầy đủ và đẹp nhất.

Cho một đồ thị vô hướng đầy đủ gồm n đỉnh. Các đỉnh được đánh số từ 1 đến n. Bạn được cho một tập hợp E gồm n - 3 cạnh. Hãy đếm số cây khung của đồ thị được cho sao cho cả n - 3 cạnh của tập hợp E đều thuộc cây khung này.

Nhắc lại:
- Cây khung của một đồ thị vô hướng liên thông n đỉnh là một cây gồm toàn bộ n đỉnh của đồ thị và n - 1 cạnh nào đó thuộc đồ thị này.
- Đồ thị vô hướng đầy đủ gồm n đỉnh là đồ thị vô hướng có n(n-1)/2 cạnh, sao cho hai đỉnh bất kỳ đều được kết nối trực tiếp bởi một cạnh.

Input

Dòng đầu tiên chứa số nguyên n (4 ≤ n ≤ 1000).
Trong n - 3 dòng còn lại, mỗi dòng chứa hai số nguyên x và y (1 ≤ x < y ≤ n) cho biết cạnh (x, y) thuộc tập hợp E. Dữ liệu vào đảm bảo n - 3 cạnh này đôi một phân biệt.

Output

In ra một số nguyên duy nhất là số cây khung của đồ thị được cho chứa tất cả n - 3 cạnh thuộc tập hợp E. Do kết quả có thể rất lớn, bạn chỉ cần in ra phần dư của số lượng cây khung tìm được khi chia cho 10^9 + 22071997.

Scoring

- Subtask 1 (30 điểm): n ≤ 100
- Subtask 2 (70 điểm): n ≤ 1000

Examples

Input
4
1 2

Output
8

Input
4
3 4

Output
8

Note

Với một đồ thị đầy đủ gồm 4 đỉnh, có 8 cây khung chứa cạnh (1, 2):
- {(1, 2), (1, 3), (1, 4)}
- {(1, 2), (1, 3), (2, 4)}
- {(1, 2), (1, 3), (3, 4)}
- {(1, 2), (2, 3), (2, 4)}
- {(1, 2), (1, 4), (2, 3)}
- {(1, 2), (1, 4), (3, 4)}
- {(1, 2), (2, 3), (3, 4)}
- {(1, 2), (2, 4), (3, 4)}
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

const long long mod = 1022071997;
const int maxn = 1e3 + 5;
int dsu[maxn];
int bucket[maxn];

int selected[maxn];

int fnd(int index) {
  if (dsu[index] == index) return index;
  return dsu[index] = fnd(dsu[index]);
}

int make_union(int a, int b) {
  a = fnd(a);
  b = fnd(b);
  if (a != b) {
    if (bucket[a] < bucket[b]) swap(a, b);
    bucket[a] += bucket[b];
    dsu[b] = a;
    return true;
  }
  return false;
}

long long binary_exp(long long base, long long exp) {
  long long res = 1;
  while (exp > 0) {
    if (exp & 1) {
      res = (res * base) % mod;
    }

    base = (base * base) % mod;
    exp >>= 1;
  }
  return res;
}


int main() {
  cin.tie(0)->sync_with_stdio(0);

  #if _debug == 1
  freopen("input.inp", "r", stdin);

  #elif _debu == 2
  freopen("input.inp", "r", stdin);

  #else
  freopen("cntmst.inp", "r", stdin);
  freopen("cntmst.out", "w", stdout);

  #endif // _debug

  #if _debug == 1
  debug(mod);
  #endif // _debug

  long long n;
  cin >> n;

  iota(dsu, dsu + maxn, 0);
  fill_n(bucket, maxn, 1);

  for (int i = 1; i <= n - 3; i++) {
    int a, b;
    cin >> a >> b;
    if (!make_union(a, b)) {
      cout << 0;
      return 0;
    }
  }

  long long sum = 0, mul = 1;
  long long cnt = 0;
  for (int i = 1; i <= n; i++) {
    int root = fnd(i);
    if (selected[root]) continue;

    sum += bucket[root];
    mul = (mul * bucket[root]) % mod;
    cnt++;
    selected[root] = 1;
  }

  #if _debug == 1
  debug(n, sum, mul);
  #endif // _debug

  long long res = (mul * binary_exp(sum, cnt - 2)) % mod;
  cout << res;

  /**
    Cho n nhom, moi nhom co x nguoi. Can lay ra moi nhom mot nguoi va ghep voi mot nguoi nao do o nhom khac.
    Sau khi ghep thi tat ca nguoi o 2 nhom duoc gop lai lam mot nhom.
    Khong duoc ghep 2 nguoi o chung mot nhom.
    Tim so cach ghep toan bo nhom lai lam mot.
  **/

}
