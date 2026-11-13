#include <bits/stdc++.h>
using namespace std;

/**
BÀI 1. RÚT GỌN ĐOẠN (CUTSEQ.*)

Cho một dãy gồm N chữ số thuộc đoạn 0..9 (N ≤ 200). Ở mỗi bước, ta có thể lấy ra từ dãy này một đoạn liên tiếp các chữ số giống nhau và nhận được một số tiền bằng bình phương độ dài của đoạn được lấy ra. Nếu sau khi lấy, dãy đã cho bị tách làm 2 dãy con, 2 dãy con này lập tức được sát nhập lại thành 1 (giữ nguyên thứ tự).
Hãy tính số lượng tiền lớn nhất có thể thu được.

Input:
- Dòng đầu ghi số N. Dòng thứ hai ghi N chữ số thể hiện dãy.

Output:
- Ghi ra số lượng tiền lớn nhất có thể thu được.

Example:
Input:
6
100011

Output:
18
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

unordered_map<string, int> dp;
int make_dp(string s) {
  if (s.size() == 0)
    return 0;
  if (dp[s] != 0)
    return dp[s];

  int last_char = s[0];
  int len = 1;
  int res = 0;
  string new_string;
  for (int i = 1; i < s.size(); i++) {
    if (last_char == s[i]) {
      len++;
    } else {
      int current = len * len;
      new_string = s.substr(0, i - len) + s.substr(i, (int)s.size() - i);

      debug(s, (char)last_char, len, new_string);

      current += make_dp(new_string);
      res = max(res, current);

      last_char = s[i];
      len = 1;
    }
  }

  int current = len * len;
  new_string = s.substr(0, (int)s.size() - len);
  current += make_dp(new_string);
  res = max(res, current);

  dp[s] = res;
  return res;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);

#if _debug == 1
  freopen("input.inp", "r", stdin);

#else
  freopen("CUTSEQ.INP", "r", stdin);
  freopen("CUTSEQ.OUT", "w", stdout);

#endif // _debug

  int n;
  cin >> n;
  string s;
  cin >> s;
  cout << make_dp(s);

}
