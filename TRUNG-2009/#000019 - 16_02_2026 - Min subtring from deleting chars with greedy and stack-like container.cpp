#include <bits/stdc++.h>
using namespace std;

// Cho string S ký tự chữ số có độ dài 0 < n <= 10^6. Xóa đi k ký tự (0 < k < n) để có số bé nhất
// Input:
// 65278934
// 3

// Output:
// 27834

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cerr.tie(0);
    // freopen("input.inp", "r", stdin);    
    // freopen("output.out", "w", stdout);
    // freopen("error.err", "w", stderr);

    string num; cin >> num;
    string current;
    int k; cin >> k;
    for (char c : num) {
        while (k > 0 && current.size() > 0 && current.back() > c) {
            current.pop_back();
            k--;
        }
        current.push_back(c);
    }

    // k remain
    while (k > 0) {
        current.pop_back();
        k--;
    }

    // -0
    int start = 0;
    while (current[start] == '0' && start < (int)current.size()) {
        start++;
    }
    if (start == (int)current.size()) cout << '0';
    else cout << current.substr(start);
    
    return 0;
}
