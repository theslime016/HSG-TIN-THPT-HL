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

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cerr.tie(nullptr);
    // freopen("input.inp", "r", stdin);
    // freopen("output.out", "w", stdout);
    // freopen("error.err", "w", stderr);

    int n; std::cin >> n;
    while (n--) {
        std::string num;
        std::cin >> num;

        if (num.size() == 1) {
            std::cout << num << '\n';
            continue;
        }

        std::bitset<10> occur;
        std::string max_value = "0", current = "";
        for (int l = 0, r = 0; l < (int)num.size() && r < (int)num.size(); r++) {
            while (occur[num[r] - '0']) {
                occur[num[l] - '0'] = false;
                l++;
            }
            occur[num[r] - '0'] = true;
            if (r-l+1 < (int)max_value.size()) continue;
            current = num.substr(l, r-l+1);
            if (max_value.size() < current.size()) max_value = current;
            else if (max_value.size() == current.size()) max_value = std::max(max_value, current);
        }
        std::cout << max_value << '\n';
    }
    
    return 0;
}
