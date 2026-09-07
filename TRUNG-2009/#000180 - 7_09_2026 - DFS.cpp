#include <bits/stdc++.h>
using namespace std;

int n, q;
const int maxn = 1e5+5;
vector<pair<int, long long>> adj[maxn];
struct edges {
    int a, b;
    long long val;
} A[maxn];

long long res = 0;
int task[maxn];
int query = 0;
bool dfs(int index = 1, int parent = 0) {
    int flag = 0;
    //cout << index << ' ' << parent << '\n';
    for (const auto& x : adj[index]) {
        if (x.first == parent) continue;

        if (dfs(x.first, index)) {
            flag = 1;
            res += x.second;
        }
    }
    return (task[index] == query) | flag;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    freopen("input.inp", "r", stdin);
    //freopen("output.out", "w", stdout);

    cin >> n >> q;
    for (int i = 1; i < n; i++) {
        int a, b;
        long long val;
        cin >> a >> b >> val;
        adj[a].push_back({b, val});
        adj[b].push_back({a, val});
        A[i].a = a;
        A[i].b = b;
        A[i].val = val;
    }

    for (int i = 1; i <= q; i++) {
        int type;
        cin >> type;
        if (type == 1) {
            int index;
            long long val;
            cin >> index >> val;
            A[index].val = val;
            for (auto& x : adj[A[index].a]) {
                if (x.first == A[index].b) {x.second = val; break;}
            }
            for (auto& x : adj[A[index].b]) {
                if (x.first == A[index].a) {x.second = val; break;}
            }
        } else if (type == 2) {
            res = 0;
            query++;

            int k;
            cin >> k;
            int index;
            for (int i = 1; i <= k; i++) {
                cin >> index;
                task[index] = query;
            }
            dfs(index, 0);
            cout << res << '\n';
        }
    }

}
