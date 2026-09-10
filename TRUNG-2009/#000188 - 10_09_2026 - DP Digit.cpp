#include <bits/stdc++.h>
using namespace std;

long long power[10];
int visited[1500];
bitset<1500> check;

long long dp[20][1500][2];
long long dfs(int pos, int sum_sq, bool tight, const string& val) {
    if (pos == val.size()) {
        return check[sum_sq];
    }

    if (dp[pos][sum_sq][tight] != -1) return dp[pos][sum_sq][tight];

    long long res = 0;
    int limit = tight ? val[pos] - '0' : 9;
    for (int num = 0; num <= limit; num++) {
        int new_tight = tight && (num == limit);
        res += dfs(pos+1, sum_sq + power[num], new_tight, val);
    }
    return dp[pos][sum_sq][tight] = res;
}

long long get_loop(const long long &val) {
    if (val <= 0) return 0;
    memset(dp, -1, sizeof dp);
    return dfs(0, 0, true, to_string(val));
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    freopen("input.inp", "r", stdin);

    power[0] = 0;
    power[1] = 1;
    power[2] = 4;
    power[3] = 9;
    power[4] = 16;
    power[5] = 25;
    power[6] = 36;
    power[7] = 49;
    power[8] = 64;
    power[9] = 81;
    int cnt = 1;
    for (long long i = 1; i < 1500; i++, cnt++) {
        long long current = i;
        int flag = 1;
        long long next = 0;
        //vector<long long> trace;
        while (next != 1 && flag) {
            while (current > 0 && flag) {
                next += power[current%10];
                current /= 10;
            }
            //trace.push_back(next);
            if (next == 1) {
                /*
                cerr << i << ' ';
                for (const long long& x : trace) cerr << x << ' ';
                cerr << '\n';
                */
                break;
            } else if (visited[next] == cnt) {
                check[i] = true;
                /*
                cerr << i << '#';
                for (const long long& x : trace) cerr << x << ' ';
                cerr << '\n';
                */
                break;
            } else {
                visited[next] = cnt;
            }
            swap(next, current);
        }
    }

    int t; cin >> t;
    while (t--) {
        long long l, r; cin >> l >> r;
        cout << get_loop(r) - get_loop(l-1) << '\n';
    }
}
