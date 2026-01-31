#include <bits/stdc++.h>

// Đề bài: Cho array A có n element nguyên dương a, in ra A sau khi áp dụng permutation P (được biểu diễn dưới dạng array 0-index) k lần.
// Constraints: 1 <= n, a, k <= 1e6
// - Input:
// + Dòng 1: Số nguyên dương n, k
// + Dòng 2: n phần tử của A
// + Dòng 3: n phần tử của P
// - Output: n phần tử của A sau khi áp dụng P k lần

// - Input:
// 5 1000000
// 10 20 30 40 50
// 1 2 0 4 3
// - Output:
// 30 10 20 40 50

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    // freopen("input.inp", "r", stdin);
    // freopen("output.out", "w", stdout);
    // freopen("error.err", "w", stderr);

    int n, k; std::cin >> n >> k;
    std::vector<int> A(n), P(n);
    for (int i = 0; i < n; i++) std::cin >> A[i];
    for (int i = 0; i < n; i++) std::cin >> P[i];

    std::vector<int> result(n);
    std::vector<bool> visited(n, false);
    for (int i = 0; i < n; i++) {
        if (visited[i]) continue;
        std::vector<int> cycle;
        int current = i;
        while (!visited[current]) {
            visited[current] = true;
            cycle.push_back(current);
            current = P[current];
        }

        int L = cycle.size();
        int shift = k % L;

        for (int j = 0; j < L; j++) {
            int source_index = cycle[j];
            int target_index = cycle[(j+shift)%L];
            result[target_index] = A[source_index];
        }
    }

    for (const int& x : result) std::cout << x << ' ';

    return 0;
}