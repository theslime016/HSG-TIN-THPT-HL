#include <bits/stdc++.h>
using namespace std;

/*
Tên bài toán: Điệp Vụ Biên Giới (Phiên bản Giao thức Cầu Nối)

Mô tả:
Mạng lưới tình báo gồm N cơ sở và M tuyến liên lạc hai chiều. Một Cụm tình báo là tập hợp các cơ sở mà nếu cắt bất kỳ một tuyến nào cũng không làm mất khả năng kết nối nội bộ. Sức mạnh của Cụm là số lượng cơ sở bên trong. Sau khi nén, các Cụm tạo thành một Cây vô hướng.

Chiến dịch:
1. Chọn tập hợp các Cụm độc lập (không kề nối trực tiếp) có tổng sức mạnh lớn nhất.
2. Vận chuyển K chuyến hàng từ U_i đến V_i dọc theo cấu trúc Cây. Mỗi Cụm trên đường đi sẽ tăng 1 đơn vị cảnh giác (ban đầu là 0).
3. Trả lời Q nghi vấn: Cụm chứa cơ sở C có nằm trên đường đi vận chuyển giữa Cụm chứa A và Cụm chứa B không? Nếu có, in ra mức độ cảnh giác hiện tại của Cụm đó. Nếu không, in ra 0.

Dữ liệu vào:
- Dòng 1: N, M, K, Q (1 <= N, M, K, Q <= 200,000).
- M dòng tiếp theo: u, v mô tả tuyến liên lạc.
- K dòng tiếp theo: U_i, V_i mô tả chuyến hàng.
- Q dòng tiếp theo: A, B, C mô tả nghi vấn.
(Đồ thị ban đầu liên thông).

Dữ liệu ra:
- Dòng 1: Tổng sức mạnh lớn nhất ở Giai đoạn 1.
- Q dòng tiếp theo: Kết quả cho truy vấn loại 3.
*/

int n, m, k, q;
const int maxn = 2e5;
struct edges {
  int a, b;
};
vector<edges> tree;
vector<pair<int, int>> adj[maxn];
vector<int> radj[maxn];
int timein[maxn], timeout[maxn];
int low[maxn];
int num[maxn];
int timer = 1;

int dsu[maxn];
int bucket[maxn];
int bucket_id = 1;

int fnd(int index) {
  if (dsu[index] == index)
    return index;
  return dsu[index] = fnd(dsu[index]);
}

void group(int a, int b) {
  a = fnd(a);
  b = fnd(b);
  if (a != b) {
    if (bucket[a] < bucket[b])
      swap(a, b);
    bucket[a] += bucket[b];
    dsu[b] = a;
  }
}

void dfs(int index, int prank) {
  low[index] = num[index] = timein[index] = timer++;
  dsu[index] = index;
  bucket[index] = 1;
  for (auto &x : adj[index]) {
    if (x.second == prank)
      continue;
    if (num[x.first]) {
      low[index] = min(low[index], num[x.first]);
    } else {
      dfs(x.first, x.second);
      if (low[x.first] > num[index]) {
        //cerr << index << ' ' << x.first << ' ';
        if (index != 0 && bucket[fnd(x.first)] > 1) tree.push_back({fnd(index), fnd(x.first)});
      } else {
        low[index] = min(low[index], low[x.first]);
        group(index, x.first);
      }
    }
  }
  timeout[index] = timer - 1;
}

long long dp[2];
int visited_id = 1;
int visited[maxn];
void make_dp(int index, int prank, int color) {
  int head = fnd(index);
  visited[index] = visited_id;
  for (const auto &x : adj[index]) {
    if (visited[x.first] == visited_id || x.second == prank)
      continue;
    int chead = fnd(x.first);
    if (bucket[chead] > 1 && chead != head) {
        dp[!color] += bucket[chead];
        make_dp(x.first, x.second, !color);
    } else {
        make_dp(x.first, x.second, color);
    }
  }
}


const int _log = 20;
int up[maxn][_log];
int dist[maxn];
void make_lca(int index, int parent, int current) {
    timein[index] = timer++;
    dist[index] = current;
    up[index][0] = parent;
    for (int exp = 1; exp < _log; exp++) {
        up[index][exp] = up[ up[index][exp-1] ][exp-1];
    }

    for (int x : radj[index]) {
        if (x == parent) continue;
        make_lca(x, index, current+1);
    }
    timeout[index] = timer-1;
}

bool is_lca(int a, int b) {
    return timein[a] <= timein[b] && timeout[a] >= timeout[b];
}

int get_lca(int a, int b) {
    if (is_lca(a, b)) return a;
    if (is_lca(b, a)) return b;

    for (int exp = _log - 1; exp >= 0; exp--) {
        if (up[a][exp] && !is_lca(up[a][exp], b)) {
            a = up[a][exp];
        }
    }
    return up[a][0];
}

int get_dist(int a, int b) {
    return dist[a] + dist[b] - 2 * dist[get_lca(a, b)];
}

int on_path(int a, int b, int x) {
    return get_dist(a, x) + get_dist(x, b) == get_dist(a, b);
}

int fenwick[maxn];
void transport(int a, int b) {
    fenwick[timein[get_lca(a, b)]]++;
    while (!is_lca(a, b) && a) {
        fenwick[timein[a]]++;
        a = up[a][0];
    }
    while (!is_lca(b, a) && b) {
        fenwick[timein[b]]++;
        b = up[b][0];
    }
}

int main() {
  cin.tie(0)->sync_with_stdio(0);

  freopen("input.inp", "r", stdin);
  // freopen("output.out", "w", stdout);

  cin >> n >> m >> k >> q;
  for (int i = 1; i <= m; i++) {
    int a, b;
    cin >> a >> b;
    adj[a].push_back({b, i});
    adj[b].push_back({a, i});
  }

  fill_n(bucket, n + 1, 1);
  adj[0].push_back({1, -1});
  dfs(0, 0);
  make_dp(0, 0, 0);
  //// SUB 2
  cout << max(dp[0], dp[1]) << '\n';

  int root;
  if (tree.size() > 0) {
      for (auto& x : tree) {
        radj[fnd(x.a)].push_back(fnd(x.b));
        radj[fnd(x.b)].push_back(fnd(x.a));
        //cout << x.a << ' ' << x.b << '\n';
        root = x.b;
      }
  }

  make_lca(root, 0, 0);

  for (int i = 1; i <= k; i++) {
    int a, b;
    cin >> a >> b;
    a = fnd(a);
    b = fnd(b);
    transport(a, b);
  }

  for (int i = 1; i <= q; i++) {
    //// SUB 3
    int a, b, x;
    cin >> a >> b >> x;
    a = fnd(a);
    b = fnd(b);
    x = fnd(x);
    if (k == 0 || !on_path(a, b, x)) {
      cout << 0 << '\n';
    } else {
      cout << fenwick[timein[x]] << '\n';
    }
  }

}
