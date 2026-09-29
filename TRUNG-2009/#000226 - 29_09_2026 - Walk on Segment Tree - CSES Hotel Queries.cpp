#include <bits/stdc++.h>
using namespace std;
 
const int maxn = 2e5 + 5;
const long long inf = 1e18;
long long segment[4*maxn];
long long A[maxn];
long long build(int index, int l, int r) {
    if (l > r) return -inf;
    if (l == r) return segment[index] = A[l];
 
    int mid = (l + r) >> 1;
    return segment[index] = max(build(index << 1, l, mid), build(index << 1 | 1, mid+1, r));
}
 
long long update(int index, int l, int r, int uindex, const long long& val) {
    if (l == r) return segment[index] = val;
 
    int mid = (l + r) >> 1;
    if (uindex <= mid) {
        update(index << 1, l, mid, uindex, val);
    } else {
        update(index << 1 | 1, mid+1, r, uindex, val);
    }
    return segment[index] = max(segment[index << 1], segment[index << 1 | 1]);
}
 
int fetch(int index, int l, int r, const long long& val) {
    if (l == r) return segment[index] >= val ? l : 0;
 
    int mid = (l + r) >> 1;
    if (val <= segment[index << 1]) return fetch(index << 1, l, mid, val);
    else if (val <= segment[index << 1 | 1]) return fetch(index << 1 | 1, mid+1, r, val);
    else return 0;
}
 
#define _debug 0
int main() {
    cin.tie(0)->sync_with_stdio(0);
 
    #if _debug == 1
    freopen("input.inp", "r", stdin);
    #else
 
    #endif // _debug
 
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> A[i];
    build(1, 1, n);
    for (int i = 1; i <= m; i++) {
        long long x;
        cin >> x;
        int index = fetch(1, 1, n, x);
        cout << index << ' ';
        if (index != 0) {
            update(1, 1, n, index, A[index] - x);
            A[index] -= x;
        }
    }
}
