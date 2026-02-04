#include <bits/stdc++.h>

// Cho mot so nguyen k (1 <= k <= 5000), tim so cach tach k thanh tong cac so nguyen to (co the trung nhau)
// Input: 11
// Output: 6

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    // freopen("input.inp", "r", stdin);
    // freopen("output.out", "w", stdout);
    // freopen("error.err", "w", stderr);

    long long k; std::cin >> k;
    if (k == 1) return std::cout << 0, 0;
    if (k <= 3) return std::cout << 1, 0;
    
    const long long mod = 1e9 + 7;
    
    std::vector<long long> dp(k+1, 0);
    std::vector<int> prime;
    std::bitset<5001> is_prime;
    is_prime.set();
    dp[0] = 1;
    for (int i = 2; i <= k; i++) {
        if (!is_prime[i]) continue;
        prime.push_back(i);
        for (int j = i*i; j <= k; j+=i) {
            is_prime[j] = false;
        }
    }

    for (int p : prime) {
        for (int i = p; i <= k; i++) {
            dp[i] = (dp[i] + dp[i-p])%mod;
        }
    }

    std::cout << dp[k];

    return 0;
}
