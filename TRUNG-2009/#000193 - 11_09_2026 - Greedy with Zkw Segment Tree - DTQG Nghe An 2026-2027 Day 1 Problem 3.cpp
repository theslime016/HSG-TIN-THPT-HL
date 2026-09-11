#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5 + 5;
int n, k;
pair<int, int> A[maxn]; // val - index
int B[maxn];
int cnt_select = 0;

const int inf = 1e6;
const int m = 131072;
struct node {
    int val;
    int index;
    bool operator<(const node& other) const {
        return this->val < other.val || (this->val == other.val && this->index > other.index);
    }
};
node segment0[m*2+5];
node segment1[m*2+5];
void prebuild() {
    fill(segment0, segment0 + (m*2+5), node{inf, -1});
    fill(segment1, segment1 + (m*2+5), node{inf, -1});
    for (int i = 1; i <= n; i++) {
        segment0[i+m].val = A[i].first;
        segment0[i+m].index = i;
        segment1[i+m].index = i;
    }

    for (int i = m - 1; i > 0; i--) {
        segment0[i] = min(segment0[i << 1], segment0[i << 1 | 1]);
    }
}

void update0(int index, int val) {
    index += m;
    segment0[index].val = val;
    for (index >>= 1; index > 0; index >>= 1) {
        segment0[index] = min(segment0[index << 1], segment0[index << 1 | 1]);
    }
}

void update1(int index, int val) {
    index += m;
    segment1[index].val = val;
    for (index >>= 1; index > 0; index >>= 1) {
        segment1[index] = min(segment1[index << 1], segment1[index << 1 | 1]);
    }
}

node fetch0(int l) {
    int s = m + l - 1;
    int t = m + n + 1;

    node res = {inf, -1};
    for (; s ^ t ^ 1; s >>= 1, t >>= 1) {
        if (~s & 1) res = min(res, segment0[s ^ 1]);
        if (t & 1) res = min(res, segment0[t ^ 1]);
    }
    return res;
}

node fetch1(int l) {
    int s = m + l - 1;
    int t = m + n + 1;

    node res = {inf, -1};
    for (; s ^ t ^ 1; s >>= 1, t >>= 1) {
        if (~s & 1) res = min(res, segment1[s ^ 1]);
        if (t & 1) res = min(res, segment1[t ^ 1]);
    }
    return res;
}

bool init_select() {
    for (int i = 1; i <= n; i++) {
        node res = fetch0(i+1);
        if (res.val < A[i].first) {
            cnt_select = 2;
            A[i].second = true;
            A[res.index].second = true;
            swap(A[i], A[res.index]);
            update1(i, A[i].first);
            update1(res.index, A[res.index].first);
            update0(i, inf);
            update0(res.index, inf);
            return true;
        }
    }
    return false;
}

bool swap_local() {
    // sort selected
    bool change = false;
    for (int i = 1; i <= n; i++) {
        if (!A[i].second) continue;
        node res = fetch1(i+1);
        if (res.val < A[i].first) {
            swap(A[i], A[res.index]);
            update1(i, A[i].first);
            update1(res.index, A[res.index].first);
            change = true;
            break;
        }
    }
    return change;
}

bool detect() {
    bool found = false;
    for (int i = 1; i <= n; i++) {
        if (!A[i].second) continue;
        if (A[i].first == B[i]) {
            A[i].second = false;
            cnt_select--;
            update1(i, inf);
            update0(i, A[i].first);
            found = true;
        }
    }
    return found;
}

bool loop() {
    bool found = false;
    for (int i = 1; i <= n; i++) {
        if (A[i].second == 0) {
            node res1 = fetch1(i+1);
            node res0 = {inf, -1};
            if (cnt_select + 2 <= k) {
                res0 = fetch0(i+1);
            }

            node res = res0.val < res1.val ? res0 : res1;

            if (res.val < A[i].first) {
                A[i].second = true;
                update0(i, inf);
                cnt_select++;
                if (!A[res.index].second) {
                    A[res.index].second = true;
                    cnt_select++;
                    update0(res.index, inf);
                }
                swap(A[i], A[res.index]);
                update1(i, A[i].first);
                update1(res.index, A[res.index].first);
                found = true;
                break;
            }
        } else if (A[i].second == 1) {
            node res = fetch0(i+1);
            if (res.val < A[i].first) {
                A[res.index].second = true;
                update0(res.index, inf);
                cnt_select++;
                swap(A[i], A[res.index]);
                update1(i, A[i].first);
                update1(res.index, A[res.index].first);
                found = true;
                break;
            }
        }
    }
    return found;
}

void debugA() {
    for (int i = 1; i <= n; i++) {
        cout << A[i].first << ' ';
    }
    cout << '\n';
    for (int i = 1; i <= n; i++) {
        cout << A[i].second << ' ';
    }
    cout << '\n';
}

const int debug = 0;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    freopen("input.inp", "r", stdin);
    freopen("output.out", "w", stdout);

    cin >> n >> k;
    for (int index = 1; index <= n; index++) {
        cin >> A[index].first;
        B[index] = A[index].first;
    }

    prebuild();

    if (k >= 2 && !init_select()) {
        for (int i = 1; i <= n; i++) {
            cout << A[i].first << ' ';
        }
        return 0;
    } else if (debug) {
        cout << "INIT" << '\n';
        debugA();
    }

    bool change = true;
    while (change) {
        change = false;
        if (cnt_select < k && loop()) {
            change = true;

            if (debug) {
                cout << "NEWPAIR" << '\n';
                debugA();
            }

        }

        if (swap_local()) {
            change = true;

            if (debug) {
                cout << "SWAP" << '\n';
                debugA();
            }
        }

        if (detect()) {
            change = true;

            if (debug) {
                cout << "DETECT" << '\n';
                debugA();
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        cout << A[i].first << ' ';
    }
}
