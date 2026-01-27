#include <bits/stdc++.h>
using namespace std;
vector<bool> a(1000001,true);
void snt(){
    int limit = sqrt(1000000);
    a[0] = a[1] = false;
    for(int i = 2; i <= limit; i++){
        if(a[i]){
            for(int j = i*i; j <= 1000000; j+= i){
                a[j] = false;
            }
        }
    }
    return;
}
int demuoc(int n){
    int sum = 0;
    for(int i = 1; i*i <= n; i++){
        if(n%i == 0){
            sum++;
            if(i != n/i){
                sum++;
            }
        }
    }
    return sum;
}
string thuaso(int n){
    string s;
    string temp;
    int i = 2;
    while(n > 1){
        if(a[i]){
            if(n % i == 0){
                temp = to_string(i);
                s += temp;
                if(n/i > 1){
                    s.push_back('*');
                }
                n /= i;
            }
        }
        if(n % i != 0){
            i++;
        }
    };
    return s;
}
int main(){
    int n; cin >> n;
    snt();
    vector<int> s(n);

    for(int i = 0; i < n; i++){
        cin >> s[i];
    }
    for(auto x:s){
        cout << demuoc(x) << " ";
        string a = thuaso(x);
        cout << a << endl;
    }
    return 0;
}
