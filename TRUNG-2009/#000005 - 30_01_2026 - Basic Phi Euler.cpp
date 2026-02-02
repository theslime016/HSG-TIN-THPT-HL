#include <bits/stdc++.h>

// Tinh phi Euler cua 1 so nguyen duong tu 1 -> 2^31 - 1

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    // freopen("input.inp", "r", stdin);
    // freopen("output.out", "w", stdout);
    // freopen("error.err", "w", stderr);

    long long n; std::cin >> n;
    long long result = n;
    for (long long i = 2; i*i <= n; i++) {
        if (n%i == 0) {
            result -= result/i;
            while (n%i == 0) n /= i;
        }
    }
    if (n > 1) result -= result/n;
    std::cout << result;

    
    return 0;
}