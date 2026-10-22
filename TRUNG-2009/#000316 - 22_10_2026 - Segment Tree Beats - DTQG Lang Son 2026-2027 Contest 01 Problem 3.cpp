#include <bits/stdc++.h>
using namespace std;

/*
Cho một dãy gồm n số nguyên A (n <= 2*10^5, 0 <= Ai <= 10^9).
Định nghĩa một phần tử an toàn là phần tử có giá trị lớn hơn hoặc bằng C (0 <= C <= 10^9).
Cho Q truy vấn (Q <= 2*10^5) thuộc 4 loại:
- Loại 1: l r h - Cập nhật Ai = min(Ai, h) với mọi i trong khoảng [l, r].
- Loại 2: l r - Tính tổng các phần tử trong đoạn [l, r].
- Loại 3: l r - Tìm phần tử lớn nhất trong đoạn [l, r].
- Loại 4: l r - Đếm số lượng cụm an toàn cực đại trong đoạn [l, r].

Giới hạn:
1 <= l <= r <= n
0 <= h <= 10^9

Giải thích về cụm an toàn:
- Một cụm an toàn là một cụm chỉ chứa các phần tử an toàn.
- Một cụm an toàn cực đại là cụm lớn nhất có thể trong đoạn [l, r] (không thể mở rộng thêm ra hai phía).
Ví dụ với C = 10 và dãy A = [15, 1, 15, 16, 17, 1, 18]:
+ Các cụm [3, 4], [4, 5] là các cụm an toàn.
+ Các cụm [1], [3, 4, 5], [7] là các cụm an toàn cực đại.

Các Subtask:
- Subtask 1: n, q <= 2000
- Subtask 2: Không có truy vấn loại 1
- Subtask 3: Truy vấn loại 1 đều có l = 1 và r = n
- Subtask 4: n, q <= 50 000
- Subtask 5: Không có giới hạn gì thêm
*/

#define _debug 1

#if _debug == 1
#define debug(x) cerr << #x << ':' << (x) << ' ';
#define newline cerr << '\n';

#else
#define debug(x)
#define newline

#endif // _debug

const int maxn = 2e5 + 5;
const long long inf = 1e18;
long long A[maxn];
int n, q;
long long c;

struct NODE {
  long long sum_val = 0;

  long long max1 = -inf;
  long long max2 = -inf;
  int cnt_max = 0;

  int cnt = 0;
  int left = 0;
  int right = 0;
} segment[maxn << 2];

NODE proc(const NODE& a, const NODE& b) {
  NODE res;
  res.sum_val = a.sum_val + b.sum_val;

  if (a.max1 > b.max1) {
    res.max1 = a.max1;
    res.cnt_max = a.cnt_max;
    res.max2 = max(a.max2, b.max1);
  } else if (a.max1 < b.max1) {
    res.max1 = b.max1;
    res.cnt_max = b.cnt_max;
    res.max2 = max(a.max1, b.max2);
  } else {
    res.max1 = a.max1;
    res.cnt_max = a.cnt_max + b.cnt_max;
    res.max2 = max(a.max2, b.max2);
  }

  res.cnt = a.cnt + b.cnt;
  res.left = a.left;
  res.right = b.right;
  if (a.right && b.left) res.cnt--;
  return res;
}

void apply(int index, long long val) {
  if (val >= segment[index].max1) return;

  segment[index].sum_val -= (segment[index].max1 - val)
                            * segment[index].cnt_max;
  segment[index].max1 = val;
  if (val < c) {
    segment[index].cnt = 0;
    segment[index].left = 0;
    segment[index].right = 0;
  }
}

void push_down(int index) {
  long long tag = segment[index].max1;
  if (segment[index << 1].max1 > tag) {
    apply(index << 1, tag);
  }
  if (segment[index << 1 | 1].max1 > tag) {
    apply(index << 1 | 1, tag);
  }
}

void build(int index, int l, int r) {
  if (r < l) return;
  if (l == r) {
    segment[index].max1 = A[l];
    segment[index].cnt_max = 1;

    segment[index].sum_val = A[l];

    segment[index].left = segment[index].right =
                            (segment[index].max1 >= c);
    segment[index].cnt = segment[index].left;
    return;
  }

  int mid = l + ((r - l) >> 1);
  build(index << 1, l, mid);
  build(index << 1 | 1, mid + 1, r);
  segment[index] = proc(segment[index << 1], segment[index << 1 | 1]);
}

void update(int index, int l, int r, int ql, int qr, long long val) {
  if (l > qr || r < ql) return;
  if (val >= segment[index].max1) return;
  if (l >= ql && r <= qr && val > segment[index].max2
      && val < segment[index].max1) {
    apply(index, val);
    return;
  }

  push_down(index);

  int mid = l + ((r - l) >> 1);
  update(index << 1, l, mid, ql, qr, val);
  update(index << 1 | 1, mid + 1, r, ql, qr, val);
  segment[index] = proc(segment[index << 1], segment[index << 1 | 1]);
}

NODE query(int index, int l, int r, int ql, int qr) {
  if (l > qr || r < ql) return NODE();
  else if (l >= ql && r <= qr) return segment[index];

  push_down(index);

  int mid = l + ((r - l) >> 1);
  return proc(query(index << 1, l, mid, ql, qr),
              query(index << 1 | 1, mid + 1, r, ql, qr));
}

void solve_subtask1() {
  while (q--) {
    int type;
    cin >> type;

    if (type == 1) {
      int l, r;
      long long h;
      cin >> l >> r >> h;
      for (int i = l; i <= r; i++) {
        A[i] = min(A[i], h);
      }

    } else if (type == 2) {
      int l, r;
      cin >> l >> r;
      long long res = 0;
      for (int i = l; i <= r; i++) {
        res += A[i];
      }
      cout << res << '\n';



    } else if (type == 3) {
      int l, r;
      cin >> l >> r;
      long long res = -inf;
      for (int i = l; i <= r; i++) {
        res = max(res, A[i]);
      }
      cout << res << '\n';



    } else if (type == 4) {
      int l, r;
      cin >> l >> r;
      long long res = 0;

      int current = 0;
      for (int i = l; i <= r; i++) {
        if (current == 0 && A[i] >= c) {
          current = 1;
          res++;
        } else if (current == 1 && A[i] < c) {
          current = 0;
        }
      }
      cout << res << '\n';


    }

  }
}


int main() {
  cin.tie(0)->sync_with_stdio(0);

#if _debug == 1
  freopen("input.inp", "r", stdin);

#elif _debug == 2
  freopen("input.inp", "r", stdin);

#else
  freopen("BARIER.INP", "r", stdin);
  freopen("BARIER.OUT", "w", stdout);

#endif // _debug

  cin >> n >> q >> c;
  for (int i = 1; i <= n; i++) cin >> A[i];

  build(1, 1, n);

  while (q--) {
    int type;
    cin >> type;
    if (type == 1) {
      int l, r;
      long long h;
      cin >> l >> r >> h;
      update(1, 1, n, l, r, h);
    } else {
      int l, r;
      cin >> l >> r;
      NODE res = query(1, 1, n, l, r);
      if (type == 2) cout << res.sum_val << '\n';
      if (type == 3) cout << res.max1 << '\n';
      if (type == 4) cout << res.cnt << '\n';
    }
  }

#if _debug == 1



#endif // _debug

}
