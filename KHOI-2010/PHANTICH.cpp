#include <bits/stdc++.h>
using namespace std;
int main() {
    freopen("PHANTICH.INP", "r", stdin);
    freopen("PHANTICH.OUT", "w", stdout);
    long long x;
    int demChan = 0, demLe = 0;
    long long mn = LLONG_MAX, mx = LLONG_MIN;
    while (cin >> x) {
        if (x % 2 == 0) demChan++;
        else demLe++;
        mn = min(mn, x);
        mx = max(mx, x);
    }
    cout << demLe << " " << demChan << "\n";
    cout << mx << " " << mn;
    return 0;
}