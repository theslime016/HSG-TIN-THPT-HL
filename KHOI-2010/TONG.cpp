#include <bits/stdc++.h>
using namespace std;
int main() {
    freopen("TONG.INP", "r", stdin);
    freopen("TONG.OUT", "w", stdout);
    int m, n;
    cin >> m >> n;
    long long sum = 0;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            int x;
            cin >> x;
            sum += x;
        }
    }
    cout << sum;
    return 0;
}