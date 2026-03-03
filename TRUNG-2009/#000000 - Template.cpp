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

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cerr.tie(NULL);
    // freopen("input.inp", "r", stdin);
    // freopen("output.out", "w", stdout);
    // freopen("error.err", "w", stderr);

    

    return 0;
}
