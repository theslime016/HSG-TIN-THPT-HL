#include <bits/stdc++.h>
using namespace std;
int main() {
    freopen("KITU.INP", "r", stdin);
    freopen("KITU.OUT", "w", stdout);
    string s;
    int k;
    cin >> s;
    cin >> k;
    stack<char> st;
    for (char c : s) {
        while (!st.empty() && k > 0 && st.top() > c) {
            st.pop();
            k--;
        }
        st.push(c);
    }
    while (k > 0 && !st.empty()) {
        st.pop();
        k--;
    }
    string res = "";
    while (!st.empty()) {
        res += st.top();
        st.pop();
    }
    reverse(res.begin(), res.end());
    int i = 0;
    while (i < res.size() && res[i] == '0') i++;
    res = res.substr(i);
    if (res == "") res = "0";
    cout << res;
    return 0;
}