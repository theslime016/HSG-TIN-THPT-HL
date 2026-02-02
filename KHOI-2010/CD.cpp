#include <bits/stdc++.h>
using namespace std;
int main() {
    freopen("CHIADOAN.INP", "r", stdin);
    freopen("CHIADOAN.OUT", "w", stdout);
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    int S = 0;
    for (int x : a) S += x;
    int ans = 1;
    int prefix = 0;
    for (int i = 0; i < n; i++) {
        prefix += a[i];
        if (S % prefix != 0) continue;
        int target = prefix;
        int cnt = 0, cur = 0;
        bool ok = true;
        for (int j = 0; j < n; j++) {
            cur += a[j];
            if (cur == target) {
                cnt++;
                cur = 0;
            } else if (cur > target) {
                ok = false;
                break;
            }
        }
        if (ok && cur == 0)
            ans = max(ans, cnt);
    }
    cout << ans;
    return 0;
}