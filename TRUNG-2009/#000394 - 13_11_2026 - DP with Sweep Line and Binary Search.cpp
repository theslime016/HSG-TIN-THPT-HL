#include <bits/stdc++.h>
using namespace std;

/**
File: SALE.txt

Bài 3. Khuyến mại

Một lễ hội tổ chức trong rất nhiều ngày với rất nhiều trò chơi lý thú được diễn ra tại công viên Rồng vừa khai trương. Có tất cả m loại vé có thể dùng để mua vé tham dự lễ hội. Loại vé thứ i có giá pi và có hiệu lực gi ngày tính từ ngày mua (tính cả ngày mua). Với vé này, trong tất cả những ngày có hiệu lực, người mua được tự do ra vào vui chơi tại công viên. Trong thời gian tổ chức, ban tổ chức đưa ra chương trình khuyến mại sẽ giảm 50% giá vé với khách hàng mua vé vào 1 trong k ngày r1, r2, ..., rk.
Chú ý: Giá vé giảm giá = phần nguyên của giá vé/2. Ví dụ nếu giá vé là 5 thì sau khi giảm sẽ là 2.

Yêu cầu:
Bob đặc biệt muốn có mặt trong n ngày d1, d2, ..., dn. Hãy xác định tổng số tiền nhỏ nhất Bob cần bỏ ra để mua vé của mình.

Dữ liệu: Vào từ file SALE.INP
- Dòng đầu chứa 3 số nguyên n, m, k (m ≤ 10; k ≤ n ≤ 10^5).
- Dòng thứ 2 chứa n số nguyên dương d1, d2, ..., dn.
- Dòng thứ 3 chứa m số nguyên dương g1, g2, ..., gm.
- Dòng thứ 4 chứa m số nguyên dương p1, p2, ..., pm.
- Dòng thứ 5 chứa k số nguyên dương r1, r2, ..., rk.

Các dòng 2, 3, 4, 5 liệt kê theo thứ tự tăng dần và giá trị không vượt quá 5 * 10^5.

Kết quả: Ghi ra file SALE.OUT một số nguyên duy nhất là tổng số tiền nhỏ nhất tìm được.

Ví dụ:
SALE.INP
2 2 1
1 4
1 4
6 14
5

SALE.OUT
12

Ví dụ khác:
SALE.INP
2 2 1
1 4
1 4
6 14
1

SALE.OUT
7

Ràng buộc:
- 20% số test có n, m, k ≤ 4; di, gi, ri ≤ 7.
- 20% số test khác có n, k ≤ 300; di, gi, ri ≤ 1000.
- 20% số test khác có n, k ≤ 300.
- 20% số test khác có k = 0.
- 20% số test còn lại không có ràng buộc bổ sung.
**/

#define _debug 0

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
#define debug(...) (void(0))
#define newline (void(0))

#endif // _debug

const int maxn = 1e5 + 5;
const int maxday = 5e5 + 5;
const long long inf = 1e18;
int n, m, k;
int day[maxn];
int is_day[maxday];

int active[maxn];
int cost[maxn];

int sale[maxday];

long long dp[maxn];

int main() {
  cin.tie(0)->sync_with_stdio(0);

#if _debug == 1
  freopen("input.inp", "r", stdin);

#else
  freopen("SALE.INP", "r", stdin);
  freopen("SALE.OUT", "w", stdout);

#endif // _debug

  cin >> n >> m >> k;
  for (int i = 1; i <= n; i++) {
    cin >> day[i];
    is_day[ day[i] ] = 1;
  }

  for (int i = 1; i <= m; i++)
    cin >> active[i];
  for (int i = 1; i <= m; i++)
    cin >> cost[i];
  for (int i = 1; i <= k; i++) {
    int val;
    cin >> val;
    sale[val] = 1;
  }

#if _debug == 1
  cerr << "day: " << '\n';
  for (int i = 1; i <= n; i++)
    cerr << day[i] << ' ';
  newline;

  cerr << "range: " << '\n';
  for (int i = 1; i <= m; i++)
    cerr << active[i] << ' ';
  newline;

  cerr << "cost: " << '\n';
  for (int i = 1; i <= m; i++)
    cerr << cost[i] << ' ';
  newline;

#endif // _debug

  for (int i = 0; i <= n; i++)
    dp[i] = inf;

  int current = day[n];
  while (current >= 1) {
    if (sale[current] || is_day[current]) {
      for (int i = 1; i <= m; i++) {
        long long current_cost = cost[i];
        if (sale[current])
          current_cost >>= 1;

        int lim = current + active[i] - 1;
        int start = lower_bound(day + 1, day + n + 1, current) - day;
        int stop = upper_bound(day + 1, day + n + 1, lim) - day;

        if (start >= 1 && day[start] <= lim) {
          current_cost += dp[stop];
          for (int j = start; j < stop; j++) {
            if (current_cost < dp[j]) {
              dp[j] = current_cost;
            } else {
              break;
            }
          }
#if _debug == 1
          debug(current, i, start, stop, current_cost);
#endif // _debug
        }

      }
    }
    current--;
  }

#if _debug == 1
  newline;
  cerr << "dp: " << endl;
  for (int i = 1; i <= n; i++)
    cerr << dp[i] << ' ';
  newline;
#endif // _debug

  cout << dp[1];

}
