#include <bits/stdc++.h>
using namespace std;

/*
Cho N string ban đầu và Q string query, mỗi query hỏi số lượng string có chung prefix là string query.
*/

const int maxn = 1e5 + 5;
const int maxchar = 30;
int trie[maxn*maxchar][maxchar]; // index
int cnt[maxn*maxchar];
int node_count = 1;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, q; cin >> n >> q;
    string s;
    for (int i = 1; i <= n; i++) {
        cin >> s;
        int index = 0;
        for (char c : s) {
            if (!trie[index][c - 'a']) trie[index][c - 'a'] = node_count++;
            index = trie[index][c - 'a'];
            cnt[index]++;
        }
    }

    for (int i = 1; i <= q; i++) {
        cin >> s;
        int current_index = 0;
        for (char c : s) {
            if (!trie[current_index][c -'a']) {
                current_index = 0;
                break;
            }
            current_index = trie[current_index][c - 'a'];
        }
        cout << cnt[current_index] << '\n';
    }

}
