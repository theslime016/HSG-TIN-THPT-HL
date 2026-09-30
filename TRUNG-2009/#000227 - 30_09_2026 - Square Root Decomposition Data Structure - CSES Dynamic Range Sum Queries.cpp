#include <bits/stdc++.h>
using namespace std;
 
const int maxn = 2e5 + 5;
const long long inf = 1e18;
long long A[maxn];
long long block[maxn];
int n, q, sz;
 
pair<int, int> get_point(int index) {
    return {
        (index-1) * sz + 1,
        min(index * sz, n)
    };
}
 
#define _debug 0
int main() {
    cin.tie(0)->sync_with_stdio(0);
 
#if _debug == 1
    freopen("input.inp", "r", stdin);
#else
 
#endif // _debug
 
    cin >> n >> q;
    for (int i = 1; i <= n; i++) cin >> A[i];
    // start = (index-1) * sqrt(n) + 1
    // end = min(index * sqrt(n), n)
    sz = sqrt(n);
    for (int i = 1; (i-1)*sz+1 <= n; i++) {
        auto [start, end] = get_point(i);
 
        for (int j = start; j <= end; j++) {
            block[i] += A[j];
        }
    }
 
    while (q--) {
        int type;
        cin >> type;
        if (type == 1) {
            int index;
            long long val;
            cin >> index >> val;
            A[index] = val;
            int tag = (index-1)/sz + 1;
            auto [start, end] = get_point(tag);
            block[tag] = 0;
            while (start <= end) {
                block[tag] += A[start];
                start++;
            }
        } else {
            int l, r;
            cin >> l >> r;
            long long res = 0;
            while (l <= r) {
                if ((l-1)%sz == 0 && r >= (l-1) + sz) {
                    int index = (l-1)/sz+1;
                    res += block[index];
                    l += sz;
                } else {
                    res += A[l];
                    l++;
                }
            }
            cout << res << '\n';
        }
    }
 
}
