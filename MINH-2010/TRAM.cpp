#include<bits/stdc++.h>
#define ll long long
using namespace std;
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    // freopen("TRAM.INP","r",stdin);
    // freopen("TRAM.OUT","w",stdout);
    ll n;cin>>n;vector<ll> a(n);
    for(ll&x:a) cin>>x;
    sort(a.begin(),a.end());
    ll ans=LLONG_MAX;
    for(int i=1;i<n;i++) ans=min(ans,a[i]-a[i-1]);
    cout<<ans<<'\n';
    return 0;
}