#include <bits/stdc++.h>
#define ll long long
using namespace std;
const ll INF=1e6;
vector<bool> nt(INF+5,true);
void sieve(){
    nt[0]=nt[1]=false;
    for(ll i=2;i*i<=INF;i++) if(nt[i]) for(ll j=i*i;j<=INF;j+=i) nt[j]=false;
}
int main(){
    std::ios::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);sieve();
    int t;cin>>t;ll tcp=0,cnt=0;
    while(t--){
        ll n;cin>>n;if(n<0){
            ll res=sqrt(n);
            if(res*res==n) tcp+=n;
            if(nt[n]) cnt++;
        }
    }
    cout<<cnt<<" "<<tcp<<"\n";
    return 0;
}