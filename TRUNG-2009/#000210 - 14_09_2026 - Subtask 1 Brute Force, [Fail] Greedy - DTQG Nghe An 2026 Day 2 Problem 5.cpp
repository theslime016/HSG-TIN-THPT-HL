#include <bits/stdc++.h>
using namespace std;

const int maxn = 2e5 + 5;
int n, q;
long long k;
long long H[maxn];

namespace subtask1 {
long long H2[maxn];
void solve() {
    while (q--) {
        long long W;
        cin >> W;
        memcpy(H2, H, maxn);
        int res = 0;
        while (W > 0) {
            for (int i = 1; i <= n; i++) {
                if (i == n || H2[i+1] > H2[i]) {
                    H2[i]++;
                    W--;
                    res = max(res, i);
                    break;
                }
            }
        }
        cout << res << ' ';
    }
}
}

namespace subtask4 {
long long pref[maxn];
long long suff[maxn];
long long best[maxn];
void solve() {
    long long current = 0;
    long long mx = 0;
    int cnt = 0;
    for (int i = 1; i <= n; i++, cnt++) {
        if (H[i] > mx) {
            current += (H[i] - mx) * cnt;
        } else {
            current += abs(mx - H[i]);
        }
        pref[i] = current;
        mx = max(mx, H[i]);
    }

    current = mx = cnt = 0;
    for (int i = n; i > 0; i--, cnt++) {
        if (H[i] > mx) {
            current += (H[i] - mx) * cnt;
        } else {
            current += abs(mx - H[i]);
        }
        suff[i] = current;
        mx = max(mx, H[i]);
    }

    mx = 0;
    cnt = 0;
    for (int i = 1; i <= n; i++, cnt++) {
        if (H[i] > mx) {

        }
    }
}
}

namespace fallback {
long long H2[maxn];
void solve() {
    while (q--) {
        long long W;
        cin >> W;
        int best_dead = n;
        for (int i = 1; i <= n; i++) {
            H[i] += k;
            memcpy(H2, H, maxn);
            int res = 0;
            long long temp_W = W;
            while (temp_W > 0) {
                for (int i = 1; i <= n; i++) {
                    if (i == n || H2[i+1] > H2[i]) {
                        H2[i]++;
                        temp_W--;
                        res = max(res, i);
                        break;
                    }
                }
            }
            best_dead = min(res, best_dead);
            H[i] -= k;
        }
        cout << best_dead << ' ';
    }
}
}

#define _debug 0
int main() {
    cin.tie(0)->sync_with_stdio(0);

#if _debug == 1
    freopen("input.inp", "r", stdin);
#else

#endif // _debug

    // Q1 luong nuoc it nhat de lu vuot qua cot nay la bao nhieu
    // Q2 so lang no bao ve duoc (ke ca chinh no neu khong bi vuot qua)
    // Q1 + Q2 -> ket qua

    // Q1 = nang tat ca len max phia truoc, neu <= max phia truoc thi chi can + 1
    // neu > max phia truoc thi nang tiep len hien tai roi + 1

    // Nang the nao cho nhanh? (Q2)
    // Truoc tien thi simulate de test cai Q1 truoc
    // Chi can tra loi cau hoi: De nang 1 prefix/suffix len bang nhau thi mat bao nhieu nuoc
    // Sau do thi cong thuc se la so luong nuoc * so lang

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> H[i];
    }

    cin >> q >> k;
    if (n <= 50 && q <= 50 && k == 0) subtask1::solve();
    else fallback::solve();
}
