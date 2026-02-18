#include <bits/stdc++.h>
using namespace std;
int main() {
    freopen("VIEC NHA.INP", "r", stdin);
    freopen("VIEC NHA.OUT", "w", stdout);
    long long T;
    int C;
    cin >> T;
    cin >> C;
    vector<long long> a(C);
    for (int i = 0; i < C; i++) {
        cin >> a[i];
    }
    sort(a.begin(), a.end());
    long long sum = 0;
    int cnt = 0;
    for (int i = 0; i < C; i++) {
        if (sum + a[i] <= T) {
            sum += a[i];
            cnt++;
        } else {
            break;
        }
    }
    cout << cnt;
    return 0;
}