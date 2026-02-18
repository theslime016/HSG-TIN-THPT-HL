#include <bits/stdc++.h>
using namespace std;
int main() {
    freopen("NENXAU.INP", "r", stdin);
    freopen("NENXAU.OUT", "w", stdout);
    string s;
    getline(cin, s);
    int n = s.size();
    for (int i = 0; i < n; ) {
        int cnt = 1;
        while (i + 1 < n && s[i] == s[i + 1]) {
            cnt++;
            i++;
        }
        cout << cnt << s[i];
        i++;
    }
    return 0;
}