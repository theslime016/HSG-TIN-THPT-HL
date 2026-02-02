#include <bits/stdc++.h>
using namespace std;
int main() {
    freopen("BALLOON.INP", "r", stdin);
    freopen("BALLOON.OUT", "w", stdout);
    int n;
    long long S;
    cin >> n >> S;
    vector<long long> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    sort(a.begin(), a.end());
    int l = 0, r = n - 1;
    int ans = 0;
    while (l < r) {
        long long sum = a[l] + a[r];
        if (sum == S) {
            ans++;
            l++;
            r--;
        } else if (sum < S) {
            l++;
        } else {
            r--;
        }
    }
    cout << ans;
    return 0;
}