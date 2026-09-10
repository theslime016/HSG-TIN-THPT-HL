#include <bits/stdc++.h>
using namespace std;

int k;
long long dp[20][100][100][2]; // pos - val_mod - sum_mod - tight
long long dfs(int pos, int val_mod, int sum_mod, int tight, const string& S) {
    if (pos == S.size()) {
        return val_mod == 0 && sum_mod == 0;
    }

    if (dp[pos][val_mod][sum_mod][tight] != -1) return dp[pos][val_mod][sum_mod][tight];

    long long res = 0;
    int limit = tight ? S[pos] - '0' : 9;
    for (int num = 0; num <= limit; num++) {
        int new_tight = tight && (num == limit);
        res += dfs(pos+1, (val_mod * 10 + num) % k, (sum_mod + num) % k, new_tight, S);
    }

    return dp[pos][val_mod][sum_mod][tight] = res;
}

long long get_num(const long long& val) {
    if (val < 0) return 0;
    memset(dp, -1, sizeof dp);
    return dfs(0, 0, 0, 1, to_string(val));
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    freopen("input.inp", "r", stdin);

    long long l, r;
    cin >> l >> r >> k;
    cout << get_num(r) - get_num(l-1);
}
