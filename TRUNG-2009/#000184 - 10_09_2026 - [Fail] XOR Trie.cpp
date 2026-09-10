#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5 + 5;
const int maxnode = 3e6 + 5;
int trie[maxnode][2];
int cnt[maxnode];
int node_count = 1;
int n;
long long k;
void inline insert(long long val) {
            int cur = 0;
        while (val > 0) {
            if (!trie[cur][val & 1]) trie[cur][val & 1] = node_count++;
            cur = trie[cur][val & 1];
            cnt[cur]++;
            val >>= 1;
        }
}

long long fetch(long long val) {
    long long res = 0;
    int index = 0;
    while (k > 0) {
        if (k & 1) {
            for (int i = 0; i <= 1; i++) {
                int bitxor = (val & 1) ^ i;
                if (bitxor == 0 && trie[index][i]) {
                    res += cnt[trie[index][i]];
                } else if (bitxor == 1) {
                    index = trie[index][i];
                }
            }
        } else {
            for (int i = 0; i <= 1; i++) {
                int bitxor = (val & 1) ^ i;
                if (bitxor == 0) {
                    index = trie[index][i];
                }
            }
        }
        k >>= 1;
        val >>= 1;
        if (index == 0) break;
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> k;
    long long res = 0;
    for (int i = 1; i <= n; i++) {
        long long val;
        cin >> val;
        cout << fetch(val) << '\n';
        insert(val);
    }
}
