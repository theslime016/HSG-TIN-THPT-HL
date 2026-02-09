#include <bits/stdc++.h>
using namespace std;
int main() {
    freopen("SOTU.INP", "r", stdin);
    freopen("SOTU.OUT", "w", stdout);
    string s, word;
    getline(cin, s);
    stringstream ss(s);
    map<string, int> dem;
    while (ss >> word) {
        dem[word]++;
    }
    for (auto x : dem) {
        cout << x.first << " " << x.second << endl;
    }
    return 0;
}