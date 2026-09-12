#include <bits/stdc++.h>
using namespace std;

const int maxn = 60;
const int maxm = 15;
const long long mod = 1e9 + 7;
long long fact[maxn];
long long revfact[maxn];
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


    fact[0] = 1;
    for (long long i = 1; i < maxn; i++) {
        fact[i] = (fact[i-1] * i)%mod;
    }

    long long exp = 1e9 + 7 - 2;
    long long current = fact[maxn - 1];
    long long res = 1;
    while (exp > 0) {
        if (exp & 1) {
            res = (res * current) % mod;
        }
        current = (current * current) % mod;
        exp >>= 1;
    }

    revfact[maxn-1] = res;
    revfact[0] = 1;
    for (long long i = maxn - 2; i > 0; i--) {
        revfact[i] = (revfact[i+1] * (i+1)) % mod;
    }

    f = (f * (fact[m] - 1)) % mod;
    cout << f;
}
