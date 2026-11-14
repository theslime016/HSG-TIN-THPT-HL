#include <bits/stdc++.h>
using namespace std;

/**
Trượt tuyết

Cuộc thi trượt tuyết có n vận động viên tham gia. Tuyến đường trượt dài m km. Các vận động viên xuất phát lần lượt cách nhau 1 phút. Tốc độ trượt của vận động viên thứ i là wi km/phút. Vận động viên i vượt vận động viên j nếu anh xuất phát sau vận động viên j và về đích trước.
Hãy xác định tổng số lần vượt trong cuộc thi.

Dữ liệu: Vào từ file văn bản SKIING.INP:
- Dòng đầu tiên chứa 2 số nguyên n và m (1 ≤ n ≤ 5*10^5, 1 ≤ m ≤ 10^9),
- Dòng thứ 2 chứa n số nguyên w1, w2, ..., wn (1 ≤ wi ≤ 10^9, i = 1 ÷ n).

Kết quả: Đưa ra file văn bản SKIING.OUT một số nguyên – tổng số lần vượt trong cuộc thi.

Ví dụ:
SKIING.INP
5 49
24 27 2 15 32

SKIING.OUT
3
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

const int maxn = 5e5 + 5;
int n;
long long m;

long long A[maxn];

struct FRACTION {
  long long int_part;
  long long up, down;

  void init(long long _int_part, long long _up, long long _down) {
    int_part = _int_part + _up / _down;
    up = _up%_down;
    down = _down;
  }

  friend bool operator<(const FRACTION& a, const FRACTION& b) {
    if (a.int_part != b.int_part)
      return a.int_part < b.int_part;
    else
      return a.up * b.down < a.down * b.up;
  }

  friend bool operator==(const FRACTION& a, const FRACTION& b) {
    return a.int_part == b.int_part && a.up * b.down == a.down * b.up;
  }
};

FRACTION timer[maxn];

struct FENWICK {
  int data[maxn];

  void update(int index, int val) {
    for (; index > 0; index -= index & -index) {
      data[index] += val;
    }
  }

  int fetch(int index) {
    int res = 0;
    for (; index < maxn; index += index & -index) {
      res += data[index];
    }
    return res;
  }
} fenwick;

int main() {
  cin.tie(0)->sync_with_stdio(0);

#if _debug == 1
  freopen("input.inp", "r", stdin);

#else
  freopen("SKIING.INP", "r", stdin);
  freopen("SKIING.OUT", "w", stdout);

#endif // _debug

  cin >> n >> m;
  for (int i = 1; i <= n; i++)
    cin >> A[i];

  vector<FRACTION> comp;
  comp.reserve(n);
  for (int i = 1; i <= n; i++) {
    int penalty = i - 1;
    timer[i].init(penalty, m, A[i]);
    comp.push_back(timer[i]);
  }

#if _debug == 1
  for (int i = 1; i <= n; i++) {
    debug(i, timer[i].int_part, timer[i].up, timer[i].down);
    newline;
  }

#endif // _debug

  sort(comp.begin(), comp.end());
  comp.erase(unique(comp.begin(), comp.end()), comp.end());

#if _debug == 1
  cerr << "comp: " << endl;
  for (FRACTION x : comp)
    cerr << x.int_part << '+' << x.up << '/' << x.down << endl;
  newline;

#endif // _debug

  auto fnd = [&](FRACTION val) {
    return lower_bound(comp.begin(), comp.end(), val) - comp.begin() + 1;
  };

  long long res = 0;
  for (int i = 1; i <= n; i++) {
    int fnd_index = fnd(timer[i]);
    res += fenwick.fetch(fnd_index + 1);
    fenwick.update(fnd_index, 1);
  }

  cout << res;

}
