#include <bits/stdc++.h>
using namespace std;
int main() {
    long long a, b, c;
    cin >> a >> b >> c;
    cout << (a + b) % c << " ";
    long long sub = (a - b) % c;
    if (sub < 0) sub += c;
    cout << sub << " ";
    cout << (a % c * b % c) % c;
    return 0;
}