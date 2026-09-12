#include <bits/stdc++.h>
using namespace std;

const int maxn = 60;
const int maxm = 15;
const long long mod = 1e9 + 7;
int n, m, s;

namespace sub1 {
long long derange[maxn];
int gr[maxm];
void solve() {
    for (int i = 1; i <= n; i++) {
        int gr_id;
        cin >> gr_id;
        gr[gr_id]++;
    }
    long long f = 1;
    for (int i = 1; i <= m; i++) {
        f = (f * gr[i]) % mod;
    }

    derange[1] = 0;
    derange[2] = 1;
    for (long long i = 3; i < maxn; i++) {
        derange[i] = (i - 1) * ((derange[i-1] + derange[i-2]) %mod) % mod;
    }

    cout << (f * derange[m]) % mod;
}
}

#define _DEBUG 0
namespace sub2 {
bool rep[maxn][maxn];
bool hate[maxn][maxn];
int gr[maxn];
vector<int> store[maxm];

long long res;
int selected[maxm];
int change[maxm];
void check() {
    iota(change+1, change+1+m, 1);
    do {
        bool derange = true;
        for (int i = 1; i <= m; i++) {
            if (change[i] == i) {
                derange = false;
                break;
            }
        }
        if (!derange) continue;

        bool can_go = true;
        for (int i = 1; i <= m; i++) {
            int a = selected[i];
            int b = selected[change[i]];
            // a -> b
            if (!rep[a][b]) {
                can_go = false;
                break;
            }
        }
        if (can_go) res = (res+1)%mod;
    } while (next_permutation(change + 1, change + m + 1));
}

void make_dfs(int gr_id) {
    if (gr_id > m) {
        check();
        return;
    }

    for (int x : store[gr_id]) {
        selected[gr_id] = x;
        make_dfs(gr_id+1);
        selected[gr_id] = 0;
    }
}

void solve() {
    for (int i = 1; i <= n; i++) {
        int gr_id;
        cin >> gr_id;
        gr[i] = gr_id;
        store[gr_id].push_back(i);
    }

    for (int i = 1; i <= s; i++) {
        int a, b;
        cin >> a >> b;
        hate[a][b] = true;
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            int gr_id = gr[j];
            int haters = 0;
            int total = store[gr_id].size()-1;
            for (int candidate : store[gr_id]) {
                if (candidate == j) continue;
                if (hate[candidate][i]) haters++;
            }
            if (haters <= total/2) rep[i][j] = true;
        }
    }

    make_dfs(1);
    cout << res;

    #if _DEBUG


    #endif
}
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    #if _DEBUG
    freopen("input.inp", "r", stdin);
    #else
    freopen("ROTATION.INP", "r", stdin);
    freopen("ROTATION.OUT", "w", stdout);
    #endif

    cin >> n >> m >> s;
    if (s == 0) sub1::solve();
    else sub2::solve();
}
