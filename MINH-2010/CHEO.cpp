#include <bits/stdc++.h>
#define ll long long
using namespace std;
int main(){
    std::ios::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    ll n,tc=0,tb=0;cin>>n;vector<vector<ll>> a(n,vector<ll>(n));
    for(ll i=0;i<n;i++) for(ll j=0;j<n;j++) cin>>a[i][j];
    for(ll i=0;i<n;i++) for(ll j=0;j<n;j++){
        if(i==j) tc+=a[i][j];
        if(i==0||i==n-1||j==0||j==n-1) tb+=a[i][j];
    }
    cout<<tc<<'\n'<<tb<<'\n';
    return 0;
}