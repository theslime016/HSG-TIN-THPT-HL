#include <bits/stdc++.h>
using namespace std;

/*
TÊN BÀI: KHO BÁU (THE KEY SEQUENCE)
Giới hạn thời gian: 2.0s
Giới hạn bộ nhớ: 256 MB

ĐỀ BÀI:
Có N chiếc rương kho báu, chiếc rương thứ i có giá trị là C_i.

Bạn tìm thấy một hành lang dài chứa K chiếc chìa khóa xếp thành một hàng ngang, được đánh số từ 1 đến K. Chiếc chìa khóa ở vị trí thứ i có thể được dùng để mở một trong hai chiếc rương A_i hoặc B_i (lưu ý: không thể dùng một chiếc chìa khóa để mở cả hai rương). Mỗi chiếc rương chỉ có thể được mở khóa tối đa một lần.

Bạn có Q đợt thám hiểm. Trong đợt thám hiểm thứ i, hệ thống an ninh chỉ cho phép bạn lấy và sử dụng các chiếc chìa khóa nằm trong đoạn liên tiếp từ vị trí L_i đến vị trí R_i trên hành lang.

Yêu cầu: Với mỗi đợt thám hiểm, hãy cho biết tổng giá trị kho báu lớn nhất bạn có thể thu được nếu lựa chọn mở rương một cách tối ưu bằng các chìa khóa trong đoạn [L_i, R_i].
Lưu ý: Các đợt thám hiểm là hoàn toàn độc lập với nhau (các rương và chìa khóa khôi phục lại trạng thái chưa sử dụng sau mỗi đợt).

INPUT:
- Dòng đầu tiên chứa ba số nguyên N, K, Q (1 <= N, K, Q <= 100,000).
- Dòng thứ hai chứa N số nguyên C_1, C_2, ..., C_N (1 <= C_i <= 10^9).
- K dòng tiếp theo, dòng thứ i chứa hai số nguyên A_i và B_i (1 <= A_i, B_i <= N, A_i != B_i) mô tả khả năng mở khóa của chiếc chìa khóa thứ i.
- Q dòng tiếp theo, dòng thứ i chứa hai số nguyên L_i và R_i (1 <= L_i <= R_i <= K) mô tả truy vấn của đợt thám hiểm thứ i.

OUTPUT:
- Gồm Q dòng, dòng thứ i chứa một số nguyên duy nhất là tổng giá trị kho báu lớn nhất thu được trong đợt thám hiểm thứ i.

---------------------------------------------------------
VÍ DỤ 1:
Input:
4 4 3
10 20 30 40
1 2
2 3
3 4
4 1
1 2
1 4
2 4

Output:
50
100
90

Giải thích VD 1:
- Truy vấn 1 (Đoạn chìa [1, 2]): Ta có chìa (1-2) và chìa (2-3). Có 2 chìa, ta mở được tối đa 2 rương trong số các rương 1, 2, 3. Chọn mở rương 2 và 3 để được giá trị lớn nhất: 20 + 30 = 50.
- Truy vấn 2 (Đoạn chìa [1, 4]): Ta có cả 4 chìa tạo thành một chu trình khép kín. Ta có thể mở trọn vẹn cả 4 rương. Tổng = 10 + 20 + 30 + 40 = 100.
- Truy vấn 3 (Đoạn chìa [2, 4]): Ta có 3 chìa (2-3), (3-4), (4-1). Ta mở được tối đa 3 rương trong 4 rương. Bỏ lại rương 1 (giá trị nhỏ nhất là 10). Tổng = 20 + 30 + 40 = 90.

---------------------------------------------------------
VÍ DỤ 2:
Input:
5 5 2
5 10 15 20 25
1 2
1 2
3 4
4 5
3 5
1 5
3 4

Output:
75
45

Giải thích VD 2:
- Truy vấn 1 (Đoạn chìa [1, 5]): Ta có toàn bộ chìa. Đồ thị tạo thành 2 thành phần liên thông: {1, 2} có 2 đỉnh 2 cạnh (chu trình) và {3, 4, 5} có 3 đỉnh 3 cạnh (chu trình). Ta có thể mở toàn bộ 5 rương. Tổng = 5+10+15+20+25 = 75.
- Truy vấn 2 (Đoạn chìa [3, 4]): Ta có chìa (3-4) và (4-5). Đây là một cây gồm 3 đỉnh {3, 4, 5} và 2 cạnh. Ta mở được 2 rương. Giá trị các rương là 15, 20, 25. Ta bỏ lại rương có giá trị 15. Chọn mở rương 4 và 5. Tổng = 20 + 25 = 45.
*/

const int maxn = 1e5 + 5;
const long long inf = 1e18;
long long chest[maxn];
long long minx[maxn];
long long sum[maxn];
pair<int, int> key[maxn];

struct STATE {
  int a, b;
  int other_data;
  int bucket;
  int cnt;
  long long minx;
  long long sum;
  long long local;
};

struct uf {
  int n;
  long long local;
  vector<int> data;
  vector<int> bucket;
  vector<int> cnt; // edges
  stack<STATE> st;
  //set<int> s;

  uf (int n) {
    this->n = n;
    this->local = 0;
    data.assign(n+1, 0);
    iota(data.begin(), data.end(), 0);
    bucket.assign(n+1, 1);
    cnt.assign(n+1, 0);
    //for (int i = 1; i <= n; i++) s.insert(i);
  }

  void reset() {
    this->local = 0;
    iota(data.begin(), data.end(), 0);
    bucket.assign(n+1, 1);
    cnt.assign(n+1, 0);
    while (!st.empty()) st.pop();
    memcpy(minx, chest, sizeof chest);
    memcpy(sum, chest, sizeof chest);
    //set.clear();
    //for (int i = 1; i <= n; i++) s.insert(i);
  }

  int fnd(int index) {
    while (index != data[index]) {
      index = data[index];
    }
    return index;
  }

  void make_log(int a, int b) {
    st.push({a, b, data[b], bucket[a], cnt[a], minx[a], sum[a], local});
  }

  void rollback() {
    while (!st.empty()) {
      int a = st.top().a;
      int b = st.top().b;
      bucket[a] = st.top().bucket;
      cnt[a] = st.top().cnt;
      minx[a] = st.top().minx;
      sum[a] = st.top().sum;
      data[b] = st.top().other_data;
      local = st.top().local;
      st.pop();
    }
  }

  long long get_val(int index) {
    return sum[index] - ((bucket[index] - 1 == cnt[index]) ? minx[index] : 0);
  }

  void proc(int a, int b, int type = 0) {
    a = fnd(a);
    b = fnd(b);

    if (a != b) {
      if (bucket[a] < bucket[b]) swap(a, b);
      if (type) make_log(a, b);
      local -= get_val(a) + get_val(b);

      data[b] = a;
      cnt[a] += cnt[b] + 1;
      bucket[a] += bucket[b];
      minx[a] = min(minx[a], minx[b]);
      sum[a] += sum[b];
      //s.erase(b);
      local += get_val(a);
    } else {
      if (type) make_log(a, b);
      local -= get_val(a);
      cnt[a]++;
      local += get_val(a);
    }
  }
};

int sz, num_block;
int get_id[maxn];
long long res[maxn];

const int maxnode = 500;
int lblock[maxnode], rblock[maxnode];
struct TASK {
  int l, r;
  int index;

  bool operator<(const TASK& other) {
    int tag1 = get_id[this->l];
    int tag2 = get_id[other.l];
    if (tag1 == tag2) return this->r < other.r;
    else return tag1 < tag2;
  }

} task[maxn];

#define _debug 0
int main() {
  cin.tie(0)->sync_with_stdio(0);

#if _debug == 1
  freopen("input.inp", "r", stdin);
#else
  freopen("input.inp", "r", stdin);
  freopen("output.out", "w", stdout);
#endif // _debug

  int n, k, q;
  cin >> n >> k >> q;
  for (int i = 1; i <= n; i++) cin >> chest[i];
  for (int i = 1; i <= k; i++) cin >> key[i].first >> key[i].second;
  for (int i = 1; i <= q; i++) {
    cin >> task[i].l >> task[i].r;
    task[i].index = i;
  }

  sz = max(1, k / (int)sqrt(q));
  num_block = (k-1)/sz + 1;
  for (int i = 1; i <= k; i++) {
    get_id[i] = (i-1)/sz + 1;
  }

  for (int i = 1; i <= num_block; i++) {
    lblock[i] = (i-1)*sz + 1;
    rblock[i] = min(k, i * sz);
  }

  sort(task+1, task+q+1);

#if _debug == 1
  cout << sz << ' ' << num_block << '\n' << '\n';
  for (int i = 1; i <= num_block; i++) cout << lblock[i] << ' ' << rblock[i] << '\n';
  cout << '\n';
  for (int i = 1; i <= q; i++) cout << task[i].index << ' ' << task[i].l << ' ' << task[i].r << '\n';
#endif // _debug

  uf dsu(n);
  int current_parity = -1;
  int pt2 = 0;
  for (int i = 1; i <= q; i++) {
    int tag = get_id[task[i].l];
    if (tag != current_parity) {
      current_parity = tag;
      dsu.reset();
      pt2 = rblock[tag];
    }

    int other_tag = get_id[task[i].r];
    if (tag == other_tag) {
      for (int j = task[i].l; j <= task[i].r; j++) {
        dsu.proc(key[j].first, key[j].second, 1);
      }
      res[task[i].index] = dsu.local;
      dsu.rollback();
      continue;
    }

    while (pt2 < task[i].r) {
      pt2++;
      dsu.proc(key[pt2].first, key[pt2].second);
    }

    int pt1 = task[i].l - 1;
    while (pt1 < rblock[tag]) {
      pt1++;
      dsu.proc(key[pt1].first, key[pt1].second, 1);
    }

    res[task[i].index] = dsu.local;
    dsu.rollback();
  }

  for (int i = 1; i <= q; i++) cout << res[i] << '\n';
}
