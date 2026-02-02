#include <bits/stdc++.h>
#include <windows.h>
#define ll long long
using namespace std;
using str=string;
vector<ll> snt;ll a,b;
bool isnt(ll n){
    if(n<2) return false;
    if(n==2||n==3) return true;
    if(n%2==0||n%3==0) return false;
    for(ll i=5;i*i<=n;i+=6){
        if(n%i==0||n%(i+2)==0) return false;
    }
    return true;
}
void back(ll cur){
    if(cur>b) return;
    if(cur>=a&&cur<=b)snt.push_back(cur);
    ll di[]={1,3,7,9};
    for(ll d:di){
        ll nx=cur*10+d;
        if(nx<=b&&isnt(nx)) back(nx);
    }
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    SetConsoleOutputCP(65001);
    // freopen("SPRIME.INP","r",stdin);
    // freopen("SPRIME.OUT","w",stdout);
    cin>>a>>b;
    ll s[]={2,3,5,7};
    for(ll si:s){
        if(si<=b&&isnt(si)) back(si);
    }
    sort(snt.begin(),snt.end());
    if(snt.empty()) cout<<"NO";
    else{
        for(ll sp:snt) cout<<sp<<"\n";
    }
    return 0;
}