#include <bits/stdc++.h>
using namespace std;

#define _debug 0

#if _debug == 1
#define debug(x) cerr << #x << ':' << (x) << ' ';
#define newline cerr << '\n';

#else
#define debug(x)
#define newline

#endif // _debug

/*
================================================================================
BÀI TEST THỰC CHIẾN: MẠNG LƯỚI THÔNG TIN (TREE NETWORK)
Time Limit: 1.0s
Memory Limit: 256 MB
================================================================================

MÔ TẢ BÀI TOÁN:
Cho một cây vô hướng gồm N đỉnh (đánh số từ 1 đến N). Ban đầu, tất cả các đỉnh
đều có giá trị bằng 0.

Bạn cần xử lý Q thao tác thuộc hai loại sau:
- Thao tác loại 1: "1 u v w" — Cộng thêm giá trị w vào tất cả các đỉnh nằm trên
  đường đi đơn duy nhất từ đỉnh u đến đỉnh v.
- Thao tác loại 2: "2 u v" — Tính tổng giá trị của tất cả các đỉnh nằm trên
  đường đi đơn duy nhất từ đỉnh u đến đỉnh v.

DỮ LIỆU VÀO (INPUT):
- Dòng đầu tiên chứa hai số nguyên dương N và Q (1 <= N, Q <= 10^5).
- Tiếp theo là N - 1 dòng, mỗi dòng chứa hai số nguyên u, v (1 <= u, v <= N,
  u != v) mô tả một cạnh của cây.
- Tiếp theo là Q dòng, mỗi dòng mô tả một thao tác:
  + Nếu là loại 1: "1 u v w" (1 <= u, v <= N, -10^9 <= w <= 10^9).
  + Nếu là loại 2: "2 u v" (1 <= u, v <= N).

DỮ LIỆU RA (OUTPUT):
- Với mỗi thao tác loại 2, in ra một số nguyên duy nhất là tổng giá trị tìm được
  trên một dòng.

RÀNG BUỘC (SUBTASKS):
- Subtask 1 (20% số điểm): N, Q <= 1000.
- Subtask 2 (20% số điểm): Cây có dạng một đường thẳng (đỉnh i nối với đỉnh i+1).
- Subtask 3 (20% số điểm): Mọi thao tác loại 1 đều có u = 1 (cập nhật từ gốc đến
  một đỉnh).
- Subtask 4 (40% số điểm): Không có ràng buộc gì thêm.

================================================================================
HỆ THỐNG TEST CASE
================================================================================

--- Test Case 1 (Cơ bản - Cây nhỏ) ---
Input:
3 3
1 2
2 3
1 1 3 5
2 1 3
2 2 2

Output:
15
5

Giải thích:
- Cập nhật 1 1 3 5: Cộng 5 vào đường đi 1-2-3. Giá trị các đỉnh: [5, 5, 5].
- Truy vấn 2 1 3: Tổng đường đi 1-2-3 là 5 + 5 + 5 = 15.
- Truy vấn 2 2 2: Tổng đường đi từ 2 đến 2 là 5.


--- Test Case 2 (Cây phân nhánh, có số âm) ---
Input:
5 5
1 2
1 3
3 4
3 5
1 2 4 10
2 4 5
1 3 5 -5
2 2 5
2 1 1

Output:
20
20
10

Giải thích:
- Ban đầu: [0, 0, 0, 0, 0]
- Lệnh 1 2 4 10: Đường đi 2-1-3-4 được +10. Mảng: [10, 10, 10, 10, 0]
- Lệnh 2 4 5: Đường đi 4-3-5. Tổng: 10 + 10 + 0 = 20.
- Lệnh 1 3 5 -5: Đường đi 3-5 bị trừ 5. Mảng: [10, 10, 5, 10, -5]
- Lệnh 2 2 5: Đường đi 2-1-3-5. Tổng: 10 + 10 + 5 + (-5) = 20.
- Lệnh 2 1 1: Đỉnh 1 có giá trị 10.


--- Test Case 3 (Cây dạng đường thẳng - Bẫy đệ quy tràn stack) ---
Input:
4 4
1 2
2 3
3 4
1 1 4 1
1 2 3 2
2 1 4
2 2 2

Output:
8
3

Lưu ý: Test này dùng để kiểm tra xem bạn có dùng #pragma để tăng giới hạn stack
hoặc dùng DFS không đệ quy không. Nếu dùng đệ quy trên N=10^5 (dạng đường thẳng),
code của bạn có thể bị Runtime Error (Segmentation Fault).


--- Test Case 4 (Bẫy tràn số - Overflows) ---
Input:
2 3
1 2
1 1 2 1000000000
1 1 2 1000000000
2 1 2

Output:
2000000000

Lưu ý: Tổng có thể lên tới 10^14, hãy chắc chắn bạn dùng long long cho mọi biến
liên quan đến giá trị đỉnh, tổng Segment Tree, và Lazy.


--- Test Case 5 (Cây hình sao - Star Graph) ---
Input:
5 4
1 2
1 3
1 4
1 5
1 2 3 10
1 4 5 20
2 2 4
2 1 1

Output:
60
30

Giải thích:
- Lệnh 1 2 3 10: Đường đi 2-1-3. Các đỉnh 2, 1, 3 được +10. Mảng: [10, 10, 10, 0, 0]
- Lệnh 1 4 5 20: Đường đi 4-1-5. Các đỉnh 4, 1, 5 được +20. Mảng: [30, 10, 10, 20, 20]
- Lệnh 2 2 4: Đường đi 2-1-4. Tổng: 10 + 30 + 20 = 60.
- Lệnh 2 1 1: Đỉnh 1 có giá trị 30.

================================================================================
*/

const int maxn = 1e5 + 5;
int n, q;

long long segment[maxn << 2];
long long lazy[maxn << 2];

void push_down(int index) {
  if (!lazy[index]) return;

  segment[index << 1] += lazy[index];
  segment[index << 1 | 1] += lazy[index];

  lazy[index << 1] += lazy[index];
  lazy[index << 1 | 1] += lazy[index];

  lazy[index] = 0;
}

void update(int index, int l, int r, int ql, int qr, const long long& val) {
  if (l > qr || r < ql) return;
  if (l >= ql && r <= qr) {
    segment[index] += val;
    lazy[index] += val;
    return;
  }

  push_down(index);

  int mid = l + ((r - l) >> 1);
  update(index << 1, l, mid, ql, qr, val);
  update(index << 1 | 1, mid + 1, r, ql, qr, val);

  segment[index] = segment[index << 1] + segment[index << 1 | 1];
}

long long fetch(int index, int l, int r, int ql, int qr) {
  if (l > qr || r < ql) return 0;
  if (l >= ql && r <= qr) return segment[index];

  push_down(index);

  int mid = l + ((r - l) >> 1);
  return fetch(index << 1, l, mid, ql, qr) + fetch(index << 1 | 1, mid + 1, r, ql, qr);
}

vector<int> adj[maxn];
int child[maxn], parent[maxn];
int depth[maxn];

int timein[maxn], timeout[maxn];
int head[maxn];
int timer = 1;

int make_dfs(int index, int p, int d) {
  parent[index] = p;
  depth[index] = d;
  child[index] = 1;

  for (int x : adj[index]) {
    if (x == p) continue;
    child[index] += make_dfs(x, index, d + 1);
  }

  return child[index];
}

void build(int index, int p, int head_index) {
  timein[index] = timer++;
  head[index] = head_index;
  int best_index = -1;
  for (int x : adj[index]) {
    if (x == p) continue;

    if (best_index == -1) best_index = x;
    else if (child[x] > child[best_index]) best_index = x;
  }

  if (best_index == -1) return;

  build(best_index, index, head_index);
  for (int x : adj[index]) {
    if (x == p || x == best_index) continue;
    build(x, index, x);
  }

  timeout[index] = timer - 1;
}

void query_update(int a, int b, const long long& val) {
  while (head[a] != head[b]) {
#if _debug == 1
    debug(a);
    debug(b);
#endif // _debug

    if (depth[head[a]] < depth[head[b]]) swap(a, b);

#if _debug == 1
    debug(a);
    debug(b);
#endif // _debug

    update(1, 1, n, timein[head[a]], timein[a], val);
    a = parent[head[a]];


#if _debug == 1
    debug(a);
    debug(b);
    newline;
#endif // _debug
  }

  if (depth[a] < depth[b]) swap(a, b);
  update(1, 1, n, timein[b], timein[a], val);
}

long long query_fetch(int a, int b) {
  long long res = 0;
  while (head[a] != head[b]) {
    if (depth[head[a]] < depth[head[b]]) swap(a, b);
    res += fetch(1, 1, n, timein[head[a]], timein[a]);
    a = parent[head[a]];
  }

  if (depth[a] < depth[b]) swap(a, b);
  res += fetch(1, 1, n, timein[b], timein[a]);
  return res;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);

#if _debug == 1
  freopen("input.inp", "r", stdin);

#elif _debug == 2
  freopen("input.inp", "r", stdin);
  freopen("output.out", "w", stdout);

#else

#endif // _debug

  cin >> n >> q;
  for (int i = 1; i < n; i++) {
    int a, b;
    cin >> a >> b;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }

  make_dfs(1, 0, 1);

#if _debug == 1
  for (int i = 1; i <= n; i++) {
    debug(i);
    debug(child[i]);
    debug(parent[i]);
    debug(depth[i]);
    newline;
  }
  newline;

#endif // _debug

  build(1, 0, 1);

#if _debug == 1

  for (int i = 1; i <= n; i++) {
    debug(i);
    debug(timein[i]);
    debug(timeout[i]);
    debug(head[i]);
    newline;
  }

#endif // _debug

  while (q--) {
    int type;
    cin >> type;
    if (type == 1) {
      int a, b;
      long long w;
      cin >> a >> b >> w;
      query_update(a, b, w);
    } else if (type == 2) {
      int a, b;
      cin >> a >> b;
      cout << query_fetch(a, b) << '\n';
    }
  }

#if _debug == 1

  for (int i = 1; i <= n; i++) {
    debug(i);
    debug(fetch(1, 1, n, timein[i], timein[i]));
    newline;
  }

#endif // _debug

}
