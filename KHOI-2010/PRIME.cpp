#include <bits/stdc++.h>
using namespace std;
bool isPrime(long long x) {
    if (x < 2) return false;
    if (x == 2 || x == 3) return true;
    if (x % 2 == 0) return false;
    for (long long i = 3; i * i <= x; i += 2)
        if (x % i == 0) return false;
    return true;
}
int main() {
    freopen("PRIME.INP", "r", stdin);
    freopen("PRIME.OUT", "w", stdout);
    string s;
    cin >> s;
    int n = s.size();
    long long ans = -1;
    for (int mask = 1; mask < (1 << n); mask++) {
        string t = "";
        for (int i = 0; i < n; i++)
            if (mask & (1 << i))
                t += s[i];
        if (t[0] == '0') continue;

        long long val = stoll(t);
        if (isPrime(val))
            ans = max(ans, val);
    }
    cout << ans;
    return 0;
}