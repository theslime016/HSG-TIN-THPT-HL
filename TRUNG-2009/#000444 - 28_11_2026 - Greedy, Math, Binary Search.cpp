#include <bits/stdc++.h>
using namespace std;

/**
Kỳ thi Duyên Hải đã trở thành một kỳ thi chất lượng và uy tín. Quy mô kỳ thi vượt qua ranh giới về mặt địa lý và đã thu hút nhiều tỉnh thành tham gia. Cùng với việc mở rộng về quy mô, kỳ thi cũng thay đổi hình thức thi. Kỳ thi Duyên Hải năm 2222, có n học sinh tham gia, các học sinh được đánh số từ 1 đến n. Tất cả các học sinh sẽ phải trải qua ba bài thi ở ba môn Lập trình tính toán, Trí tuệ nhân tạo và An toàn thông tin với thể thức như sau:

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

int A[maxn], B[maxn];

struct PLAYER {
  int a, b, c;
  PLAYER() = default;
  PLAYER(int _a, int _b, int _c) {
    a = _a;
    b = _b;
    c = _c;

    if (a < b)
      swap(a, b);
    if (b < c)
      swap(b, c);
    if (a < b)
      swap(a, b);

    if (b == c) {
      b++;
      c = 0;
      if (a < b) swap(a, b);
    }
    if (a == b) {
      a++;
      b = 0;
      if (b < c) swap(b, c);
    }
  }

  bool operator<(const PLAYER& other) const {
    if (a != other.a)
      return a < other.a;
    if (b != other.b)
      return b < other.b;
    return c < other.c;
  }
};

vector<int> make_lim(const PLAYER& current, int index) {
  vector<int> lim;

  for (int i = 1; i <= n; i++) {
    if (i == index)
      continue;

    auto check = [&](int c) {
      PLAYER other{A[i], B[i], c};
      return other < current;
    };

    int l = 0, r = n;
    for (int d = r - l; d > 0; d >>= 1) {
      while (l + d <= r && check(l + d))
        l += d;
    }
    lim.push_back(l);
  }
  return lim;
}

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
    vector<int> lim_best = make_lim(PLAYER(A[i], B[i], 1), i);
    vector<int> lim_worst = make_lim(PLAYER(A[i], B[i], n), i);

    int best_play = 1;
    int worst_play = 1;

    sort(lim_best.begin(), lim_best.end());
    sort(lim_worst.begin(), lim_worst.end());

    int best_num = n;
    for (int j = lim_best.size() - 1; j >= 0; j--) {
      if (best_num <= lim_best[j]) {
        best_play++;
      } else {
        best_num--;
      }
    }

    int worst_num = 1;
    for (int lim : lim_worst) {
      if (worst_num <= lim) {
        worst_play++;
        worst_num++;
      }
    }

    cout << best_play << ' ' << worst_play << '\n';
  }

}
