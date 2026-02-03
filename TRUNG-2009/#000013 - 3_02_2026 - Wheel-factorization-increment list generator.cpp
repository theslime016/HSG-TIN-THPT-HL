#include <bits/stdc++.h>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    // freopen("input.inp", "r", stdin);
    // freopen("output.out", "w", stdout);
    // freopen("error.err", "w", stderr);

    const int d[] = {2, 3, 5, 7};
    const int m = 2*3*5*7;
    std::vector<int> result;
    for (int i = 1; i <= m+1; i++) {
        bool found = true;
        for (int p : d) if (i%p == 0) found = false;
        if (found) result.push_back(i);
    }

    std::cout << "first: " << result[1] << '\n';
    for (int i = 1; i+1 < (int)result.size(); i++) std::cout << result[i+1] - result[i] << ',';

    return 0;
}
