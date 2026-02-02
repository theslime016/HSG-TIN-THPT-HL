#include <bits/stdc++.h>

// Cho so nguyen duong A (A <= 10^9), tim so nguyen duong N nho nhat sao cho N^N chia het cho A
//Input: A
//Output: N

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    // freopen("input.inp", "r", stdin);
    // freopen("output.out", "w", stdout);
    // freopen("error.err", "w", stderr);

    long long x;
    std::cin >> x;

    std::vector<std::pair<int, int>> factor;
    long long radical = 1;
    int count = 0;
    for (int d : {2, 3, 5}) {
        count = 0;
        while (x%d == 0) { x /= d; count++; }

        if (count != 0) {
            factor.push_back({d, count});
            radical *= d;
        }
    }

    int increments[] = {4, 2, 4, 2, 4, 6, 2, 6};
    for (int d = 7, l = 0; d*d <= x; d += increments[l++]) {
        count = 0;
        if (l == 8) l = 0;
        while (x%d == 0) {
            x /= d;
            count++;
        }
        if (count != 0) {
            factor.push_back({d, count});
            radical *= d;
        }
    }
    if (x > 1) {
        factor.push_back({x, 1});
        radical *= x;
    }

    if (radical >= 30) {
        std::cout << radical;
        return 0;
    }

    for (int mul = 1; mul <= 30; mul++) {
        long long N = mul*radical;
        int new_mul = mul;
        bool ok = true;
        for (auto& pFactor : factor) {
            count = 0;
            while (new_mul%pFactor.first == 0) {
                new_mul /= pFactor.first;
                count++;
            }
            int v = (count > 0) ? (count+1) : 1;
            int a = pFactor.second;
            if (N*v < a) {
                ok = false;
                break;
            }
        }
        if (ok) {
            std::cout << N;
            return 0;
        }
    }

    return 0;
}