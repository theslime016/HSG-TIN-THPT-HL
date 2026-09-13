#include <bits/stdc++.h>
using namespace std;

const int maxn = 2e5 + 5;
int A[maxn];
int B[maxn];
int l[maxn], r[maxn];
int dp[maxn];

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
    for (int i = 1; i <= n; i++) {cin >> A[i]; B[i] = i;}
    stack<int> st1;
    for (int i = 1; i <= n; i++) {
        while (!st1.empty() && A[st1.top()] <= A[i]) st1.pop();
        if (!st1.empty()) l[i] = st1.top();
        st1.push(i);
    }

    stack<int> st2;
    for (int i = n; i > 0; i--) {
        while (!st2.empty() && A[st2.top()] <= A[i]) st2.pop();
        if (!st2.empty()) r[i] = st2.top();
        st2.push(i);
    }

    sort(B + 1, B + n + 1, [](const int x, const int y) {return A[x] > A[y];});
    int res = 0;
    for (int i = 1; i <= n; i++) {
        int jindex = B[i];
        dp[jindex] = max(dp[l[jindex]], dp[r[jindex]]) + 1;
        res = max(res, dp[jindex]);
    }
    cout << res;
}
