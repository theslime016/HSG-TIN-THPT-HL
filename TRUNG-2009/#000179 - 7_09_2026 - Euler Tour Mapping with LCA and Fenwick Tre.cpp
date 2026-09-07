#include <bits/stdc++.h>
using namespace std;

/*
Tên bài toán: Hành trình Di sản

Mô tả:
Tỉnh Lạng Sơn đang quy hoạch một mạng lưới giao thông kết nối các điểm di sản văn hóa. Mạng lưới gồm N điểm di sản (đánh số từ 1 đến N) được kết nối bởi N - 1 tuyến đường hai chiều, đảm bảo luôn có đường đi giữa hai điểm bất kỳ. Tuyến đường thứ i kết nối hai điểm u_i, v_i và có chiều dài ban đầu là w_i.

Để phục vụ các đoàn khách du lịch, Sở Du lịch thường xuyên phải lên kế hoạch cho các tour tham quan đặc biệt và đồng thời cập nhật lại thông tin đường đi do công tác tu bổ.

Có Q sự kiện xảy ra, thuộc một trong hai loại sau:
- 1 id x: Tuyến đường thứ id (theo thứ tự dữ liệu đầu vào) được sửa chữa và cập nhật chiều dài mới thành x.
- 2 k V_1 V_2 ... V_k: Một đoàn làm phim cần quay tư liệu tại đúng k điểm di sản V_1, V_2, ..., V_k. Ban tổ chức cần rào chắn một tập hợp các tuyến đường có tổng chiều dài nhỏ nhất sao cho từ bất kỳ điểm quay nào trong tập k điểm trên đều có thể di chuyển đến các điểm quay còn lại mà chỉ sử dụng các tuyến đường đã được rào chắn. Hãy tính tổng chiều dài của tập hợp các tuyến đường này.

Dữ liệu vào (Input):
- Dòng đầu tiên chứa hai số nguyên dương N, Q (1 <= N, Q <= 10^5).
- N - 1 dòng tiếp theo, dòng thứ i chứa ba số nguyên u_i, v_i, w_i (1 <= u_i, v_i <= N; 1 <= w_i <= 10^9) mô tả tuyến đường thứ i.
- Q dòng tiếp theo, mỗi dòng bắt đầu bằng loại sự kiện (1 hoặc 2):
  + Nếu là 1, tiếp theo là hai số nguyên id và x (1 <= id < N; 1 <= x <= 10^9).
  + Nếu là 2, tiếp theo là số nguyên k (2 <= k <= N), theo sau là k số nguyên phân biệt V_1, V_2, ..., V_k (1 <= V_j <= N).
- Dữ liệu đảm bảo tổng các giá trị k trong tất cả các truy vấn loại 2 không vượt quá 3 * 10^5.

Dữ liệu ra (Output):
- Với mỗi truy vấn loại 2, in ra trên một dòng một số nguyên là tổng chiều dài nhỏ nhất của các tuyến đường cần rào chắn.

Ví dụ:

Input:
6 5
1 2 2
1 3 5
2 4 1
2 5 3
3 6 4
2 3 4 5 6
2 2 4 5
1 3 10
2 3 4 5 6
2 3 1 4 6

Output:
12
4
21
16

Ràng buộc (Subtasks):
- Subtask 1 (20% số điểm): N, Q <= 2000. Tổng các k <= 5000.
- Subtask 2 (30% số điểm): Không có truy vấn loại 1.
- Subtask 3 (50% số điểm): Không có ràng buộc gì thêm.
*/

const int maxn = 1e5 + 100;
const int _log = 20;
vector<pair<int, long long>> adj[maxn];
int timein[maxn], timeout[maxn];
int up[maxn][_log];
int task[maxn];
long long fenwick[maxn];
int n, q;
int timer = 1;

struct edge {
  int a, b;
  long long val;
} A[maxn];

void update(int index, const long long &val) {
  for (; index <= n; index += index & -index) {
    fenwick[index] += val;
  }
}

void proc(int l, int r, const long long &val) {
  update(l, val);
  update(r + 1, -val);
}

long long fetch(int index) {
  long long res = 0;
  for (; index > 0; index -= index & -index) {
    res += fenwick[index];
  }
  return res;
}

void dfs(int index = 1, int parent = 0, long long d = 0) {
  timein[index] = timer++;

  proc(timein[index], timein[index], d);

  up[index][0] = parent;
  for (int exp = 1; exp < _log; exp++) {
    up[index][exp] = up[up[index][exp - 1]][exp - 1];
  }

  for (const auto &x : adj[index]) {
    if (x.first == parent)
      continue;
    dfs(x.first, index, d + x.second);
  }
  timeout[index] = timer - 1;
}

bool islca(int a, int b) {
  return timein[a] <= timein[b] && timeout[a] >= timeout[b];
}

int lca(int a, int b) {
  if (islca(a, b))
    return a;
  if (islca(b, a))
    return b;

  for (int exp = _log - 1; exp >= 0; exp--) {
    if (up[a][exp] != 0 && !islca(up[a][exp], b)) {
      a = up[a][exp];
    }
  }
  return up[a][0];
}

long long dist(int a, int b) {
  return fetch(timein[a]) + fetch(timein[b]) - 2LL * fetch(timein[lca(a, b)]);
}

int main() {
  cin.tie(0)->sync_with_stdio(0);

  cin >> n >> q;
  for (int i = 1; i < n; i++) {
    cin >> A[i].a >> A[i].b >> A[i].val;
    adj[A[i].a].push_back({A[i].b, A[i].val});
    adj[A[i].b].push_back({A[i].a, A[i].val});
  }

  dfs();
  for (int i = 1; i < n; i++) {
    if (timein[A[i].a] > timein[A[i].b]) {
      swap(A[i].a, A[i].b);
    }
  }

  for (int i = 1; i <= q; i++) {
    int type;
    cin >> type;
    if (type == 1) {
      int index;
      long long diff;
      cin >> index >> diff;
      int temp = A[index].val;
      A[index].val = diff;
      diff -= temp;
      int rindex = A[index].b;
      proc(timein[rindex], timeout[rindex], diff);
    } else if (type == 2) {
      int k;
      cin >> k;
      for (int i = 1; i <= k; i++) {
        cin >> task[i];
      }

      sort(task + 1, task + k + 1,
           [&](const int x, const int y) { return timein[x] < timein[y]; });
      task[k + 1] = task[1];

      for (int i = 0; i <= k + 1; i++) {
        cerr << task[i] << ' ';
      }
      cerr << '\n';

      long long perimeter = 0;
      for (int i = 1; i <= k; i++) {
        perimeter += dist(task[i], task[i + 1]);
        cerr << dist(task[i], task[i + 1]) << ' ';
      }
      cout << perimeter / 2 << '\n';
    }
  }

  for (int i = 1; i <= n; i++) {
    cout << i << ' ' << timein[i] << ' ' << timeout[i] << ' '
         << fetch(timein[i]) << '\n';
  }

  cout << '\n';
  for (int i = 1; i <= n; i++) {
    for (int j = i; j <= n; j++) {
      cout << i << ' ' << j << ' ' << lca(i, j) << ' ' << lca(j, i) << '\n';
    }
  }
  cout << '\n';
}
