#include <bits/stdc++.h>
using namespace std;

long long dp[(1 << 16)];
long long A[(1 << 16)];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    freopen("input.inp", "r", stdin);

    int n;
    cin >> n;
    for (int i = 1; i < (1 << n); i++) {
        cin >> A[i];
        dp[i] = A[i];
    }

    for (int mask = 1; mask < (1 << n); mask++) {
        for (int sub = mask; sub > 0; sub = (sub - 1) & mask) {
            dp[mask] = max(dp[mask], dp[sub] + dp[mask ^ sub]);
        }
    }
    cout << dp[(1 << n) - 1];
}
