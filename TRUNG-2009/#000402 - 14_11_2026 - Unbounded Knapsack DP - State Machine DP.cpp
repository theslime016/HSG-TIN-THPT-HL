#include <bits/stdc++.h>
using namespace std;

/**
Xếp Phô mát

Bác John muốn xếp các miếng Phô mát vào một cái thùng để tích trữ cho mùa đông giá rét. Độ cao của thùng chứa là T (1≤T≤1000) và các miếng phô mát được đặt chồng lên nhau sao cho tổng độ cao không vượt quá giá trị này. Trang trại của bác John có N (1≤N≤100) loại phô mát khác nhau đánh số từ 1 đến N loại thứ i có chiều cao Hi (5≤Hi≤T) và có giá trị Vi (1≤Vi≤10^6) chú ý rằng chiều cao của các miếng phô mát luôn là bội số của 5. Số lượng mỗi loại là không hạn chế.
Khi các miếng phô mát được xếp chồng lên nhau thì độ cao của các miếng ở dưới bị co lại. Nếu một miếng phô mát ở dưới một miếng phô mát có độ cao lớn hơn hoặc bằng K (1≤K≤T) thì độ cao của miếng phô mát này chỉ còn lại bằng 4/5 độ cao ban đầu của nó. Tuy vậy, giá trị của miếng phô mát không thay đổi (vì độ cao của mỗi miếng phô mát luôn là bội của 5 nên sau khi nén lại độ cao của nó vẫn là số nguyên!!!).
Chiều cao của mỗi miếng phô mát hoặc giữ nguyên hoặc bằng 4/5 chiều cao ban đầu (cho dù nó bị đè bởi bao nhiêu miếng phô mát bên trên nữa).
Hãy tìm tổng giá trị lớn nhất của chồng phô mát mà bác John có thể có.
Ví dụ, bác John muốn đặt phô mát vào thùng với độ cao tối đa 53, miếng phô mát sẽ bị co lại nếu như nó nằm dưới các miếng có tổng chiều cao lớn hơn hoặc bằng 25. Trong trang trại của bác John có 3 loại phô mát như sau:
Type    Value    Height
1       100      25
2       20       5
3       40       10

Khi đó phương án tối ưu xếp phô mát của bác John là:
        Type Height Value
top ->  [1]  25    100
        [2]  4     20    <- crushed by [1] above
        [3]  8     40    <- crushed by [1] above
        [3]  8     40    <- crushed by [1] above
bottom->[3]  8     40    <- crushed by [1] above
Tổng chiều cao của các miếng phô mát sau khi xếp là:
25 + 4 + 8 + 8 + 8 = 53
Và tổng giá trị là:
100 + 20 + 40 + 40 + 40 = 240

Dữ liệu: Vào từ file văn bản CHEESE.INP
- Dòng 1: Ghi ba số nguyên N, T và K
- Dòng 2 đến dòng N+1: Dòng i+1 ghi hai số nguyên Vi và Hi.

Kết quả: Ghi ra file văn bản CHEESE.OUT
Một số nguyên duy nhất là giá trị lớn nhất của chồng phô mát.

Ví dụ:
CHEESE.INP
3 53 25
100 25
20 5
40 10

CHEESE.OUT
240

Ghi chú: Có 40% số test ứng với 40% số điểm có n≤20
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

const int maxn = 123;
const int maxh = 1234;
const int maxtype = 5;
const long long inf = 1e18;

int n, t, k;
long long dp[maxh][maxtype]; /// rem h - type: 1:norm 2:free 4/5
long long value[maxn], cost[maxn];
int type[maxn];


int main() {
  cin.tie(0)->sync_with_stdio(0);

#if _debug == 1
  freopen("input.inp", "r", stdin);

#else
  freopen("CHEESE.INP", "r", stdin);
  freopen("CHEESE.OUT", "w", stdout);

#endif // _debug

  cin >> n >> t >> k;
  for (int i = 1; i <= n; i++) {
    cin >> value[i] >> cost[i];
    if (cost[i] >= k)
      type[i] = 2;
    else
      type[i] = 1;
  }

  #if _debug == 1
  cerr << "type: " << endl;
  for (int i = 1; i <= n; i++) cout << type[i] << ' ';
  newline;
  #endif // _debug

  fill(&dp[0][0], &dp[0][0] + maxh * maxtype, -inf);
  dp[t][1] = 0;
  long long res = 0;
  for (int h = t - 1; h >= 0; h--) {
    for (int i = 1; i <= n; i++) {
      int norm_cost = cost[i];
      int best_cost = (cost[i]/5) * 4;
      int color = type[i];

      if (h + norm_cost <= t && dp[h + norm_cost][1] != -inf) {
        dp[h][color] = max(dp[h][color], dp[h + norm_cost][1] + value[i]);
      }

      if (h + best_cost <= t && dp[h + best_cost][2] != -inf) {
        dp[h][2] = max(dp[h][2], dp[h + best_cost][2] + value[i]);
      }

      res = max({res, dp[h][1], dp[h][2]});
    }
  }

  cout << res;

}
