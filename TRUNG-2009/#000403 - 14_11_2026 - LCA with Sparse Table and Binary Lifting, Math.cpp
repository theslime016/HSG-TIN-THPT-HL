#include <bits/stdc++.h>
using namespace std;

/**
Bảo dưỡng

Trang trại nuôi trồng thủy sản ở đại dương bao gồm n trạm đánh số từ 1 đến n. Trạm 1 là mô đun chế biến và điều hành chung. Đây là trạm duy nhất nổi trên mặt nước. Các trạm còn lại đều ở dưới mặt nước.
Trừ trạm 1, mỗi trạm trong số các trạm còn lại được nối với một trạm trên nó, gần mặt nước hơn. Độ dài các dây neo nối 2 trạm là như nhau, vì vậy các trạm neo với trạm 1 đều ở độ sâu d so với mặt nước, các trạm neo với trạm độ sâu d sẽ nằm ở độ sâu 2d, ... Từ nhật ký bảo dưỡng dây neo người ta biết được các cặp trạm có dây neo nối với nhau.
Phần lớn các công việc do rô bốt đảm nhiệm, nhưng cũng có những việc phải thợ lặn trực tiếp thực hiện. Để đi từ trạm này sang trạm khác người thợ lặn phải bám theo các dây neo để khỏi mất phương hướng. Thời gian đi từ một trạm tới trạm kế tiếp là 1 đơn vị, không phụ thuộc vào việc nổi lên hay lặn xuống. Cứ đi lên hoặc đi xuống p khoảng cách giữa các trạm người thợ lặn cần ghé vào trạm nghỉ một khoảng thời gian t để thích nghi với việc thay đổi độ sâu. Ngoài ra, khi đang đi lên mà phải chuyển sang lặn xuống cũng phải nghỉ một khoảng thời gian t.
Có m nhóm thợ. Nhóm thợ thứ i sau khi hoàn thành xong công việc duy tu bảo dưỡng bên ngoài trạm ai nhận được yêu cầu chuyển sang làm các công việc tương tự ở trạm bi.

Yêu cầu: Cho số nguyên n, p, t, ai, bi (i = 1 ÷ m) và n-1 cặp giá trị khác nhau từng đôi một (ui, vi) cho biết có dây neo nối trực tiếp 2 trạm ui và vi (1 ≤ ui, vi, a, b ≤ n, a ≠ b, ui ≠ vi, i = 1 ÷ n-1). Hãy xác định thời gian ít nhất chuyển từ ai tới bi (i = 1 ÷ m).

Dữ liệu: Vào từ file văn bản MAINTAIN.INP:
- Dòng đầu tiên chứa 5 số nguyên n, p, t (2 ≤ n ≤ 10^5, 1 ≤ p ≤ n, 1 ≤ t ≤ 10^6),
- Dòng thứ i trong n-1 dòng sau chứa 2 số nguyên ui và vi.
- Dòng tiếp theo ghi số nguyên dương m (1 ≤ m ≤ 10^5)
- m dòng cuối cùng, dòng thứ i chứa hai số nguyên ai, bi.

Kết quả: Đưa ra file văn bản MAINTAIN.OUT m số nguyên – thời thời gian ít nhất chuyển từ ai tới bi (i = 1 ÷ m).

Ví dụ:
MAINTAIN.INP
14 2 1
11 8
8 13
7 8
7 4
4 1
2 1
1 6
2 3
2 5
12 10
14 10
6 9
3 10
1
8 10

MAINTAIN.OUT
9
**/

#define _debug 0

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
#define debug(...) (void(0))
#define newline (void(0))

#endif // _debug

const int maxn = 1e5 + 5;
const int maxlog = __lg(maxn) + 1;

int n, p, t;
vector<int> adj[maxn];

int up[maxn][maxlog];
int dist[maxn][maxlog];
int timein[maxn], timeout[maxn];
int timer = 1;
void make_dfs(int index, int parent) {
  up[index][0] = parent;
  dist[index][0] = 1;
  timein[index] = timer++;

  for (int exp = 1; exp < maxlog; exp++) {
    up[index][exp] = up[ up[index][exp - 1] ][exp - 1];
    dist[index][exp] = dist[index][exp - 1] + dist[up[index][exp-1]][exp - 1];
  }

  for (int x : adj[index]) {
    if (x == parent)
      continue;
    make_dfs(x, index);
  }

  timeout[index] = timer - 1;
}

bool is_lca(int a, int b) {
  return timein[a] <= timein[b] && timeout[a] >= timeout[b];
}

long long make_lca(int a, int b) {
  int turn = 0;
  if (!is_lca(a, b) && !is_lca(b, a))
    turn = 1;

#if _debug == 1
  debug(a, b);
#endif // _debug

  long long dist_left = 0;
  for (int exp = maxlog - 1; exp >= 0; exp--) {
    if (up[a][exp] && !is_lca(up[a][exp], b)) {
      dist_left += dist[a][exp];

      a = up[a][exp];
    }
  }

  long long dist_right = 0;
  for (int exp = maxlog - 1; exp >= 0; exp--) {
    if (up[b][exp] && !is_lca(up[b][exp], a)) {
      dist_right += dist[b][exp];

      b = up[b][exp];
    }
  }

  if (!is_lca(a, b))
    dist_left += dist[a][0];
  if (!is_lca(b, a))
    dist_right += dist[b][0];

#if _debug == 1
  debug(dist_left, dist_right);
  newline;
#endif // _debug

  long long base = dist_left + dist_right;
  long long penalty = 0;

  /// left -> right
  penalty = (dist_left/p + dist_right/p) * t + t;

  if (dist_left != 0 && dist_left%p == 0) {
    penalty -= t;
  }
  if (dist_right != 0 && dist_right%p == 0) {
    penalty -= t;
  }
  if (!turn) {
    penalty -= t;
  }
  return base + penalty;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);

#if _debug == 1
  freopen("input.inp", "r", stdin);

#else
  freopen("MAINTAIN.INP", "r", stdin);
  freopen("MAINTAIN.OUT", "w", stdout);

#endif // _debug


  cin >> n >> p >> t;
  for (int i = 1; i < n; i++) {
    int a, b;
    cin >> a >> b;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }

  make_dfs(1, 0);

  int q;
  cin >> q;
  while (q--) {
    int a, b;
    cin >> a >> b;
    cout << make_lca(a, b) << '\n';
  }

}
