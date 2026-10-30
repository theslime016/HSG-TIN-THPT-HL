#include <bits/stdc++.h>
using namespace std;

/*
PGAME
Input: pgame.inp
Output: pgame.out

Tại các hội nghị toán học, các nhà toán học trẻ thường thư dãn bằng trò chơi vòng số nguyên tố.
Để đơn giản, chúng ta đánh số các nhà toán học từ 1 đến n.
Đầu tiên, n nhà toán học xếp lần lượt (từ 1 đến n) thành một vòng tròn lớn ngược chiều kim đồng hồ. Nhà toán học 1 đứng trong một hình vuông còn n - 1 nhà toán học còn lại đứng trong các vòng tròn nhỏ.
Trò chơi được thực hiện k lượt. Tại lượt thứ i, nhà toán học đứng trong hình vuông nhảy lên hô "đến lượt tôi!" và thực hiện việc đổi chỗ với người đứng bên phải anh ta p_i lần (ở đây p_i là số nguyên tố thứ i).
Viết chương trình cho trước n, k và A. Hãy xác định số hiệu của các nhà toán học đứng cạnh nhà toán học mang số hiệu A (trên vòng tròn lớn).
Input:
- Một dòng duy nhất chứa ba số nguyên n, k và A (1 <= A <= n) lần lượt là số lượng nhà toán học, số vòng chơi và số hiệu của nhà toán học cần xác định hàng xóm (1 <= n <= 5*10^6; 1 <= k <= 5*10^5).
Output:
- Một dòng duy nhất chứa hai số nguyên là số hiệu của người đứng bên phải, bên trái của nhà toán học số hiệu A.
Example:
Test 1:
Input:
5 3 1
Output:
3 5

Test 2:
Input:
5 3 2
Output:
5 4

Test 3:
Input:
5 4 5
Output:
3 2
Scoring:
- Subtask 1 (25% số điểm): 3 <= n <= 1000; 1 <= k <= 1000.
- Subtask 2 (25% số điểm): 3 <= n <= 1000; 1 <= k <= 50000.
- Subtask 3 (25% số điểm): 3 <= n <= 50000; 1 <= k <= 50000.
- Subtask 4 (25% số điểm): Không có ràng buộc bổ sung.
*/


#if defined(__has_include) && __has_include("slime_debug_016.h")
#include "slime_debug_016.h"

#else
#define _debug 0

#endif // defined

/// MACRO
#if _debug == 1
#define debug(x) cerr << #x << ':' << (x) << ' ';
#define newline cerr << '\n';

#else
#define debug(x) 42
#define newline 42

#endif // _debug

const int maxn = 5e6 + 5;
long long n, k;

int make_forward(int tar, long long p) {
  long long q = p / (n - 1);
  long long r = p % (n - 1);
  if (tar == 0) return p%n;
  else if (tar <= r) return ((tar - q - 1)%n + n)%n;
  else return ((tar - q)%n + n)%n;
}

int make_backward(int tar, long long p) {
  long long q = p / (n - 1);
  long long r = p % (n - 1);
  if (tar == p%n) return 0;

  int cand1 = (tar + q + 1)%n;
  int cand2 = (tar + q)%n;
  if (1 <= cand1 && cand1 <= r) return cand1;
  else return cand2;
}

const long long maxprime= 8e6;
bitset<maxprime> is_prime;
long long prime[maxn];
int ptr = 1;

int main() {
  cin.tie(0)->sync_with_stdio(0);

#if _debug == 1
  freopen("input.inp", "r", stdin);

#elif _debug == 2
  freopen("input.inp", "r", stdin);

#else
  freopen("pgame.inp", "r", stdin);
  freopen("pgame.out", "w", stdout);

#endif // _debug

  is_prime.set();
  is_prime[0] = is_prime[1] = false;
  for (long long i = 2; i*i < maxprime; i++) {
    if (!is_prime[i]) continue;
    for (long long j = i*i; j < maxprime; j+=i) {
      is_prime[j] = false;
    }
  }

  for (int i = 2; i < maxprime; i++) {
    if (is_prime[i]) prime[ptr++] = i;
  }

  cin >> n >> k;
  int start_point;
  cin >> start_point;
  start_point--;
  for (int i = 1; i <= k; i++) {
    start_point = make_forward(start_point, prime[i]);
  }

  long long tar1 = ((start_point - 1)%n + n)%n;
  long long tar2 = (start_point + 1)%n;
  for (int i = k; i >= 1; i--) {
    tar1 = make_backward(tar1, prime[i]);
    tar2 = make_backward(tar2, prime[i]);
  }
  cout << tar2 + 1 << ' ' << tar1 + 1;
}
