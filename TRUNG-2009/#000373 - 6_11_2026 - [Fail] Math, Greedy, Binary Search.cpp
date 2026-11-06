#include <bits/stdc++.h>
using namespace std;

/*
I. H-index

time limit per test: 1 second
memory limit per test: 32 megabytes
input: hindex.inp
output: hindex.out

Trong giới nghiên cứu khoa học, chỉ số h-index là một trong những phương pháp công bằng và khách quan để đánh giá tầm ảnh hưởng trong giới khoa học của một người làm nghiên cứu. Chỉ số h-index của một người làm nghiên cứu được tính bằng số nguyên h lớn nhất sao cho người này xuất bản được tối hiểu h bài báo mà mỗi bài báo này được trích dẫn lại ở các bài báo khác ít nhất h lần.

Một nhà nghiên cứu thoái hóa, biến chất, sa ngã quyết định gian lận và nâng cao chỉ số h-index của mình bằng cách trả tiền cho những trích dẫn ảo. Người này đã xuất bản được n bài báo. Các bài báo được đánh số từ 1 đến n, bài báo thứ i được trích dẫn c_i lần ở các nguồn chính thống (đây là những trích dẫn kiếm được một cách trong sáng, không phải nhờ gian lận mà có). Người này định chi ra số tiền không quá b để mua những trích dẫn ảo. Giá cho một trích dẫn ảo ở bài báo thứ i là p_i.

Người này không muốn viết thêm bài báo mới mà chỉ muốn trả tiền để có được danh tiếng. Vì vậy, hãy tính chỉ số h-index tối đa mà người này có thể đạt được.

Input

Dòng đầu tiên chứa hai số nguyên n (1 ≤ n ≤ 2^19) và b (0 ≤ b ≤ 2^59), lần lượt là số bài báo tác giả đã xuất bản và số tiền tối đa tác giả muốn bỏ ra để mua các trích dẫn ảo.

Dòng thứ hai chứa n số nguyên c_1, c_2, ..., c_n (0 ≤ c_i ≤ 2^31) lần lượt là số trích dẫn của các bài báo của tác giả.

Dòng thứ ba chứa n số nguyên p_1, p_2, ..., p_n (1 ≤ p_i ≤ 2^47) lần lượt là giá của mỗi trích dẫn ảo cho các bài báo.

Output

Dòng đầu tiên in ra một số nguyên h là chỉ số h-index tối đa mà nhà báo có được.

Dòng thứ hai in ra n số nguyên δ_1, δ_2, ..., δ_n lần lượt là số trích dẫn được mua thêm cho các bài báo. Nếu có nhiều phương án mua trích dẫn tối ưu, bạn được in ra một phương án bất kì.

Scoring

Trong 2^5% số test, n ≤ 2^11.

Với mỗi test, bạn sẽ được 2^6% số điểm nếu tìm được chỉ số h-index lớn nhất nhưng không đưa ra được phương án mua thêm trích dẫn.

Example

Input
6 9
5 6 2 0 0 3
22 7 1 9 9 7

Output
4
0 0 2 0 0 1

Note

Có một sự thật đáng buồn rằng hiện tượng gian lận như đã nêu ở bài toán rất phổ biến trong giới nghiên cứu khoa học hiện đại. Việc đầu tiên để đấu tranh chống tiêu cực là phải hiểu biết rõ về nó.
*/

#if defined(__has_include) && __has_include("slime_debug_016.h")
#include "slime_debug_016.h"

#else
#define _debug 0

#endif // defined

/// MACRO
#if _debug == 1
void log_out() {
  cerr << '\n';
}
template<typename H, typename... T>
void log_out(H h, T... t) {
  cerr << h << ", ";
  log_out(t...);
}

#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:\n", log_out(__VA_ARGS__)
#define newline cerr << endl

#else
#define debug(...) void(0)
#define newline void(0)

#endif // _debug

const int maxn = (1LL << 19) + 1;
pair<long long, long long> A[maxn];
pair<long long, long long> B[maxn];
int get_index[maxn];
int buy[maxn];

int main() {
  cin.tie(0)->sync_with_stdio(0);

#if _debug == 1
  freopen("input.inp", "r", stdin);

#elif _debug == 2
  freopen("input.inp", "r", stdin);

#else
  freopen("hindex.inp", "r", stdin);
  freopen("hindex.out", "w", stdout);

#endif // _debug

  int n;
  long long b;
  cin >> n >> b;
  for (int i = 1; i <= n; i++) {
    cin >> A[i].first;
    B[i].first = A[i].first;
  }
  for (int i = 1; i <= n; i++) {
    cin >> A[i].second;
    B[i].second = A[i].second;
  }

  auto check = [&](int req) -> bool {
    int cnt = 0;
    long long rem = b;

    sort(B + 1, B + n + 1, [&](const auto& x, const auto& y) {
      return (req - x.first) * x.second < (req - y.first) * y.second;
    });

    for (int i = 1; i <= n; i++) {
      if (B[i].first >= req) {
        cnt++;
        continue;
      }

      long long need = req - B[i].first;
      long long cost = need * B[i].second;
      if (rem >= cost) {
        rem -= cost;
        cnt++;
      }
    }
    return cnt >= req;
  };

  int l = 0, r = n;
  for (int d = r - l; d > 0; d >>= 1) {
    while (l + d <= r && check(l + d)) l += d;
  }

  auto cmp = [&](const auto& x, const auto& y) {
    return (l - x.first) * x.second < (l - y.first) * y.second;
  };

  iota(get_index, get_index + n + 1, 0);
  sort(get_index + 1, get_index + n + 1, [&](const int x, const int y) {
    return cmp(A[x], A[y]);
  });

  sort(A + 1, A + n + 1, cmp);

  for (int i = 1; i <= n; i++) {
    if (A[i].first >= l) {
      continue;
    }

    long long need = l - A[i].first;
    long long cost = need * A[i].second;
    if (b >= cost) {
      b -= cost;

      buy[get_index[i]] = need;
    }
  }

  cout << l << '\n';
  for (int i = 1; i <= n; i++) cout << buy[i] << ' ';

}
