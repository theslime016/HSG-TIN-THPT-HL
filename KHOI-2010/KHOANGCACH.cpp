#include <bits/stdc++.h>
using namespace std;
int main() {
    freopen("KHOANGCACH.INP", "r", stdin);
    freopen("KHOANGCACH.OUT", "w", stdout);
    int n;
    cin >> n;
    unordered_map<long long, int> first;
    long long x;
    int maxDist = -1, pos1 = -1, pos2 = -1;
    for (int i = 1; i <= n; i++) {
        cin >> x;
        if (!first.count(x)) {
            first[x] = i;
        } else {
            int d = i - first[x];
            if (d > maxDist || (d == maxDist && i > pos2)) {
                maxDist = d;
                pos1 = first[x];
                pos2 = i;
            }
        }
    }
    if (maxDist == -1) {
        cout << -1;
    } else {
        cout << maxDist << "\n" << pos1 << " " << pos2;
    }
    return 0;
}