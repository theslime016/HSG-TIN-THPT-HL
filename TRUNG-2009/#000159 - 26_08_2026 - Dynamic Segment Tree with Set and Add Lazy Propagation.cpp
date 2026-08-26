#include <bits/stdc++.h>
using namespace std;

/*
Để bảo vệ vương quốc khỏi lũ quái vật phương Bắc, Nhà vua ra lệnh xây dựng một
bức tường thành khổng lồ trải dài trên một ranh giới thẳng có độ dài N mét (được
đánh số tọa độ từ 1 đến N). Ban đầu, tại mọi tọa độ, độ cao của tường thành đều
bằng 0.
Quá trình xây dựng kéo dài trong nhiều năm, được giám sát bởi vị quan Tể tướng
có tính khí thất thường. Ông ta liên tục đưa ra Q mệnh lệnh thuộc 4 loại khác
nhau. Đôi khi là đắp thêm đất, đôi khi lại dùng phép thuật san bằng tất cả.
CÁC LOẠI MỆNH LỆNH (TRUY VẤN):
1. Mệnh lệnh Đắp đất (Loại 1): 1 L R v
   Đắp thêm một lớp đất cao v mét dọc theo đoạn tường từ mét thứ L đến mét thứ
R. (Tăng A[i] thêm v với mọi L <= i <= R).
2. Mệnh lệnh San phẳng (Loại 2): 2 L R v
   Tể tướng không hài lòng. Ông ta dùng phép thuật cắt gọt hoặc đúc thêm đá để
toàn bộ đoạn tường từ mét thứ L đến mét thứ R có độ cao CHÍNH XÁC bằng v. (Gán
A[i] = v với mọi L <= i <= R).
3. Báo cáo Khối lượng (Loại 3): 3 L R
   Nhà vua muốn biết tổng khối lượng vật liệu cấu thành nên đoạn tường từ L đến
R. Cụ thể, hãy in ra TỔNG độ cao của các mét tường trong đoạn này.
4. Báo cáo Điểm yếu (Loại 4): 4 L R
   Tướng quân phòng vệ muốn tìm chòi canh cao nhất. Hãy in ra ĐỘ CAO LỚN NHẤT
trong đoạn tường từ L đến R.

DỮ LIỆU VÀO (Input): Đọc từ file WALL.INP
- Dòng đầu tiên chứa 2 số nguyên dương N và Q (N là chiều dài biên giới, Q là số
lượng mệnh lệnh).
- Q dòng tiếp theo, mỗi dòng bắt đầu bằng một số nguyên T (1 <= T <= 4) thể hiện
loại mệnh lệnh.
  + Nếu T = 1 hoặc T = 2, tiếp theo là 3 số L, R, v.
  + Nếu T = 3 hoặc T = 4, tiếp theo là 2 số L, R.
DỮ LIỆU RA (Output): Ghi ra file WALL.OUT
- Với mỗi truy vấn loại 3 và loại 4, in kết quả trên một dòng. (Chú ý: Kết quả
có thể rất lớn, vượt quá giới hạn số nguyên 32-bit).
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
- Lệnh '2 3 7 8': San phẳng đoạn 3-7 thành độ cao 8 -> [10, 10, 8, 8, 8, 8, 8,
5, 0, 0]
- Lệnh '3 1 10': Tính tổng toàn bộ -> 10+10+8+8+8+8+8+5+0+0 = 56.
- Lệnh '4 1 10': Tìm Max toàn bộ -> Lớn nhất là 10.
*/

const long long inf = 1e15;
const int maxnode = 6e6;
struct node {
  long long sum;
  long long maxval;

  long long lazysum;
  long long lazyset;

  int left;
  int right;
} segment[maxnode];

int root = 1;
int node_count = 2;
long long __start_ = 1;
long long __end_ = 1e9;

int newnode() {
  int index = node_count++;
  segment[index].sum = 0;
  segment[index].maxval = 0;
  segment[index].lazysum = 0;
  segment[index].lazyset = -inf;
  return index;
}

void apply(int index, int type, int l, int r, const long long &val) {
  int len = r - l + 1;
  if (type == 2) {
    segment[index].sum = val * len;
    segment[index].maxval = val;
    segment[index].lazyset = val;
    segment[index].lazysum = 0;
  } else if (type == 1) {
    segment[index].sum += val * len;
    segment[index].maxval += val;
    if (segment[index].lazyset != -inf)
      segment[index].lazyset += val;
    else
      segment[index].lazysum += val;
  }
}

void pushup(int index) {
  segment[index].sum = 0;
  segment[index].maxval = -inf;
  int lindex = segment[index].left;
  int rindex = segment[index].right;
  if (segment[index].left) {
    segment[index].sum += segment[lindex].sum;
    segment[index].maxval = max(segment[index].maxval, segment[lindex].maxval);
  }

  if (segment[index].right) {
    segment[index].sum += segment[rindex].sum;
    segment[index].maxval = max(segment[index].maxval, segment[rindex].maxval);
  }
}

void pushdown(int index, int l, int r) {
  if (!segment[index].lazysum && segment[index].lazyset == -inf)
    return;

  if (!segment[index].left)
    segment[index].left = newnode();
  if (!segment[index].right)
    segment[index].right = newnode();

  int mid = l + (r - l) / 2;

  if (segment[index].lazyset != -inf) {
    apply(segment[index].left, 2, l, mid, segment[index].lazyset);
    apply(segment[index].right, 2, mid + 1, r, segment[index].lazyset);
  }

  if (segment[index].lazysum) {
    apply(segment[index].left, 1, l, mid, segment[index].lazysum);
    apply(segment[index].right, 1, mid + 1, r, segment[index].lazyset);
  }

  segment[index].lazyset = -inf;
  segment[index].lazysum = 0;
}

void update(int &index, int type, int l, int r, int u, int v,
            const long long &val) {
  if (!index)
    index = newnode();

  if (l > v || r < u)
    return;
  if (l >= u && r <= v) {
    apply(index, type, l, r, val);
    return;
  }

  pushdown(index, l, r);

  int mid = l + (r - l) / 2;

  update(segment[index].left, type, l, mid, u, v, val);
  update(segment[index].right, type, mid + 1, r, u, v, val);

  pushup(index);
}

long long fetch(int index, int type, int l, int r, int u, int v) {
  if (!index)
    return 0;

  if (l > v || r < u)
    return 0;
  if (l >= u && r <= v) {
    return type == 3 ? segment[index].sum : segment[index].maxval;
  }

  pushdown(index, l, r);

  int mid = l + (r - l) / 2;

  long long leftval = fetch(segment[index].left, type, l, mid, u, v);
  long long rightval = fetch(segment[index].right, type, mid + 1, r, u, v);

  return type == 3 ? (leftval + rightval) : max(leftval, rightval);
}

void ranker() {
  deque<pair<int, int>> task;
  task.push_back({root, 1});
  int last_rank = 0;
  while (!task.empty()) {
    auto [index, rank] = task.front();
    task.pop_front();

    if (rank != last_rank) {
      cerr << "\nrank: " << rank << ' ';
      last_rank = rank;
    }

    cerr << index << '[' << segment[index].sum << '/' << segment[index].maxval
         << "] ";

    if (segment[index].left)
      task.push_back({segment[index].left, rank + 1});
    if (segment[index].right)
      task.push_back({segment[index].right, rank + 1});
  }
}

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n, q;
  cin >> n >> q;

  __end_ = 10;

  while (q--) {
    int type;
    cin >> type;
    if (type == 1 || type == 2) {
      int l, r;
      long long val;
      cin >> l >> r >> val;
      update(root, type, __start_, __end_, l, r, val);
    } else {
      int l, r;
      cin >> l >> r;
      cout << fetch(root, type, __start_, __end_, l, r) << '\n';
    }
  }
  ranker();
}
