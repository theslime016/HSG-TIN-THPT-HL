#include <bits/stdc++.h>
using namespace std;
int main() {
    freopen("GAME.INP", "r", stdin);
    freopen("GAME.OUT", "w", stdout);
    int N;
    cin >> N;
    vector<long long> A(N);
    for (int i = 0; i < N; i++) cin >> A[i];

    if (N < 3) {
        cout << 0;
        return 0;
    }
    vector<long long> maxL(N), minR(N);
    maxL[0] = A[0];
    for (int i = 1; i < N; i++)
        maxL[i] = max(maxL[i - 1], A[i]);
    minR[N - 1] = A[N - 1];
    for (int i = N - 2; i >= 0; i--)
        minR[i] = min(minR[i + 1], A[i]);
    long long ans = 0;
    for (int j = 1; j <= N - 2; j++) {
        long long S = 2 * maxL[j - 1] - A[j] - minR[j + 1];
        if (S > ans) ans = S;
    }
    cout << ans;
    return 0;
}