#include <bits/stdc++.h>

// Cho doan [a, b] (1 <= a <= b < 10^7), tim va in ra cac so sieu nguyen to o trong doan do
// Input: 3 57
// Output:
// 3
// 5
// 7
// 23
// 29
// 31
// 37
// 53

const int MAX = 10'000'000;
std::bitset<MAX> is_prime;

void sieve() {
    is_prime.set();
    is_prime[0] = is_prime[1] = 0;
    for (long long i = 2; i*i < MAX; i++) {
        if (!is_prime[i]) continue;
        for (long long k = i*i; k < MAX; k+=i) {
            is_prime[k] = 0;
        }
    }
}

bool check(long long num) {
    if (num < 2) return false;
    while (num) {
        if (!is_prime[num]) return false;
        num /= 10;
    }
    return true;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    // freopen("input.inp", "r", stdin);
    // freopen("output.out", "w", stdout);
    // freopen("error.err", "w", stderr);

    long long a, b; std::cin >> a >> b;
    sieve();
    while (a <= b) {
        if (check(a)) {
            std::cout << a << '\n';
        }
        a++;
    }

    return 0;
}
