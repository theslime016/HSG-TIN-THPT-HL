#include <bits/stdc++.h>
#define ll long long
using namespace std;
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;ll k;cin>>n>>k;
    vector<int>a(n),p(n),res(n);
    for(ll i=0;i<n;i++){cin>>a[i];}
    for(ll i=0;i<n;i++){cin>>p[i];}
    vector<bool> visit(n,false);
    for(ll i=0;i<n;i++){
        if(visit[i]) continue;
        vector<int> cy;int cur=i;
        while(!visit[cur]){
            visit[cur]=true;
            cy.push_back(cur);
            cur=p[cur];
        }
        int l=cy.size();ll sh=k%l;
        for(int j=0;j<l;j++) res[cy[(j+sh)%l]]=a[cy[j]];
    }
    for(ll x:res) cout<<x<<" ";
    return 0;
}