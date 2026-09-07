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

const int maxn = 1e5 + 5;
const int _log = 20;
vector<pair<int, long long>> adj[maxn];
int timein[maxn], timeout[maxn];
long long up[maxn][_log];
long long dist[maxn][_log];

int timer = 1;
void dfs(int index, int parent) {
    timein = timer++;
    up[index][0] = parent;
    for (int exp = 1; exp < _log; exp++) {
        up[index][exp] = up[ up[index][exp-1] ][exp-1];
        dist[index][exp] = dist[ dist[index][exp-1] ][exp-1];
    }

    for (const auto& x : adj[index]) {
        if (x.first == parent) continue;

        dist[x.first][0] = x.second;

        dfs(x, index);
    }
    timeout = timer++;
}

bool islca(int a, int b) {
    return timein[a] <= timein[b] && timeout[a] >= timeout[b];
}

int lca(int a, int b) {
    if (islca(a, b)) return a;
    if (islca(b, a)) return b;

    for (int exp = _log - 1; exp >= 0; exp--) {
        if (!islca(up[a][exp], b)) {
            a = up[a][exp];
        }
    }
    return up[a][0];
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    freopen("input.inp", "r", stdin);
    freopen("output.out", "w", stdout);

    int n, q; cin >> n >> q;
    for (int i = 1; i <= n; i++) {
        int a, b; long long val;
        cin >> a >> b >> val;
        adj[a].push_back({b, val});
        adj[b].push_back({a, val});
    }


    for (int i = 1; i <= q; i++) {
        int type; cin >> type;
        if (type == 1) {

        } else if (type == 2) {
            int k; cin >> k;
            vector<int> contain(k+1);
            stack<int> valid;
            int glca;
            for (int i = 1; i <= k; i++) {
                cin >> contain[i];
            }

            for (int i = 1; i < k; i++) {
                glca = lca(contain[i], contain[i+1]);
            }

            for (int i = 1; i <= k; i++) {
                int flag = 1;
                for (int j = i+1; j <= k; j++) {
                    //if (islca(contain[i], contain[j]))
                }
            }
        }
    }

}
