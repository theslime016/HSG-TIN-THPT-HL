#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5 + 5;
int n;
long long req[maxn];
vector<int> adj[maxn];
int deg[maxn];

namespace subtask1 {
    void solve() {
        long long res = 0;
        for (int i = 1; i <= n; i++) {
            res = max(res, req[i]);
        }
        cout << res;
    }
}

namespace subtask2 {
    void solve() {
        int res = 0;
        for (int i = 1; i <= n; i++) {
            if (deg[i] == 1) res++;
        }
        cout << res/2;
    }
}

#define _debug 0
int main() {
    cin.tie(0)->sync_with_stdio(0);

    #if _debug == 1
    freopen("input.inp", "r", stdin);
    #else

    #endif // _debug

    cin >> n;
    int sub2 = 1;
    for (int i = 1; i <= n; i++) {
        cin >> req[i];
        if (req[i] != 1) sub2 = 0;
    }

    int sub1 = 1;
    long long mx = 0;
    for (int i = 1; i < n; i++) {
        int a, b; cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
        deg[a]++;
        deg[b]++;
        if (deg[a] > 2 || deg[b] > 2) sub1 = 0;
    }
    if (sub2) subtask2::solve();
    else subtask1::solve();
}
