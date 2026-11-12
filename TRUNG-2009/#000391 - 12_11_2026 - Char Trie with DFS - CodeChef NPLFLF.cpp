#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5 + 5;
const int maxnode = maxn * 30;
int container[maxnode];
int trie[maxn][30];
int trie_cnt = 0;

void add(const string& s) {
    int index = 0;
    for (int i = (int)s.size() - 1; i >= 0; i--) {
        char c = s[i] - 'a';
        if (trie[index][c] == 0) {
            trie[index][c] = ++trie_cnt;
        }
        index = trie[index][c];
        container[index]++;
    }
}

int fnd(int index, int rem_len, int tar) {
    int ok = 0;
    for (int c = 0; c < 26; c++) {
        if (!trie[index][c]) continue;
        int nxt = trie[index][c];
        if (container[nxt] < tar) continue;
        
        if (rem_len - 1 == 0) return true;
        else ok |= fnd(nxt, rem_len - 1, tar);
        
        if (ok == 1) return true;
    }
    return ok;
}

string task[maxn];
int deleted[maxn];
void del(int query_index) {
    if (deleted[query_index]) return;
    
    int index = 0;
    for (int i = (int)task[query_index].size() - 1; i >= 0; i--) {
        char c = task[query_index][i] - 'a';
        if (trie[index][c] == 0) break;
        index = trie[index][c];
        container[index]--;
    }
    deleted[query_index] = 1;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    
    int q;
    cin >> q;
    string s;
    for (int i = 1; i <= q; i++) {
        int type;
        cin >> type;
        if (type == 1) {
            cin >> s;
            task[i] = s;
            add(s);
        } else if (type == 2) {
            int num, len;
            cin >> num >> len;
            cout << (fnd(0, len, num) == true ? "YES" : "NO") << '\n';
        } else if (type == 3) {
            int query_index;
            cin >> query_index;
            del(query_index);
        }
    }
    
}
