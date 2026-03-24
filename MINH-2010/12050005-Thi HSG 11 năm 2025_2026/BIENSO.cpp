#include <bits/stdc++.h>
#define ll long long
using namespace std;
using str = string;
int main(){
    std::ios::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    freopen("BIENSO.INP", "r", stdin);
    freopen("BIENSO.OUT", "w", stdout);
    ll n, co = 0, co68 = 0;
    cin >> n;
    while (n--){
        str s;
        cin >> s;
        ll sum = 0, b = s.length();
        bool hople = true;
        if (b < 8 || b > 8)
            hople = false;
        for (ll i = 0; i < b; i++){
            if (i != 2 && !(s[i] >= '0' && s[i] <= '9')){
                hople = false;
                break;
            }
            else if (i == 2 && !(s[i] >= 'A' && s[i] <= 'Z')){
                hople = false;
                break;
            }
            if (i >= 3 && i <= 8)
                sum += s[i] - '0';
        }
        if (hople){
            co++;
            if (sum % 6 == 0 || sum % 8 == 0)
                co68++;
        }
    }
    cout << co << '\n'
         << co68;
    return 0;
}