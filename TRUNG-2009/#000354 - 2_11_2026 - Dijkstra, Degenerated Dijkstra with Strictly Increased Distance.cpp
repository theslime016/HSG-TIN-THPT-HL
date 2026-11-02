#include <bits/stdc++.h>
using namespace std;

/*
D. Du lịch Bắc Ninh
time limit per test: 1 second
memory limit per test: 256 megabytes
input: quanho.inp
output: quanho.out

Sau khi ra đề xong cho kỳ thi VNOP (Vietnam National Olympiad in Philosophy) Online 2017, GS — TSKH — NGND — CVCC PVH quyết định tự thưởng cho mình một chuyến du lịch Bắc Ninh.

Bắc Ninh là tỉnh nổi tiếng với dân ca quan họ. Bắc Ninh là trung tâm xứ Kinh Bắc cổ xưa. Hiện nay trên địa bàn tỉnh Bắc Ninh có khoảng 41 lễ hội đáng chú ý trong năm được duy trì. Trong đó có những lễ hội lớn như: hội chùa Dâu, Hội Lim, hội đền Đô, hội đền Bà Chúa Kho. Con người Bắc Ninh truyền thống văn hoá, hiếu khách, cần cù và sáng tạo, với những bàn tay khéo léo mang đậm nét đan gian của vùng trung tâm nhưng nhỏ hẹp, tôm tép, củ đậu, đống trám bạc, khắc gỗ, làm giấy, tranh vẽ dân gian... nổi bật là những làn điệu dân ca quan họ. Ngoài ra, nếu ai có dịp về Đình Bảng du xuân, thì không thể bỏ qua cơ hội thưởng thức món bánh phu thê đặc sản nổi tiếng của vùng đất kinh kỳ. Những cặp bánh thơm ngon được người dân Đình Bảng dùng trong những mâm lễ cưới hỏi hay những ngày lễ, Tết với mong ước về một cuộc sống sung túc, ấm no, hạnh phúc. Bánh phu thê (còn nghĩa là chồng vợ) nên người ta thường mua ít nhất một cặp chứ không bao giờ mua lẻ một chiếc...

Thành phố Bắc Ninh bao gồm n khu phố. Các khu phố được đánh số từ 1 tới n, và được nối với nhau bởi m con đường hai chiều. Mỗi con đường có một độ dài niêng.

Vào dịp ghé thăm của GS — TSKH — NGND — CVCC PVH, có rất nhiều sự kiện quảng bá văn hóa và du lịch Bắc Ninh được diễn ra. Đặc biệt, vào mỗi ngày, tại thành phố n sẽ diễn ra buổi biểu diễn quan họ. Thêm vào đó, những chiếc bánh phu thê cũng được bán ở tất cả các khu phố trên toàn Bắc Ninh. Mỗi ngày, tại khu phố i có p_i chiếc bánh phu thê được mang ra bán ở đây.

Là người yêu thích văn hóa Phương Đông từ lâu, GS — TSKH — NGND — CVCC PVH không muốn bỏ lỡ giây phút thưởng thức quan họ Bắc Ninh, nên đã chọn con đường đi ngắn nhất để đi từ khu phố 1 (khách sạn của GS) tới khu phố n (nơi diễn ra sự kiện nghệ thuật). Ngoài ra, GS còn muốn trên con đường ngắn nhất của mình, tổng số lượng bánh phu thê được rao bán ở đây là lớn nhất.

Hãy giúp GS tìm ra độ dài đường đi ngắn nhất và tổng số bánh được rao bán nhiều nhất trên con đường này.

Input
Dòng đầu tiên chứa số nguyên dương n (1 <= n <= 10^5) là số khu phố tại Bắc Ninh.
Dòng thứ hai chứa n số nguyên p1, p2, ..., pn (0 <= p_i <= 10^9), lần lượt là số bánh phu thê được rao bán tại các khu phố 1, 2, ..., n.
Dòng thứ ba chứa số nguyên m (0 <= m <= 10^5) là số con đường hai chiều trên toàn thành phố.
m dòng tiếp theo, mỗi dòng chứa ba số nguyên dương u, v và c (1 <= u, v <= n, 1 <= c <= 10^9), cho biết một con đường độ dài c giữa hai khu phố u và v.

Output
Nếu không tồn tại đường đi từ khu phố 1 tới khu phố n, in ra "impossible". Ngược lại, in ra hai số nguyên trên một dòng lần lượt là độ dài đường đi ngắn nhất từ khu phố 1 tới khu phố n và tổng số bánh phu thê tối đa được rao bán trên một con đường ngắn nhất.

Scoring
- Subtask 1 (22.5 điểm): p1 = p2 = ... = pn = 0.
- Subtask 2 (22.5 điểm): n <= 1000 và mọi con đường có độ dài c = 1.
- Subtask 3 (55.0 điểm): Không có ràng buộc gì thêm.

Examples

input
8
2 1 1 1 100 1 1 2
10
1 2 1
2 3 2
3 4 2
4 8 1
1 8 7
1 5 3
5 8 4
1 6 2
6 7 2
7 8 2
output
6 7

input
6
1 1 2 3 1 0
7
1 2 2
2 3 3
3 6 4
1 4 4
4 3 2
4 5 3
5 6 2
output
9 5

input
9
1 1 1 1 1 1 1 1 1
10
1 2 3
2 5 3
1 6 2
6 7 2
7 5 2
5 3 1
3 4 2
4 9 3
5 8 2
8 9 4
output
12 7

input
2
5 5
0
output
impossible

Note
Trong ví dụ đầu tiên:
- Con đường 1 -> 2 -> 3 -> 4 -> 8 có độ dài 6 và tổng số bánh là 7. Đây là con đường tối ưu.
- Con đường 1 -> 6 -> 7 -> 8 tuy có độ dài 6 nhưng tổng số bánh là 6, nên không tối ưu.
- Con đường 1 -> 8 tuy có rất nhiều bánh nhưng tổng độ dài là 7 nên không tối ưu.
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

const int maxn = 1e5 + 5;
const long long inf = 1e18;
long long A[maxn];
vector<pair<int, long long>> adj[maxn]; // index - dist

long long dist[maxn];
long long sum[maxn];
pair<long long, int> cdist[maxn];

int main() {
  cin.tie(0)->sync_with_stdio(0);

#if _debug == 1
  freopen("input.inp", "r", stdin);

#elif _debug == 2
  freopen("input.inp", "r", stdin);

#else
  freopen("quanho.inp", "r", stdin);
  freopen("quanho.out", "w", stdout);

#endif // _debug

  int n;
  cin >> n;
  for (int i = 1; i <= n; i++) cin >> A[i];

  int m;
  cin >> m;
  for (int i = 1; i <= m; i++) {
    int a, b;
    long long w;
    cin >> a >> b >> w;
    adj[a].push_back({b, w});
    adj[b].push_back({a, w});
  }

  fill_n(dist, maxn, inf);
  fill_n(sum, maxn, -inf);

  priority_queue< pair<long long, int>, vector<pair<long long, int>>,
                  greater<pair<long long, int>> > pq; // dist - index
  dist[1] = 0;
  pq.push({0, 1});
  while (!pq.empty()) {
    long long d = pq.top().first;
    int index = pq.top().second;

    pq.pop();

    if (d > dist[index]) continue;

    for (const pair<int, long long>& x : adj[index]) {
      int next_index = x.first;
      long long w = x.second;

      if (d + w < dist[next_index]) {
        dist[next_index] = d + w;
        pq.push({d + w, next_index});
      }

    }

  }

  if (dist[n] == inf) {
    cout << "impossible";
    return 0;
  }

  for (int i = 1; i <= n; i++) {
    cdist[i] = {dist[i], i};
  }

  sort(cdist + 1, cdist + n + 1);
  sum[1] = A[1];
  for (int i = 1; i <= n; i++) {
    long long d = cdist[i].first;
    int fnd = cdist[i].second;

    for (const pair<int, long long>& x : adj[fnd]) {
      if (d + x.second == dist[x.first]
          && sum[fnd] + A[x.first] > sum[x.first]) {
        sum[x.first] = sum[fnd] + A[x.first];
      }
    }

  }

  cout << dist[n] << ' ' << sum[n];

}
