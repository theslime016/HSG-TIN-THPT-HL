#include <bits/stdc++.h>
using namespace std;
int main() {
    freopen("XOAKT.INP", "r", stdin);
    freopen("XOAKT.OUT", "w", stdout);
    string s1, s2;
    getline(cin, s1);
    getline(cin, s2);
    for (char c : s1) {
        if (s2.find(c) == string::npos)
            cout << c;
    }
    return 0;
}
