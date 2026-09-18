#include <bits/stdc++.h>
using namespace std;

const int maxn = 2e5 + 5;
long long prefx[maxn], prefy[maxn];
int n, q;

#define _debug 0

int main() {
    cin.tie(0)->sync_with_stdio(0);

    #if _debug == 1
    freopen("input.inp", "r", stdin);
    #else

    #endif // _debug

    cin >> n >> q;
    vector<long long> x, y;
    x.reserve(n);
    y.reserve(n);
    for (int i = 1; i <= n; i++) {
        long long a, b;
        cin >> a >> b;
        x.push_back(a);
        y.push_back(b);
    }
    sort(x.begin(), x.end());
    sort(y.begin(), y.end());

    for (int i = 1; i <= n; i++) {
        prefx[i] = prefx[i-1] + x[i-1];
        prefy[i] = prefy[i-1] + y[i-1];
    }

    while (q--) {
        long long a, b;
        cin >> a >> b;
        long long res = 0;
        int indexx = upper_bound(x.begin(), x.end(), a) - x.begin();
        res += (a * indexx - prefx[indexx]) + (prefx[n] - prefx[indexx] - a * (n - indexx));

        int indexy = upper_bound(y.begin(), y.end(), b) - y.begin();
        res += (b * indexy - prefy[indexy]) + (prefy[n] - prefy[indexy] - b * (n - indexy));

        cout << res << '\n';
    }

}
