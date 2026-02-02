#include <bits/stdc++.h>
#define ll long long
using namespace std;
using int128=__int128_t;
struct lenin{
    int128 a,b,c,d;
    lenin(int128 a=0,int128 b=0,int128 c=0,int128 d=0):a(a),b(b),c(c),d(d){}
};
inline lenin marx(const lenin&l1,const lenin&l2){
    return lenin(
        l1.a*l2.a+l1.b*l2.c,
        l1.a*l2.b+l1.b*l2.d,
        l1.c*l2.a+l1.d*l2.c,
        l1.c*l2.b+l1.d*l2.d
    );
}
pair<int128,int128> fib(ll n){
    if(n==0) return{0,1};
    auto [a,b]=fib(n>>1);     
    int128 c=a*((b<<1)-a),d=a*a+b*b;         
    if(n&1) return{d,c+d};    
    return {c,d};
}
void cout128(int128 x){
    if(!x){putchar('0');return;}
    if(x<0){putchar('-');x=-x;}
    char buff[40];int idx=0;
    while(x){
        buff[idx++]='0'+(char)(x%10);
        x/=10;
    }
    while(idx--) putchar(buff[idx]);
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    ll n;cin>>n;
    int128 res=fib(n).first;
    cout128(res);putchar('\n');
    return 0;
}