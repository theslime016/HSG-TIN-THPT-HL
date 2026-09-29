#include <bits/stdc++.h>
using namespace std;

/*
Cho mot do thi n dinh m canh
Dinh co the co 2 mau la W va B
Dinh co mot trong so X
Cho q truy van chuyen mau dinh v thanh mau c va gop tat ca cac dinh co chung mau lai thanh mot dinh
Sau moi truy van in ra so luong dinh con lai va dinh co trong so X lon nhat

5 5
1 2 3 4 5
BWBBW
1 2
2 4
2 3
4 5
3 5
2
2 B
3 W
*/

struct uf {
    int n;
    int active;
    int res;
    vector<int> data;
    vector<int> val;
    vector<char> color;

    uf (int n) {
        this->n = n;
        this->active = n;
        this->res = 0;
        data.assign(n+1, 0);
        iota(data.begin(), data.end(), 0);
        val.assign(n+1, 0);
        color.assign(n+1, '-');
    }

    int fnd(int index) {
        if (index == data[index]) return index;
        return data[index] = fnd(data[index]);
    }

    void proc(int a, int b) {
        a = fnd(a);
        b = fnd(b);
        if (a != b) {
            val[a] += val[b];
            data[b] = a;
            active--;
            res = max(res, val[a]);
        }
    }
};

const int maxn = 1e3 + 5;
int arc[maxn][maxn];

#define _debug 1
int main() {
    cin.tie(0)->sync_with_stdio(0);

#if _debug == 1
    freopen("input.inp", "r", stdin);
#else

#endif // _debug

    int n, m;
    cin >> n >> m;

    uf dsu(n);
    for (int i = 1; i <= n; i++) cin >> dsu.val[i];
    for (int i = 1; i <= n; i++) {
        cin >> dsu.color[i];
        dsu.res = max(dsu.res, dsu.val[i]);
    }
    // Tim mau chinh chu
    // Check color
    // -> Color 1 -> continue
    // -> Color 0 -> gop cac adj vao
    //   | Xet i = canh -> Neu = 1 thi gop vao roi xoa no di
    //   | Xet j = canh dang xet, neu = 1 + khac no va khac i thi bat 1 o arc i
    for (int i = 1; i <= m; i++) {
        int a, b;
        cin >> a >> b;
        arc[a][b] = 1;
        arc[b][a] = 1;
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cout << arc[i][j] << ' ';
        }
        cout << '\n';
    }

    int q;
    cin >> q;
    while (q--) {
        int v;
        char c;
        cin >> v >> c;
        int index = dsu.fnd(v);
        if (dsu.color[index] != c) {
            dsu.color[index] = c;
            // xoa link index - parent, index - child
            // them link parent - child
            for (int j = 1; j <= n; j++) {
                if (index == j) continue;
                if (!arc[index][j]) continue;
                int rindex = dsu.fnd(j);
                if (rindex == index || dsu.color[rindex] != dsu.color[index]) {
                    continue;
                }
                dsu.proc(index, rindex);
                arc[index][j] = 0;
                arc[j][index] = 0;
                for (int k = 1; k <= n; k++) {
                    if (k == index || k == j) continue;
                    if (!arc[k][j]) continue;
                    arc[j][k] = 0;
                    arc[k][j] = 0;

                    arc[index][k] = 1;
                    arc[k][index] = 1;
                }
            }
        }
        cout << dsu.active << ' ' << dsu.res << '\n';
    }
}
