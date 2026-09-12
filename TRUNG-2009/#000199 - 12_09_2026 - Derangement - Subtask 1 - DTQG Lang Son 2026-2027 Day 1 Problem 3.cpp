#include <bits/stdc++.h>
using namespace std;

const int maxn = 60;
const int maxm = 15;
const long long mod = 1e9 + 7;
long long derange[maxn];
int gr[maxm];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    //freopen("input.inp", "r", stdin);
    freopen("ROTATION.INP", "r", stdin);
    freopen("ROTATION.OUT", "w", stdout);

    int n, m, s; cin >> n >> m >> s;
    for (int i = 1; i <= n; i++) {
        int gr_id;
        cin >> gr_id;
        gr[gr_id]++;
    }
    long long f = 1;
    for (int i = 1; i <= m; i++) {
        f = (f * gr[i]) % mod;
    }

    derange[1] = 0;
    derange[2] = 1;
    for (long long i = 3; i < maxn; i++) {
        derange[i] = (i - 1) * ((derange[i-1] + derange[i-2]) %mod) % mod;
    }

    cout << (f * derange[m]);
}
