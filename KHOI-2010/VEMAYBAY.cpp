#include <bits/stdc++.h>
using namespace std;
int main() {
    freopen("VEMAYBAY.INP", "r", stdin);
    freopen("VEMAYBAY.OUT", "w", stdout);
    int m, n;
    cin >> m >> n;
    vector<vector<int>> a(m + 1, vector<int>(n + 1));
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> a[i][j];
        }
    }
    int Q;
    cin >> Q;
    while (Q--) {
        int r, c;
        cin >> r >> c;
        if (r < 1 || r > m || c < 1 || c > n) {
            cout << "Invalid position\n";
        } else if (a[r][c] == 0) {
            cout << "Available\n";
        } else {
            cout << "Not available\n";
        }
    }
    return 0;
}