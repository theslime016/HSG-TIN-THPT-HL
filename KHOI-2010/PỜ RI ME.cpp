#include <bits/stdc++.h>
using namespace std;
const int MAXN = 5000000;
bool isPrime[MAXN + 1];
bool isFullPrime[MAXN + 1];
vector<int> fullPrimes;
bool checkFullPrime(int x) {
    while (x > 0) {
        if (!isPrime[x]) return false;
        x /= 10;
    }
    return true;
}
int main() {
    freopen("PRIME.INP", "r", stdin);
    freopen("PRIME.OUT", "w", stdout);
    int N;
    cin >> N;
    fill(isPrime, isPrime + N + 1, true);
    isPrime[0] = isPrime[1] = false;
    for (int i = 2; i * i <= N; i++) {
        if (isPrime[i]) {
            for (int j = i * i; j <= N; j += i)
                isPrime[j] = false;
        }
    }
    for (int i = 2; i <= N; i++) {
        if (checkFullPrime(i)) {
            isFullPrime[i] = true;
            fullPrimes.push_back(i);
        }
    }
    for (int i = 2; i <= N; i++) {
        bool ok = false;
        if (isFullPrime[i]) ok = true;
        else {
            for (int p : fullPrimes) {
                if (p >= i) break;
                if (isFullPrime[i - p] && p != i - p) {
                    ok = true;
                    break;
                }
            }
        }
        if (ok) cout << i << " ";
    }
    return 0;
}