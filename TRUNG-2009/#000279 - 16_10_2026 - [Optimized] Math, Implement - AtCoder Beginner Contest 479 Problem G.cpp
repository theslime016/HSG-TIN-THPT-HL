#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_map;

#ifdef __SIZEOF_INT128__
typedef __int128_t int128;

bool compare_fraction(long long a, long long b, long long c, long long d) {
  int128 c1 = (int128) a * d;
  int128 c2 = (int128) b * c;
  return c1 < c2;
}

#else
typedef long long int128;

bool compare_fraction(long long a, long long b, long long c, long long d) {
  if (b < 0) {
    a = -a, b = -b;
  }
  if (d < 0) {
    c = -c, d = -d;
  }

  if (a < 0 && c < 0) return compare_fraction(-c, d, -a, b);

  long long f1 = a/b;
  long long f2 = c/d;
  if (f1 != f2) return f1 < f2;

  long long r1 = a%b;
  long long r2 = c%d;

  if (r2 == 0) return false;
  if (r1 == 0) return true;

  return compare(d, r2, b, r1);
}

#endif // __SIZEOF_INT128__

struct FRACTION {
  long long up;
  long long down;

  FRACTION() = default;
  FRACTION(long long a, long long b) {
    if (b < 0) a = -a, b = -b;
    up = a;
    down = b;
  }

  friend bool operator<(const FRACTION& a, const FRACTION& b) {
    return compare_fraction(a.up, a.down, b.up, b.down);
  }
};

FRACTION calc(const vector<int>& A, const vector<int>& B) {
  vector<pair<FRACTION, long long>> point; // FRACTION - Weight/B[i]
  int n = A.size();
  point.reserve(n);

  long long total = 0;
  for (int i = 0; i < n; i++) {
    if (B[i] != 0) {
      total += abs(B[i]);
      point.push_back({FRACTION(A[i], B[i]), abs(B[i])});
    }
  }

  sort(point.begin(), point.end());
  long long cand_x = 0, cand_y = 1;
  long long current = 0;
  for (const auto& x : point) {
    current += x.second;
    if (current * 2LL >= total) {
      cand_x = x.first.up;
      cand_y = x.first.down;
      break;
    }
  }

  if (cand_y < 0) cand_x = -cand_x, cand_y = -cand_y;

  if (cand_x > cand_y) cand_x = cand_y = 1;
  if (cand_x < -cand_y) cand_x = -1, cand_y = 1;

  long long up_res = 0;
  long long down_res = cand_y;
  for (int i = 0; i < n; i++) {
    up_res += abs(A[i]*cand_y - B[i]*cand_x);
  }

  long long d = __gcd(up_res, down_res);
  return FRACTION(up_res/d, down_res/d);
}

#define _debug 0
int main() {
  cin.tie(0)->sync_with_stdio(0);

#if _debug == 1
  freopen("input.inp", "r", stdin);
#else

#endif // _debug

  int n;
  cin >> n;
  vector<int> A, B;
  A.reserve(n);
  B.reserve(n);
  for (int i = 1; i <= n; i++) {
    int x;
    cin >> x;
    A.push_back(x);
  }

  for (int i = 1; i <= n; i++) {
    int x;
    cin >> x;
    B.push_back(x);
  }

  FRACTION res1 = calc(A, B);
  FRACTION res2 = calc(B, A);
  FRACTION res = min(res1, res2);
  cout << res.up << ' ' << res.down;

}
