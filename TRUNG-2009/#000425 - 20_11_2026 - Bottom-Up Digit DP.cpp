#include <bits/stdc++.h>
using namespace std;

/**
LUCKY

Thông tin chung:
- Điểm: 100
- Giới hạn thời gian: 1.0s
- Giới hạn bộ nhớ: 1G
- Input: stdin
- Output: stdout
- Tác giả: lethanhbinh

Mô tả:
Một số nguyên dương được gọi là "số may mắn" nếu nó không chứa số 4 và không có hai chữ số 7 nào đứng liền kề nhau.

Yêu cầu: Hãy tính tổng các số may mắn xuất hiện trong đoạn [L, R]. Do con số này có thể rất lớn nên bạn chỉ cần lấy phần dư của nó khi chia cho 10^9 + 7.

Input:
- Một dòng duy nhất chứa hai số nguyên L, R (1 ≤ L ≤ R ≤ 10^18).

Output:
- In ra một số nguyên duy nhất là kết quả tìm được.

Example:
Test 1
Input:
1 10

Output:
51

Note:
Các số may mắn trong đoạn [1, 10] gồm: 1, 2, 3, 5, 6, 7, 8, 9, 10 (số 4 bị loại vì chứa chữ số 4). Tổng các số này là: 1 + 2 + 3 + 5 + 6 + 7 + 8 + 9 + 10 = 51.
**/

#define _debug 0

#if _debug == 1
void logout() {
  cerr << endl;
}
template<typename H, typename... T>
void logout(H h, T... t) {
  cerr << h << ", ";
  logout(t...);
}
#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:" << endl, logout(__VA_ARGS__)
#define debugtitle cerr << __PRETTY_FUNCTION__ << " line: " << __LINE__ << endl
#define newline cerr << endl

#else
#define debug(...) (void(0))
#define debugtitle (void(0))
#define newline (void(0))

#endif // _debug

const long long mod = 1e9 + 7;

long long dp[20][2];
long long cnt[20][2];
long long pow10[20];
string num;
pair<long long, long long> make_dp(int index, int flag_head, int flag_tight, int flag_adj) {
  int pos = (int)num.size() - index;
  if (pos == 0) {
    return (!flag_head ? (make_pair(0, 1)) : make_pair(0, 0));
  }

  if (!flag_head && !flag_tight && dp[pos][flag_adj] != -1)
    return {dp[pos][flag_adj], cnt[pos][flag_adj]};

  long long res = 0;
  long long total_cnt = 0;
  int lim = flag_tight ? (num[index] - '0') : 9;
  for (long long c = 0; c <= lim; c++) {
    if (flag_adj && c == 7)
      continue;
    if (c == 4)
      continue;

    int new_flag_head = flag_head && (c == 0);
    int new_flag_tight = flag_tight && (c == lim);
    int new_flag_adj = c == 7;

    pair<long long, long long> local = make_dp(index + 1, new_flag_head, new_flag_tight, new_flag_adj);

    res = (res + local.first) % mod;
    res = (res + ((c * pow10[pos - 1])%mod * local.second)%mod)%mod;
    total_cnt = (total_cnt + local.second) % mod;

//#if _debug == 1
//    debugtitle;
//    debug(pos, num[index], c);
//    debug(local.first, local.second, res, total_cnt);
//    debug(flag_head, flag_tight, flag_adj);
//    debug(new_flag_head, new_flag_tight, new_flag_adj);
//    newline;
//#endif // _debug

  }
  if (!flag_head && !flag_tight) {
    dp[pos][flag_adj] = res;
    cnt[pos][flag_adj] = total_cnt;
  }
  return {res, total_cnt};
}

long long query_fetch(long long x) {
  if (x <= 0)
    return 0;

  num = to_string(x);
  pair<long long, long long> res = make_dp(0, 1, 1, 0);
  return res.first;
}

void precalc() {
  pow10[0] = 1;
  for (int exp = 1; exp < 20; exp++) {
    pow10[exp] = (pow10[exp-1] * 10) % mod;
  }
}

int main() {
  cin.tie(0)->sync_with_stdio(0);

#if _debug == 1
  freopen("input.inp", "r", stdin);
  freopen("log.txt", "w", stderr);

#elif _debug == 2
  freopen("input.inp", "r", stdin);

#else

#endif // _debug

  memset(dp, -1, sizeof dp);
  memset(cnt, -1, sizeof cnt);

  precalc();

  long long l, r;
  cin >> l >> r;
  cout << ((query_fetch(r) - query_fetch(l - 1)) % mod + mod)%mod;
}
