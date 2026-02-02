#include <bits/stdc++.h>
using namespace std;
int main() {
    freopen("ASTRING.INP", "r", stdin);
    freopen("ASTRING.OUT", "w", stdout);
    int M, N;
    cin >> M >> N;
    string s1, s2;
    cin >> s1 >> s2;
    int i = 0, j = 0;
    while (i < M && j < N) {
        if (s1[i] == s2[j]) i++;
        j++;
    }
    if (i == M) cout << "Y";
    else cout << "N";
    return 0;
}