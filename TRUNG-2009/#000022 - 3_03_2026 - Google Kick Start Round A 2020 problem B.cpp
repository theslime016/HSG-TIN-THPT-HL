#include <bits/stdc++.h>
using namespace std;

#ifdef __WIN32
    inline int getchar_unlocked() {return _getchar_nolock();}
    inline int putchar_unlocked(int c) {return _putchar_nolock(c);}
#endif

// int128 type
#ifdef __SIZEOF_INT128__
typedef __int128_t int128;
typedef __uint128_t uint128;

template<typename T>
istream& read_int(istream& is, T& val) {
    val = 0;
    int c;

    while ((c = is.get()) != EOF && isspace(c)) {}

    bool neg = false;
    if constexpr (is_signed_v<T>) {
        if (c == '-') {
            neg = true;
            c = is.get();
        }
    } else {
        if (c == '-') {
            is.setstate(ios::failbit);
            return is;
        }
    }

    if (c == '+') c = is.get();
    if (c == EOF || !isdigit(c)) {
        is.setstate(ios::failbit);
        return is;
    }

    while (c != EOF && isdigit(c)) {
        val = val*10 + (c - '0');
        c = is.get();
    }

    if (neg) val = -val;
    if (c != EOF) is.putback(c);

    return is;
}

istream& operator>>(istream& is, int128& val) {
    return read_int(is, val);
}

istream& operator>>(istream& is, uint128& val) {
    return read_int(is, val);
}

template<typename T>
ostream& print_uint(ostream& os, T val) {
    char buffer[40];
    int pos = 0;

    while (val > 0) {
        buffer[pos++] = val%10 + '0';
        val /= 10;
    }
    
    while (pos--) os << buffer[pos];
    return os;
}

ostream& operator<<(ostream& os, const int128& val) {
    if (val == 0) {
        os << '0';
        return os;
    }
    
    uint128 unsigned_val = val > 0 ? val : -(uint128)val;
    if (val < 0) os << '-';
    return print_uint(os, unsigned_val);
}

ostream& operator<<(ostream& os, const uint128& val) {
    if (val == 0) {
        os << '0';
        return os;
    }
    return print_uint(os, val);
}

#else
typedef long long int128;
typedef unsigned long long uint128;
#endif

// Eratosthenes
template<size_t N, typename T>
void sieve(T& is_prime) {
    is_prime[0] = is_prime[1] = false;
    for (size_t i = 2; i*i < N; i++) {
        if (!is_prime[i]) continue;
        for (size_t j = i*i; j < N; j+=i) {
            is_prime[j] = false;
        }
    }
}


int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cerr.tie(NULL);
    // freopen("input.inp", "r", stdin);
    // freopen("output.out", "w", stdout);
    // freopen("error.err", "w", stderr);
    
    int prefix[31], dp[1501];
    int T; cin >> T;
    for (int tc = 1; tc <= T; tc++) {
        memset(dp, -1, sizeof(dp));
        dp[0] = 0;

        int N, K, P; cin >> N >> K >> P;
        for (int i = 1; i <= N; i++) {
            memset(prefix, 0, sizeof(prefix));
            int stackVal = 0;

            for (int k = 1; k <= K; k++) {
                cin >> stackVal;
                prefix[k] = prefix[k-1] + stackVal;
            }

            for (int j = P; j >= 1; j--) {
                for (int x = 1; x <= K; x++) {
                    if (j-x >= 0) {
                        if (dp[j-x] != -1) {
                            dp[j] = max(dp[j], dp[j-x] + prefix[x]);
                        }
                    } else break;
                }
            }
        }

        cout << "Case #" << tc << ": " << dp[P] << '\n';
    }

    return 0;
}
