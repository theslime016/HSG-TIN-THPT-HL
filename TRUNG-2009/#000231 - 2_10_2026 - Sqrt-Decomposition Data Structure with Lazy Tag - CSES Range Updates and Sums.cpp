#include <bits/stdc++.h>
using namespace std;

const int maxn = 2e5 + 5;
long long A[maxn];
long long block[maxn];
long long lazy_set[maxn]; // block
long long lazy_sum[maxn]; // block

#define _debug 0
int main() {
    cin.tie(0)->sync_with_stdio(0);

    #if _debug == 1
    freopen("input.inp", "r", stdin);
    #else

    #endif // _debug

    int n, q;
    cin >> n >> q;
    int sz = sqrt(n);
    for (int i = 1; i <= n; i++) cin >> A[i];

    for (int i = 1; (i-1)*sz + 1 <= n; i++) {
        for (int j = (i-1)*sz + 1; j <= min(n, i * sz); j++) {
            block[i] += A[j];
        }
    }

    while (q--) {
        int type;
        cin >> type;
        if (type == 1) { // increase
            int l, r;
            long long val;
            cin >> l >> r >> val;

            while (l <= r) {
                int index = (l-1)/sz + 1;
                if ((l - 1)%sz == 0 && r - l + 1 >= sz) {
                    if (lazy_set[index]) lazy_set[index] += val;
                    else lazy_sum[index] += val;
                    l += sz;
                } else {
                    int pt = (index - 1) * sz + 1;
                    int nxt = min(n, index * sz);
                    block[index] = 0;
                    while (pt <= nxt) {
                        if (lazy_set[index]) A[pt] = lazy_set[index];
                        else A[pt] += lazy_sum[index];

                        if (pt >= l && pt <= r) A[pt] += val;
                        block[index] += A[pt];
                        pt++;
                    }

                    lazy_set[index] = lazy_sum[index] = 0;
                    l = pt;
                }
            }
        } else if (type == 2) { // set
            int l, r;
            long long val;
            cin >> l >> r >> val;

            while (l <= r) {
                int index = (l - 1)/sz + 1;
                if ((l-1)%sz == 0 && r - l + 1 >= sz) {
                    lazy_set[index] = val;
                    lazy_sum[index] = 0;
                    l += sz;
                } else {
                    int pt = (index - 1) * sz + 1;
                    int nxt = min(n, index * sz);
                    block[index] = 0;
                    while (pt <= nxt) {
                        if (pt >= l && pt <= r) A[pt] = val;
                        else if (lazy_set[index]) A[pt] = lazy_set[index];
                        else if (lazy_sum[index]) A[pt] += lazy_sum[index];
                        block[index] += A[pt];
                        pt++;
                    }

                    lazy_set[index] = lazy_sum[index] = 0;
                    l = pt;
                }
            }
        } else if (type == 3) {
            int l, r;
            cin >> l >> r;

            long long res = 0;
            while (l <= r) {
                int index = (l-1)/sz + 1;
                if ((l-1)%sz == 0 && r - l + 1 >= sz) {
                    if (lazy_set[index]) res += lazy_set[index] * sz;
                    else if (lazy_sum[index]) res += lazy_sum[index] * sz + block[index];
                    else res += block[index];
                    l += sz;
                } else {
                    if (lazy_set[index]) res += lazy_set[index];
                    else if (lazy_sum[index]) res += lazy_sum[index] + A[l];
                    else res += A[l];
                    l++;
                }
            }
            cout << res << '\n';
        }
    }

}
