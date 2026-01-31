#include <bits/stdc++.h>
#define ll long long
using namespace std;
const ll INF=1e6;
vector<ll> nt(INF+1);
void spf(){
    for(ll i=1;i<=INF;i++) nt[i]=i;
    for(ll i=2;i*i<=INF;i++){
        if(nt[i]==i){
            for(ll j=i*i;j<=INF;j+=i){
                if(nt[j]==j) nt[j]=i;
            }
        }
    }
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);spf();
    ll t;cin>>t;
    while(t--){
        ll m;cin>>m;ll tm=m;
        map<ll,ll> res;
        while(tm>1){
            res[nt[tm]]++;
            tm/=nt[tm];
        }
        ll n_d=1;
        for(auto&x:res) n_d*=(x.second+1);
        cout<<n_d<<" ";
        bool fi=true;
        for(auto&x:res){
            for(ll i=0;i<x.second;i++){
                if(!fi) cout<<"*";
                cout<<x.first;
                fi=false;
            }
        }
        cout<<'\n';
    }
    return 0;
}