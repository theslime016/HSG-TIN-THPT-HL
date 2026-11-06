#include <bits/stdc++.h>
using namespace std;

/*
F. Né tránh cẩu lương

time limit per test: 1.5 seconds
memory limit per test: 256 megabytes
input: cauluong.inp
output: cauluong.out

Các thế hệ sinh viên từng học ở Đại học Sư Phạm Hà Nội hay Đại học Quốc Gia Hà Nội hẳn đều biết, trên con đường dẫn từ nhà K ra thư viện gần khu ký túc xá, men theo bờ tường chùa Thánh Chúa, có một hàng ghế đá dài được đặt cạnh một vườn cây. Nơi đây là địa điểm lý tưởng để thư giãn, có thể vừa ngồi đọc sách, vừa tận hưởng bầu không khí trong lành cùng bóng mát của những tán cây.

Nhưng trớ trêu thay, nơi đây cũng tiềm ẩn nhiều nguy cơ xảy ra bạo lực. Số là, rất nhiều cặp đôi đã lợi dụng dãy ghế đá này để hẹn hò, tâm sự và làm nhiều chuyện khác. Các bạn hẳn đều biết, hẹn hò và thể hiện tình cảm nơi công cộng là hành vi đáng lên án, vi phạm các quy tắc đạo đức chuẩn mực của xã hội, làm mất mỹ quan đô thị và quan trọng nhất là xâm phạm tới quyền mưu cầu hạnh phúc của dân FA — một quyền bất khả xâm phạm được pháp luật bảo vệ. Nghiêm trọng hơn, không ít cặp đôi đã làm "nhiều chuyện khác" tới mức khiến những người xung quanh nhẹ thì thấy phản cảm, khó chiu; nặng thì nóng mắt và muốn gây chiến tranh. Tất nhiên, nhiều cặp đôi yêu nhau đã phải chịu hậu quả hết sức thương tâm cho hành vi gây hấn của mình. Một vài cặp đôi khác đã nhận ra được sự sai trái, nên có cặp đôi hôm trước đến ngồi cùng nhau thì hôm sau chỉ có một người đến còn người kia biến đi đâu không rõ; cũng có cặp đôi khác thì hôm trước ngồi cùng nhau còn hôm sau thì mỗi người ngồi một ghế khác nhau và cùng với một người khác.

Dãy ghế có n chiếc ghế đá xếp thành đường thẳng, được đánh số lần lượt theo thứ tự từ 1 tới n. Khoảng cách giữa hai ghế đá liên tiếp bất kỳ là 1. Một ngày, GSPVH muốn ra ghế đá ngồi đọc nốt cuốn tiểu thuyết "Ai hiểu được lòng em" nổi tiếng do nhà văn Lục Xu viết. Những chiếc ghế đá từ vị trí l tới vị trí r được đặt gần nhiều cây to, vì thế nên không khí sẽ rất dễ chịu và GSPVH muốn ngồi ở một trong các ghế này. Khi GSPVH tới nơi, đã có sẵn m cặp đôi đang ngồi hẹn hò tâm sự ở các ghế đá số p1, p2, ..., pm. Tất cả các ghế còn lại đều trống. Vốn là người chịu nhiều đau thương trong tình yêu, GSPVH muốn chọn một chiếc ghế đá trống để ngồi sao cho khoảng cách từ ghế đá này đến cặp đôi ngồi gần nhất là lớn nhất có thể. Nếu như mọi ghế đá từ l đến r đều đã bị chiếm bởi các cặp đôi, GSPVH buộc phải chọn một ghế bất kỳ, dùng vũ lực để cưỡng chế nhân vật nam đang ngồi tại đây ra khỏi ghế và ngồi vào đây thay thế.

Input

Dòng đầu tiên chứa hai số nguyên θ và t (1 ≤ θ ≤ 5, 1 ≤ t ≤ 10^6) — số thứ tự của subtask chứa test này và số bộ dữ liệu trong file input. t bộ dữ liệu này lần lượt được mô tả sau đó, theo khuôn dạng sau:

- Dòng đầu tiên là một dòng trống.
- Dòng thứ hai chứa hai số nguyên n và m (1 ≤ n ≤ 10^9, 1 ≤ m ≤ 15·10^4) — số ghế đá trên hàng ghế và số cặp đôi đang ngồi ở đây.
- Dòng thứ ba chứa hai số nguyên l và r (1 ≤ l ≤ r ≤ n) — ghế đầu tiên và ghế cuối cùng trong những ghế mà GSPVH muốn ngồi.
- Dòng thứ tư chứa m số nguyên phân biệt p1, p2, ..., pm (1 ≤ pi ≤ n) — vị trí các ghế mà các cặp đôi chọn để hẹn hò.

Tổng giá trị của m trong các bộ dữ liệu của một file input không quá 10^6.

Output

Với mỗi bộ test, in ra kết quả là một số nguyên: Nếu trong các ghế từ vị trí l đến vị trí r còn một ghế trống, in ra khoảng cách tối đa từ vị trí GSPVH ngồi đên cặp đôi gần nhất. Nếu GSPVH buộc phải dùng vũ lực để cưỡng ép một nhân vật nam ra khỏi ghế, in ra 0.

Các số được viết trên một dòng, ngăn cách với nhau bởi dấu cách.

Scoring

Bộ test của bài gồm 100 tests, mỗi test có giá trị 1 điểm. Các test được chia vào 5 subtask với ràng buộc như sau:

- Subtask 1 (10 điểm): m ≤ 1
- Subtask 2 (15 điểm): m ≤ 2
- Subtask 3 (15 điểm): max(m, n) ≤ 3000 và [công thức trong ảnh]
- Subtask 4 (25 điểm): max(m, n) ≤ 150000 và [công thức trong ảnh]
- Subtask 5 (35 điểm): Không có ràng buộc gì thêm.

Với mỗi một test, nếu output của bạn có định dạng không hợp lệ (chứa nhiều hơn hoặc ít hơn t số, chứa số không phải số nguyên hoặc số có giá trị không thuộc đoạn [0..10^9], chứa ký tự lạ không phải số,...), bạn được 0 điểm. Ngược lại, giả sử bạn đáp đúng c trong số t bộ dữ liệu, bạn được [công thức trong ảnh] điểm.

Example

Input

5 2

5 2
1 3
1 5

5 3
1 3
1 2 3

Output

2 0

Note

Trong bộ dữ liệu thứ nhất, GSPVH muốn ngồi một trong ba ghế số 1, 2 hoặc 3. Có hai cặp đôi đang ngồi ở hai ghế số 1 và 5, do đó GSPVH sẽ chọn ghế số 3, nơi có khoảng cách tới cặp đôi gần nhất là 2.

Trong bộ dữ liệu thứ hai, cả ba ghế mà GSPVH muốn ngồi (ghế số 1, 2 và 3) đều bị các cặp đôi chiếm dụng. Không còn cách nào khác, GSPVH buộc phải vùng lên, đấu tranh để giành ghế cho mình.
*/

#if defined(__has_include) && __has_include("slime_debug_016.h")
#include "slime_debug_016.h"

#else
#define _debug 0

#endif // defined

/// MACRO
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
#define debug(...) void(0)
#define newline void(0)

#endif // _debug

const int maxn = 1e6 + 5;
const int inf = 1e9;
int A[maxn];

int main() {
  cin.tie(0)->sync_with_stdio(0);

#if _debug == 1
  freopen("input.inp", "r", stdin);

#elif _debug == 2
  freopen("input.inp", "r", stdin);

#else
  freopen("cauluong.inp", "r", stdin);
  freopen("cauluong.out", "w", stdout);

#endif // _debug

  int cauluong;
  cin >> cauluong;

  int n, m, l, r;

  int t;
  cin >> t;
  while (t--) {
    cin >> n >> m;
    cin >> l >> r;

    A[1] = 0; A[m + 2] = (n << 1);
    for (int i = 2; i <= m + 1; i++) cin >> A[i];
    sort(A + 2, A + m + 2);

    #if _debug == 1
    newline;
    cerr << "A: " << ' ';
    for (int i = 1; i <= m + 2; i++) {
      cerr << A[i] << ' ';
    }
    newline;

    #endif // _debug

    int ptr = upper_bound(A + 1, A + m + 3, l) - A - 1;
    int min_dist = 0;
    while (ptr < m + 2 && A[ptr] <= r) {
      int mid = A[ptr] + (A[ptr + 1] - A[ptr])/2;
      if (ptr == 1) mid = l;

      mid = min(r, max(l, mid));
      int dist = inf;

      if (ptr != 1) dist = min(dist, abs(mid - A[ptr]));
      if (ptr + 1 != m + 2) dist = min(dist, abs(mid - A[ptr + 1]));

      if (mid != A[ptr] && mid != A[ptr+1]) min_dist = max(min_dist, dist);
      ptr++;
    }

    cout << min_dist << '\n';
  }

}
