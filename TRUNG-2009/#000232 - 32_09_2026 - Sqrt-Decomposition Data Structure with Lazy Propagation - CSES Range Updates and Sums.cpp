#include <bits/stdc++.h>
using namespace std;

const int maxn = 2e5 + 5;
const int maxnode = 500;
const long long inf = 1e18;

long long A[maxn];
long long get_id[maxn];

long long block[maxnode];
long long lblock[maxnode], rblock[maxnode];
long long lazy_set[maxnode], lazy_sum[maxnode];
int n, q;
int sz, num_block;

void push_down(int index) {
    int pt = lblock[index];
    while (pt <= rblock[index]) {
        if (lazy_set[index] != inf) A[pt] = lazy_set[index];
        else if (lazy_sum[index]) A[pt] += lazy_sum[index];

        pt++;
    }

    lazy_set[index] = inf;
    lazy_sum[index] = 0;
}

void push_up(int index) {
    int pt = lblock[index];
    block[index] = 0;
    while (pt <= rblock[index]) {
        block[index] += A[pt];
        pt++;
    }
}

void sum_update(int l, int r, const long long &val) {
    int tag_l = get_id[l];
    int tag_r = get_id[r];
    if (tag_l == tag_r) {
        push_down(tag_l);
        for (int i = l; i <= r; i++) {
            A[i] += val;
        }
        push_up(tag_l);
        return;
    }

    push_down(tag_l);
    for (int i = l; i <= rblock[tag_l]; i++) A[i] += val;
    push_up(tag_l);

    push_down(tag_r);
    for (int i = lblock[tag_r]; i <= r; i++) A[i] += val;
    push_up(tag_r);

    for (int i = tag_l + 1; i <= tag_r - 1; i++) {
        if (lazy_set[i] != inf) lazy_set[i] += val;
        else lazy_sum[i] += val;
    }
}

void set_update(int l, int r, const long long& val) {
    int tag_l = get_id[l];
    int tag_r = get_id[r];
    if (tag_l == tag_r) {
        push_down(tag_l);
        for (int i = l; i <= r; i++) A[i] = val;
        push_up(tag_l);
        return;
    }

    push_down(tag_l);
    for (int i = l; i <= rblock[tag_l]; i++) A[i] = val;
    push_up(tag_l);

    push_down(tag_r);
    for (int i = lblock[tag_r]; i <= r; i++) A[i] = val;
    push_up(tag_r);

    for (int i = tag_l + 1; i <= tag_r - 1; i++) {
        lazy_set[i] = val;
    }
}

long long fetch(int l, int r) {
    long long res = 0;
    int tag_l = get_id[l];
    int tag_r = get_id[r];
    if (tag_l == tag_r) {
        push_down(tag_l);
        for (int i = l; i <= r; i++) res += A[i];
        push_up(tag_l);
        return res;
    }

    push_down(tag_l);
    for (int i = l; i <= rblock[tag_l]; i++) res += A[i];
    push_up(tag_l);

    push_down(tag_r);
    for (int i = lblock[tag_r]; i <= r; i++) res += A[i];
    push_up(tag_r);

    for (int i = tag_l + 1; i <= tag_r - 1; i++) {
        if (lazy_set[i] != inf) res += lazy_set[i] * sz;
        else if (lazy_sum[i]) res += lazy_sum[i] * sz + block[i];
        else res += block[i];
    }
    return res;
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

    sz = sqrt(n);
    num_block = (n-1)/sz + 1;
    for (int i = 1; i <= n; i++) {
        int tag = (i-1)/sz + 1;
        get_id[i] = tag;
        block[tag] += A[i];
    }

    for (int i = 1; i <= num_block; i++) {
        lblock[i] = (i-1)*sz + 1;
        rblock[i] = min(n, i * sz);
    }

    #if _debug == 1
    for (int i = 1; i <= num_block; i++) {
        cout << block[i] << ' ' << lblock[i] << ' ' << rblock[i] << '\n';
    }
    #endif // _debug

    fill(lazy_set, lazy_set + maxnode, inf);

    while (q--) {
        int type;
        cin >> type;
        if (type == 1) {
            int l, r;
            long long val;
            cin >> l >> r >> val;
            sum_update(l, r, val);
        } else if (type == 2) {
            int l, r;
            long long val;
            cin >> l >> r >> val;
            set_update(l, r, val);
        } else {
            int l, r;
            cin >> l >> r;
            cout << fetch(l, r) << '\n';
        }
    }

}
