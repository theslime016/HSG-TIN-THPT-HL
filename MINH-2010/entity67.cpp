#include <bits/stdc++.h>
#include <bitset>
#define ll long long
#define ld long double
using namespace std;
const int MAXN=5000,MAXB=MAXN,MX_PHASE=4;
const int MX_COLOUR=MX_PHASE,MX_LEVEL=8;
const int MOD=1e9+7;
const ll INF=1e18;
struct PhaseMask{
    array<bitset<MAXB+1>,1<<MX_PHASE> dp;
    PhaseMask(){
        for(int m=0;m<(1<<MX_PHASE);m++) dp[m].reset();
        dp[0].set(0);
    }
    void add(int mask,int cost){if(cost<=MAXB) dp[mask].set(cost);}
    PhaseMask merge(const PhaseMask&other) const{
        PhaseMask res;
        for(int m1=0;m1<(1<<MX_PHASE);m1++) for(int m2=0;m2<(1<<MX_PHASE);m2++){
            if(m1&m2) continue;
            int new_mask=m1|m2;
            auto shift=dp[m1];
            for(int c=0;c<=MAXB;c++) if(other.dp[m2][c]) res.dp[new_mask]|=(dp[m1]<<c);
        }
        return res;
    }
    vector<pair<int,ll>> get_best_val(const vector<ll>&val_by_cost){
        vector<pair<int,ll>> res;
        for(int m=0;m<(1<<MX_PHASE);m++) for(int c=0;c<=MAXB;c++) if(dp[m][c]&&val_by_cost[c]>0) res.emplace_back(c,val_by_cost[c]);
        return res;
    }
};
struct Point{
    ll cost,val;int colour,phase_mask;
    bool operator<(const Point&other) const{
        if(cost!=other.cost) return cost<other.cost;
        return val>other.val;
    }
};
class ConvexPareto{
    private:
        vector<Point>points;
        static bool is_redundant(const Point&a,const Point&b,const Point&c){
            return (__int128_t)(b.val - a.val) * (c.cost - b.cost)>=(__int128_t)(c.val - b.val) * (b.cost - a.cost);
        }
    public:
        void add_point(ll cost,ll val,int colour,int phase_mask){
            Point p={cost,val,colour,phase_mask};
            auto it=lower_bound(points.begin(),points.end(),p);
            if(it!=points.begin()){
                auto prev_it=prev(it);
                if(prev_it->val>=val) return;
            }
            while(it!=points.end()&&it->val<=val) it=points.erase(it);
            it=points.insert(it,p);
            if(it!=points.begin()&&next(it)!=points.end()){
                auto a=prev(it),b=it,c=next(it);
                if(is_redundant(*a,*b,*c)) points.erase(b);
            }
        }
        ll query_max_val(ll max_cost){
            int l=0,r=(int)points.size()-1;
            while(r-l>2){
                int m1=l+(r-l)/3;
                int m2=r-(r-l)/3;
                if(points[m1].val<points[m2].val) l=m1;
                else r=m2;
            }
            ll best=0;
            for(int i=l;i<=r;i++) if(points[i].cost<=max_cost){
                best=max(best,points[i].val);
            }
            return best;
        }
        const vector<Point>&get_points() const{return points;}
};
class TreeDP{
private:
    int N,B;
    vector<int> L;
    vector<array<array<array<ll,MX_LEVEL>,MX_COLOUR>,MX_PHASE>> val;
    vector<vector<int>> adj;
    vector<int> sz,h,pr,depth,head;
    void dfs_size(int u,int p){
        sz[u]=1;h[u]=-1;pr[u]=p;
        int mx_size=0;
        for(int v:adj[u]){
            if(v==p) continue;
            depth[v]=depth[u]+1;
            dfs_size(v,u);sz[u]+=sz[v];
            if(sz[v]>mx_size){mx_size=sz[v];h[u]=v;}
        }
    }
    vector<vector<ConvexPareto>> dp_by_colour;
    vector<int> phase_co;
    void add_node_to_dp(int u,int colour_u){
        for(int pha=0;pha<MX_PHASE;pha++){
            auto old_phase=phase_co;
            if(phase_co[pha]+1>L[pha]) continue;
            for(int level=0;level<MX_LEVEL;level++){
                ll value=val[u][pha][colour_u][level];
                if(value<=0) continue;
                int new_phase_mask=1<<pha;
                phase_co[pha]++;
                dp_by_colour[u][colour_u].add_point(level,value,colour_u,new_phase_mask);
                phase_co[pha]--;
            }
            phase_co=old_phase;
        }
    }
    void dfs_dsu(int u,int p,bool keep){
        for(int v:adj[u]){
            if(v==p||v==h[u]) continue;
            dfs_dsu(v,u,false);
        }
        if(h[u]!=-1){
            dfs_dsu(h[u],u,true);
            dp_by_colour[u]=move(dp_by_colour[h[u]]);
        }
        for(int c=0;c<MX_COLOUR;c++) add_node_to_dp(u,c);
        for(int v:adj[u]){
            if(v==p||v==h[u]) continue;
            for(int c1=0;c1<MX_COLOUR;c1++){
                for(int c2=0;c2<MX_COLOUR;c2++){
                    if(c1==c2&&c1!=-1) continue;
                    ConvexPareto merged;
                    for(const auto&p1:dp_by_colour[u][c1].get_points()) for(const auto&p2:dp_by_colour[v][c2].get_points()){
                        if(p1.cost+p2.cost>B) continue;
                        if(p1.phase_mask&p2.phase_mask) continue;
                        if(c1==c2&&c1!=-1)continue;
                        merged.add_point(
                            p1.cost+p2.cost,p1.val+p2.val,
                            p2.colour,p1.phase_mask|p2.phase_mask
                        );
                    }
                    dp_by_colour[u][c2]=move(merged);
                }
            }
        }
        if(!keep) for(int c=0;c<MX_COLOUR;c++) dp_by_colour[u][c]=ConvexPareto();
    }
public:
    TreeDP(int n,int b,vector<int> l,vector<array<array<array<ll,MX_LEVEL>,MX_COLOUR>,MX_PHASE>>v,vector<vector<int>>ad):N(n),B(b),L(l),val(v),adj(ad){
        sz.resize(N+1);
        h.resize(N+1);
        pr.resize(N+1);
        depth.resize(N+1);
        head.resize(N+1);
        dfs_size(1,0);
        dp_by_colour.resize(N+1,vector<ConvexPareto>(MX_COLOUR));
        phase_co.resize(MX_PHASE,0);
    }
    ll solve(){
        dfs_dsu(1,0,true);
        ll ans=0;
        for(int c=0;c<MX_COLOUR;c++) ans=max(ans,dp_by_colour[1][c].query_max_val(B));
        return ans;
    }
    array<ll,4> get_best_phase_vector(){
    array<ll,4> phase_enegy={0,0,0,0};
    ll best_val=-INF;
    const Point* best_point=nullptr;
    for(int c=0;c<MX_COLOUR;c++) for(const auto&p:dp_by_colour[1][c].get_points()){
        if(p.val>best_val){
            best_val=p.val;
            best_point=&p;
        }
    }
    if(best_point){
        int mask=best_point->phase_mask;
        int cnt=__builtin_popcount(mask);
        if(cnt>0) for(int pha=0;pha<MX_PHASE;pha++) if(mask>>pha&1) phase_enegy[pha]=best_val/cnt;
    }
    return phase_enegy;
}
};
class FastDinic{
private:
    struct Edge{int to,rev;ll cap;};
    vector<vector<Edge>> g;
    vector<int> level,iter;int n;
    bool bfs(int s,int t){
        fill(level.begin(),level.end(),-1);
        queue<int> q;
        level[s]=0;q.push(s);
        while(!q.empty()){
            int v=q.front();q.pop();
            for(const Edge&e:g[v]) if(e.cap>0&&level[e.to]<0){
                level[e.to]=level[v]+1;
                q.push(e.to);
            }
        }
        return level[t]>=0;
    }
    ll dfs(int v,int t,ll f){
        if(v==t) return f;
        for(int&i=iter[v];i<(int)g[v].size();i++){
            Edge&e=g[v][i];
            if(e.cap>0&&level[v]<level[e.to]){
                ll d=dfs(e.to,t,min(f,e.cap));
                if(d>0){
                    e.cap-=d;g[e.to][e.rev].cap+=d;
                    return d;
                }
            }
        }
        return 0;
    }
public:
    FastDinic(int size):n(size){g.resize(n);level.resize(n);iter.resize(n);}
    void add_edge(int from,int to,ll cap){
        g[from].push_back({to,(int)g[to].size(),cap});
        g[to].push_back({from,(int)g[to].size()-1,0});
    }
    ll max_flow(int s,int t){
        ll flow=0;
        while(bfs(s,t)){
            fill(iter.begin(),iter.end(),0);
            ll f;
            while((f=dfs(s,t,INF))>0) flow+=f;
        }
        return flow;
    }
};
struct Edge{int to;ll w;};
class GraphSolver{
private:
    int n,m;
    vector<vector<Edge>> g,gr;
    vector<int>order,comp,comp_id;
    vector<bool> visited;
    vector<ll> dist;
    int comp_cnt;bool has_neg_cycle_flag;
    void dfs1(int u){
        visited[u]=true;
        for(const auto&e:g[u]) if(!visited[e.to]) dfs1(e.to);
        order.push_back(u);
    }
    void dfs2(int u,int id){
        visited[u]=true;
        comp_id[u]=id;
        for(const auto&e:gr[u]) if(!visited[e.to]) dfs2(e.to,id);
    }
    bool has_neg_cycle_in_scc(const vector<int>&scc_nodes){
        int sz=scc_nodes.size();
        vector<ll> dist_scc(sz,0);
        unordered_map<int,int>idx;
        for(int i=0;i<sz;i++) idx[scc_nodes[i]]=i;
        for(int iter=0;iter<sz;iter++){
            bool update=false;
            for(int u:scc_nodes) for(const auto&e:g[u]){
                if(comp_id[e.to]!=comp_id[u]) continue;
                int iu=idx[u];
                int iv=idx[e.to];
                if(dist_scc[iv]>dist_scc[iu]+e.w){
                    dist_scc[iv]=dist_scc[iu]+e.w;
                    update=true;
                    if(iter==sz-1) return true;
                }
            }
            if(!update) break;
        }
        return false;
    }
public:
    GraphSolver(int nodes,int edges):n(nodes),m(edges){
        g.resize(n + 1);
        gr.resize(n + 1);
        visited.resize(n + 1);
        comp_id.resize(n + 1);
        dist.resize(n + 1);
        has_neg_cycle_flag=false;
    }
    void add_edge(int u,int v,ll w){
        g[u].push_back({v,w});
        gr[v].push_back({u,w});
    }
    void remove_edge(int u,int v,ll w){
        for(auto it = g[u].begin(); it != g[u].end(); ){
            if(it->to == v && it->w == w){
                it = g[u].erase(it);
                break;
            } else ++it;
        }
        for(auto it = gr[v].begin(); it != gr[v].end(); ){
            if(it->to == u && it->w == w){
                it = gr[v].erase(it);
                break;
            } else ++it;
        }
    }
    bool build_scc(){
        order.clear();
        fill(visited.begin(),visited.end(),false);
        for(int i=1;i<=n;i++) if(!visited[i]) dfs1(i);
        fill(visited.begin(),visited.end(),false);
        comp_cnt=0;
        reverse(order.begin(),order.end());
        for(int u:order) if(!visited[u]) dfs2(u,comp_cnt++);
        vector<vector<int>> scc_nodes(comp_cnt);
        for(int i=1;i<=n;i++)scc_nodes[comp_id[i]].push_back(i);
        for(int i = 0; i < comp_cnt; i++){
            if(scc_nodes[i].size()>=1&&has_neg_cycle_in_scc(scc_nodes[i])){has_neg_cycle_flag=true;return false;}
        }
        return true;
    }
    bool has_neg_cycle() const{return has_neg_cycle_flag;}
    vector<ll> compute_dist_from(int start){
        fill(dist.begin(), dist.end(), -INF);
        dist[start] = 0;
        vector<vector<pair<int, ll>>> dag(comp_cnt);
        vector<int> in_degree(comp_cnt, 0);
        for(int u = 1; u <= n; u++) {
            for(const auto& e : g[u]) {
                int cu = comp_id[u];
                int cv = comp_id[e.to];
                if(cu != cv) {
                    dag[cu].push_back({cv, e.w});
                    in_degree[cv]++;
                }
            }
        }
        queue<int> q;
        vector<ll> comp_dist(comp_cnt, -INF);
        comp_dist[comp_id[start]] = 0;
        for(int i = 0; i < comp_cnt; i++) if(in_degree[i] == 0) q.push(i);
        while(!q.empty()) {
            int u_comp = q.front(); q.pop();
            for(const auto& [v_comp, w] : dag[u_comp]) {
                if(comp_dist[v_comp] < comp_dist[u_comp] + w) comp_dist[v_comp]=comp_dist[u_comp]+w;
                if(--in_degree[v_comp] == 0) q.push(v_comp);
            }
        }
        for(int i = 1; i <= n; i++) dist[i]=comp_dist[comp_id[i]];
        
        return dist;
    }
};
struct Matrix{
    int a[4][4];
    Matrix(){memset(a,0,sizeof(a));}
    Matrix operator*(const Matrix&other)const{
        Matrix res;
        for(int i=0;i<4;i++) for(int k=0;k<4;k++){
            if(a[i][k]==0) continue;
            for(int j=0;j<4;j++) res.a[i][j]=(res.a[i][j]+(ll)a[i][k]*other.a[k][j])%MOD;
        }
        return res;
    }
    array<ll,4> apply(const array<ll,4>&vec)const{
        array<ll,4> res={0,0,0,0};
        for(int i=0;i<4;i++) for(int j=0;j<4;j++) res[i]=(res[i]+(ll)a[i][j]*vec[j])%MOD;
        return res;
    }
};
class MatrixSolver{
private:
    Matrix A;
    vector<Matrix> pow2;
public:
    MatrixSolver(const Matrix&mat):A(mat){
        pow2.push_back(A);
        for(int i=1;i<=60;i++) pow2.push_back(pow2[i-1]*pow2[i-1]);
    }
    Matrix power(ll T){
        Matrix res;
        for(int i=0;i<4;i++) res.a[i][i]=1;
        for(int i=0;T>0;i++,T>>=1) if(T&1) res=res*pow2[i];
        return res;
    }
    array<ll,4> apply_power(ll T,const array<ll,4>&vec){
        auto mat=power(T);
        return mat.apply(vec);
    }
};
class QuantumQueryHandler{
private:
    vector<array<array<array<ll,8>,4>,4>> val_history[MAXN+1];
    vector<bool> graph_valid_history[MAXN+1];
    vector<array<array<int,4>,4>> matrix_history[MAXN+1];
    vector<ll> T_history[MAXN+1];
    vector<vector<ll>> dist_history[MAXN+1];
    struct Key{int ver,u;ll T;};
    map<Key,ll> cache;
    int n;ll b;
    vector<int> L;
    vector<vector<int>> adj;
    int version_cnt=1;
public:
    QuantumQueryHandler(int _n, ll _b, vector<int> _L, vector<array<array<array<ll,8>,4>,4>> _val,vector<vector<int>> _adj): n(_n),b(_b),L(_L),adj(_adj){
        val_history[0]=_val;
    }
    void init_graph_matrix(bool valid,array<array<int,4>,4> mat,ll T,vector<ll> dist){
        graph_valid_history[0].push_back(valid);
        matrix_history[0].push_back(mat);
        T_history[0].push_back(T);
        dist_history[0].push_back(dist);
    }
    int update_val(int old,int u,int p,int c,int l,ll v){
        int nv=version_cnt++;
        val_history[nv]=val_history[old];
        graph_valid_history[nv]=graph_valid_history[old];
        matrix_history[nv]=matrix_history[old];
        T_history[nv]=T_history[old];
        dist_history[nv]=dist_history[old];
        val_history[nv][u][p][c][l]=v;
        return nv;
    }
    int update_graph(int old, bool valid, vector<ll> new_dist){
        int nv = version_cnt++;
        val_history[nv] = val_history[old];
        graph_valid_history[nv] = graph_valid_history[old];
        matrix_history[nv] = matrix_history[old];
        T_history[nv] = T_history[old];
        dist_history[nv] = dist_history[old];
        graph_valid_history[nv].clear();
        graph_valid_history[nv].push_back(valid);
        dist_history[nv].clear();
        dist_history[nv].push_back(new_dist);
        return nv;
    }
    int update_matrix(int old, array<array<int,4>,4> mat, ll T){
        int nv = version_cnt++;
        val_history[nv] = val_history[old];
        graph_valid_history[nv] = graph_valid_history[old];
        matrix_history[nv] = matrix_history[old];
        T_history[nv] = T_history[old];
        dist_history[nv] = dist_history[old];
        matrix_history[nv].clear();
        matrix_history[nv].push_back(mat);
        T_history[nv].clear();
        T_history[nv].push_back(T);
        return nv;
    }
    ll query(int ver, int u, ll Tadd){
        Key key = {ver, u, Tadd};
        auto it = cache.find(key);
        if(it != cache.end()) return it->second;
        if(ver >= version_cnt) return cache[key] = -1;
        if(graph_valid_history[ver].empty() || !graph_valid_history[ver][0]) 
            return cache[key] = -1;
        TreeDP tree(n, b, L, val_history[ver], adj);
        ll tree_val = tree.solve();
        auto phase = tree.get_best_phase_vector();
        Matrix A;
        if(!matrix_history[ver].empty()){
            auto& mat = matrix_history[ver][0];
            for(int i=0;i<4;i++) for(int j=0;j<4;j++) 
                A.a[i][j] = mat[i][j];
        }
        ll T_ver=T_history[ver].empty()?0:T_history[ver][0];
        MatrixSolver ms(A);
        auto fp=ms.apply_power(T_ver+Tadd,phase);
        ll msum = 0;
        for(int i=0;i<4;i++) msum=(msum+fp[i])%MOD;
        ll graph_val=0;
        if(!dist_history[ver].empty()&&u<dist_history[ver][0].size()) graph_val=dist_history[ver][0][u];
        ll res=tree_val+graph_val+msum;
        cache[key]=res;
        return res;
    }
};
static char stdinBuffer[(1<<22)+1];
static char* stdinBufPtr = stdinBuffer;
static char stdoutBuffer[(1<<22)+1];
static char* stdoutBufPtr = stdoutBuffer;
static char stderrBuffer[(1<<22)+1];
static char* stderrBufPtr = stderrBuffer;
inline char getchar_fast() {
    if(*stdinBufPtr == '\0') return EOF;
    return *stdinBufPtr++;
}
inline void putchar_fast(char c) {
    *stdoutBufPtr++ = c;
}
inline int read_int() {
    int x = 0, sign = 1;
    char c = getchar_fast();
    while(c < '0' || c > '9') {
        if(c == '-') sign = -1;
        c = getchar_fast();
    }
    while(c >= '0' && c <= '9') {
        x = x * 10 + (c - '0');
        c = getchar_fast();
    }
    return x * sign;
}
inline ll read_ll() {
    ll x = 0, sign = 1;
    char c = getchar_fast();
    while(c < '0' || c > '9') {
        if(c == '-') sign = -1;
        c = getchar_fast();
    }
    while(c >= '0' && c <= '9') {
        x = x * 10 + (c - '0');
        c = getchar_fast();
    }
    return x * sign;
}
inline void write_ll(ll x) {
    if(x < 0) {
        putchar_fast('-');
        x = -x;
    }
    char buf[20];
    int len = 0;
    do {
        buf[len++] = '0' + (x % 10);
        x /= 10;
    } while(x > 0);
    while(len--) {
        putchar_fast(buf[len]);
    }
    putchar_fast('\n');
}
int main(){
    std::ios::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);std::cout.tie(nullptr);
    size_t ByteRead=fread(stdinBuffer,1,sizeof(stdinBuffer),stdin);
    stdinBuffer[ByteRead]='\0';
    int n=read_int();ll b=read_ll();
    vector<int> L(4);
    for(int i=0;i<4;i++) L[i]=read_int();
    vector<array<array<array<ll,MX_LEVEL>,MX_COLOUR>,MX_PHASE>>val(n+1);
    for(int i=1;i<=n;i++) for(int p=0;p<4;p++) for(int c=0;c<4;c++) for(int l=0;l<8;l++) val[i][p][c][l]=read_ll();
    vector<vector<int>> adj(n+1);
    for(int i=1;i<n;i++){
        int u=read_int();
        int v=read_int();
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    int m=read_int();
    GraphSolver graph(n,m);
    for(int i=0;i<m;i++){
        int u=read_int(),v=read_int();ll w=read_ll();
        graph.add_edge(u,v,w);
    }
    Matrix A;
    for(int i=0;i<4;i++) for(int j=0;j<4;j++) A.a[i][j]=read_int();
    ll T=read_ll();
    if(!graph.build_scc()){
        write_ll(-1);
        fwrite(stdoutBuffer,1,stdoutBufPtr-stdoutBuffer,stdout);
        return 0;
    }
    vector<ll> dist=graph.compute_dist_from(1);
    QuantumQueryHandler qh(n,b,L,val,adj);
    array<array<int,4>,4> init_mt;
    for(int i=0;i<4;i++) for(int j=0;j<4;j++) init_mt[i][j]=A.a[i][j];
    qh.init_graph_matrix(true,init_mt,T,dist);
    int Q=read_int();
    int cur_ver=0;
    for(int i=0;i<Q;i++){
        int type=read_int();
        if(type==1){
            int u = read_int(), p = read_int(), c = read_int(), l = read_int();
            ll new_val = read_ll();
            cur_ver = qh.update_val(cur_ver, u, p, c, l, new_val);
        }
        else if(type==2){
            int u = read_int(), v = read_int(); 
            ll w = read_ll();
            int add = read_int();
            if(add) graph.add_edge(u,v,w);
            else graph.remove_edge(u,v,w);
            bool valid = graph.build_scc();
            vector<ll> new_dist = graph.compute_dist_from(1);
            cur_ver=qh.update_graph(cur_ver, valid, new_dist);
        }
        else if(type==3){
            array<array<int,4>,4> new_mat;
            for(int i=0;i<4;i++) for(int j=0;j<4;j++) new_mat[i][j] = read_int();
            ll new_T = read_ll();
            cur_ver=qh.update_matrix(cur_ver, new_mat, new_T);
        }
        else if(type==4){
            int ver = read_int(), u = read_int(); 
            ll Tq = read_ll();
            ll ans = qh.query(ver, u, Tq);
            write_ll(ans);
        }
    }
    fwrite(stdoutBuffer,1,stdoutBufPtr-stdoutBuffer,stdout);
    return 0;
}