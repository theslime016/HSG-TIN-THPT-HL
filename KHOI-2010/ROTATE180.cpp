#include <bits/stdc++.h>
using namespace std;
int main() {
    freopen("ROTATE180.INP", "r", stdin);
    freopen("ROTATE180.OUT", "w", stdout);
    int n;
    cin >> n;
    vector<vector<int>> a(n, vector<int>(n));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> a[i][j];

    for (int i = n - 1; i >= 0; i--) {
        for (int j = n - 1; j >= 0; j--) {
            cout << a[i][j] << " ";
        }
        cout << "\n";
    }
    return 0;
}