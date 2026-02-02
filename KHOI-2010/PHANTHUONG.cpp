#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    freopen("PHANTHUONG.INP", "r", stdin);
    freopen("PHANTHUONG.OUT", "w", stdout);
    int n;
    cin >> n;
    vector<long long> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    vector<long long> L(n), R(n);
    stack<int> st;
    while (!st.empty()) st.pop();
    for (int i = 0; i < n; i++) {
        while (!st.empty() && a[st.top()] <= a[i]) st.pop();
        L[i] = st.empty() ? i + 1 : i - st.top();
        st.push(i);
    }
    while (!st.empty()) st.pop();
    for (int i = n - 1; i >= 0; i--) {
        while (!st.empty() && a[st.top()] < a[i]) st.pop();
        R[i] = st.empty() ? n - i : st.top() - i;
        st.push(i);
    }
    long long sumMax = 0;
    for (int i = 0; i < n; i++)
        sumMax += a[i] * L[i] * R[i];
    while (!st.empty()) st.pop();
    for (int i = 0; i < n; i++) {
        while (!st.empty() && a[st.top()] >= a[i]) st.pop();
        L[i] = st.empty() ? i + 1 : i - st.top();
        st.push(i);
    }
    while (!st.empty()) st.pop();
    for (int i = n - 1; i >= 0; i--) {
        while (!st.empty() && a[st.top()] > a[i]) st.pop();
        R[i] = st.empty() ? n - i : st.top() - i;
        st.push(i);
    }
    long long sumMin = 0;
    for (int i = 0; i < n; i++)
        sumMin += a[i] * L[i] * R[i];
    cout << sumMax - sumMin;
    return 0;
}