#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int MAXN=55,MAXK=15,MAXB=105,INF=-1e9;
ll n,k,b,l[4];vector<ll> adj[MAXN];
int a[MAXN][4][4][MAXK];
struct state{
    ll get,be,cnt[4],l_te;
    bool operator<(const state&s)const{
        if(get!=s.get) return get<s.get;
        if(be!=s.be) return be<s.be;
        for(ll i=0;i<4;i++) if(cnt[i]!=s.cnt[i]) return cnt[i]<s.cnt[i];
        return l_te<s.l_te;
    }
    bool dominates(const state&s)const{
        if(get>s.get) return false;
        if(be<s.be) return false;
        for(ll i=0;i<4;i++) if(cnt[i]>s.cnt[i]) return false;
        return true;
    }
};
vector<state> dp[MAXN];
void prune_states(vector<state>& st){
    if(st.empty()) return;
    const int MAX_STATES = 1000;
    if(st.size() > MAX_STATES){
        sort(st.begin(), st.end(), [](const state& a, const state& b){
            return a.be > b.be;
        });
        st.resize(MAX_STATES);
    }
    sort(st.begin(), st.end(), [](const state& a, const state& b){
        if(a.get != b.get) return a.get < b.get;
        return a.be > b.be;
    });
    
    vector<state> filtered;
    ll max_be = -1e18;
    ll max_cnt[4] = {0,0,0,0};
    
    for(const auto& s : st){
        bool dominated = false;
        if(s.be <= max_be){
            dominated = true;
            for(int i=0;i<4;i++){
                if(s.cnt[i] > max_cnt[i]){
                    dominated = false;
                    break;
                }
            }
        }
        
        if(!dominated){
            filtered.push_back(s);
            if(s.be > max_be){
                max_be = s.be;
                for(int i=0;i<4;i++) max_cnt[i] = s.cnt[i];
            }
        }
    }
    st = filtered;
}
void add(vector<state>& st, const state& new_s){
    if(!st.empty()){
        const state& last = st.back();
        if(last.get <= new_s.get && last.be >= new_s.be){
            bool dom = true;
            for(int i=0;i<4;i++) if(last.cnt[i] < new_s.cnt[i]) {dom=false;break;}
            if(dom) return;
        }
    }
    st.push_back(new_s);
    if(st.size() > 2000) prune_states(st); 
}
void dfs(ll u,ll parent){
    vector<state> node;
    for(ll s=0;s<4;s++){
        for(ll t=0;t<4;t++){
            ll best_k = 0, best_be = -1e18;
            for(ll k1=0;k1<=k;k1++){
                if(k1>b) break;
                ll bene = a[u][s][t][k1];
                if(bene > best_be){
                    best_be = bene;
                    best_k = k1;
                }
            }
            if(best_be < 0) continue;
            if(l[s] < 1) continue;
            state new_s;
            new_s.get = best_k;
            new_s.be = best_be;
            memset(new_s.cnt,0,sizeof(new_s.cnt));
            new_s.cnt[s] = 1;
            new_s.l_te = t;
            add(node, new_s);
        }
    }
    prune_states(node);
    vector<ll> chill;
    for(ll v:adj[u]) if(v!=parent){dfs(v,u);chill.push_back(v);}
    if(chill.empty()){dp[u] = node;return;}
    sort(chill.begin(), chill.end(), [&](ll a, ll b){return dp[a].size()<dp[b].size();});
    vector<state> cur = node;
    prune_states(cur);
    for(ll v:chill){
        vector<state> merge;
        if(cur.size() > 100 && dp[v].size() > 100){
            vector<state> best_cur = cur,best_v = dp[v];
            sort(best_cur.begin(), best_cur.end(), [](const state& a, const state& b){
                return a.be > b.be;
            });
            sort(best_v.begin(), best_v.end(), [](const state& a, const state& b){
                return a.be > b.be;
            });
            if(best_cur.size() > 50) best_cur.resize(50);
            if(best_v.size() > 50) best_v.resize(50);
            for(const state& st_u:best_cur){
                for(const auto& st_v:best_v){
                    if(st_u.l_te == st_v.l_te) continue;
                    ll total = st_u.get + st_v.get;
                    if(total > b) continue;
                    bool val = true;
                    ll to_cnt[4];
                    for(ll i=0;i<4;i++){
                        to_cnt[i] = st_u.cnt[i] + st_v.cnt[i];
                        if(to_cnt[i] > l[i]) {val=false; break;}
                    }
                    if(!val) continue;
                    state new_s;
                    new_s.get = total;
                    new_s.be = st_u.be + st_v.be;
                    memcpy(new_s.cnt, to_cnt, sizeof(to_cnt));
                    new_s.l_te = st_u.l_te;
                    add(merge, new_s);
                }
            }
        }else{
            for(const state& st_u:cur){
                for(const auto& st_v:dp[v]){
                    if(st_u.l_te == st_v.l_te) continue;
                    ll total = st_u.get + st_v.get;
                    if(total > b) continue;
                    bool val = true;
                    ll to_cnt[4];
                    for(ll i=0;i<4;i++){
                        to_cnt[i] = st_u.cnt[i] + st_v.cnt[i];
                        if(to_cnt[i] > l[i]) {val=false; break;}
                    }
                    if(!val) continue;
                    state new_s;
                    new_s.get = total;
                    new_s.be = st_u.be + st_v.be;
                    memcpy(new_s.cnt, to_cnt, sizeof(to_cnt));
                    new_s.l_te = st_u.l_te;
                    add(merge, new_s);
                }
            }
        }
        for(const auto& st_u:cur) add(merge, st_u);
        cur = merge;prune_states(cur);
    }
    dp[u] = cur;
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>n>>k>>b;
    for(int i=0;i<4;i++) cin>>l[i];
    for(ll i=0;i<n-1;i++){
        ll u,v;cin>>u>>v;u--;v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    for(ll u=0;u<n;u++) for(ll s=0;s<4;s++){
        for(ll t=0;t<4;t++) for(ll k1=0;k1<=k;k1++) cin>>a[u][s][t][k1];
    }
    dfs(0,-1);
    ll ans=0;
    for(const auto& s:dp[0]) ans=max(ans,s.be);
    cout<<ans<<'\n';
    return 0;
}
