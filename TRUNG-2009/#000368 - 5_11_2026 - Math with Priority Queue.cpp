#include <bits/stdc++.h>
using namespace std;

/*
A. strdel

time limit per test: 1 second
memory limit per test: 256 megabytes

Cho xâu S độ dài n chỉ gồm các chữ cái từ a đến z.

Một xâu con liên tiếp của S được gọi là tệ nếu nó chỉ có một loại chữ cái.

Hãy tìm cách xóa đi đúng k ký tự sao cho số xâu con tệ của S sau khi xóa là nhỏ nhất, in ra số lượng xâu con tệ ít nhất có thể có.

Input

- Dòng đầu tiên gồm hai số nguyên dương 1 ≤ n ≤ 10^5, 1 ≤ k ≤ n.
- Dòng thứ hai là xâu S độ dài n, chỉ gồm các chữ cái thường từ a đến z.

Output
Gồm một dòng duy nhất là kết quả bài toán.

Scoring

- Subtask 1 (21% số điểm): n ≤ 20.
- Subtask 3 (23% số điểm): n ≤ 28.
- Subtask 2 (27% số điểm): n ≤ 5000.
- Subtask 4 (29% số điểm): Không có ràng buộc gì thêm.

Examples

input
10 2
babbbddaaa
output
11

input
19 7
dbcbcdaaaddbccddadd
output
12

Note
Ở ví dụ 1, ta chọn xóa hai ký tự ở vị trí 6 và 10, xâu S trở thành: "babbbddaa" và có số xâu con tệ là 11.
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

int main() {
  cin.tie(0)->sync_with_stdio(0);

#if _debug == 1
  freopen("input.inp", "r", stdin);

#elif _debug == 2
  freopen("input.inp", "r", stdin);

#else

#endif // _debug

  int n, k;
  cin >> n >> k;
  long long res = 0;
  char last = '#';
  int cnt = 0;

  priority_queue<int, vector<int>, less<int>> pq;

  for (int i = 1; i <= n; i++) {
    char c;
    cin >> c;
    if (c == last) {
      cnt++;
    } else {
      pq.push(cnt);
      debug(i, cnt);

      last = c;
      cnt = 1;
    }
    res += cnt;
  }

  pq.push(cnt);
  debug(n, cnt);

  for (int i = 1; i <= k; i++) {
    int best = pq.top();
    pq.pop();
    res -= best;
    best--;
    pq.push(best);
  }

  cout << res;

}
