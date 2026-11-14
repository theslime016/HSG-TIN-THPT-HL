#include <bits/stdc++.h>
using namespace std;

/**
BÀI 2. TRẠM THU PHÍ (STATIONS.*)
Dọc theo đường cao tốc được xây dựng theo phương thức BOT có n trạm thu phí. Trạm thứ i ở vị trí x_i tính từ đầu con đường. Để quản lý hoạt động, các trạm thu phí được chia ra thành k đơn vị, mỗi đơn vị bao gồm các trạm thu phí liên tiếp nhau và có từ a đến b trạm, mỗi trạm phải thuộc một đơn vị quản lý. Bán kính quản lý của mỗi đơn vị được đo bằng khoảng cách từ trạm đầu tiên đến trạm cuối cùng trong đơn vị này. Những người làm công tác quản lý thường xuyên phải đi duyệt tất cả các trạm trong đơn vị quản lý của mình. Vì vậy, việc phân chia các trạm vào các đơn vị quản lý phải đảm bảo sao cho bán kính quản lý lớn nhất phải là nhỏ nhất.
Ví dụ, có 6 trạm thu phí ở các vị trí 1, 2, 3, 4, 6, 13 và cần chia thành 2 đơn vị quản lý, mỗi đơn vị quản lý từ 2 đến 4 trạm. Với việc phân chia tối ưu, bán kính quản lý lớn nhất sẽ là 13 - 6 = 7.
Yêu cầu: Hãy đưa ra bán kính quản lý lớn nhất trong cách phân chia tối ưu.
Dữ liệu vào: Từ file STATIONS.INP
- Dòng đầu tiên chứa 4 số nguyên n, k, a, b.
- Dòng thứ hai chứa n số nguyên x_1, x_2, ..., x_n thể hiện vị trí các trạm thu phí.
Kết quả: Ghi ra file STATIONS.OUT
- Một số nguyên duy nhất là bán kính quản lý lớn nhất trong cách phân chia tối ưu.
Ví dụ:
STATIONS.INP
6 2 2 4
1 2 3 4 6 13

STATIONS.OUT
7
**/

#define _debug 1

const int maxn = 205;
const long long inf = 1e18;

long long A[maxn];
long long dp[maxn][maxn];

int main() {
  cin.tie(0)->sync_with_stdio(0);

#if _debug == 1
  freopen("input.inp", "r", stdin);

#else
  freopen("STATIONS.INP", "r", stdin);
  freopen("STATIONS.OUT", "w", stdout);

#endif // _debug

  int n, k, a, b;
  cin >> n >> k >> a >> b;
  for (int i = 1; i <= n; i++) cin >> A[i];

  fill(&dp[0][0], &dp[0][0] + maxn * maxn, inf);
  dp[0][0] = 0;

  for (int t = 1; t <= k; t++) {
    for (int i = a; i <= n; i++) {
      for (int j = i - a + 1; j >= max(1, i - b + 1); j--) {
        if (dp[j-1][t-1] != inf) {
          dp[i][t] = min(dp[i][t], max(A[i] - A[j], dp[j-1][t-1]));
        }
      }
    }
  }

  cout << dp[n][k];
}
