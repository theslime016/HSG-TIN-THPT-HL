#include <bits/stdc++.h>
using namespace std;

/**
P. Đường đi trên bảng
giới hạn thời gian mỗi test: 1.5 seconds
giới hạn bộ nhớ mỗi test: 512 megabytes
đầu vào: walk.inp
đầu ra: walk.out

Cho một bảng hình chữ nhật gồm m hàng và n cột. Các hàng được đánh số từ 1 đến m theo thứ tự từ trên xuống dưới. Các cột được đánh số từ 1 đến n theo thứ tự từ trái qua phải. Giao của hàng thứ i và cột thứ j của bảng là một ô vuông được ký hiệu là (i, j).

Bạn cần đi từ ô góc trái trên của bảng (ô (1, 1)) tới một số ô trên bảng. Tại mỗi bước, bạn chỉ được đi từ vị trí hiện tại sang phải hoặc xuống dưới một ô. Nói cách khác, nếu hiện tại bạn đang ở ô (x, y), trong bước tiếp theo bạn có thể đi tới một trong hai ô (x, y + 1) và (x + 1, y). Bạn không được phép đi ra ngoài bảng. Ngoài ra, trên bảng có p ô chứa hổ sâu mà bạn không thể đi vào.

Bạn được cho q ô trên bảng, với mỗi ô, bạn cần đếm số cách đi từ ô (1, 1) đến vị trí này. Hai cách đi được coi là khác nhau nếu tập hợp các ô đi qua ở hai cách là khác nhau.

Đầu vào
Dòng đầu tiên chứa bốn số nguyên m, n, p và q (1 ≤ m, n ≤ 2·10^6, 0 ≤ p ≤ 4000, 1 ≤ q ≤ 3000) lần lượt là số hàng và số cột của bảng, số ô bạn không thể đi vào và số ô mà bạn cần đếm số cách di chuyển tới đó.

Trong p dòng tiếp theo, mỗi dòng chứa hai số nguyên u và v (1 ≤ u ≤ m, 1 ≤ v ≤ n) cho biết bạn không thể đi vào ô (u, v). Dữ liệu vào đảm bảo p ô này đôi một phân biệt, và bạn có thể đi vào ô (1, 1).

Trong q dòng cuối cùng, mỗi dòng chứa hai số nguyên s và t (1 ≤ s ≤ m, 1 ≤ t ≤ n) cho biết bạn cần đếm số cách đi từ ô (1, 1) đến ô (s, t). Dữ liệu vào đảm bảo ô này không nằm trong p ô mà bạn không thể đi vào.

Đầu ra
In ra q số nguyên lần lượt thể hiện số cách đi từ ô (1, 1) đến q vị trí đã cho. Do kết quả có thể rất lớn, bạn chỉ cần in ra phần dư của kết quả khi chia cho 10^7 + 1203. Các số được viết trên một dòng, ngăn nhau bởi dấu cách.

Ghi điểm
- Subtask 1 (14 điểm): m, n ≤ 10^4
- Subtask 2 (12 điểm): p = 0
- Subtask 3 (12 điểm): p = 1
- Subtask 4 (11 điểm): p ≤ 10
- Subtask 5 (11 điểm): p ≤ 100
- Subtask 6 (10 điểm): Không có ràng buộc gì thêm.

Ví dụ

input
3 3 2 6
2 3
3 1
1 2
1 3
2 1
2 2
3 2
3 3

output
1 1 1 2 2 2
**/

#define _debug 0

#if _debug == 1
void logout() {cerr << endl;}
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

const int maxn = 2e6 + 5;
const int maxfact = maxn << 1;
const int maxpoint = 4e3 + 5;
const long long mod = 1e7 + 1203;

int row_num, col_num, point_num, q;

long long dp[maxpoint];
pair<int, int> point[maxpoint];


long long fact[maxfact];
long long inv_fact[maxfact];

long long binary_exp(long long base, long long exp) {
  long long res = 1;
  while (exp > 0) {
    if (exp & 1) {
      res = (res * base) % mod;
    }
    base = (base * base) % mod;
    exp >>= 1;
  }
  return res;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);

  #if _debug == 1
  freopen("input.inp", "r", stdin);

  #elif _debug == 2
  freopen("input.inp", "r", stdin);

  #else
  freopen("walk.inp", "r", stdin);
  freopen("walk.out", "w", stdout);

  #endif // _debug

  fact[0] = 1;
  for (int i = 1; i < maxfact; i++) {
    fact[i] = (fact[i - 1] * i) % mod;
  }

  inv_fact[maxfact - 1] = binary_exp(fact[maxfact - 1], mod - 2);
  for (int i = maxfact - 2; i >= 0; i--) {
    inv_fact[i] = (inv_fact[i + 1] * (i + 1)) % mod;
  }

  cin >> row_num >> col_num >> point_num >> q;
  for (int i = 1; i <= point_num; i++) {
    cin >> point[i].first >> point[i].second;
  }

  sort(point + 1, point + point_num + 1);

  auto get_way = [&](int x, int y) {
    return ((fact[x + y] * inv_fact[x])%mod * inv_fact[y])%mod;
  };

  for (int i = 1; i <= point_num; i++) {
    int x = point[i].first - 1;
    int y = point[i].second - 1;
    dp[i] = get_way(x, y);
    for (int j = 1; j < i; j++) {
      int delta_x = point[i].first - point[j].first;
      int delta_y = point[i].second - point[j].second;
      if (delta_x >= 0 && delta_y >= 0) {
        long long way = get_way(delta_x, delta_y);

        dp[i] = ((dp[i] - (way*dp[j])%mod)%mod + mod)%mod;
      }
    }
  }

  auto fnd = [&](const pair<int, int>& val) {
    return upper_bound(point + 1, point + point_num + 1, val) - &point[0] - 1;
  };

  while (q--) {
    int a, b;
    cin >> a >> b;
    int x = a - 1;
    int y = b - 1;
    long long res = get_way(x, y);

    int fnd_index = fnd(make_pair(a, b));
    for (int i = 1; i <= fnd_index; i++) {
      int delta_x = a - point[i].first;
      int delta_y = b - point[i].second;
      if (delta_x >= 0 && delta_y >= 0) {
        long long way = get_way(delta_x, delta_y);
        res = ((res - way*dp[i])%mod + mod)%mod;
      }
    }
    cout << res << ' ';
  }

}
