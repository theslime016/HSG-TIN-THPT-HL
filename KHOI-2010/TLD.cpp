#include <bits/stdc++.h>
using namespace std;
int main() {
    long long a, b, c;
    cin >> a >> b >> c;
    long long result = 1;
    for (long long i = a; i <= b; i++) {
        result = (result * i) % c;
        if (result == 0) break;
    }
    cout << result;
    return 0;
}