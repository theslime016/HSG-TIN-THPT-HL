#include <bits/stdc++.h>
using namespace std;
int sumDigits(long long x) {
    int s = 0;
    while (x > 0) {
        s += x % 10;
        x /= 10;
    }
    return s;
}
int main() {
    int n;
    cin >> n;
    int cnt;
    for(int i = 1; i < n; i++) {
        long long x;
        cin >> x;
        if(x % 5 ==5 && sumDigits(x) % 5 == 0)
        cnt++;
    }
    cout << cnt;
}