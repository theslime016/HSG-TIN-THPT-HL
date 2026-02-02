#include <bits/stdc++.h>

// Cho array A gom N integer elements co dang: a1, a2, a3,..., aN (0 < a <= 10^6)
// Yeu cau:
// - In ra cac so hoan hao co trong day (cac so co tong uoc (khong tinh chinh no) bang voi chinh no: 6)
// - In ra cac so nguyen to tron (cac so nguyen to co tong cac chu so bang 10: 37)
// - In ra cac so sieu nguyen to (cac so nguyen to ma khi bo 1 so tuy y cac chu so ben phai thi phan con lai van la so nguyen to: 2393)

// Input:
// 6
// 2 6 19 37 73 2393

// Output:
// 6
// 19 37 73
// 2 37 73 2393

const int max_value = 1'000'000;
std::vector<bool> is_prime(max_value+1, true);
void sieve() {
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i*i <= max_value; i++) {
        if (!is_prime[i]) continue;
        for (int j = i*i; j <= max_value; j+=i) is_prime[j] = false;
    }
}

int sumDigit(int a) {
    int sum = 0;
    while (a) {
        sum += a%10;
        a /= 10;
    }
    return sum;
}


bool perfectNumber(const int& a) {
    int sum = 1;
    for (int i = 2; i*i < a; i++) {
        if (a%i == 0) {
            sum += i;
            if (i != a/i) sum += a/i;
        }
        if (sum > a) return false;
    }
    return sum == a;
}

bool roundPrimeNumber(const int& a) {
    if (!is_prime[a]) return false;
    if (sumDigit(a) != 10) return false;
    else return true;
}

bool superPrimeNumber(int a) {
    while (a) {
        if (!is_prime[a]) return false;
        a /= 10;
    }
    return true;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    freopen("input.inp", "r", stdin);
    freopen("output.out", "w", stdout);
    // freopen("error.err", "w", stderr);

    sieve();

    int n, A; std::cin >> n;
    std::vector<int> perfect, round, super;
    for (int i = 1; i <= n; i++) {
        std::cin >> A;
        if (perfectNumber(A)) perfect.push_back(A);
        if (roundPrimeNumber(A)) round.push_back(A);
        if (superPrimeNumber(A)) super.push_back(A);
    }

    for (const int x : perfect) std::cout << x << ' ';
    std::cout << '\n';
    for (const int x : round) std::cout << x << ' ';
    std::cout << '\n';
    for (const int x : super) std::cout << x << ' ';

    return 0;
}