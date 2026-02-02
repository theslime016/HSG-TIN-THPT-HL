#include <bits/stdc++.h>
#define ll long long
using namespace std;
using str=string;
bool ASCII(char c){return (c>='a'&&c<='z')||(c>='A'&&c<='Z');}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    freopen("DEMTU.INP","r",stdin);
    freopen("DEMTU.OUT","w",stdout);
    str s,w;getline(cin,s);
    ll n,res=0,co=0;cin>>n;stringstream ss(s);
    while(ss>>w){
        for(char c:w){
            if(ASCII(c)) co++;
        }
        if(co==n){res++;co=0;}
        else co=0;
    }
    cout<<res<<"\n";
}