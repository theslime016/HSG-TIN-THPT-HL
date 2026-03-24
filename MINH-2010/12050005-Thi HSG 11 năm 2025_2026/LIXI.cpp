#include <bits/stdc++.h>
#define ll long long
using namespace std;
const ll INF = 1e6;
ll tong(ll n){
    ll res = n % 10;
    n /= 10;
    while (n > 0)
    {
        res += n % 10;
        n /= 10;
    }
    return res;
}
int main(){
    std::ios::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    freopen("LIXI.INP", "r", stdin);
    freopen("LIXI.OUT", "w", stdout);
    ll n, mx = 0;
    cin >> n;
    vector<ll> a(n);
    for (ll &x : a){
        cin >> x;
        mx = max(mx, x);
    }
    for (ll x : a){
        if (x >= 0 && tong(x) == 10){
            cout << "YES";
            return 0;
        }
        else if (tong(-x) == 10){
            cout << "YES";
            return 0;
        }
    }
    cout << "NO";
    return 0;
}