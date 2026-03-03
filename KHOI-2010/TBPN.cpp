#include <bits/stdc++.h>
using namespace std;
const long long MOD = 1e9 + 7;
const long long INV6 = 166666668;
int main() {
    long long n;
    cin >> n;
    n %= MOD;
    long long ans = n;
    ans = ans * ((n + 1) % MOD) % MOD;
    ans = ans * ((2 * n + 1) % MOD) % MOD;
    ans = ans * INV6 % MOD;
    cout << ans;
    return 0;
}