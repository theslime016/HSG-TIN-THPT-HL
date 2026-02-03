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

long long a, b;
int inc[] = {4, 2, 4, 2, 4, 6, 2, 6};
bool is_prime(long long x) {
    if (x < 2) return false;
    if (x < 4) return true;
    if (x%3 == 0) return false;
    for (int d = 7, i = 0; d*d <= x; d+=inc[i]) {
        if (i == 8) i = 0;
        if (x%d == 0) return false;
    }
    return true;
}

std::vector<long long> result;
void backtrack(long long num) {
    if (num > b) return;
    if (num >= a && is_prime(num)) {
        result.push_back(num);
    }
    
    for (int i : {1, 3, 7, 9}) {
        backtrack(num*10+i);
    }
    return;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    // freopen("input.inp", "r", stdin);
    // freopen("output.out", "w", stdout);
    // freopen("error.err", "w", stderr);

    std::cin >> a >> b;
    for (int i : {2, 3, 5, 7}) {
        backtrack(i);
    }

    std::sort(result.begin(), result.end());

    for (long long n : result) std::cout << n << '\n';

    return 0;
}
