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

bool palindrome(const long long& x) {
    long long rev = 0, copy = x;
    while (copy) {
        rev = rev*10 + copy%10;
        copy /= 10;
    }
    if (rev == x) return true;
    else return false;
}

bool factor(long long x) {
    if (x%2 == 0 && x%3 == 0 && x%5 == 0) return true;
    int count = 0;
    for (int d : {2, 3, 5}) {
        if (x%d == 0) {
            count++;
            while (x%d == 0) x /= d;
        }
    }
    
    static int inc[] = {4, 2, 4, 2, 4, 6, 2, 6};
    for (long long d = 7, i = 0; d*d <= x; d+=inc[i], i = (i+1)%8) {
        if (x%d == 0) {
            count++;
            while (x%d == 0) x /= d;
        }
        if (count >= 3) return true;    
    }
    if (x > 1) count++;
    if (count >= 3) return true;
    else return false;
}

// Cho 0 < a < b < 1e7 với a và b nguyên dương, tìm trong đoạn [a, b] số lượng số thỏa mãn các điều kiện sau:
// 1. Là số đối xứng: 66, 212,...
// 2. Có từ 3 ước số nguyên tố trở lên: 282 có các ước nguyên tố là 2, 3, 47

// Input: 71 9623340
// Output: 7104

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cerr.tie(NULL);
    // freopen("input.inp", "r", stdin);
    // freopen("output.out", "w", stdout);
    // freopen("error.err", "w", stderr);
    
    long long start, end; cin >> start >> end;
    int result = 0;
    for (long long num = start; num <= end; num++) {
        if (palindrome(num) && factor(num)) result++;
    }

    cout << result;

    return 0;
}
