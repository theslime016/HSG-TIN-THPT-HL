#include <bits/stdc++.h>
using namespace std;

/*
E. DNA
time limit per test: 0.25 seconds
memory limit per test: 8 megabytes
input: adn.inp
output: adn.out

Như các bạn đã biết, một chuỗi DNA có thể được biểu diễn bởi một xâu kí tự mà trong đó mỗi tự là một trong bốn chữ cái in hoa A, T, G hay C.

Có ba phép làm thay đổi chuỗi gen thường gặp:

- Thêm: Thêm một kí tự vào trong chuỗi DNA. Kí tự được thêm vào phải là một trong bốn chữ cái in hoa A, T, G hay C.
- Xóa: Xóa một kí tự đang có trong chuỗi DNA.
- Sửa: Thay thế một kí tự đang có trong chuỗi DNA bằng một kí tự khác. Kí tự mới phải là một trong bốn chữ cái in hoa A, T, G hay C.

Cho hai chuỗi DNA s và t, hãy cho biết có thể biến đổi từ s thành t qua không quá hai phép biến đổi hay không.

Input
Dòng đầu tiên chứa xâu s, dòng thứ hai chứa xâu t. Cả hai xâu s và t đều có độ dài từ 1 đến 50, và chỉ chứa các kí tự A, T, G và C.

Output
In ra Yes nếu có thể biến đổi từ s sang t trong không quá hai phép biến đổi, No nếu điều này là không khả thi.

Example
input
AAAAA
AACAACA

output
Yes
*/

#if defined(__has_include) && __has_include("slime_debug_016.h")
#include "slime_debug_016.h"

#else
#define _debug 0

#endif // defined

/// MACRO
#if _debug == 1
void log_out() {
  cerr << '\n';
}
template<typename H, typename... T>
void log_out(H h, T... t) {
  cerr << h << ", ";
  log_out(t...);
}

#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:\n", log_out(__VA_ARGS__)
#define newline cerr << endl

#else
#define debug(...) void(0)
#define newline void(0)

#endif // _debug

string A, B;
set<string> s;

void make_dfs(int index, int op) {
  if (op > 1) return;

  s.insert(A);

  if (index == A.size()) {
    if (op == 0) {
      for (char c : {
             'A', 'T', 'G', 'C'
           }) {
        A.insert(index, 1, c);
        make_dfs(index + 1, op + 1);
        A.erase(index, 1);
      }
    }
    return;
  }

  char temp = A[index];
  A.erase(index, 1);
  make_dfs(index, op + 1);
  A.insert(index, 1, temp);

  for (char c : {
         'A', 'T', 'G', 'C'
       }) {
    A[index] = c;
    make_dfs(index + 1, op + 1);
    A[index] = temp;
  }

  for (char c : {
         'A', 'T', 'G', 'C'
       }) {
    A.insert(index, 1, c);
    make_dfs(index + 1, op + 1);
    A.erase(index, 1);
  }

  make_dfs(index + 1, op);
}

void make_check(int index, int op) {
  if (op > 1) return;

  if (s.count(B)) {
    cout << "Yes";
    exit(0);
  }

  if (index == B.size()) {
    if (op == 0) {
      for (char c : {
             'A', 'T', 'G', 'C'
           }) {
        B.insert(index, 1, c);
        make_check(index + 1, op + 1);
        B.erase(index, 1);
      }
    }
    return;
  }

  char temp = B[index];
  B.erase(index, 1);
  make_check(index, op + 1);
  B.insert(index, 1, temp);

  for (char c : {
         'A', 'T', 'G', 'C'
       }) {
    B[index] = c;
    make_check(index + 1, op + 1);
    B[index] = temp;
  }

  for (char c : {
         'A', 'T', 'G', 'C'
       }) {
    B.insert(index, 1, c);
    make_check(index + 1, op + 1);
    B.erase(index, 1);
  }

  make_check(index + 1, op);
}

int main() {
  cin.tie(0)->sync_with_stdio(0);

#if _debug == 1
  freopen("input.inp", "r", stdin);

#elif _debug == 2
  freopen("input.inp", "r", stdin);

#else
  freopen("adn.inp", "r", stdin);
  freopen("adn.out", "w", stdout);

#endif // _debug

  cin >> A >> B;

  make_dfs(0, 0);

#if _debug == 1
  for (const string& x : s) {
    debug(x);
  }


#endif // _debug

  make_check(0, 0);
  cout << "No";

}
