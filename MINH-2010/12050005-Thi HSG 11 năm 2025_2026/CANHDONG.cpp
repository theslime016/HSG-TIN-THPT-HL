#include <bits/stdc++.h>
#define ll long long
using namespace std;
int main(){
    std::ios::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    freopen("CANHDONG.INP", "r", stdin);
    freopen("CANHDONG.OUT", "w", stdout);
    ll m, n, t1 = 0;
    cin >> m >> n;
    vector<vector<ll>> a(m, vector<ll>(n)), b(m, vector<ll>(n));
    vector<pair<ll, ll>> dd(n);
    for (ll i = 0; i < m; i++)
        for (ll j = 0; j < n; j++){
            cin >> a[i][j];
            t1 += a[i][j];
        }
    cout << t1 << '\n';
    for (ll i = 0; i < m; i++)
        for (ll j = 0; j < n; j++){
            cin >> b[i][j];
            dd[j].first = (j + 1);
            if (b[i][j] >= 0)
                dd[j].second++;
        }
    ll best = 0, mx = INT_MIN;
    for (ll i = 0; i < n; i++){
        if (mx < dd[i].second){
            mx = dd[i].second;
            best = dd[i].first;
        }
        else if (mx == dd[i].second)
            best = min(best, dd[i].first);
    }
    cout << "\n"<< best;
    return 0;
}