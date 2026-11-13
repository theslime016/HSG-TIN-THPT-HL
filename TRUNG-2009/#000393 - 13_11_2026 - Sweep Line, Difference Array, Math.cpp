#include <bits/stdc++.h>
using namespace std;

/**
File: FESTIVALS.txt

Bài 2. Festivals

Có n lệ hội, lệ hội thứ i được tổ chức từ ngày li tới ngày ri. An xin nghỉ phép và dự định đi chơi vào bắt đầu từ ngày x, và các thời điểm tiếp theo cách nhau d ngày (x, x + d, x + 2d, ...). Vào ngày không có lệ hội, An có thể thảnh thơi ngủ nướng cả ngày.

Yêu cầu:
Hãy giúp An lựa chọn ngày bắt đầu x để số lệ hội An có thể tham gia là nhiều nhất. Nếu có nhiều ngày có thể chọn, đưa ra số hiệu ngày có giá trị nhỏ nhất.

Dữ liệu: vào từ file FESTIVALS.INP
- Dòng đầu tiên chứa 2 số nguyên dương n, d.
- n dòng tiếp theo, dòng thứ i chứa 2 số nguyên không âm li, ri xác định ngày bắt đầu và ngày kết thúc. Các ngày đánh số từ 0.

Kết quả: Ghi ra file FESTIVALS.OUT 2 số nguyên không âm là số lệ hội lớn nhất mà An có thể tham gia và ngày bắt đầu An dự định đi chơi.

Ví dụ:
FESTIVALS.INP
4 4
5 5
0 2
10 11
15 23

FESTIVALS.OUT
3 1

Giải thích: An có thể tham gia lệ hội 1 (ngày 5), lệ hội 2 (ngày 1), lệ hội 4 (ngày 17, 21).

Ràng buộc:
- 30% số test có n, d ≤ 10^3; li, ri ≤ 10^5.
- 30% số test khác có n, d ≤ 10^3.
- 40% số test còn lại có n ≤ 10^5; d, li, ri ≤ 10^15.
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
long long n, d;
pair<long long, int> event[maxn << 2];
pair<long long, int> task[maxn << 2];

int main() {
  cin.tie(0)->sync_with_stdio(0);

#if _debug == 1
  freopen("input.inp", "r", stdin);

#else
  freopen("FESTIVALS.INP", "r", stdin);
  freopen("FESTIVALS.OUT", "w", stdout);

#endif // _debug

  cin >> n >> d;
  int cnt = 0;
  int event_cnt = 0;
  for (int i = 1; i <= n; i++) {
    long long l, r;
    cin >> l >> r;

    long long len = r - l + 1;
    if (len >= d)
      cnt++;
    else {
      l %= d;
      r %= d;
      event[++event_cnt] = {r + 1, - 1};
      event[++event_cnt] = {l, 1};
      if (r < l)
        event[++event_cnt] = {0, 1};
    }
  }

  sort(event + 1, event + event_cnt + 1);
  long long last_event = -1;
  int current = 0;
  int task_cnt = 0;
  pair<long long, int> x;
  for (int i = 1; i <= event_cnt; i++) {
    x = event[i];
    if (x.first == last_event) {
      current += x.second;
    } else {
      task[++task_cnt] = {last_event, current};
      last_event = x.first;
      current = x.second;
    }
  }
  task[++task_cnt] = {last_event, current};
  sort(task + 1, task + task_cnt + 1);

  current = 0;
  int max_val = 0;
  long long index = 0;
  for (int i = 1; i <= task_cnt; i++) {
    x = task[i];
    current += x.second;
    if (current > max_val) {
      max_val = current;
      index = x.first;
    }
  }

  cout << max_val + cnt << ' ' << index;

}
