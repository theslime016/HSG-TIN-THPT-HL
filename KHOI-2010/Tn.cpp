#include <bits/stdc++.h>
using namespace std;
const long long MOD = 1e9 + 7;
const long long inv2 = 500000004;
int main() {
    long long n;
    cin >> n;
    n %= MOD;
    long long ans = n * ((n + 1) % MOD) % MOD;
    ans = ans * inv2 % MOD;
    cout << ans;
    return 0;
}