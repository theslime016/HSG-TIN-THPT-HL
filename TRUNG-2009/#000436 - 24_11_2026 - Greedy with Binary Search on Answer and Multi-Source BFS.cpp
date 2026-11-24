#include <bits/stdc++.h>
using namespace std;

/**
Giới hạn bộ nhớ mỗi test: 256 megabytes
Đầu vào: shipping.inp
Đầu ra: shipping.out

Dịch COVID-19 cùng biến thể Delta lây lan siêu nhanh đã buộc người dân thủ đô phải trải qua những ngày "ai ở đâu ở yên đó" ngột ngạt quanh bốn bức tường. Tuy nhiên, với quyết tâm chống dịch cao độ và chiến dịch tiêm chủng vaccine thần tốc, Hà Nội giờ đây đã phủ đầy vùng xanh và loài virus tàn độc đã phải lùi bước. Thành phố kiểm soát được dịch, lệnh giãn cách được nới lỏng và niềm tin về cuộc sống "bình thường mới" đang dần trào khắp nơi.

Vì kinh doanh mặt hàng không thiết yếu, hệ thống cửa hàng trà sữa của GSPVH buộc phải đóng cửa suốt hai tháng vừa qua. Nay khi được phép hoạt động, GSPVH rất quyết tâm vực dậy trào lưu trà sữa, đưa trà sữa trở lại là người bạn thân thiết gắn gũi với các bạn trẻ. Để chuẩn bị gặp lại khách hàng, GS không chỉ nghiên cứu công thức pha chế mới, nhập nhiều nguyên liệu mới mà còn lên các phương án giao hàng hiệu quả để phục vụ các tín đồ.

Thành phố Hà Nội có n khu dân cư, được đánh số từ 1 đến n. n khu dân cư được kết nối bởi m con đường hai chiều, mỗi con đường có độ dài 1. Tuy vậy, từ một khu dân cư có thể không tới được tất cả các khu dân cư còn lại. Hệ thống phân phối trà sữa của GSPVH có k cửa hàng, cửa hàng thứ i được đặt tại khu dân cư u_i. Tại đây, GS đã nhập đủ nguyên liệu để pha chế c_i ly trà sữa và bán một ly trà sữa với giá p_i. Tại một khu dân cư có thể có không, một hoặc nhiều cửa hàng của GSPVH.

Nhằm giúp tính toán khả năng phân phối trà sữa tới người tiêu dùng, GSPVH đã đặt ra q kịch bản. Trong kịch bản thứ j, GS giả định có một đơn đặt t_j cốc trà sữa tới khu dân cư v_j và người đặt hàng chỉ muốn trả số tiền tối đa là b_j cho toàn bộ đơn hàng. GS muốn biết trong kịch bản này, việc đáp ứng đơn đặt hàng có khả thi không, và nếu có, cần ít nhất bao lâu để giao hàng. Biết rằng các ly trà sữa có thể được giao đồng thời, thời gian để giao một ly trà sữa bằng độ dài quãng đường từ cửa hàng pha chế cho tới khu dân cư của người nhận, thời gian pha chế là không đáng kể và thời gian giao toàn bộ đơn hàng được tính bằng khoảng cách từ lúc bắt đầu pha ly đầu tiên tới khi ly cuối cùng tới tay khách hàng.

Hãy giúp GSPVH xác định tính khả thi và thời gian giao hàng tối thiểu trong mỗi kịch bản. Chú ý rằng tất cả chỉ là giả định, nghĩa là không có ly trà sữa nào thực sự được pha chế và được giao, do đó mọi kịch bản độc lập với nhau.

Đầu vào
Dòng đầu tiên chứa hai số nguyên n và m (1 <= n <= 5000, 0 <= m <= 5000), lần lượt là số khu dân cư và số con đường trong thành phố Hà Nội. Trong m dòng tiếp theo, mỗi dòng chứa hai số nguyên x và y (1 <= x, y <= n) cho biết có một con đường nối hai khu dân cư x và y.

Dòng tiếp theo chứa một số nguyên k (1 <= k <= 5000) là số cửa hàng trong hệ thống của GSPVH. Trong k dòng tiếp theo, dòng thứ i chứa ba số nguyên u_i (1 <= u_i <= n), c_i và p_i (1 <= c_i, p_i <= 10^9) cho biết cửa hàng thứ i đặt tại khu dân cư u_i, có sẵn nguyên liệu để pha chế c_i ly trà sữa và giá bán mỗi ly trà sữa tại đây là p_i.

Dòng tiếp theo chứa một số nguyên q (1 <= q <= 1000) là số kịch bản GSPVH đặt ra. Trong q dòng cuối cùng, dòng thứ j chứa ba số nguyên v_j (1 <= v_j <= n), t_j và b_j (1 <= t_j, sqrt(b_j) <= 10^9) cho biết trong kịch bản thứ j, có một đơn hàng yêu cầu giao t_j ly trà sữa tới khu dân cư v_j và tổng giá tiền của hóa đơn không được quá b_j.

Đầu ra
In ra q số nguyên, số thứ j là thời gian giao hàng tối thiểu trong kịch bản thứ j, hoặc -1 nếu đơn hàng này không thể đáp ứng được.

Ghi điểm
- Subtask 1 (24 điểm): n, m, k <= 50
- Subtask 2 (32 điểm): n, m, k <= 500
- Subtask 3 (44 điểm): n, m, k <= 5000

Ví dụ
Input:
7 6
1 2
2 3
4 1
1 5
5 6
6 7
3
4 3 1
3 3 2
7 3 3
3
1 4 7
2 10 20
3 2 1

Output:
2 -1 -1

Ghi chú
Trong kịch bản thứ nhất, GSPVH cần giao 4 ly trà sữa tới khu dân cư 1 sao cho tổng giá trị hóa đơn không quá 7. Để đáp ứng yêu cầu của khách, GS cho pha chế 2 ly trà sữa tại cửa hàng 2 rồi giao hàng cho khách theo con đường 3 -> 2 -> 1; đồng thời cho pha chế 2 ly trà sữa tại cửa hàng 1 rồi giao cho khách theo con đường 4 -> 1. Như vậy, tất cả các ly trà sữa sẽ tới tay khách hàng trong thời gian 2 và tổng giá trị hóa đơn là 2*2 + 2*1 = 6.

Trong kịch bản thứ hai, khách đặt hàng tới 10 ly trà sữa trong khi toàn bộ hệ thống của GSPVH chỉ có đủ nguyên liệu để pha 9 ly trà sữa. Như vậy, GS không thể đáp ứng được yêu cầu của khách hàng.

Trong kịch bản thứ ba, khách hàng đặt 2 ly trà sữa nhưng lại chỉ sẵn sàng trả số tiền tối đa là 1, điều này là không khả thi vì mỗi ly trà sữa của GSPVH có giá ít nhất là 1.
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

const int maxn = 5005;

int n, m, k, q;

vector<int> adj[maxn];
int dist[maxn][maxn];

struct TASK {
  int index;
  long long cost;
  long long stock;
} task[maxn];

pair<int, int> dq[maxn]; /// index - dist;

int main() {
  cin.tie(0)->sync_with_stdio(0);

#if _debug == 1
  freopen("input.inp", "r", stdin);

#elif _debug == 2
  freopen("input.inp", "r", stdin);

#else
  freopen("shipping.inp", "r", stdin);
  freopen("shipping.out", "w", stdout);

#endif // _debug

  cin >> n >> m;
  for (int i = 1; i <= m; i++) {
    int a, b;
    cin >> a >> b;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }

  memset(dist, -1, sizeof dist);
  for (int i = 1; i <= n; i++) {
    dist[i][i] = 0;
    int head_ptr = 1, tail_ptr = 0;
    dq[++tail_ptr] = {i, 0};
    while (head_ptr <= tail_ptr) {
      pair<int, int> x = dq[head_ptr];
      head_ptr++;

      for (int a : adj[x.first]) {
        if (dist[i][a] != -1)
          continue;
        dist[i][a] = x.second + 1;
        dq[++tail_ptr] = {a, x.second + 1};
      }
    }
  }

  cin >> k;
  for (int i = 1; i <= k; i++) {
    cin >> task[i].index >> task[i].stock >> task[i].cost;
  }

  sort(task + 1, task + k + 1, [&](const TASK& a, const TASK& b) {
    return a.cost < b.cost;
  });

  cin >> q;
  while (q--) {
    int index;
    long long req;
    long long budget;
    cin >> index >> req >> budget;

    auto check = [&](int req_dist) {
      long long rem_req = req;
      long long rem_budget = budget;

      for (int i = 1; i <= k; i++) {
        if (dist[index][ task[i].index ] == -1)
          continue;
        if (dist[index][ task[i].index ] > req_dist)
          continue;

        long long buy = min(rem_req, task[i].stock);
        long long total_cost = buy * task[i].cost;

        if (rem_budget >= total_cost) {
          rem_budget -= total_cost;
          rem_req -= buy;
        } else {
          break;
        }

        if (rem_req == 0) break;

      }

      return rem_req == 0 && rem_budget >= 0;
    };

    int l = 0, r = maxn;
    for (int d = r - l; d > 0; d >>= 1) {
      while (r - d >= l && check(r - d))
        r -= d;
    }

    if (r == maxn) {
      cout << -1 << ' ';
    } else {
      cout << r << ' ';
    }

  }



}
