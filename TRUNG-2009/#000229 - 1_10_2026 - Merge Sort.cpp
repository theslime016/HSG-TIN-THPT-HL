#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e3 + 5;
int A[maxn];
int temp[maxn];

bool check(int a, int b) {return a < b;}

void merge_sort(int l, int r) {
    if (r < l) return;
    if (r - l <= 1) {
        if (r - l == 1 && !check(A[l], A[r])) swap(A[l], A[r]);
        return;
    }

    int mid = l + ((r - l) >> 1);
    merge_sort(l, mid);
    merge_sort(mid+1, r);
    int pt1 = l;
    int pt2 = mid+1;
    int pos = 0;

    while (pt1 <= mid && pt2 <= r) {
        if (check(A[pt1], A[pt2])) temp[pos++] = A[pt1++];
        else temp[pos++] = A[pt2++];
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

    #endif // _debug

    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> A[i];
    merge_sort(1, n);

    for (int i = 1; i <= n; i++) cout << A[i] << ' ';
}
