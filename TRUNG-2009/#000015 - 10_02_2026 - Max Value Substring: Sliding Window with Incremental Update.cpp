#include <bits/stdc++.h>

// Tim substring a trong string int m sao cho a = max va cac digit khong xuat hien qua 1 lan.
// Input:
// 7
// 2
// 12345
// 1223
// 333333
// 623345
// 223456567896
// 1234567890

// Output:
// 2
// 12345
// 23
// 3
// 623
// 56789
// 1234567890

unsigned long long pow10[20];
void init() {
    pow10[0] = 1;
    for (int i = 1; i < 19; i++) {
        pow10[i] = pow10[i-1]*10;
    }
    return;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cerr.tie(nullptr);
    // freopen("input.inp", "r", stdin);
    // freopen("output.out", "w", stdout);
    // freopen("error.err", "w", stderr);

    int n; std::cin >> n;
    init();
    while (n--) {
        std::string num;
        std::cin >> num;

        if (num.size() == 1) {
            std::cout << num << '\n';
            continue;
        }

        std::bitset<10> occur;
        unsigned long long literal = 0, result = 0;
        for (int l = 0, r = 0; l < (int)num.size() && r < (int)num.size(); r++) {
            while (occur[num[r] - '0']) {
                literal -= (num[l] - '0')*pow10[r-l-1];
                occur[num[l] - '0'] = false;
                l++;
            }
            literal = literal * 10 + (num[r] - '0');
            occur[num[r] - '0'] = true;
            result = std::max(result, literal);
        }

        std::cout << result << '\n';
    }
    
    return 0;
}
