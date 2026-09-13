#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5 + 5;
const long long inf = 1e18;
long long W[maxn];
vector<int> adj[maxn];
long long dp[maxn][3];
void make_dp(int index, int parent) {
    dp[index][0] = W[index];
    dp[index][1] = inf;
    dp[index][2] = 0;
    long long sum_child = 0;
    long long mindiff = inf;
    for (int x : adj[index]) {
        if (x == parent) continue;
        make_dp(x, index);

        dp[index][0] += min({dp[x][0], dp[x][1], dp[x][2]});
        dp[index][2] += dp[x][1];

        sum_child += min(dp[x][0], dp[x][1]);
        mindiff = min(mindiff, dp[x][0] - min(dp[x][0], dp[x][1]));
    }

    dp[index][1] = sum_child + mindiff;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    freopen("input.inp", "r", stdin);

    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> W[i];
    }

    for (int i = 1; i < n; i++) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    make_dp(1, 0);
    cout << min(dp[1][0], dp[1][1]);
}
