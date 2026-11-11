#include <bits/stdc++.h>
using namespace std;

/*
DQUERY

Điểm: 100
Thời gian: 1.0s
Bộ nhớ: 1G
Input: stdin
Output: stdout
Tác giả: lethanhbinh

Cho dãy số nguyên A = (a1, a2, ..., an) và một số các truy vấn. Mỗi truy vấn có dạng hai số nguyên (i, j) với ý nghĩa cần tính số giá trị khác nhau nằm trong dãy con:
ai, a(i+1), ..., aj

Yêu cầu: Viết chương trình thực hiện các truy vấn nói trên.

Input:
- Dòng 1: Số nguyên dương n ≤ 10^5;
- Dòng 2: n số nguyên a1, a2, ..., an (|ai| ≤ 10^9);
- Dòng 3: Số nguyên dương Q (Q ≤ 2 * 10^5) — số lượng các truy vấn;
- Dòng 4 ... Q + 3: Dòng 3 + k chứa hai số nguyên i, j (1 ≤ i ≤ j ≤ n) mô tả truy vấn thứ k (k = 1 ÷ Q).

Output:
- In ra Q dòng, mỗi dòng một số nguyên lần lượt là kết quả tìm được của các truy vấn theo thứ tự 1, 2, ..., Q.

Example:
Test 1
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
const int maxq = 2e5 + 5;

struct FENWICK {
  int data[maxn];

  void update(int index, int val) {
    for (; index < maxn; index += index & -index) {
      data[index] += val;
    }
  }

  int fetch(int index) {
    int res = 0;
    for (; index > 0; index -= index & -index) {
      res += data[index];
    }
    return res;
  }
};

int n, q;

int A[maxn];
int last_pos[maxn];

struct EVENT {
  int l;
  int index;
};
vector<EVENT> event[maxn]; /// R
int query_res[maxq];

int main() {
  cin.tie(0)->sync_with_stdio(0);

#if _debug == 1
  freopen("input.inp", "r", stdin);

#else

#endif // _debug

  cin >> n;

  vector<int> comp;
  comp.reserve(n);

  for (int i = 1; i <= n; i++) {
    cin >> A[i];
    comp.push_back(A[i]);
  }

  sort(comp.begin(), comp.end());
  comp.erase(unique(comp.begin(), comp.end()), comp.end());

  auto fnd = [&](int val) {
    return lower_bound(comp.begin(), comp.end(), val) - comp.begin() + 1;
  };

  cin >> q;
  for (int i = 1; i <= q; i++) {
    int l, r;
    cin >> l >> r;
    EVENT temp;
    temp.l = l;
    temp.index = i;
    event[r].push_back(temp);
  }

  memset(last_pos, -1, sizeof last_pos);

  FENWICK fenwick{};
  for (int r = 1; r <= n; r++) {
    int fnd_index = fnd(A[r]);
    if (last_pos[fnd_index] != -1) {
      fenwick.update(last_pos[fnd_index], -1);
    }

    fenwick.update(r, 1);
    last_pos[fnd_index] = r;

    for (const EVENT& x : event[r]) {
      query_res[x.index] = fenwick.fetch(r) - fenwick.fetch(x.l-1);
    }

  }

  for (int i = 1; i <= q; i++) cout << query_res[i] << '\n';

}
