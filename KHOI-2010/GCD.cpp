#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    freopen("GCD.INP", "r", stdin);
    freopen("GCD.OUT", "w", stdout);
    int n;
    cin >> n;
    const int MAXA = 1000000;
    vector<int> cnt(MAXA + 1, 0);
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        cnt[x]++;
    }
    for (int d = MAXA; d >= 1; d--) {
        int dem = 0;
        for (int multiple = d; multiple <= MAXA; multiple += d) {
            dem += cnt[multiple];
            if (dem >= 2) {
                cout << d;
                return 0;
            }
        }
    }
    return 0;
}