#include <bits/stdc++.h>
using namespace std;

const int maxn = 4005;
const int maxedge = 4e5 + 5;
struct edge {
    int a, b;
    long long w;
} task[maxedge];
int n, m, q;

struct dsu {
    int n;
    vector<int> data;
    vector<int> bucket;
    long long res;
    dsu(int n) {
        this->n = n;
        res = 0;
        data.assign(n+1, 0);
        iota(data.begin(), data.end(), 0);
        bucket.assign(n+1, 1);
    }

    int fnd(int index) {
        if (index == data[index]) return index;
        return data[index] = fnd(data[index]);
    }

    bool compress(int a, int b, long long w) {
        a = fnd(a);
        b = fnd(b);
        if (a != b) {
            if (bucket[a] < bucket[b]) swap(a, b);
            bucket[a] += bucket[b];
            data[b] = a;
            res += w;
            return true;
        }
        return false;
    }
};

const int _log = 20;
vector<pair<int, long long>> adj[maxn];
int jump[maxn][_log];
long long dist[maxn][_log];
long long timein[maxn], timeout[maxn];
long long timer = 1;
void make_lca(int index, int parent, long long w) {
    jump[index][0] = parent;
    dist[index][0] = w;
    timein[index] = timer++;
    for (int exp = 1; exp < _log; exp++) {
        jump[index][exp] = jump[ jump[index][exp-1] ][exp-1];
        dist[index][exp] = max(dist[index][exp-1], dist[ jump[index][exp-1] ][exp-1] );
    }

    for (const auto& x : adj[index]) {
        if (x.first == parent) continue;
        make_lca(x.first, index, x.second);
    }
    timeout[index] = timer++;
}

bool is_lca(int a, int b) {
    return timein[a] <= timein[b] && timeout[a] >= timeout[b];
}

long long get_lca(int a, int b) {
    long long res = 0;
    for (int exp = _log - 1; exp >= 0; exp--) {
        if (jump[a][exp] && !is_lca(jump[a][exp], b)) {
            res = max(res, dist[a][exp]);
            a = jump[a][exp];
        }
    }

    for (int exp = _log - 1; exp >= 0; exp--) {
        if (jump[b][exp] && !is_lca(jump[b][exp], a)) {
            res = max(res, dist[b][exp]);
            b = jump[b][exp];
        }
    }

    if (is_lca(a, b)) return max(res, dist[b][0]);
    else if (is_lca(b, a)) return max(res, dist[a][0]);
    else return max({res, dist[a][0], dist[b][0]});
}

#define _debug 0

int main() {
    cin.tie(0)->sync_with_stdio(0);

    #if _debug == 1
    freopen("input.inp", "r", stdin);
    #else

    #endif // _debug

    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        cin >> task[i].a >> task[i].b >> task[i].w;
    }

    sort(task + 1, task + m + 1, [](const edge& x, const edge& y) {
        return x.w < y.w;
    });

    dsu uf(n);
    for (int i = 1; i <= m; i++) {
        if (uf.compress(task[i].a, task[i].b, task[i].w)) {
            adj[task[i].a].push_back({task[i].b, task[i].w});
            adj[task[i].b].push_back({task[i].a, task[i].w});
        }
    }

    make_lca(1, 0, 0);

    cin >> q;
    while (q--) {
        int a, b;
        cin >> a >> b;
        cout << uf.res - get_lca(a, b) << '\n';
    }
}
