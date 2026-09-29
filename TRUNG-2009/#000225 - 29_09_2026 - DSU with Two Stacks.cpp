#include <bits/stdc++.h>
using namespace std;

/*
Xem hai tap co giong nhau hoan toan khong
*/

struct uf {
    int n;
    vector<int> data;
    vector<int> bucket;

    uf() = default;
    uf(int n) {
        this->n = n;
        data.assign(n+1, 0);
        iota(data.begin(), data.end(), 0);
        bucket.assign(n+1, 1);
    }

    int fnd(int index) {
        if (data[index] == index) return index;
        return data[index] = fnd(data[index]);
    }

    void proc(int a, int b) {
        a = fnd(a);
        b = fnd(b);
        if (a != b) {
            if (bucket[a] < bucket[b]) swap(a, b);
            bucket[a] += bucket[b];
            data[b] = a;
        }
    }

    int check(int a, int b) {
        return fnd(a) == fnd(b);
    }
};

#define _debug 1
int main() {
    cin.tie(0)->sync_with_stdio(0);

    #if _debug == 1
    freopen("input.inp", "r", stdin);
    #else

    #endif // _debug

    int n, q;
    cin >> n >> q;

    uf dsu[2]{uf(n), uf(n)};
    stack<pair<int, int>> wait[2]{};
    while (q--) {
        int parity, a, b;
        cin >> parity >> a >> b;
        parity--;
        dsu[parity].proc(a, b);
        if (!dsu[!parity].check(a, b)) wait[!parity].push({a, b});
        while (!wait[parity].empty()) {
            auto [x, y] = wait[parity].top();
            if (dsu[parity].check(x, y)) {
                wait[parity].pop();
            } else {
                break;
            }
        }

        if (wait[parity].empty() && wait[!parity].empty()) cout << "YES" << '\n';
        else cout << "NO" << '\n';
    }
}
