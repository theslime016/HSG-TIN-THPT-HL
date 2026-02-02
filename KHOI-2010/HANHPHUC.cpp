#include <bits/stdc++.h>
using namespace std;
const long long MOD = 1e9 + 7;
const int MAXS = 700;
bool prime(int x) {
    if (x < 2) return false;
    for (int i = 2; i * i <= x; i++)
        if (x % i == 0) return false;
    return true;
}
vector<long long> mul(vector<long long> a, vector<long long> b) {
    vector<long long> c(MAXS, 0);
    for (int i = 0; i < MAXS; i++)
        if (a[i])
            for (int j = 0; j + i < MAXS; j++)
                c[i + j] = (c[i + j] + a[i] * b[j]) % MOD;
    return c;
}
int main() {
    freopen("HAPPY.INP", "r", stdin);
    freopen("HAPPY.OUT", "w", stdout);
    long long n;
    cin >> n;
    vector<vector<long long>> dp(60, vector<long long>(MAXS, 0));
    for (int i = 1; i <= 26; i++) dp[0][i] = 1;
    for (int k = 1; k < 60; k++)
        dp[k] = mul(dp[k - 1], dp[k - 1]);
    vector<long long> res(MAXS, 0);
    res[0] = 1;
    for (int k = 0; k < 60; k++)
        if (n & (1LL << k))
            res = mul(res, dp[k]);
    long long ans = 0;
    for (int s = 0; s < MAXS; s++)
        if (prime(s))
            ans = (ans + s * res[s]) % MOD;
    cout << ans;
}