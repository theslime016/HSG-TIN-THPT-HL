#include <bits/stdc++.h>
using namespace std;
int main() {
    freopen("MAXTU.INP", "r", stdin);
    freopen("MAXTU.OUT", "w", stdout);
    string s;
    getline(cin, s);
    int maxLen = 0, curLen = 0;
    for (char c : s) {
        if (isalpha(c)) {
            curLen++;
            maxLen = max(maxLen, curLen);
        } else {
            curLen = 0;
        }
    }
    cout << maxLen;
    return 0;
}