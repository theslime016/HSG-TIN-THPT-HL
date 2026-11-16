#include <bits/stdc++.h>
using namespace std;

/**
Trung thu

Thông tin chung:
- Điểm: 1600
- Giới hạn thời gian: 2s
- Giới hạn bộ nhớ: 512 MB
- Input: TRUNGTHU.INP
- Output: TRUNGTHU.OUT

Mô tả:
Trung thu năm nay, Trường Phổ thông nội trú TH và THCS Hùng Sơn tổ chức đêm hội trăng rằm cho học sinh. Đây là trường học thuộc xã miền núi nhiều khó khăn của thành phố Đà Nẵng. Trong đêm hội, tiết mục rước đèn ông sao được học sinh mong chờ, bởi nhà trường phát cho mỗi học sinh một chiếc đèn ông sao nhiều màu lấp lánh.

Một nghệ nhân làm lồng đèn nổi tiếng ở Hội An phụ trách công việc chuẩn bị những chiếc đèn. Trong xưởng hiện có n chiếc đèn chưa sơn. Thời gian sơn xong chiếc đèn thứ i là a_i phút, sau đó nghệ nhân mang ra sân phơi ngay và quay lại sơn tiếp các chiếc đèn khác. Sân rộng nên có thể phơi nhiều chiếc đèn cùng lúc. Chiếc đèn thứ i chờ b_i phút mới khô. Nghệ nhân làm việc liên tục và chọn các chiếc đèn ngẫu nhiên để sơn.

Yêu cầu:
Hãy tính số đèn hoàn thiện nhiều nhất trong thời gian T phút.

Input:
Đọc từ tệp TRUNGTHU.INP.
- Dòng đầu tiên chứa hai số nguyên n, T (1 ≤ n ≤ 2 × 10^5; 1 ≤ T ≤ 10^15).
- Dòng thứ hai chứa n số nguyên a_1, a_2, ..., a_n (1 ≤ a_i ≤ 10^9).
- Dòng thứ ba chứa n số nguyên b_1, b_2, ..., b_n (1 ≤ b_i ≤ 10^9).

Output:
Ghi ra tệp TRUNGTHU.OUT một số nguyên duy nhất là số đèn hoàn thiện nhiều nhất.
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
#define debug_title cerr << __PRETTY_FUNCTION__ << " line: " << __LINE << endl
#define newline cerr << endl

#else
#define debug(...) (void(0))
#define debug_title (void(0))
#define newline (void(0))

#endif // _debug

const int maxn = 2e5 + 5;
int n;
long long t;

struct TASK {
  long long x, y;
} task[maxn];

int main() {
  cin.tie(0)->sync_with_stdio(0);

#if _debug == 1
  freopen("input.inp", "r", stdin);

#elif _debug == 2
  freopen("input.inp", "r", stdin);

#else
  freopen("TRUNGTHU.INP", "r", stdin);
  freopen("TRUNGTHU.OUT", "w", stdout);

#endif // _debug

  cin >> n >> t;
  for (int i = 1; i <= n; i++) {
    int x, y;
    cin >> x >> y;
    task[i] = {x, y};
  }

  sort(task + 1, task + n + 1, [&](const TASK& a, const TASK& b) {
    return a.y > b.y;
  });

#if _debug == 1
  for (int i = 1; i <= n; i++) {
    debug(i, task[i].x, task[i].y);
  }

#endif // _debug

  struct cmp_task {
    bool operator()(const TASK& a, const TASK& b) {
      return a.x < b.x;
    }
  };

  priority_queue<TASK, vector<TASK>, cmp_task> pq;
  long long timer = 0;
  for (int i = 1; i <= n; i++) {
    timer += task[i].x;
    pq.push(task[i]);
    if (timer + task[i].y > t) {
      timer -= pq.top().x;
      pq.pop();
    }
  }

  cout << pq.size();
}
