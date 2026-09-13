#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e4 + 5;
const int inf = 1e6;
int cnt['9'+1];
char s[maxn];
char buffer1[maxn], buffer2[maxn];
char* current = &buffer1[0];
char* best = &buffer2[0];

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
    for (int i = 1; i <= n; i++) {
        cin >> s[i];
        cnt[ s[i] ]++;
    }

    for (char num = '0'; num <= '9'; num++) {
        if (cnt[num] >= k) {
            cout << 0 << '\n';
            for (int i = 1; i <= n; i++) {
                cout << s[i];
            }
            return 0;
        }
    }

    int best_cost = inf;
    for (char num = '0'; num <= '9'; num++) {
        memcpy(current, s, maxn);

        int req = k - cnt[num];
        char tail = num - 1;
        char head = num + 1;
        int cost = 1;
        int total = 0;
        while (req > 0) {
            for (int i = 1; i <= n && req; i++) {
                if (current[i] == head) {
                    current[i] = num;
                    req--;
                    total += cost;
                }
            }

            for (int i = n; i > 0 && req; i--) {
                if (current[i] == tail) {
                    current[i] = num;
                    req--;
                    total += cost;
                }
            }

            cost++;
            tail--;
            head++;
        }
        if (best_cost > total) {
            best_cost = total;
            swap(best, current);
        } else if (best_cost == total && strncmp(current + 1, best + 1, n) < 0) {
            swap(best, current);
        }
    }

    cout << best_cost << '\n';
    for (int i = 1; i <= n; i++) {
        cout << best[i];
    }
}
