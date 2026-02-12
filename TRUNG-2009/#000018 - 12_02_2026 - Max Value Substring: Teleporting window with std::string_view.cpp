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
        std::string num; std::cin >> num;
        if (num.size() == 1) {
            std::cout << num << '\n';
            continue;
        }
        std::string_view max_value = "";
        std::string_view full = num;
        int occur[10]; memset(occur, -1, sizeof(occur));
        // std::fill_n(A, sizeof(A)/A[0], -1);
        for (int l = 0, r = 0; r < (int)num.size(); r++) {
            if (occur[num[r] - '0'] >= l) l = occur[num[r] - '0'] + 1;
            occur[num[r] - '0'] = r;

            if (r-l+1 < (int)max_value.size()) continue;

            std::string_view current = full.substr(l, r-l+1);
            
            if ((r-l+1 == (int)max_value.size() && current > max_value) ||
                r-l+1 > (int)max_value.size()) {
                max_value = current;
            }

        }
        std::cout << max_value << '\n';
    }


    return 0;
}
