#include <bits/stdc++.h>
using namespace std;

/**
Chia kẹo

Thông tin chung:
- Điểm: 2200p
- Giới hạn thời gian: 2s
- Giới hạn bộ nhớ: 256 MB

Mô tả:
Một lớp học có n học sinh, học sinh thứ i (1 ≤ i ≤ n) có mã học sinh là số nguyên dương a_i. Hai học sinh khác nhau có mã học sinh khác nhau.

Cuối năm học, thầy giáo chủ nhiệm phát kẹo thưởng cho cả lớp. Là một giáo viên dạy môn Tin học nên thầy sẽ phát kẹo theo quy tắc sau:
- Tất cả n học sinh đứng thành một hàng, học sinh thứ...

(Ghi chú: Nội dung đề bài trong file HTML bị cắt ngang tại đây, không có đầy đủ phần quy tắc phát kẹo, Input, Output và Ví dụ).
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

const int maxn = 2e5 + 5;
const int maxval = 5e5 + 5;
const int inf = 1e9;
int n, q;

int A[maxn];
int lpf[maxval];

vector<pair<int, long long>> events[maxn];

long long profit[maxval];
long long S[maxn];

vector<pair<int, int>> factor; /// factor - exp

void make_dfs(int index, int current, int qindex) {
  if (index >= factor.size()) {
    S[qindex] += profit[current];

    #if _debug == 1
    debugtitle;
    debug(qindex, current);
    newline;
    #endif // _debug

    return;
  }

  for (int exp = 0; exp <= factor[index].second; exp++) {
    make_dfs(index + 1, current, qindex);
    current *= factor[index].first;
  }
}

void make_num(int a, int index) {
  if (a == 1) {
    S[index] += profit[a];
    return;
  }

  factor.clear();
  int last_num = inf;
  int cnt = -1;
  while (a > 1) {
    int num = lpf[a];
    if (num == last_num) {
      cnt++;
    } else {
      if (last_num != inf)
        factor.push_back({last_num, cnt});
      last_num = num;
      cnt = 1;
    }

    a /= lpf[a];
  }
  factor.push_back({last_num, cnt});

  #if _debug == 1
  newline;
  for (const auto& x : factor) {
    debug(x.first, x.second);
  }
  newline;
  #endif // _debug

  make_dfs(0, 1, index);
}


int main() {
  cin.tie(0)->sync_with_stdio(0);

#if _debug == 1
  freopen("input.inp", "r", stdin);

#elif _debug == 2
  freopen("input.inp", "r", stdin);

#else

#endif // _debug


  iota(lpf, lpf + maxval, 0);
  for (int i = 2; i*i < maxval; i++) {
    if (lpf[i] == i) {
      for (int j = i * i; j < maxval; j+=i) {
        if (lpf[j] == j)
          lpf[j] = i;
      }
    }
  }

  cin >> n >> q;
  for (int i = 1; i <= n; i++)
    cin >> A[i];

  for (int i = 1; i <= q; i++) {
    int l, r;
    int x;
    long long val;
    cin >> l >> r >> x >> val;

    events[l].push_back({x, val});
    events[r + 1].push_back({x, -val});
  }

  for (int i = 1; i <= n; i++) {
    for (const auto& x : events[i]) {
      profit[x.first] += x.second;
    }

    make_num(A[i], i);
  }

  for (int i = 1; i <= n; i++) {
    cout << S[i] << ' ';
  }

}
