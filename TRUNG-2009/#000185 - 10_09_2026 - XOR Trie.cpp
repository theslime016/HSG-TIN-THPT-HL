#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5 + 5;
const int maxnode = 3e6 + 5;
const int _limit = 30;
int trie[maxnode][2];
long long cnt[maxnode];
int node_count = 1;

void inline insert(long long val) {
    int root = 0;
    for (int pos = _limit - 1; pos >= 0; pos--) {
        int bit = (val >> pos) & 1;
        if (!trie[root][bit]) trie[root][bit] = node_count++;
        root = trie[root][bit];
        cnt[root]++;
    }
}

long long fetch(long long x, long long k) {
    int root = 0;
    long long res = 0;
    for (int pos = _limit - 1; pos >= 0; pos--) {
        int bit_x = (x >> pos) & 1;
        int bit_k = (k >> pos) & 1;
        if (bit_k == 1) {
            int branch_0 = bit_x;
            if (trie[root][branch_0]) {
                res += cnt[trie[root][branch_0]];
            }

            int branch_1 = 1 - bit_x;
            if (trie[root][branch_1]) {
                root = trie[root][branch_1];
            } else {
                return res;
            }
        } else {
            int branch_0 = bit_x;
            if (trie[root][branch_0]) {
                root = trie[root][branch_0];
            } else {
                return res;
            }
        }
    }

    if (root) res += cnt[root];
    return res;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    freopen("input.inp", "r", stdin);

    int n; long long k;
    cin >> n >> k;
    long long total = 0;
    for (int i = 1; i <= n; i++) {
        long long val; cin >> val;
        total += fetch(val, k);
        insert(val);
    }
    cout << total;
}
