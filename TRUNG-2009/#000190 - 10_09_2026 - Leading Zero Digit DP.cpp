#include <bits/stdc++.h>
using namespace std;

long long dp[20][2][2]; // pos - parity - tight
long long dfs(int pos, int parity, int tight, const string& s) {
    if (pos == (int)s.size()) {
        return 1;
    }

    if (dp[pos][parity][tight] != -1) return dp[pos][parity][tight];

    long long res = 0;
    int _start = !parity;
    int _end = tight ? s[pos] - '0' : 9;
    for (int num = _start; num <= _end; num+=2) {
        int new_tight = tight && (num == _end);
        res += dfs(pos+1, !parity, new_tight, s);
    }
    return dp[pos][parity][tight] = res;
}

long long get_num(const long long &val) {
    if (val <= 0) return 0;
    memset(dp, -1, sizeof dp);
    string s = to_string(val);
    long long n = s.size();
    long long res = 0;
    for (int len = 1; len < n; len++) {
        for (int num = 1; num <= 9; num += 2) {
            if (len == 1) res ++;
            else res += dfs(n - len + 1, 1, 0, s);
        }
    }

    int _end = s[0] - '0';
    for (int num = 1; num <= _end; num += 2) {
        res += dfs(1, 1, num == _end, s);
        if (n == 1) res++;
    }
    return res;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    freopen("input.inp", "r", stdin);

    long long l, r;
    cin >> l >> r;
    cout << get_num(r) - get_num(l-1);
}
