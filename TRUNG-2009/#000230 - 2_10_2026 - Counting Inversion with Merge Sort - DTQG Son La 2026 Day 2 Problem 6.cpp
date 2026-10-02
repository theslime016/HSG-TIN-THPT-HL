#include <bits/stdc++.h>
using namespace std;

const int maxn = 5e4 + 5;
long long X[maxn];
long long A[maxn];
long long temp[maxn];

bool check(long long a, long long b) {return a <= b;}

long long res;
void merge_sort(int l, int r) {
    if (r <= l) return;

    int mid = l + ((r - l) >> 1);
    merge_sort(l, mid);
    merge_sort(mid+1, r);
    int pt1 = l;
    int pt2 = mid+1;
    int pos = 0;

    while (pt1 <= mid && pt2 <= r) {
        if (check(A[pt1], A[pt2])) temp[pos++] = A[pt1++];
        else temp[pos++] = A[pt2++], res += mid - pt1 + 1;
    }

    while (pt1 <= mid) temp[pos++] = A[pt1++];
    while (pt2 <= r) temp[pos++] = A[pt2++];

    copy(temp, temp + pos, A + l);
}

#define _debug 0
int main() {
    cin.tie(0)->sync_with_stdio(0);

    #if _debug == 1
    freopen("input.inp", "r", stdin);
    #else
    freopen("CHECKINV.inp", "r", stdin);
    freopen("CHECKINV.out", "w", stdout);
    #endif // _debug

    int n, q;
    cin >> n >> q;
    for (int i = 1; i <= n; i++) cin >> X[i];

    while (q--) {
        int l, r;
        cin >> l >> r;
        res = 0;
        memcpy(A, X, sizeof (X));
        merge_sort(l, r);
        cout << res << '\n';
    }
}
