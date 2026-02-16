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
    int k; cin >> k;
    while (k--) {
        int i = 0;
        while (i < (int)num.size() && num[i] < num[i+1]) i++;
        num.erase(i, 1);
    }

    // -0
    int start = 0;
    while (num[start] == '0' && start < (int)num.size()) {
        start++;
    }
    if (start == (int)num.size()) cout << '0';
    else cout << num.substr(start);
    
    return 0;
}
