#include <bits/stdc++.h>
using namespace std;
int main() {
    freopen("SPNUM.INP", "r", stdin);
    freopen("SPNUM.OUT", "w", stdout);
    int n, k;
    cin >> n >> k;
    vector<bool> isPrime(n + 1, true);
    isPrime[0] = isPrime[1] = false;
    for (int i = 2; i * i <= n; i++) {
        if (isPrime[i]) {
            for (int j = i * i; j <= n; j += i)
                isPrime[j] = false;
        }
    }
    int ans = 0;
    for (int i = 2; i <= n; i++) {
        if (isPrime[i]) {
            if (__builtin_popcount(i) == k)
                ans++;
        }
    }
    cout << ans;
    return 0;
}