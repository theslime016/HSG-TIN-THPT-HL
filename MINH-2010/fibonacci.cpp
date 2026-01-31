#include <bits/stdc++.h>
#define ll long long
using namespace std;
using ll128=__int128_t;
struct marx{
    ll128 a,b,c,d;
    marx(ll128 a=0,ll128 b=0,ll128 c=0,ll128 d=0):a(a),b(b),c(c),d(d){}
};
inline marx multi(const marx&m1,const marx&m2){
    return marx(
        m1.a*m2.a+m1.b*m2.c,
        m1.a*m2.b+m1.b*m2.d,
        m1.c*m2.a+m1.d*m2.c,
        m1.c*m2.b+m1.d*m2.d
    );
}
inline marx power(marx m,ll n){
    marx res(1,0,0,1);
    while(n>0){
        if(n&1) res=multi(res,m);
        m=multi(m,m);
        n>>=1;
    }
    return res;
}
inline ll128 fib(ll n){
    if(n==0) return 0;
    if(n==1||n==2) return 1;
    marx base(1,1,1,0);
    marx res=power(base,n-1);
    return res.a;
}
int main(){
    ll n;cin>>n;
    ll128 res=fib(n);
    if(res==0){cout<<"0";return 0;}
    if(res<0){cout<<"-";res=-res;}
    string s="";
    while(res>0){
        s+=char('0'+(res%10));res/=10;
    }
    reverse(s.begin(),s.end());
    cout<<s<<"\n";
    return 0;

}
