#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e6 + 5;
vector<int> adj[maxn];
char color[maxn];

int active;
int res;
int n, m;

int dsu[maxn];
int bucket[maxn];

int fnd(int index) {
    if (dsu[index] == index) return index;
    return dsu[index] = fnd(dsu[index]);
}

void nproc(int a, int b) {
    a = fnd(a);
    b = fnd(b);
    if (a != b) {
        bucket[a] += bucket[b];
        dsu[b] = a;
    }
}

void hproc(int a, int b) {
    a = fnd(a);
    b = fnd(b);
    if (a != b) {
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
}

int get_index(int a, int b) {
    return (a - 1) * m + b;
}

#define _debug 1
int main() {
    cin.tie(0)->sync_with_stdio(0);

#if _debug == 1
    freopen("input.inp", "r", stdin);
#else

#endif // _debug

    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> color[get_index(i, j)];
        }
    }

    iota(dsu, dsu+maxn, 0);
    fill(bucket, bucket+maxn, 1);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            int index = get_index(i, j);
            if (i < n && color[get_index(i+1, j)] == color[index]) nproc(index, get_index(i+1, j));
            if (j < m && color[get_index(i, j+1)] == color[index]) nproc(index, get_index(i, j+1));
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            int index = get_index(i, j);
            if (i < n && color[get_index(i+1, j)] != color[index]) hproc(index, get_index(i+1, j));
            if (j < m && color[get_index(i, j+1)] != color[index]) hproc(index, get_index(i, j+1));
        }
    }

    for (int i = 1; i <= n*m; i++) {
        if (dsu[i] == i) {
            sort(adj[i].begin(), adj[i].end());
            adj[i].erase(unique(adj[i].begin(), adj[i].end()), adj[i].end());
        }
    }

    for (int i = 1; i <= n*m; i++) {
        if (dsu[i] == i) {
            res = max(res, bucket[i]);
            active++;
        }
    }

    int t;
    cin >> t;
    while (t--) {
        char c;
        int a, b;
        cin >> c >> a >> b;
        int index = get_index(a, b);
        int rindex = fnd(index);
        if (color[rindex] != c) {
            vector<int> prog;
            swap(prog, adj[rindex]);
            color[rindex] = c;

            for (int x : prog) {
                rindex = fnd(rindex);
                int current = fnd(x);
                if (rindex == current) continue;

                if (adj[rindex].size() < adj[current].size()) swap(rindex, current);

                color[rindex] = c;
                bucket[rindex] += bucket[current];
                dsu[current] = rindex;
                active--;
                res = max(res, bucket[rindex]);

                for (int y : adj[current]) {
                    adj[rindex].push_back(y);
                }
            }
        }
        cout << active << ' ' << res << '\n';
    }
}
