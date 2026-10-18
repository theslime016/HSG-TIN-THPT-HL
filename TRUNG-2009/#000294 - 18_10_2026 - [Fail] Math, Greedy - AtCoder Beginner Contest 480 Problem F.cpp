#include <bits/stdc++.h>
using namespace std;

#define _debug 2

#if _debug == 1
#define debugl(x) cerr << (#x) << ':' << (x) << ' ';
#define debugr(x) cerr << (#x) << ':' << (x) << '\n';
#define new_line cerr << '\n';

#else
#define debugl(x)
#define debugr(x)
#define new_line

#endif // _debug

const int maxn = 30;
long long A[maxn];
long long B[maxn];

int main() {
  cin.tie(0)->sync_with_stdio(0);

#if _debug == 1
  freopen("input.inp", "r", stdin);

#elif _debug == 2
  freopen("input.inp", "r", stdin);
  freopen("output.out", "w", stdout);

#else

#endif // _debug

  long long n;
  long long m;
  cin >> n >> m;
  long long s = 0;
  for (int i = 1; i <= n; i++) {
    cin >> A[i];
    B[i] = A[i] * m;
    s += A[i];
  }

  sort(B + 1, B + max(n, m) + 1);
  for (int i = 1; i <= max(n, m); i++) debugl(B[i]);
  new_line;

  int ptr1 = 1;
  int ptr2 = max(n, m);
  long long op = 0;

  for (int i = 1; i <= m; i++) {
    long long current = 0;
    while (ptr1 <= max(n, m) && B[ptr1] + current <= s) current += B[ptr1], B[ptr1++] = 0;

    while (current < s) {
      long long need = min(B[ptr2] - s, s - current);
      B[ptr2] -= need;
      if (B[ptr2] == s) ptr2--;

      current += need;
      op++;
    }

    debugl(op);
    debugl(ptr1);
    debugl(ptr2);
    new_line;
    debugl(s);
#if _debug == 1
    for (int i = 1; i <= max(n, m); i++) debugl(B[i]);
#endif // _debug
    new_line;


  }

  cout << op;

}
