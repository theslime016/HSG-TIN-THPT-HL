#include <bits/stdc++.h>
using namespace std;

const int maxn = 2e5+5;
pair<int, long long> A[maxn];
int leftc[maxn], rightc[maxn];
long long segment[4*maxn];

void update(int index, int l, int r, int ql, int qr, const long long& val) {
    if (ql > r || qr < l) return;
    if (ql <= l && r <= qr) {
        segment[index] = max(segment[index], val);
        return;
    }

    int mid = l + (r-l)/2;
    update(index*2, l, mid, ql, qr, val);
    update(index*2+1, mid+1, r, ql, qr, val);
}

long long fetch(int index, int l, int r, int pos) {
    if (l == r) return segment[index];
    int mid = l + (r-l)/2;
    if (pos <= mid) return max(segment[index], fetch(index*2, l, mid, pos));
    else return max(segment[index], fetch(index*2 + 1, mid+1, r, pos));
}

#define _DEBUG 2

int main() {
    cin.tie(0)->sync_with_stdio(0);

    #if _DEBUG == 1
    freopen("input.inp", "r", stdin);
    #elif _DEBUG == 2
    freopen("DUDAY.INP", "r", stdin);
    freopen("DUDAY.OUT", "w", stdout);
    #else
    #endif // _DEBUG

    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> A[i].second;
        A[i].first = i;
    }

    stack<int> st;
    for (int i = 1; i <= n; i++) {
        while (!st.empty() && A[st.top()].second < A[i].second) st.pop();
        if (!st.empty()) leftc[i] = st.top();
        st.push(i);
    }

    while(!st.empty()) st.pop();

    for (int i = n; i >= 1; i--) {
        while (!st.empty() && A[st.top()].second < A[i].second) st.pop();
        if (!st.empty()) rightc[i] = st.top();
        else rightc[i] = n + 1;
        st.push(i);
    }

    sort(A+1, A+n+1, [](const auto& x, const auto& y){return x.second > y.second;});
    long long res = 0;
    for (int i = 1; i <= n; i++) {
        long long dp = fetch(1, 1, n, A[i].first) + 1;
        res = max(res, dp);

        int rindex = A[i].first;
        if (rindex - leftc[rindex] > 1) update(1, 1, n, leftc[rindex] + 1, rindex - 1, dp);
        if (rightc[rindex] - rindex > 1) update(1, 1, n, rindex + 1, rightc[rindex] - 1, dp);
    }
    cout << res;
}
