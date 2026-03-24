#include <bits/stdc++.h>
#define ll long long
using namespace std;
int main(){
    std::ios::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    freopen("TIEUTHU.INP", "r", stdin);
    freopen("TIEUTHU.OUT", "w", stdout);
    ll m, n, tb = 0, tkb = 0;
    cin >> m >> n;
    vector<pair<ll, ll>> th(m + 1);
    for (ll i = 1; i <= m; i++){
        ll tt = 0;
        for (ll j = 1; j <= n; j++){
            ll x;
            cin >> x;
            tt += x;
            if (i == 1 || i == m || j == 1 || j == n)
                tb += x;
            else
                tkb += x;
        }
        th[i].second = tt;
        th[i].first += i;
    }
    ll best = 0, mx = INT_MIN;
    for (ll i = 1; i <= m; i++){
        if (th[i].second > mx){
            mx = th[i].second;
            best = th[i].first;
        }
        else if (th[i].second == mx)
            best = min(best, th[i].first);
    }
    cout << best << '\n'
         << (tb > tkb ? "YES" : "NO");
    return 0;
}