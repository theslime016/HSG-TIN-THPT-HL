#include <bits/stdc++.h>
using namespace std;

/**
QUAN HỆ HỌ HÀNG

Để theo dõi thực trạng đời sống của động vật hoang dã phục vụ cho công tác bảo tồn thiên nhiên người ta gắn cho mỗi động vật bắt được một con chip, trong đó có chứa mã phân loại. Theo dõi đường di chuyển và hoạt động hàng ngày của chúng người ta biết được rất nhiều thông tin, trong đó có việc ra đời của các động vật thế hệ F2, F3, … Mã phân loại là một số thập phân nguyên dương không vượt quá 10^9. Các cặp mã phân loại đảm bảo nếu hai cá thể có quan hệ họ hàng với nhau thì hai mã phải có ít nhất một chữ số giống nhau. Ví dụ 2 con vật có các mã phân loại tương ứng là 47 và 107 có quan hệ họ hàng với nhau, còn hai con vật với các mã 47 và 931 – không có quan hệ.

Cho n mã phân loại khác nhau từng đôi một. Hãy xác định số cặp động vật có quan hệ họ hàng.

Dữ liệu: Vào từ file văn bản RELATIVE.INP:
- Dòng đầu tiên chứa số nguyên n (2 ≤ n ≤ 5×10^5),
- Dòng thứ 2 chứa n mã phân loại.

Kết quả: Đưa ra file văn bản RELATIVE.OUT số cặp động vật xác định được.

Ví dụ:
RELATIVE.INP
5
10 74 47 77 301

RELATIVE.OUT
4
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
#define newline cerr << endl

#else
#define debug(...) (void(0))
#define newline (void(0))

#endif // _debug

#define popcount(x) __builtin_popcountll((x))

const int maxn = 5e5 + 5;
const int maxnum = (1LL << 12);
int n;

long long cnt[maxnum];

string num;
int get_mask() {
  int mask = 0;
  for (char c : num) {
    mask |= (1 << (c - '0'));
  }
  return mask;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);

  #if _debug == 1
  freopen("input.inp", "r", stdin);

  #else
  freopen("RELATIVE.INP", "r", stdin);
  freopen("RELATIVE.OUT", "w", stdout);

  #endif // _debug

  cin >> n;

  long long res = 0;
  for (int i = 1; i <= n; i++) {
    cin >> num;
    int mask = get_mask();

    for (int submask = mask; submask > 0; submask--, submask = submask & mask) {
      if ((popcount(submask))%2 == 1) {
        res += cnt[submask];
      } else {
        res -= cnt[submask];
      }
      cnt[submask]++;
    }
  }

  cout << res;

}
