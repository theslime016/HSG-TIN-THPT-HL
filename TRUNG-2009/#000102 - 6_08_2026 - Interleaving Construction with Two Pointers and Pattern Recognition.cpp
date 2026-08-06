#include <bits/stdc++.h>
using namespace std;
/*
======================================================================
PROBLEM: CẶP HOÁN VỊ MA THUẬT (THE MAGIC PAIR)
======================================================================
Tags: #Constructive_Algorithms, #Math, #Two_Pointers

[MÔ TẢ BÀI TOÁN]
Trong một nghi thức tế lễ, pháp sư cần chuẩn bị hai hàng bùa chú.
Mỗi hàng là một hoán vị của các số nguyên từ 1 đến N (với N là số lẻ).
Gọi hai hàng này lần lượt là A và B.

Nghi thức yêu cầu tổng sức mạnh của từng cột phải tăng dần hoặc giảm
dần đều đặn. Cụ thể, gọi S[i] = A[i] + B[i] (1 <= i <= N) là tổng
của cột thứ i. Dãy S[1], S[2], ..., S[N] phải tạo thành một cấp số
cộng với công sai d (d = 1 hoặc d = -1).

Nhiệm vụ của bạn là: Cho trước số lẻ N và công sai d. Hãy kiến thiết
(construct) ra hai hoán vị A và B thỏa mãn điều kiện trên.

[INPUT FORMAT]
- Dòng đầu tiên chứa số nguyên T (1 <= T <= 10^4) — số lượng test cases.
- T dòng tiếp theo, mỗi dòng chứa hai số nguyên N và d:
  + N là số lượng bùa chú trong một hàng (1 <= N <= 10^5, N luôn lẻ).
  + d là công sai yêu cầu (d thuộc {-1, 1}).
- Tổng của N trên tất cả các test cases không vượt quá 2 * 10^5.

[OUTPUT FORMAT]
- Với mỗi test case, in ra hai dòng:
  + Dòng thứ nhất chứa N số nguyên, biểu diễn hoán vị A.
  + Dòng thứ hai chứa N số nguyên, biểu diễn hoán vị B.
(Nếu có nhiều cặp hoán vị thỏa mãn, in ra một cặp bất kỳ).

[EXAMPLE]
* Input:
2
5 1
3 -1

* Output:
1 4 2 5 3
3 1 4 2 5
2 3 1
3 1 2

[GIẢI THÍCH VÍ DỤ]
* Test case 1 (N = 5, d = 1):
  Hàng A: 1 4 2 5 3
  Hàng B: 3 1 4 2 5
  Tổng S: 4 5 6 7 8 (Cấp số cộng, d = 1)

* Test case 2 (N = 3, d = -1):
  Hàng A: 2 3 1
  Hàng B: 3 1 2
  Tổng S: 5 4 3 (Cấp số cộng, d = -1)
*/

#define debugr(x) cout << #x << " = " << (x) << '\n'
#define debugl cout << '\n'#include <bits/stdc++.h>
using namespace std;
/*
======================================================================
PROBLEM: CẶP HOÁN VỊ MA THUẬT (THE MAGIC PAIR)
======================================================================
Tags: #Constructive_Algorithms, #Math, #Two_Pointers

[MÔ TẢ BÀI TOÁN]
Trong một nghi thức tế lễ, pháp sư cần chuẩn bị hai hàng bùa chú.
Mỗi hàng là một hoán vị của các số nguyên từ 1 đến N (với N là số lẻ).
Gọi hai hàng này lần lượt là A và B.

Nghi thức yêu cầu tổng sức mạnh của từng cột phải tăng dần hoặc giảm
dần đều đặn. Cụ thể, gọi S[i] = A[i] + B[i] (1 <= i <= N) là tổng
của cột thứ i. Dãy S[1], S[2], ..., S[N] phải tạo thành một cấp số
cộng với công sai d (d = 1 hoặc d = -1).

Nhiệm vụ của bạn là: Cho trước số lẻ N và công sai d. Hãy kiến thiết
(construct) ra hai hoán vị A và B thỏa mãn điều kiện trên.

[INPUT FORMAT]
- Dòng đầu tiên chứa số nguyên T (1 <= T <= 10^4) — số lượng test cases.
- T dòng tiếp theo, mỗi dòng chứa hai số nguyên N và d:
  + N là số lượng bùa chú trong một hàng (1 <= N <= 10^5, N luôn lẻ).
  + d là công sai yêu cầu (d thuộc {-1, 1}).
- Tổng của N trên tất cả các test cases không vượt quá 2 * 10^5.

[OUTPUT FORMAT]
- Với mỗi test case, in ra hai dòng:
  + Dòng thứ nhất chứa N số nguyên, biểu diễn hoán vị A.
  + Dòng thứ hai chứa N số nguyên, biểu diễn hoán vị B.
(Nếu có nhiều cặp hoán vị thỏa mãn, in ra một cặp bất kỳ).

[EXAMPLE]
* Input:
2
5 1
3 -1

* Output:
1 4 2 5 3
3 1 4 2 5
2 3 1
3 1 2

[GIẢI THÍCH VÍ DỤ]
* Test case 1 (N = 5, d = 1):
  Hàng A: 1 4 2 5 3
  Hàng B: 3 1 4 2 5
  Tổng S: 4 5 6 7 8 (Cấp số cộng, d = 1)

* Test case 2 (N = 3, d = -1):
  Hàng A: 2 3 1
  Hàng B: 3 1 2
  Tổng S: 5 4 3 (Cấp số cộng, d = -1)
*/

#define debugr(x) cout << #x << " = " << (x) << '\n'
#define debugl cout << '\n'

int main() {
  cin.tie(0)->sync_with_stdio(false);

  int t;
  cin >> t;
  while (t--) {
    int n, d;
    cin >> n >> d;
    vector<int> A(n + 1);
    vector<int> B(n + 1);
    int m = (n + 1) / 2;
    int x = 1, y = m;
    int s = 1;
    for (int i = 1; i <= n; i++) {
      A[i] = x;
      B[i] = y;
      if (y == n)
        s = -1;
      y += s;

      swap(x, y);
    }

    auto f = [&](int x, int y, vector<int> &S) {
      if (d == 1) {
        for (int i = x; i <= y; i++)
          cout << S[i] << ' ';
      } else {
        for (int i = y; i >= x; i--)
          cout << S[i] << ' ';
      }
    };
    f(1, n, A);
    cout << '\n';
    f(1, n, B);
    cout << '\n';

    // debugl;
    // debugl;
    // for (int i = 1; i <= n; i++)
    // cout << A[i] + B[i] << ' ';
  }
  return 0;
}

int main() {
  cin.tie(0)->sync_with_stdio(false);

  int t;
  cin >> t;
  while (t--) {
    int n, d;
    cin >> n >> d;
    vector<int> A(n + 1);
    vector<int> B(n + 1);
    int m = (n + 1) / 2;
    int x = 1, y = m;
    int s = 1;
    
    // Pattern Recognition
    for (int i = 1; i <= n; i++) {
      A[i] = x;
      B[i] = y;
      if (y == n)
        s = -1;
      y += s;
      swap(x, y);
    }

    // Two Pointers
    // for (int i = 1; i <= n; i++) {
    //   if (i % 2 != 0) {
    //     A[i] = i / 2 + 1;
    //     B[i] = i / 2 + m;
    //   } else {
    //     A[i] = i / 2 + m;
    //     B[i] = i / 2;
    //   }
    // }

    auto f = [&](int x, int y, vector<int> &S) {
      if (d == 1) {
        for (int i = x; i <= y; i++)
          cout << S[i] << ' ';
      } else {
        for (int i = y; i >= x; i--)
          cout << S[i] << ' ';
      }
    };
    f(1, n, A);
    cout << '\n';
    f(1, n, B);
    cout << '\n';

    // debugl;
    // debugl;
    // for (int i = 1; i <= n; i++)
    // cout << A[i] + B[i] << ' ';
  }
  return 0;
}
