#include <bits/stdc++.h>
using namespace std;
using str=string;
int main(){
    std::ios::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    // freopen("XAU.INP","r",stdin);
    // freopen("XAU.OUT","w",stdout);
    str s;getline(cin,s);int co=0;
    stringstream ss(s);str w,res;
    while(ss>>w){
        for(char c:w) if(isdigit(c)) co++;
        if(!w.empty()) w[0]=toupper(w[0]);
        res+=w+' ';
    }
    cout<<co<<'\n'<<res<<'\n';
    return 0;
}