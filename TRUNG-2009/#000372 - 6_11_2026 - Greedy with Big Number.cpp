#include <bits/stdc++.h>
using namespace std;

/*
H. Giao trà sữa

time limit per test: 0.75 seconds
memory limit per test: 32 megabytes
input: shipping.inp
output: shipping.out

GSPVH mở một cửa hàng trà sữa nằm trên phố Chùa Láng — con phố trà sữa nổi tiếng ở Hà Nội. Phố Chùa Láng tập trung nhiều tiệm trả sữa là bởi đây là nơi đóng đô của Học viện Ngoại Thương và Học viện Ngoại Giao với nhiều hotgirl cute xinh xắn, những cô nàng đã biến đây thành chốn không thể ngó lơ của những cậu sinh viên Hà Thành. Cũng bởi vì những nàng hotgirl ấy, phố Chùa Láng không chỉ tràn ngập trà sữa mà cũng rất lắm trà xanh. Giang hồ đồn rằng, tuy các cửa hàng đều bán trà sữa, khách đến uống trà lại toàn đem theo trà xanh. Không hiểu các bạn thích trà sữa hay trà xanh, đã uống trà sữa thì có thêm trà xanh để làm gì nhỉ?

Tạm dẹp câu chuyện trà sữa — trà xanh sang một bên, giờ chúng ta trở lại với tiệm trà chanh của GSPVH. Với bản tính cute thân thiện, lại hiền lành thật thà tốt bụng, GSPVH nhanh chóng thu hút được nhiều khách. Tuy nhiên, do chưa đầu tư hệ thống giao hàng, việc xử lý các đơn hàng đặt mua mang về của GS gặp nhiều khó khăn. Thậm chí, đích thân GS phải đi giao hàng.

Phố Chùa Láng có thể mô phỏng như một đường thẳng, ở đó có gắn một trục tọa độ. Tiệm trà sữa của GSPVH nằm ở tọa độ 0. Ngày hôm nay, có n đơn hàng đặt cho GSPVH. Đơn hàng thứ i yêu cầu giao m_i cốc trà sữa đến địa điểm có tọa độ x_i. GSPVH đã pha xong toàn bộ trà sữa cho cả n đơn hàng. Tuy nhiên, mỗi một chuyến giao, GSPVH chỉ có thể mang theo mình tối đa k cốc trà sữa. Mọi khách hàng của GSPVH đều không quan tâm đến thời điểm nhận hàng, đồng thời một người có thể nhận nhiều cốc trà sữa ở những thời điểm khác nhau. Cuối ngày, GSPVH phải trở lại quán để chuẩn bị cho những ngày tiếp theo.

Hãy cho biết tổng quãng đường nhỏ nhất GSPVH cần di chuyển để giao hàng cho toàn bộ n đơn hàng.

Input

Dòng đầu tiên chứa hai số nguyên n và k (1 ≤ n ≤ 10^6, 1 ≤ k ≤ 10^7), lần lượt là số đơn hàng cần xử lý và số cốc trà sữa tối đa GSPVH có thể mang trong một lần giao hàng.

Trong n dòng tiếp theo, dòng thứ i chứa hai số nguyên x_i (0 ≤ |x_i| ≤ 10^8) và m_i (1 ≤ m_i ≤ 10^9) mô tả đơn hàng thứ i.

Output

Gồm một số nguyên duy nhất là độ dài quãng đường ngắn nhất GSPVH cần đi để giao cả n đơn hàng.

Scoring

- Subtask 1 (29 điểm): n ≤ 10^3, m_i ≤ 10^4 và k ≤ 10^5.
- Subtask 2 (28 điểm): n ≤ 10^3 và m_i ≤ 10^7.
- Subtask 3 (43 điểm): Không có ràng buộc gì thêm.

Example

Input
4 10
2 3
5 7
7 5
9 5

Output
28
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

long long n, k;
__int128_t solve(vector<pair<long long, long long>>&& task) {
  sort(task.begin(), task.end(), greater<pair<long long, long long>>());

  #if _debug == 1
  newline;
  cerr << "task: " << '\n';
  for (const auto& x : task) {
    debug(x.first, x.second);
  }
  newline;
  #endif // _debug

  __int128_t res = 0;
  int i = 0;
  while (i < (int)task.size()) {
    long long int_part = task[i].second/k + (task[i].second%k != 0 ? 1LL : 0LL);
    long long rem = task[i].second%k != 0 ? (k - task[i].second%k) : 0;

    debug(task[i].first, task[i].second, int_part, rem);

    res += (__int128_t)2 * (__int128_t)int_part * (__int128_t)task[i].first;
    i++;

    while (i < (int)task.size() && rem > 0) {
      if (rem >= task[i].second) {
        rem -= task[i].second;
        task[i].second = 0;
      } else {
        task[i].second -= rem;
        rem = 0;
      }

      if (task[i].second == 0) i++;
    }

  }

  return res;
}

int buffer[50];
void print(__int128_t x) {
  if (x == 0) {
    cout << 0;
    return;
  }

  int ptr = 0;
  while (x > 0) {
    buffer[++ptr] = x%10;
    x /= 10;
  }

  while (ptr > 0) {
    cout << buffer[ptr--];
  }
}

int main() {
  cin.tie(0)->sync_with_stdio(0);

#if _debug == 1
  freopen("input.inp", "r", stdin);

#elif _debug == 2
  freopen("input.inp", "r", stdin);

#else
  freopen("shipping.inp", "r", stdin);
  freopen("shipping.out", "w", stdout);

#endif // _debug

  cin >> n >> k;
  vector<pair<long long, long long>> pos, neg;
  pos.reserve(n);
  neg.reserve(n);
  for (int i = 1; i <= n; i++) {
    long long x, y;
    cin >> x >> y;
    if (x >= 0) pos.push_back({x, y});
    else neg.push_back({-x, y});
  }

  debug(n, k);

  __int128_t res = 0;
  res += solve(move(pos));
  res += solve(move(neg));
  print(res);
}
