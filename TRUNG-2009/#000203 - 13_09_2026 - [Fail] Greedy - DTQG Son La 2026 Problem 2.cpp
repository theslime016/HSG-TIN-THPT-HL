#include <bits/stdc++.h>
using namespace std;

const int inf = 1e5;
const int maxn = 1e4 + 5;
int cnt[10];
int cost[10];
int change[10][10];
char s[maxn];
char res[maxn][10];

#define _DEBUG 0

int main() {
    cin.tie(0)->sync_with_stdio(0);

#if _DEBUG
    freopen("input.inp", "r", stdin);
#else
    freopen("MODEL.INP", "r", stdin);
    freopen("MODEL.OUT", "w", stdout);
#endif // _DEBUG

    int n, k;
    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        cin >> s[i];
        cnt[ s[i] - '0' ]++;
    }

    for (int i = 0; i <= 9; i++) {
        if (cnt[i] >= k) {
            cout << 0 << '\n';
            for (int i = 0; i < n; i++) {
                cout << s[i];
            }
            return 0;
        }
    }

    int best_cost = inf;
    for (int i = 0; i <= 9; i++) {
        if (!cnt[i]) continue;
        int req = k - cnt[i];
        int tail = i-1;
        int head = i+1;
        while (req > 0) {
            if (tail >= 0 && cnt[tail]) {
                if (cnt[tail] >= req) {
                    change[tail][i] = req;
                    cost[i] += req * abs(i - tail);
                    req = 0;
                } else {
                    change[tail][i] = cnt[tail];
                    cost[i] += cnt[tail] * abs(i - tail);
                    req -= cnt[tail];
                }
            }

            if (head <= 9 && cnt[head]) {
                if (cnt[head] >= req) {
                    change[head][i] = req;
                    cost[i] += cnt[head] * abs(i - head);
                    req = 0;
                } else {
                    change[head][i] = cnt[head];
                    cost[i] += cnt[head] * abs(i - head);
                    req -= cnt[head];
                }
            }
            tail--;
            head++;
        }
        best_cost = min(best_cost, cost[i]);
    }

    int best_num = -1;
    for (int num = 0; num <= 9; num++) {
        if (cost[num] == best_cost) {

            for (int i = 0; i < n; i++) {
                res[i][num] = s[i];
            }

            int req = k - cnt[num];
            for (int i = 9; i > num && req; i--) {
                if (!change[i][num]) continue;
                for (int j = 0; j < n && req; j++) {
                    if (res[j][num] == i + '0') {
                        res[j][num] = num + '0';
                        req--;
                    }
                }
            }

            for (int i = 0; i < num && req; i++) {
                if (!change[i][num]) continue;
                for (int j = n-1; j >= 0 && req; j--) {
                    if (res[j][num] == i + '0') {
                        res[j][num] = num + '0';
                        req--;
                    }
                }
            }

            if (best_num == -1) {
                best_num = num;
                continue;
            }

            for (int i = 0; i < n; i++) {
                if (res[i][best_num] > res[i][num]) {
                    best_num = num;
                    break;
                } else if (res[i][best_num] < res[i][num]) {
                    break;
                }
            }
        }
    }
    cout << best_cost << '\n';
    for (int i = 0; i < n; i++) {
        cout << res[i][best_num];
    }
}
