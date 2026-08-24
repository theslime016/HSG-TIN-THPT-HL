/*late in autumn*/
#include <bits/stdc++.h>
using namespace std;

/*
Để bảo vệ vương quốc khỏi lũ quái vật phương Bắc, Nhà vua ra lệnh xây dựng một bức tường thành khổng lồ trải dài trên một ranh giới thẳng có độ dài N mét (được đánh số tọa độ từ 1 đến N). Ban đầu, tại mọi tọa độ, độ cao của tường thành đều bằng 0.
Quá trình xây dựng kéo dài trong nhiều năm, được giám sát bởi vị quan Tể tướng có tính khí thất thường. Ông ta liên tục đưa ra Q mệnh lệnh thuộc 4 loại khác nhau. Đôi khi là đắp thêm đất, đôi khi lại dùng phép thuật san bằng tất cả.
CÁC LOẠI MỆNH LỆNH (TRUY VẤN):
1. Mệnh lệnh Đắp đất (Loại 1): 1 L R v
   Đắp thêm một lớp đất cao v mét dọc theo đoạn tường từ mét thứ L đến mét thứ R. (Tăng A[i] thêm v với mọi L <= i <= R).
2. Mệnh lệnh San phẳng (Loại 2): 2 L R v
   Tể tướng không hài lòng. Ông ta dùng phép thuật cắt gọt hoặc đúc thêm đá để toàn bộ đoạn tường từ mét thứ L đến mét thứ R có độ cao CHÍNH XÁC bằng v. (Gán A[i] = v với mọi L <= i <= R).
3. Báo cáo Khối lượng (Loại 3): 3 L R
   Nhà vua muốn biết tổng khối lượng vật liệu cấu thành nên đoạn tường từ L đến R. Cụ thể, hãy in ra TỔNG độ cao của các mét tường trong đoạn này.
4. Báo cáo Điểm yếu (Loại 4): 4 L R
   Tướng quân phòng vệ muốn tìm chòi canh cao nhất. Hãy in ra ĐỘ CAO LỚN NHẤT trong đoạn tường từ L đến R.
DỮ LIỆU VÀO (Input): Đọc từ file WALL.INP
- Dòng đầu tiên chứa 2 số nguyên dương N và Q (N là chiều dài biên giới, Q là số lượng mệnh lệnh).
- Q dòng tiếp theo, mỗi dòng bắt đầu bằng một số nguyên T (1 <= T <= 4) thể hiện loại mệnh lệnh. 
  + Nếu T = 1 hoặc T = 2, tiếp theo là 3 số L, R, v.
  + Nếu T = 3 hoặc T = 4, tiếp theo là 2 số L, R.
DỮ LIỆU RA (Output): Ghi ra file WALL.OUT
- Với mỗi truy vấn loại 3 và loại 4, in kết quả trên một dòng. (Chú ý: Kết quả có thể rất lớn, vượt quá giới hạn số nguyên 32-bit).
RÀNG BUỘC (Constraints):
- 1 <= L <= R <= N <= 10^9
- 1 <= Q <= 10^5
- 1 <= v <= 10^5
- Time Limit: 1.0s
- Memory Limit: 256MB
--------------------------------------------------
VÍ DỤ (TEST CASES)
WALL.INP:
10 6
1 1 5 10
1 4 8 5
4 3 6
2 3 7 8
3 1 10
4 1 10
WALL.OUT:
15
56
10
GIẢI THÍCH VÍ DỤ:
- Khởi tạo: [0, 0, 0, 0, 0, 0, 0, 0, 0, 0]
- Lệnh '1 1 5 10': Cộng 10 vào đoạn 1-5 -> [10, 10, 10, 10, 10, 0, 0, 0, 0, 0]
- Lệnh '1 4 8 5': Cộng 5 vào đoạn 4-8 -> [10, 10, 10, 15, 15, 5, 5, 5, 0, 0]
- Lệnh '4 3 6': Tìm Max đoạn 3-6 -> Lớn nhất trong {10, 15, 15, 5} là 15.
- Lệnh '2 3 7 8': San phẳng đoạn 3-7 thành độ cao 8 -> [10, 10, 8, 8, 8, 8, 8, 5, 0, 0]
- Lệnh '3 1 10': Tính tổng toàn bộ -> 10+10+8+8+8+8+8+5+0+0 = 56.
- Lệnh '4 1 10': Tìm Max toàn bộ -> Lớn nhất là 10.
*/

const long long inf = 1e15;
const int maxnode = 2e5 + 5;
const int _log = 20;
struct node {
  int len;
  long long sum;
  long long maxval;
  long long lazyset;
  long long lazysum;
} segment[(1 << _log)];
// zkw

struct query {
  int t;
  int l, r;
  long long val;
};

int main() {
  cin.tie(0)->sync_with_stdio(0);

  for (int index = 0; index < (1 << _log); index++)
    segment[index].lazyset = -1;

  int n, q;
  cin >> n >> q;
  vector<long long> interval;
  interval.reserve(2 * q);
  vector<query> task(q);
  for (int i = 0; i < q; i++) {
    cin >> task[i].t >> task[i].l >> task[i].r;
    if (task[i].t == 1 || task[i].t == 2)
      cin >> task[i].val;

    interval.push_back(task[i].l);
    interval.push_back(task[i].r + 1);
  }

  sort(interval.begin(), interval.end());
  interval.erase(unique(interval.begin(), interval.end()), interval.end());

  int interval_count = (int)interval.size() - 1;
  int m = 1;
  int h = 0;
  while (m <= interval_count + 1) {
    m <<= 1;
    h++;
  }

  for (int i = 0; i < interval_count; i++) {
    segment[i + 1 + m].len = (interval[i + 1] - 1) - interval[i] + 1;
  }

  for (int i = m - 1; i > 0; i--) {
    segment[i].len += segment[i << 1].len + segment[i << 1 | 1].len;
  }

  auto fnd = [&](int l, int r) -> pair<int, int> {
    int lindex =
        lower_bound(interval.begin(), interval.end(), l) - interval.begin();
    int rindex =
        lower_bound(interval.begin(), interval.end(), r + 1) - interval.begin();
    return {lindex + m, rindex + 1 + m};
  };

  auto apply = [&](int index, int type, const long long &val) {
    if (segment[index].len == 0)
      return;

    if (type == 1) {
      // sum
      segment[index].sum += val * segment[index].len;
      segment[index].maxval += val;
      if (index < m) {
        if (segment[index].lazyset != -1)
          segment[index].lazyset += val;
        else
          segment[index].lazysum += val;
      }
    } else if (type == 2) {
      // set
      segment[index].sum = val * segment[index].len;
      segment[index].maxval = val;
      if (index < m) {
        segment[index].lazyset = val;
        segment[index].lazysum = 0;
      }
    }
  };

  auto pushdown_path = [&](int index) {
    for (int rank = h; rank > 0; rank--) {
      int rindex = index >> rank;

      if (segment[rindex].lazyset != -1) {
        apply(rindex << 1, 2, segment[rindex].lazyset);
        apply(rindex << 1 | 1, 2, segment[rindex].lazyset);
        segment[rindex].lazyset = -1;
      }

      if (segment[rindex].lazysum != 0) {
        apply(rindex << 1, 1, segment[rindex].lazysum);
        apply(rindex << 1 | 1, 1, segment[rindex].lazysum);
        segment[rindex].lazysum = 0;
      }
    }
  };

  auto pushup_path = [&](int index) {
    for (index >>= 1; index > 0; index >>= 1) {
      segment[index].sum =
          segment[index << 1].sum + segment[index << 1 | 1].sum;
      segment[index].maxval =
          max(segment[index << 1].maxval, segment[index << 1 | 1].maxval);
      if (segment[index].lazyset != -1) {
        segment[index].sum = segment[index].lazyset * segment[index].len;
        segment[index].maxval = segment[index].lazyset;
      } else if (segment[index].lazysum != 0) {
        segment[index].sum += segment[index].lazysum * segment[index].len;
        segment[index].maxval += segment[index].lazysum;
      }
    }
  };

  auto update = [&](int type, int l, int r, const long long &val) {
    auto [s, t] = fnd(l, r);
    pushdown_path(s);
    pushdown_path(t);

    int os = s;
    int ot = t;
    for (; s ^ t ^ 1; s >>= 1, t >>= 1) {
      if (~s & 1)
        apply(s ^ 1, type, val);
      if (t & 1)
        apply(t ^ 1, type, val);
    }
    pushup_path(os);
    pushup_path(ot);
  };

  auto fetch = [&](int type, int l, int r) {
    auto [s, t] = fnd(l, r);
    pushdown_path(s);
    pushdown_path(t);

    long long sum = 0;
    long long mx = -inf;
    for (; s ^ t ^ 1; s >>= 1, t >>= 1) {
      if (~s & 1) {
        sum += segment[s ^ 1].sum;
        mx = max(mx, segment[s ^ 1].maxval);
      }
      if (t & 1) {
        sum += segment[t ^ 1].sum;
        mx = max(mx, segment[t ^ 1].maxval);
      }
    }
    return type == 3 ? sum : mx;
  };

  for (auto &lp : task) {
    if (lp.t == 1 || lp.t == 2) {
      update(lp.t, lp.l, lp.r, lp.val);
    } else {
      cout << fetch(lp.t, lp.l, lp.r) << '\n';
    }
  }

  // for (int i = 0; i < 2 * m; i++) {
  //   cerr << segment[i].len << ' ' << segment[i].sum << ' ' <<
  //   segment[i].maxval
  //        << ' ' << segment[i].lazysum << ' ' << segment[i].lazyset << '\n';
  // }
}
