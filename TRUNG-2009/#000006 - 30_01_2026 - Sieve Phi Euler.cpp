#include <bits/stdc++.h>

// Cho q query (1 <= q <=10^5), moi query 1 so trong khoang 1 -> 2^16 - 1
// Voi moi query in ra phi Euler cua so do

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    // freopen("input.inp", "r", stdin);
    // freopen("output.out", "w", stdout);
    // freopen("error.err", "w", stderr);

    static std::array<uint16_t, 65536> phi;
    phi[0] = 0;
    for (uint16_t i = 1; i <= 65536; i++) {
        phi[i] = i;
    }

    for (uint16_t i = 2; i <= 65536; i++) {
        if (phi[i] == i) {
            for (uint16_t j = i; j <= 65536; j+=i) {
                phi[j] -= phi[j]/i;
            }
        }
    }

    uint16_t x;
    while (std::cin >> x) {
        std::cout << "phi(" << x << ") = " << phi[x] << '\n';
    }

    return 0;
}