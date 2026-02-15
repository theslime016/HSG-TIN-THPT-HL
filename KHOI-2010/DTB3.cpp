#include <bits/stdc++.h>
using namespace std;
const long long MOD = 2004010501;
int main() {
    long long a, b, c, d, e, f, g, h, i;
    cin >> a >> b >> c;
    cin >> d >> e >> f;
    cin >> g >> h >> i;
    long long det = 0;
    det = (a*e%MOD*i%MOD + b*f%MOD*g%MOD 
        + c*d%MOD*h%MOD - a*f%MOD*h%MOD 
        - b*d%MOD*i%MOD - c*e%MOD*g%MOD) % MOD;
    if (det < 0) det += MOD;
    cout << det;
    return 0;
}