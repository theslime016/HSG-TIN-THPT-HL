#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

typedef tree<int, long long, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_map;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

#define _debug 1

#if _debug == 1
#define debug(x) cerr << #x << ':' << (x) << ' ';
#define debugn(x) cerr << #x << ':' << (x) << '\n';
#define new_line cerr << '\n';

#else
#define debug(x)
#define debugn(x)
#define new_line

#endif // _debug

#define popcount(x) __builtin_popcountll(x)

/*
Vương quốc có N thành phố (1 <= N <= 18) và M con đường hai chiều nối giữa chúng.
Tại thành phố thứ i, có một rương báu chứa một số viên ngọc. Mỗi viên ngọc có một mã màu C (1 <= C <= 10^9).
Bạn cần chọn ra một *đường đi đơn* (đi qua một dãy các thành phố, không qua thành phố nào quá 1 lần, các thành phố liên tiếp phải có đường đi nối với nhau).
Tại mỗi thành phố đi qua, bạn sẽ gom tất cả ngọc vào túi. Hành trình được gọi là "Hoàn hảo" nếu trong túi của bạn, *tất cả các màu ngọc đều có số lượng là một số chẵn* (để bạn có thể ghép cặp đem bán).
Hãy tìm *số lượng thành phố nhiều nhất* bạn có thể đi qua trên một hành trình "Hoàn hảo".
======================================================================
INPUT:
* Dòng 1: N, M (N <= 18, M <= N(N - 1)/2).
* N dòng tiếp theo: Dòng thứ i bắt đầu bằng số K_i (số ngọc ở thành phố i), tiếp theo là K_i số nguyên mô tả mã màu của các viên ngọc.
* M dòng tiếp theo: Mỗi dòng u, v mô tả một con đường.

Input:
3 2
1 5
2 5 7
1 7
1 2
2 3
Output:
3

-------------------------
Input:
4 3
1 10
1 10
1 20
1 30
1 2
2 3
3 4
Output:
2
*/

const int maxmask = 1LL << 20;
const int maxnode = 20;
long long A[maxnode];
bool adj[maxnode][maxnode];
bool dp[maxmask][maxnode];

int main() {
  cin.tie(0)->sync_with_stdio(0);

#if _debug == 1
  freopen("input.inp", "r", stdin);
#else

#endif // _debug

  ordered_map color;

  int n, m;
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    int k;
    cin >> k;
    for (int j = 1; j <= k; j++) {
      long long c;
      cin >> c;
      if (!color[c]) color[c] = rng();
      A[i] ^= color[c];
    }
  }

  for (int i = 1; i <= m; i++) {
    int a, b;
    cin >> a >> b;
    adj[a][b] = 1;
    adj[b][a] = 1;
  }

  for (int node = 1; node <= n; node++) {
    int mask = 1 << (node - 1);
    dp[mask][node] = 1;
  }

  int res = 0;
  for (int mask = 1; mask < (1LL << n); mask++) {
    bool found = false;
    for (int node = 1; node <= n; node++) {
      if (!dp[mask][node]) continue;

      found = true;

      for (int nxt = 1; nxt <= n; nxt++) {
        int nxt_mask = mask | (1 << (nxt - 1));
        if ((nxt_mask ^ mask) != 0 && adj[node][nxt]) {
          dp[nxt_mask][nxt] = 1;
        }
      }

    }

    if (found) {
      long long current = 0;
      for (int node = 1; node <= n; node++) {
        if ((mask >> (node - 1)) & 1) {
          current ^= A[node];
        }
      }

      if (current == 0) res = max(res, popcount(mask));
      debug(mask);
      debugn(current);
    }

  }

  cout << res;

}
