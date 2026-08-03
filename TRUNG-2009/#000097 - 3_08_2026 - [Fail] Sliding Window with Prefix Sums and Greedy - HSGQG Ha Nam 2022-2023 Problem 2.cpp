#include <bits/stdc++.h>
using namespace std;

#define debugr(x) cout << #x << " = " << (x) << '\n'
#define debugl(x) cerr << #x << " = " << (x) << '\n'

#define rebugr cout << '\n'
#define rebugl cerr << '\n'

int main() {
    cin.tie(0)->sync_with_stdio(false);

    freopen("SUMODD.INP", "r", stdin);
    freopen("SUMODD.OUT", "w", stdout);

    int n;
    cin >> n;
    vector<int> pref(n+1, 0);
    vector<vector<int>> last_occur(2, vector<int>(n+1));
    last_occur[0][0] = 0;
    for (int i = 1; i <= n; i++) {
        char c; cin >> c;
        pref[i] += pref[i-1] + c - '0';
        bool parity = pref[i]%2;
        last_occur[parity][i] = i;
        last_occur[!parity][i] = last_occur[!parity][i-1];
    }

    for (int m = 1; m <= n; m++) {
        int index = 0;
        bool parity = 0;
        int cost = 0;
        while (index < n) {
            int range = min(index + m, n);
            if (last_occur[!parity][range] <= index) {
                break;
            } else {
                cost++;
                index = last_occur[!parity][range];
                parity = !parity;
            }
        }

        if (index == n) cout << cost << ' ';
        else cout << -1 << ' ';

    }

    return 0;
}
