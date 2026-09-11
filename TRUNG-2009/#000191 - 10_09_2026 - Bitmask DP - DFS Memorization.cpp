#include <bits/stdc++.h>
using namespace std;

#define popcount(x) __builtin_popcountll(x)

const int mod = 100;
double dp[(1 << 20)];
double A[30][30];
int visited[(1 << 20)];
int n;

double make_dp(int mask) {
    if (mask == (1 << n) - 1) return 1.0;
    if (visited[mask]) return dp[mask];

    double res = 0;
    int p = popcount(mask) + 1;
    for (int pos = 0; pos < n; pos++) {
        if (!((mask >> pos) & 1)) {
            res = max(res, make_dp(mask | (1 << pos))*(A[p][pos+1]/100.0));
        }
    }
    visited[mask] = true;
    return dp[mask] = res;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    freopen("input.inp", "r", stdin);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> A[i][j];
        }
    }

    cout << fixed << setprecision(6) << make_dp(0)*100.0;
}
