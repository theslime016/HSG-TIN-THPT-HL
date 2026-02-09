#include <bits/stdc++.h>
using namespace std;
int main() {
    freopen ("HOTEN.INP", "r", stdin);
    freopen ("HOTEN.INP", "w", stdout);
    string s;
    getline(cin, s);
    stringstream ss(s);
    string word;
    while (ss >> word) {
        cout << word << endl;
    }
    return 0;
}