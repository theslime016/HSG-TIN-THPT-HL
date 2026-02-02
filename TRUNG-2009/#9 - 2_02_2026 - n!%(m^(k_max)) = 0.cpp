#include <bits/stdc++.h>

// Cho hai so nguyen duong N va M (2 <= M <= N <= 10^9), tim so nguyen duong K lon nhat sao cho N! chia het cho M^K.
// Input: 6 6
// Output: 2

// Input: 2026 26
// Output: 166

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    // freopen("input.inp", "r", stdin);
    // freopen("output.out", "w", stdout);
    // freopen("error.err", "w", stderr);
    
    long long n, m; std::cin >> n >> m;
    long long k = LLONG_MAX;
    long long exponent_n = 0, exponent_m = 0;
    for (long long i = 2; i*i <= m; i++) {
        exponent_n = 0, exponent_m = 0;
        while (m%i == 0) {
            exponent_m++;
            m /= i;
        }
        if (exponent_m == 0) continue;
        long long temp_n = n;
        while (temp_n) {
            exponent_n += temp_n/i;
            temp_n /= i;
        }
        k = std::min(k, (long long)(exponent_n/exponent_m));
    }
    if (m > 1) {
        exponent_n = 0;
        long long temp_n = n;
        while (temp_n) {
            exponent_n += temp_n/m;
            temp_n /= m;
        }
        k = std::min(k, exponent_n);
    }
    std::cout << k;

    return 0;
}