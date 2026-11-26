#include <bits/stdc++.h>
using namespace std;

/**
Kỳ thi Duyên Hải
Kỳ thi Duyên Hải đã trở thành một kỳ thi chất lượng và uy tín. Quy mô kỳ thi vượt qua ranh giới về mặt địa lý và đã thu hút nhiều tình thành tham gia. Cùng với việc mở rộng về quy mô, kỳ thi cũng thay đổi hình thức thi. Kỳ thi Duyên Hải năm 2222, có n học sinh tham gia, các học sinh được đánh số từ 1 đến n. Tất cả các học sinh sẽ phải trải qua ba bài thi ở ba môn Lập trình tính toán, Trí tuệ nhân tạo và An toàn thông tin với thể thức như sau:

- Với mỗi bài thi, khi các thí sinh thi xong, ban giám khảo sẽ tiến hành chấm điểm bằng nhiều tiêu chí nhằm đảm bảo rằng, không có hai thí sinh bằng điểm. Ban giám khảo lập bảng xếp hạng các thí sinh trên từng môn thi riêng biệt và gửi lên Ban tổ chức ba dãy số (p_1, p_2, ..., p_n), (a_1, a_2, ..., a_n) và (s_1, s_2, ..., s_n) tương ứng là xếp hạng của ba môn Lập trình tính toán, Trí tuệ nhân tạo và An toàn thông tin. Các dãy số này đều là hoán vị của các số từ 1 đến n, với ý nghĩa: học sinh thứ i xếp thứ p_i ở môn Lập trình tính toán, thứ a_i ở môn Trí tuệ nhân tạo và thứ s_i ở môn An toàn thông tin.
- Từ bảng xếp hạng của các môn, Ban tổ chức dùng phần mềm xếp hạng các thí sinh. Thí sinh thứ i có mức phân hạng là 2^{p_i} + 2^{a_i} + 2^{s_i} và có thứ hạng chung cuộc được tính bằng số thí sinh có mức phân hạng nhỏ hơn cộng với 1. Theo cách xếp hạng của phần mềm, có thể có các thí sinh cùng thứ hạng.

Hiện tại, các thí sinh đã hoàn thành bài thi môn Lập trình tính toán và Trí tuệ nhân tạo, ban giám khảo đã chấm điểm và công bố bảng xếp hạng ở hai môn này. Tiếp theo, thí sinh chuẩn bị bước vào môn thi cuối cùng, môn An toàn thông tin. Để có được chiến lược thi phù hợp, mỗi thí sinh muốn biết thứ hạng chung cuộc tốt nhất và tồi nhất có thể của mình, sau khi môn thi cuối cùng diễn ra.

Yêu cầu: Cho biết thứ hạng của các thí sinh ở hai môn Lập trình tính toán và Trí tuệ nhân tạo, hãy giúp mỗi thí sinh tìm ra thứ hạng tốt nhất và tồi nhất chung cuộc có thể của mình khi xét trên mọi khả năng xảy ra đối với kết quả của môn An toàn thông tin.

Input
Dòng đầu chứa số nguyên dương n (1 ≤ n ≤ 3000).

Dòng thứ hai chứa n số nguyên dương p_1, p_2, ..., p_n là một hoán vị của các số từ 1 đến n, mô tả thứ hạng của các thí sinh ở môn Lập trình tính toán.

Dòng thứ ba chứa n số nguyên dương a_1, a_2, ..., a_n là một hoán vị của các số từ 1 đến n, mô tả thứ hạng của các thí sinh ở môn Trí tuệ nhân tạo.

Output
In ra n dòng, dòng thứ i chứa hai số nguyên lần lượt thể hiện thứ hạng chung cuộc tốt nhất và tồi nhất có thể của thí sinh thứ i.

Scoring
- Subtask 1 (30 điểm): n ≤ 10
- Subtask 2 (20 điểm): n ≤ 50
- Subtask 3 (20 điểm): n ≤ 200
- Subtask 4 (30 điểm): n ≤ 3000

Example

input
3
1 2 3
2 1 3

output
1 2
1 2
3 3
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

const int maxn = 3005;
int n;

struct PLAYER {
  int exp1, exp2, exp3;
  int index;

  PLAYER() = default;
  PLAYER(int a, int b, int c, int i = 0) {
    if (b < c)
      swap(b, c);
    if (a < b)
      swap(a, b);
    if (b < c)
      swap(b, c);
    if (a < b)
      swap(a, b);
    /// a >= b >= c

    exp1 = a;
    exp2 = b;
    exp3 = c;
    index = i;
  }

  bool operator<(const PLAYER& other) const {
    if (exp1 != other.exp1)
      return exp1 < other.exp1;
    if (exp2 != other.exp2)
      return exp2 < other.exp2;
    return exp3 < other.exp3;
  }

  bool operator==(const PLAYER& other) const {
    return exp1 == other.exp1
           && exp2 == other.exp2
           && exp3 == other.exp3;
  }
} player[maxn];

int A[maxn], B[maxn];

int best[maxn];
int worst[maxn];

pair<int, int> query_res[maxn];

int main() {
  cin.tie(0)->sync_with_stdio(0);

#if _debug == 1
  freopen("input.inp", "r", stdin);

#elif _debug == 2
  freopen("input.inp", "r", stdin);

#else
  freopen("ranking.inp", "r", stdin);
  freopen("ranking.out", "w", stdout);

#endif // _debug

  cin >> n;
  for (int i = 1; i <= n; i++)
    cin >> A[i];
  for (int i = 1; i <= n; i++)
    cin >> B[i];

  for (int i = 1; i <= n; i++) {
    player[i] = PLAYER(A[i], B[i], 0, i);
  }

  sort(player + 1, player + n + 1);

  /// best_play
  for (int i = 1; i <= n; i++) {
    if (player[i] == player[i - 1]) {
      best[player[i].index] = best[player[i - 1].index];
      continue;
    }

    PLAYER best_rank = PLAYER(player[i].exp1, player[i].exp2, 1);

    int best_play = 1;

    /// down -> current
    for (int j = 1; j < i; j++) {
      PLAYER other_best = PLAYER(player[j].exp1, player[j].exp2, j + 1);

      if (other_best < best_rank)
        best_play++;
    }

    /// current -> up
    for (int j = i + 1; j <= n; j++) {
      PLAYER other_best = PLAYER(player[j].exp1, player[j].exp2, j);

      if (other_best < best_rank)
        best_play++;
    }
    best[player[i].index] = best_play;
  }


  /// worst_play
  for (int i = n; i >= 1; i--) {
    if (player[i] == player[i + 1]) {
      worst[player[i].index] = worst[player[i + 1].index];
      continue;
    }

    PLAYER worst_rank = PLAYER(player[i].exp1, player[i].exp2, n);
    int worst_play = 1;

    /// down -> current
    for (int j = 1; j < i; j++) {
      PLAYER other_worst = PLAYER(player[j].exp1, player[j].exp2, j);

      if (other_worst < worst_rank)
        worst_play++;
    }

    /// current -> up
    for (int j = i + 1; j <= n; j++) {
      PLAYER other_worst = PLAYER(player[j].exp1, player[j].exp2, j + 1);

      if (other_worst < worst_rank)
        worst_play++;
    }
    worst[player[i].index] = worst_play;
  }

  for (int i = 1; i <= n; i++) {
    cout << best[i] << ' ' << worst[i] << '\n';
  }

}
