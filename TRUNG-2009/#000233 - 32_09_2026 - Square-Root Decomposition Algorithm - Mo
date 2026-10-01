#include <bits/stdc++.h>
using namespace std;

/*
Tên bài: Đếm số lượng phần tử phân biệt trong đoạn (DQUERY)
Giới hạn thời gian: 1.0s
Giới hạn bộ nhớ: 256 MB

Đề bài:
Cho một mảng A gồm N số nguyên dương. Có Q truy vấn, mỗi truy vấn gồm hai số nguyên L và R. Với mỗi truy vấn, hãy đếm xem trong đoạn từ A[L] đến A[R] có bao nhiêu giá trị phân biệt (mỗi số chỉ được đếm 1 lần, bất kể tần suất xuất hiện).

Dữ liệu vào (Input):
- Dòng đầu tiên chứa N (1 <= N <= 50,000).
- Dòng thứ hai chứa N số nguyên A_1, A_2, ..., A_N (1 <= A_i <= 10^6).
- Dòng thứ ba chứa số nguyên Q (1 <= Q <= 50,000).
- Q dòng tiếp theo, mỗi dòng chứa hai số L_i, R_i (1 <= L_i <= R_i <= N) mô tả một truy vấn.

Kết quả (Output):
- In ra Q dòng, dòng thứ i chứa một số nguyên là đáp án của truy vấn thứ i.

Ví dụ:
Input:
5
1 1 2 1 3
3
1 5
2 4
3 5

Output:
3
2
3
*/

const int maxn = 5e4 + 5;
const int maxnum = 1e6 + 5;
int A[maxn];
int cnt[maxnum];
int get_id[maxn];
int res[maxn];
int n, q;
int sz;
int track;
int pt1, pt2;

struct query {
  int l, r;
  int index;

  bool operator<(const query &other) const {
    if (get_id[this->l] != get_id[other.l])
      return get_id[this->l] < get_id[other.l];
    return (get_id[this->l] & 1) ? this->r < other.r : this->r > other.r;
  }
} task[maxn];

inline void add(int index) {
  if (++cnt[A[index]] == 1) track++;
}

inline void remv(int index) {
  if (--cnt[A[index]] == 0) track--;
}

#define _debug 0
int main() {
  cin.tie(0)->sync_with_stdio(0);

#if _debug == 1
  freopen("input.inp", "r", stdin);
#else
  freopen("input.inp", "r", stdin);
  freopen("output.out", "w", stdout);
#endif // _debug

  cin >> n;
  for (int i = 1; i <= n; i++)
    cin >> A[i];

#if _debug == 1
  for (int i = 1; i <= n; i++) {
    cout << A[i] << ' ';
  }
  cout << '\n';
#endif // _debug

  cin >> q;
  for (int i = 1; i <= q; i++) {
    cin >> task[i].l >> task[i].r;
    task[i].index = i;
  }

  sz = max(1, n / (int)sqrt(q));
  for (int i = 1; i <= n; i++) {
    get_id[i] = (i - 1) / sz + 1;
  }

  sort(task + 1, task + q + 1);

#if _debug == 1
  for (int i = 1; i <= q; i++) {
    cout << task[i].l << ' ' << task[i].r << ' ' << task[i].index << '\n';
  }
#endif // _debug

  pt1 = 1;
  pt2 = 0;
  track = 0;
  for (int i = 1; i <= q; i++) {
    int l = task[i].l;
    int r = task[i].r;
    while (pt1 > l) {
      pt1--;
      add(pt1);
    }
    while (pt2 < r) {
      pt2++;
      add(pt2);
    }

    while (pt1 < l) {
      remv(pt1);
      pt1++;
    }
    while (pt2 > r) {
      remv(pt2);
      pt2--;
    }

    res[task[i].index] = track;

#if _debug == 1
    cout << pt1 << ' ' << pt2 << '\n';
    for (int i = 1; i <= n; i++) {
      cout << cnt[i] << ' ';
    }
    cout << '\n';
#endif // _debug
  }

  for (int i = 1; i <= q; i++) {
    cout << res[i] << '\n';
  }
}
