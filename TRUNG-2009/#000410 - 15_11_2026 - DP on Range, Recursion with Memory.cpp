#include <bits/stdc++.h>
using namespace std;

/**
Xóa số

Points: 1500p
Time limit: 1s
Memory limit: 256 MB
Tags: partial-sum, modular-arithmetic

Cho số nguyên dương N. Từ N, ta được phép xóa đi một đoạn gồm một số chữ số liên tiếp (nhưng không xóa hết các chữ số), hoặc giữ nguyên N. Các chữ số còn lại ghép với nhau theo đúng thứ tự cũ tạo thành một số mới. Số mới có thể có chữ số 0 ở đầu và được hiểu như một số nguyên bình thường, ví dụ 009 là số 9.

Hai cách xóa được coi là khác nhau nếu đoạn chữ số bị xóa ở hai vị trí khác nhau, kể cả khi số mới thu được giống nhau. Việc giữ nguyên N được tính là một cách.

Yêu cầu
Hãy đếm số cách xóa để số mới thu được chia hết cho 3.

Input
Một dòng chứa số nguyên dương N có không quá 10^5 chữ số.

Output
In ra số cách xóa tìm được.

Scoring
- Subtask 1 (50% số điểm): N có không quá 300 chữ số.
- Subtask 2 (25% số điểm): N có không quá... (Nội dung bị cắt trong file HTML gốc).
**/

#define _debug 0

#if _debug == 1
void log_out() {cerr << endl;}
template<typename H, typename... T>
void log_out(H h, T... t) {
  cerr << h << ", ";
  log_out(t...);
}
#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:" << endl, log_out(__VA_ARGS__)
#define debug_title cerr << __PRETTY_FUNCTION__ << " line: " << __LINE__ << endl
#define newline cerr << endl

#else
#define debug(...) (void(0))
#define debug_title (void(0))
#define newline (void(0))

#endif // _debug

const int maxn = 1000;
const int mod = 3;

long long dp[maxn][maxn];
string num;

int sum = 0;
long long make_dp(int l, int r, int current_sum) {
  if (l > r) return 0;
  if (dp[l][r] != -1) return dp[l][r];

  int len = r - l + 1;
  dp[l][r] = (sum - current_sum)%mod == 0 && (len < num.size());

  dp[l][r] += make_dp(l + 1, r, current_sum - (num[l] - '0'));
  dp[l][r] += make_dp(l, r - 1, current_sum - (num[r] - '0'));
  dp[l][r] -= make_dp(l + 1, r - 1, current_sum - (num[l] + num[r] - 2 * '0'));

  #if _debug == 1
  debug_title;
  debug(l, r, current_sum, sum - current_sum, dp[l][r]);
  #endif // _debug

  return dp[l][r];
}

int main() {
  cin.tie(0)->sync_with_stdio(0);

  #if _debug == 1
  freopen("input.inp", "r", stdin);

  #elif _debug == 2
  freopen("input.inp", "r", stdin);

  #else

  #endif // _debug

  cin >> num;

  for (char c : num) {
    sum += (c - '0');
  }

  #if _debug == 1
  debug(num, sum);
  #endif // _debug

  memset(dp, -1, sizeof dp);
  cout << make_dp(0, (int)num.size() - 1, sum) + (sum%mod == 0);
}
