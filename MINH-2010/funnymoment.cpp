#include <bits/stdc++.h>
#define ll long long
using namespace std;
const ll INF = 1e9,MAXN=55,MAXK=6,SEASONS=4;
struct fun{ll to,cap,cost,rev;};
ll dp[MAXN][SEASONS][1<<MAXK][MAXN];vector<fun> g[MAXN];
ll n,m,k,src[MAXK],dst[MAXK],de[MAXK],season[SEASONS]={1,2,3,2};
void dfs(ll u,ll pa,ll sea,ll mk,ll tl){
    if(tl<0) return;  
    if(tl==0){
        dp[u][sea][mk][tl]=(mk==0?0:INF);
        return;
    }
    if(dp[u][sea][mk][tl]!=-1) return;
    ll&res=dp[u][sea][mk][tl];res=INF;
    for(ll sub=mk;;sub=(sub-1)&mk){
        ll c_st=0;
        for(ll i=0;i<k;i++){
            if(sub&(1<<i)) c_st+=de[i]*season[sea]; 
        }
        ll nx_sea=(sea+1)%SEASONS;
        dfs(u,pa,nx_sea,mk^sub,tl-1);
        ll val=dp[u][nx_sea][mk^sub][tl-1];
        if(val<INF) res=min(res,c_st+val);  
        if(sub==0) break;
    }
    for(auto&e:g[u]){
        ll v=e.to;if(v==pa) continue;
        for(ll sub=mk;;sub=(sub-1)&mk){
            if(sub==0) continue;
            ll total_demand=0;
            for(ll i=0;i<k;i++){
                if(sub&(1<<i)) total_demand+=de[i];
            }
            if(total_demand>e.cap) continue;
            ll transport=total_demand*e.cost*season[sea];
            ll nx_sea=(sea+1)%SEASONS;
            dfs(v,u,nx_sea,mk^sub,tl-1);
            ll val=dp[v][nx_sea][mk^sub][tl-1];
            if(val<INF) res=min(res,transport+val);  
            if(sub==0) break;
        }
    }
    for(ll i=0;i<k;i++){
        if((mk&(1<<i))&&u==dst[i]){
            ll new_mk=mk^(1<<i);
            dfs(u,pa,sea,new_mk,tl);
            ll val=dp[u][sea][new_mk][tl];
            if(val<INF) res=min(res,val);
        }
    }
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    freopen("fun.inp","r",stdin);
    freopen("fun.out","w",stdout);
    cin>>n>>m>>k;
    if(k>6){cout<<"-1\n";return 0;}
    for(ll i=0;i<m;i++){
        ll u,v,cap,cost;cin>>u>>v>>cap>>cost;
        u--;v--;
        g[u].push_back({v,cap,cost,(ll)g[v].size()});
        g[v].push_back({u,0,-cost,(ll)g[u].size()-1});
    }
    for(ll i=0;i<k;i++){
        cin>>src[i]>>dst[i]>>de[i];
        src[i]--;dst[i]--;
    }
    memset(dp,-1,sizeof(dp));
    ll full=(1<<k)-1;
    ll max_t=min(2*n,20LL);
    ll ans=INF;
    for(ll st=0;st<n;st++){
        bool val_st=true;
        for(ll i=0;i<k;i++){
            if(st!=src[i]){val_st=false;break;}
        }
        if(!val_st) continue;
        vector<fun> backup[MAXN];
        for(ll i=0;i<n;i++) backup[i]=g[i];
        dfs(st,-1,0,full,max_t);
        ans=min(ans,dp[st][0][full][max_t]);
        for(ll i=0;i<n;i++) g[i]=backup[i];
    }
    if(ans>=INF) cout<<"-1\n";
    else cout<<ans<<'\n';
    return 0;

}
