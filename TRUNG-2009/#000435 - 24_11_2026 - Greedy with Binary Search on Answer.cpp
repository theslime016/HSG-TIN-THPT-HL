#include <bits/stdc++.h>
using namespace std;

/**
Q. Dãy con có độ dài bị chặn

Thông tin chung:
- Giới hạn thời gian: 2.25 giây
- Giới hạn bộ nhớ: 256 MB
- Input: standard input
- Output: standard output

Nếu bạn gặp khó trong việc xem đề bài, hãy tải file maxsubseq-materials.zip trong mục Contest materials và xem các file ảnh bên trong để có bản đề đầy đủ và đẹp nhất.

Mô tả:
Cho dãy N số nguyên A = A1, A2, ..., AN. Ta gọi dãy con của dãy A là dãy gồm một số phần tử liên tiếp của nó, tức là dãy có dạng Ai, Ai+1, ..., Aj (1 ≤ i ≤ j ≤ N). Ta gọi độ dài của dãy là số lượng phần tử của nó còn trọng số của dãy là tổng các phần tử của nó. Một dãy con được gọi là có độ dài bị chặn nếu nó có độ dài lớn hơn hoặc bằng L và nhỏ hơn hoặc bằng H.

Yêu cầu:
Cho Q cặp số nguyên (L1, H1), (L2, H2), ..., (LQ, HQ); với mỗi cặp số (Li, Hi) hãy tìm dãy con có độ dài bị chặn bởi Li và Hi với trọng số lớn nhất.

Input:
- Dòng đầu tiên chứa hai số nguyên dương N và Q được ghi cách nhau bởi dấu cách.
- Dòng thứ hai chứa N số nguyên A1, A2, ..., AN được ghi cách nhau bởi dấu cách là các phần tử của dãy số.
- Trong Q dòng cuối cùng, dòng thứ i chứa hai số nguyên Li và Hi được ghi cách nhau bởi dấu cách.

Output:
In ra Q nhóm dòng, nhóm dòng thứ i gồm hai dòng thể hiện kết quả của bài toán ứng với bộ số (Li, Hi) theo khuôn dạng sau:
- Dòng đầu tiên ghi ra trọng số lớn nhất tìm được.
- Dòng thứ hai ghi vị trí bắt đầu và kết thúc của dãy con tìm được.
Nếu có nhiều cách chọn vị trí bắt đầu và kết thúc hợp lệ, bạn được phép in ra một cách chọn bất kỳ.

Scoring:
Trong tất cả các test, Q ≤ 500.
- 35% số test có N ≤ 50.
- 35% số test có N ≤ 400.
- 20% số test có N ≤ 20000.
- 10% số test có N ≤ 300000.

Example:
Input:
6 2
3 5 -9 6 7 -4
3 4
1 6

Output:
9
2 5
13
4 5

Note:
Với L1 = 3 và H1 = 4, dãy con độ dài bị chặn có trọng số lớn nhất là dãy 5, -9, 6, 7 với trọng số bằng 9.
Với L2 = 1 và H2 = 6, dãy con độ dài bị chặn có trọng số lớn nhất là dãy 6, 7 với trọng số bằng 13.
**/

#define _debug 0

#if _debug == 1
void logout() {cerr << endl;}
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

const int maxn = (1LL << 19);
int cheater_num, task_num, budget;

struct TASK {
  int level;
  int index;

  friend bool operator<(const TASK& a, const TASK& b) {
    return a.level > b.level;
  }

} task[maxn];

struct CHEATER {
  int max_level;
  int cost;
  int index;

  friend bool operator<(const CHEATER& a, const CHEATER& b) {
    return a.max_level > b.max_level;
  }

} cheater[maxn];

int selected[maxn]; /// task -> cheater

int main() {
  cin.tie(0)->sync_with_stdio(0);

  #if _debug == 1
  freopen("input.inp", "r", stdin);

  #elif _debug == 2
  freopen("input.inp", "r", stdin);

  #else
  freopen("cheating.inp", "r", stdin);
  freopen("cheating.out", "w", stdout);

  #endif // _debug

  int cheating;
  cin >> cheating;

  int t;
  cin >> t;
  while (t--) {
    cin >> cheater_num >> task_num >> budget;
    for (int i = 1; i <= task_num; i++) {
      cin >> task[i].level;
      task[i].index = i;
    }

    for (int i = 1; i <= cheater_num; i++) cin >> cheater[i].max_level;
    for (int i = 1; i <= cheater_num; i++) {
      cin >> cheater[i].cost;
      cheater[i].index = i;
    }

    sort(task + 1, task + task_num + 1);
    sort(cheater + 1, cheater + cheater_num + 1);

    auto check = [&](int k) {
      priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq; /// cost - index

      int rem_budget = budget;
      int cheater_index = 1;
      for (int i = 1; i <= task_num; i += k) {

        while (cheater_index <= cheater_num) {
          if (cheater[cheater_index].max_level >= task[i].level) {
            pq.push({cheater[cheater_index].cost, cheater[cheater_index].index});
            cheater_index++;
          } else {
            break;
          }
        }

        if (pq.empty()) return false;

        int cost = pq.top().first;
        int index = pq.top().second;
        pq.pop();

        rem_budget -= cost;
        if (rem_budget < 0) return false;

        for (int j = i; j < min(task_num + 1, i + k); j++) {
          selected[ task[j].index ] = index;
        }

      }

      return true;
    };

    int l = 1, r = task_num + 1;
    for (int d = r - l; d > 0; d >>= 1) {
      while (r - d >= l && check(r - d)) r -= d;
    }

    if (r == task_num + 1) {
      cout << "NO" << '\n';
      cout << '\n';
      continue;
    }

    check(r);

    cout << "YES" << '\n';
    for (int i = 1; i <= task_num; i++) {
      cout << selected[i] << ' ';
    }
    cout << '\n';

  }

}
