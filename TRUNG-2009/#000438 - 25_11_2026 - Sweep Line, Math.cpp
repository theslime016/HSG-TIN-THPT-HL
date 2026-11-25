#include <bits/stdc++.h>
using namespace std;

/**
M. Đếm dãy con
giới hạn thời gian mỗi test: 0.25 seconds
giới hạn bộ nhớ mỗi test: 128 megabytes
đầu vào: camax.inp
đầu ra: camax.out

Cho dãy số nguyên a_1, a_2, ..., a_n và một số nguyên k, bạn cần thực hiện hai nhiệm vụ sau:

- Đếm số dãy con liên tiếp có phần tử lớn nhất không quá k.
- Đếm số dãy con không cần liên tiếp có phần tử lớn nhất không quá k.

Cả hai kết quả này bạn cần in ra theo modulo 998244353.

Đầu vào
Dòng thứ nhất chứa số nguyên θ (1 ≤ θ ≤ 3) — số thứ tự của subtask chứa test này.

Dòng thứ hai chứa hai số nguyên n và k (1 ≤ n ≤ 5·10^5, -10^9 ≤ k ≤ 10^9).

Dòng thứ ba chứa n số nguyên a_1, a_2, ..., a_n (-10^9 ≤ a_i ≤ 10^9).

Đầu ra
In ra hai số nguyên không âm trên một dòng, lần lượt là đáp án của hai câu hỏi trên. Cả hai kết quả đều cần được in ra theo modulo 998244353.

Ghi điểm
Với mỗi file input, nếu output của bạn không hợp lệ (chứa ít hơn hoặc nhiều hơn hai số, chứa ký tự lạ, ...), bạn không được điểm. Ngược lại, bạn sẽ được 40% số điểm nếu tìm ra đúng 1 trong 2 số.

- Subtask 1 (35 điểm): n ≤ 20.
- Subtask 2 (25 điểm): a_1 ≤ a_2 ≤ ... ≤ a_n.
- Subtask 3 (40 điểm): Không có ràng buộc gì thêm.

Ví dụ

input
1
4 1
1 2 1 1

output
4 7

input
2
4 4
1 2 3 4

output
10 15
**/

#define _debug 0

const int maxn = 5e5 + 5;
const int mod = 998244353;
int n, k;

int A[maxn];

int main() {
  cin.tie(0)->sync_with_stdio(0);

  #if _debug == 1
  freopen("input.inp", "r", stdin);

  #elif _debug == 2
  freopen("input.inp", "r", stdin);

  #else
  freopen("camax.inp", "r", stdin);
  freopen("camax.out", "w", stdout);

  #endif // _debug

  int camax;
  cin >> camax;

  cin >> n >> k;
  vector<int> events; /// > k
  events.reserve(n + 2);
  events.push_back(0);
  for (int i = 1; i <= n; i++) {
    cin >> A[i];
    if (A[i] > k) events.push_back(i);
  }
  events.push_back(n + 1);

  long long res1 = 0;
  for (int i = 0; i + 1 < events.size(); i++) {
    long long dist = events[i + 1] - events[i] - 1;
    long long ways = ((dist * (dist + 1)) / 2)%mod;
    res1 = (res1 + ways) % mod;
  }

  sort(A + 1, A + n + 1, greater<int>());
  long long res2 = 0;
  for (int i = 1; i <= n; i++) {
    if (A[i] <= k) {
      long long dist = n - i + 1;
      long long current = 1;
      while (dist > 0) {
        current = (current << 1) % mod;
        dist--;
      }

      res2 = current % mod;
      break;
    }
  }

  if (res2 > 0) res2 = (res2 - 1)%mod;

  cout << res1 << ' ' << res2;

}
