#include <bits/stdc++.h>
using namespace std;

/**
TÊN BÀI: CHÊNH LỆCH LIỀN KỀ (ADJACENT DELTA)
Đầu vào: delta.inp
Đầu ra: delta.out
Giới hạn thời gian: 1.0 giây
Giới hạn bộ nhớ: 128 megabytes

Cho dãy số nguyên không âm a_1, a_2, ..., a_n và một số nguyên không âm delta. Một dãy con b_1, b_2, ..., b_k (k >= 1) được gọi là hợp lệ nếu chênh lệch giữa hai phần tử ĐỨNG KỀ NHAU bất kỳ trong dãy con đó không vượt quá delta. Nói cách khác:
|b_j - b_{j-1}| <= delta   với mọi 2 <= j <= k
(Mọi dãy con có đúng 1 phần tử luôn được coi là hợp lệ).

Bạn cần thực hiện hai công việc sau:
1. Đếm số dãy con khác rỗng LIÊN TIẾP hợp lệ của dãy a.
2. Đếm số dãy con khác rỗng (không nhất thiết liên tiếp) hợp lệ của dãy a.

Do kết quả có thể rất lớn, bạn chỉ cần in ra hai kết quả theo modulo 998244353.

Đầu vào:
- Dòng thứ nhất chứa số nguyên \theta (1 <= \theta <= 3) — số thứ tự của subtask chứa test này.
- Dòng thứ hai chứa hai số nguyên n và \delta (1 <= n <= 5 * 10^5, 0 <= \delta <= 10^9).
- Dòng thứ ba chứa n số nguyên a_1, a_2, ..., a_n (0 <= a_i <= 10^9).

Đầu ra:
- In ra hai số nguyên không âm trên một dòng, lần lượt là đáp án của hai câu hỏi trên theo modulo 998244353.

Ghi điểm:
- Subtask 1 (35 điểm): n <= 20.
- Subtask 2 (25 điểm): a_1 <= a_2 <= ... <= a_n.
- Subtask 3 (40 điểm): Không có ràng buộc gì thêm.

Ví dụ:
+-------------------+-------------------+
| delta.inp         | delta.out         |
+-------------------+-------------------+
| 1                 | 4 5               |
| 3 1               |                   |
| 1 3 2             |                   |
+-------------------+-------------------+
| 2                 | 15 31             |
| 5 4               |                   |
| 1 2 3 4 5         |                   |
+-------------------+-------------------+
| 3                 | 10 14             |
| 6 0               |                   |
| 0 0 1 1 1 0       |                   |
+-------------------+-------------------+
Giải thích ví dụ 1 (a = [1, 3, 2], delta = 1):
- Các dãy con liên tiếp hợp lệ (4 dãy): [1], [3], [2], [3, 2].
  (Dãy [1, 3] và [1, 3, 2] không hợp lệ vì |3 - 1| = 2 > 1).
- Các dãy con không nhất thiết liên tiếp hợp lệ (5 dãy): [1], [3], [2], [1, 2], [3, 2].
(Lưu ý: Dãy con [1, 2] lấy từ chỉ số 1 và 3 có |2 - 1| = 1 <= 1 nên hợp lệ).
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

const int maxn = 5e5 + 5;
const long long mod = 998244353;
long long A[maxn];

long long fenwick[maxn]; /// dp

void update(int index, long long val) {
  for (; index < maxn; index += index & -index) {
    fenwick[index] = (fenwick[index] + val) % mod;
  }
}

long long fetch(int index) {
  long long res = 0;
  for (; index > 0; index -= index & -index) {
    res = (res + fenwick[index]) % mod;
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
  freopen("delta.inp", "r", stdin);
  freopen("delta.out", "w", stdout);

  #endif // _debug

  int DELTA;
  cin >> DELTA;

  int n;
  long long max_delta;
  cin >> n >> max_delta;
  vector<int> events;
  events.push_back(1);

  vector<long long> comp;
  comp.reserve(n);
  for (int i = 1; i <= n; i++) {
    cin >> A[i];
    comp.push_back(A[i]);

    long long diff = abs(A[i] - A[i - 1]);
    if (i > 1 && diff > max_delta) {
      events.push_back(i);
    }
  }
  events.push_back(n + 1);

  long long res1 = n%mod;
  for (int i = 0; i + 1 < (int)events.size(); i++) {
    long long dist = events[i + 1] - events[i] - 1;
    long long ways = (dist * (dist + 1) / 2) % mod;
    res1 = (res1 + ways)%mod;
  }

  sort(comp.begin(), comp.end());
  comp.erase(unique(comp.begin(), comp.end()), comp.end());

  auto fnd = [&](long long val) {
    return upper_bound(comp.begin(), comp.end(), val) - comp.begin();
  };

  long long res2 = 0;
  for (int i = 1; i <= n; i++) {
    long long up_val = A[i] + max_delta;
    long long down_val = A[i] - max_delta;
    int up = fnd(up_val);
    int down = fnd(down_val);

    long long local = ((fetch(up) - fetch(down - 1))%mod + mod)%mod;
    local = (local + 1LL) % mod;
    res2 = (res2 + local) % mod;

    int fnd_index = fnd(A[i]);
    update(fnd_index, local);
  }

  cout << res1 << ' ' << res2;
}
