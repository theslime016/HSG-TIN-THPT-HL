#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    freopen("TROCHOI.INP", "r", stdin);
    freopen("TROCHOI.OUT", "w", stdout);
    int n;
    cin >> n;
    vector<long long> A(n), B(n);
    for (int i = 0; i < n; i++) cin >> A[i];
    for (int i = 0; i < n; i++) cin >> B[i];
    sort(B.begin(), B.end());
    long long ans = LLONG_MAX;
    for (int i = 0; i < n; i++) {
        long long x = -A[i];
        auto it = lower_bound(B.begin(), B.end(), x);
        if (it != B.end())
            ans = min(ans, llabs(A[i] + *it));
        if (it != B.begin()) {
            --it;
            ans = min(ans, llabs(A[i] + *it));
        }
    }
    cout << ans;
    return 0;
}