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

struct uf {
  int n;
  vector<int> data;
  vector<int> bucket;
  vector<int> cnt; // edges
  //set<int> s;

  uf (int n) {
    this->n = n;
    data.assign(n+1, 0);
    iota(data.begin(), data.end(), 0);
    bucket.assign(n+1, 1);
    cnt.assign(n+1, 0);
    //for (int i = 1; i <= n; i++) s.insert(i);
  }

  void reset() {
    iota(data.begin(), data.end(), 0);
    bucket.assign(n+1, 1);
    cnt.assign(n+1, 0);
    memcpy(minx, chest, sizeof chest);
    memcpy(sum, chest, sizeof chest);
    //set.clear();
    //for (int i = 1; i <= n; i++) s.insert(i);
  }

  int fnd(int index) {
    if (data[index] == index) return index;
    return data[index] = fnd(data[index]);
  }

  void proc(int a, int b) {
    a = fnd(a);
    b = fnd(b);
    if (a != b) {
      if (bucket[a] < bucket[b]) swap(a, b);
      data[b] = a;
      cnt[a] += cnt[b] + 1;
      bucket[a] += bucket[b];
      minx[a] = min(minx[a], minx[b]);
      sum[a] += sum[b];
      //s.erase(b);
    } else {
      cnt[a]++;
    }
  }
};

struct TASK {
  int l, r;
} task[maxn];

#define _debug  1
int main() {
  cin.tie(0)->sync_with_stdio(0);

#if _debug == 1
  freopen("input.inp", "r", stdin);
#else

#endif // _debug

  int n, k, q;
  cin >> n >> k >> q;
  for (int i = 1; i <= n; i++) cin >> chest[i];
  for (int i = 1; i <= k; i++) cin >> key[i].first >> key[i].second;
  for (int i = 1; i <= q; i++) cin >> task[i].l >> task[i].r;

  uf dsu(n);
  for (int i = 1; i <= q; i++) {
    auto [x, y] = task[i];

    dsu.reset();
    int pt = x;
    while (pt <= y) {
      dsu.proc(key[pt].first, key[pt].second);
      pt++;
    }

#if _debug == 1

    for (int i = 1; i <= n; i++) cout << dsu.fnd(i) << ' ';
    cout << '\n';
    for (int i = 1; i <= n; i++) cout << dsu.cnt[i] << ' ';
    cout << '\n';
    for (int i = 1; i <= n; i++) cout << dsu.bucket[i] << ' ';
    cout << '\n';
    for (int i = 1; i <= n; i++) cout << sum[i] << ' ';
    cout << '\n';
    for (int i = 1; i <= n; i++) cout << minx[i] << ' ';
    cout << '\n';

#endif // _debug

    long long res = 0;
    for (int i = 1; i <= n; i++) {
      if (dsu.data[i] != i) continue;
      res += sum[i];
      if (dsu.bucket[i] - 1 == dsu.cnt[i]) res -= minx[i];
    }
    cout << res << '\n';
  }

}
