#include <bits/stdc++.h>
using namespace std;
const long long MOD = 2004010501;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int Q;
    cin >> Q;
    long long S = 0;
    while (Q--) {
        char op;
        long long x;
        cin >> op >> x;
        if (op == '+') {
            S = (S + x) % MOD;
        } else {
            S = (S - x) % MOD;
        }
        if (S < 0) S += MOD;
    }
    cout << S;
    return 0;
}