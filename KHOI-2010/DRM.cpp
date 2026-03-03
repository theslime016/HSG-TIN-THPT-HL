#include <bits/stdc++.h>
using namespace std;
int main() {
    int L, R, M;
    cin >> L >> R >> M;
    int ans = M;
    for (int i = L; i <= R; i++) {
        for (int j = i + 1; j <= R; j++) {
            int val = (i * j) % M;
            ans = min(ans, val);
            if (ans == 0) {
                cout << 0;
                return 0;
            }
        }
    }
    cout << ans;
    return 0;
}