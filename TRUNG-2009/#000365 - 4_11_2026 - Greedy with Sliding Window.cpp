#include <bits/stdc++.h>
using namespace std;

/*
P. Camera



time limit per test: 0.5 seconds

memory limit per test: 256 megabytes

input: camera.inp

output: camera.out



Có một dãy phố gồm $n$ ngôi nhà, các ngôi nhà được đánh số từ $1$ đến $n$ theo thứ tự từ đầu phố tới cuối phố. Trong các ngôi nhà này, có $k$ ngôi nhà đã được lắp camera an ninh.



UBND thành phố thấy rằng, để đảm bảo an ninh cho toàn bộ khu phố, trong $r$ ngôi nhà liên tiếp bất kì, phải có ít nhất $t$ ngôi nhà được lắp camera. UBND thành phố muốn lắp đặt thêm ít camera nhất để đảm bảo tiêu chuẩn an ninh này. Các bạn hãy giúp họ xác định số camera ít nhất cần lắp thêm và những ngôi nhà cần được trang bị camera nhé.



Input

Dòng đầu tiên chứa bốn số nguyên $n, k, r$ và $t$ ($2 \le n \le 3 \cdot 10^5, 0 \le k \le n, 1 \le t < r \le n$), lần lượt là số ngôi nhà trong toàn dãy phố, số ngôi nhà đã được lắp sẵn camera an ninh, và hai tham số $r, t$ thể hiện tiêu chuẩn an ninh của khu phố.



Dòng thứ hai chứa $k$ số nguyên phân biệt, có giá trị từ $1$ đến $n$, là chỉ số của các ngôi nhà đã được lắp đặt sẵn camera.



Output

Dòng đầu tiên ghi một số nguyên $m$ là số camera tối thiểu cần lắp đặt thêm.



Dòng thứ hai ghi $m$ số nguyên là chỉ số của các ngôi nhà cần lắp thêm camera. Nếu có nhiều phương án chọn các ngôi nhà để lắp camera khác nhau, bạn được in ra phương án bất kì.
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

const int maxn = 3e5 + 5;
int A[maxn];
int task[maxn];
int ptr = 0;

int main() {
  cin.tie(0)->sync_with_stdio(0);

#if _debug == 1
  freopen("input.inp", "r", stdin);

#elif _debug == 2
  freopen("input.inp", "r", stdin);
  freopen("output.ans", "w", stdout);

#else
  freopen("camera.inp", "r", stdin);
  freopen("camera.out", "w", stdout);

#endif // _debug

  int n, k, r, t;
  cin >> n >> k >> r >> t;
  for (int i = 1; i <= k; i++) {
    int index;
    cin >> index;
    A[index] = 1;
  }

  int current = 0;
  for (int i = 1; i <= r; i++) {
    current += A[i];
  }

  int diff = t - current;
  for (int j = r; j >= 1 && diff > 0; j--) {
    if (A[j] == 0) {
      A[j] = 1;
      current++;
      diff--;

      task[++ptr] = j;
    }
  }

  current -= A[1];

  for (int i = 2; i + r - 1 <= n; i++) {
    current += A[i + r - 1];

    if (current < t) {
      A[i + r - 1] = 1;
      current++;
      task[++ptr] = i + r - 1;
    }

    current -= A[i];
  }

  cout << ptr << '\n';
  for (int i = 1; i <= ptr; i++) cout << task[i] << ' ';

}
