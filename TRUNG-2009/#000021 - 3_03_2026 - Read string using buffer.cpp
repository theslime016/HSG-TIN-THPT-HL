#include <bits/stdc++.h>
using namespace std;

#ifdef __SIZEOF_INT128__
typedef __int128_t int128;
typedef __uint128_t uint128;

istream& operator>>(istream& is, int128& val) {
    val = 0;
    int c;
    while ((c = is.get()) && isspace(c)) {}

    bool neg = false;
    if (c == '-') {
        neg = true;
        c = is.get();
    }

    while (c != EOF && isdigit(c)) {
        val = val*10 + (c - '0');
        c = is.get();
    }

    if (neg == true) val = -val;
    if (c != EOF) is.putback(c);

    return is;
}

ostream& operator<<(ostream& os, int128& val) {
    if (val == 0) {
        os << '0';
        return os;
    }
    
    uint128 unsigned_val = val > 0 ? val : -(uint128)val;
    char buffer[40];
    int pos = 0;

    while (unsigned_val > 0) {
        buffer[pos++] = unsigned_val%10 + '0';
        unsigned_val /= 10;
    }
    
    if (val < 0) os << '-';
    while (pos--) os << buffer[pos];
    
    return os;
}

#else
typedef __int128_t long long;
typedef __uint128_t unsigned long long;
#endif

// Input: 1 string duy nhất chỉ chứa các chữ cái Latinh viết thường (a -> z) và chữ số (0 -> 9): a12b3c

// Output:
// - Dòng 1: In ra tổng số chữ số: 6
// - Dòng 2: IN ra string đảo ngược (nếu không có in ra -1): cba

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cerr.tie(NULL);
    // freopen("input.inp", "r", stdin);
    // freopen("output.out", "w", stdout);
    // freopen("error.err", "w", stderr);

    char c;
    int sum = 0;
    char str[1'000'00]; int pos = 0;
    while ((c = getchar()) != EOF) {
        if (isdigit(c)) {
            sum += (c - '0');
        } else {
            str[pos++] = c;
        }
    }

    cout << sum << '\n';

    if (pos == 0) cout << -1;
    else while (pos--) cout << str[pos];

    return 0;
}
