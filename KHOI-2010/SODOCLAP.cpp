#include <bits/stdc++.h>
using namespace std;
bool soDocLap(long long n) {
    bool used[10] = {false};
    while (n > 0) {
        int d = n % 10;
        if (used[d]) return false;
        used[d] = true;
        n /= 10;
    }
    return true;
}
int main() {
    freopen("SODOCLAP.INP", "r", stdin);
    freopen("SODOCLAP.OUT", "w", stdout);
    long long X;
    cin >> X;
    long long ans = X + 1;
    while (true) {
        if (soDocLap(ans)) {
            cout << ans;
            break;
        }
        ans++;
    }
    return 0;
}