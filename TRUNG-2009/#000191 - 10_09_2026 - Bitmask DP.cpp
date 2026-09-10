#include <bits/stdc++.h>
using namespace std;

long long A[30][30];
long long dp[(1 << 20)];
#define popcount(x) __builtin_popcountll(x)

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n; cin >> n;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> A[i][j];
        }
    }

    memset(dp, -1, sizeof dp);
    dp[0] = 0;
    for (int mask = 0; mask < (1 << n); mask++) {
        if (dp[mask] == -1) continue;
        int p = popcount(mask)+1;
        if (p > n) continue;
        for (int pos = 0; pos < 20; pos++) {
            if (!((mask >> pos) & 1)) {
                int new_mask = mask | (1 << pos);
                dp[new_mask] = max(dp[new_mask], dp[mask] + A[p][pos+1]);
            }
        }
    }
    cout << dp[(1 << n) - 1];
}
