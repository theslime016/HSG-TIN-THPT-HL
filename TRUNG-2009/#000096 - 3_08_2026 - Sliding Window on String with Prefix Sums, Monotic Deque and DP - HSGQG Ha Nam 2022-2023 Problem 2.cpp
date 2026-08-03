#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(false);

    freopen("SUMODD.INP", "r", stdin);
    freopen("SUMODD.OUT", "w", stdout);

    int n;
    cin >> n;
    vector<int> pref(n+1, 0);
    for (int i = 1; i <= n; i++) {
        char c;
        cin >> c;
        pref[i] = pref[i-1] + c - '0';
    }

    int current_min = 1e9;
    for (int i = 1; i <= n; i++) {
        vector<int> DP(n+1, 0);
        DP[0] = 0;
        deque<int> dq[2];
        dq[0].push_back(0);
        // deque DP - index
        for (int j = 1; j <= n; j++) {
            bool parity = pref[j]%2;
            while (!dq[parity].empty() && dq[parity].front() < j-i) dq[parity].pop_front();
            while (!dq[!parity].empty() && dq[!parity].front() < j-i) dq[!parity].pop_front();

            if (!dq[!parity].empty()) {
                DP[j] = DP[dq[!parity].front()]+1;
            }

            if (DP[j] > 0) {
                while (!dq[parity].empty() && DP[dq[parity].back()] >= DP[j]) dq[parity].pop_back();
                dq[parity].push_back(j);
            }
        }


        if (DP[n] > 0) {
            current_min = min(current_min, DP[n]);
            cout << current_min << ' ';
        } else if (current_min != 1e9) {
            cout << current_min << ' ';
        } else if (DP[n] == 0) {
            cout << -1 << ' ';
        }
    }



    return 0;
}
