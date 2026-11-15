#include <bits/stdc++.h>
using namespace std;

#define _debug 0

#if _debug == 1
void log_out() {
  cerr << endl;
}
template<typename H, typename... T>
void log_out(H h, T... t) {
  cerr << h << ", ";
  log_out(t...);
}
#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:" << endl, log_out(__VA_ARGS__)
#define debug_title cerr << __func__ << " line:" << __LINE__ << endl
#define newline cerr << endl

#else
#define debug(...) (void(0))
#define newline (void(0))

#endif // _debug

const int maxn = 1e5 + 5;
const int maxquery = 5e4 + 5;
const int maxlen = 20;
const int inf = 1e9;

int A[maxn];

struct QUERY {
  int l, r;
  int val;
  int index;
  friend bool operator<(const QUERY& a, const QUERY& b) {
    if (a.r != b.r)
      return a.r < b.r;
    else
      return a.l < b.l;
  }
} task[maxquery];
int query_res[maxquery];

struct TRIE {
  int data;
  int occur;
  int flag;
} trie[maxn * maxlen][2];
int trie_cnt = 0;

void add_trie(int num, int occur) {
  int index = 0;
  for (int i = maxlen - 1; i > 0; i--) {
    bool bit = num & (1 << (i - 1));
    bool flag = (i == 1);
    if (!trie[index][bit].data) {
      trie[index][bit].data = ++trie_cnt;
    }
    trie[index][bit].occur = max(trie[index][bit].occur, occur);
    trie[index][bit].flag |= flag;
    index = trie[index][bit].data;
  }
}

void clear_trie(int index) {
  for (int bit = 0; bit <= 1; bit++) {
    if (trie[index][bit].data) {
      clear_trie(trie[index][bit].data);
      trie[index][bit] = {};
    }
  }
}

int query_fetch(int val, int l) {
  int index = 0;
  int res = 0;
  for (int i = maxlen - 1; i > 0; i--) {
    bool bit = val & (1 << (i - 1));

#if _debug == 1
    debug(i, bit, bitset<maxlen>(res));
    debug(trie[index][!bit].data);
    debug(trie[index][!bit].occur);
    debug(trie[index][!bit].flag);
    debug(trie[index][bit].data);
    debug(trie[index][bit].occur);
    debug(trie[index][bit].flag);
#endif // _debug

    int found = 0;

    if (trie[index][!bit].data) {
      int occur = trie[index][!bit].occur;
      if (occur >= l) {
        res <<= 1;
        res |= (!bit);
        index = trie[index][!bit].data;
        continue;
      }
    }

    if (trie[index][bit].data) {
      int occur = trie[index][bit].occur;
      if (occur >= l) {
        res <<= 1;
        res |= bit;
        index = trie[index][bit].data;
        continue;
      }
    }
    break;
  }

  #if _debug == 1
  debug(res ^ val);
  debug(bitset<maxlen>(res), res);
  debug(bitset<maxlen>(val), val);
  newline;
  #endif // _debug

  res ^= val;
  return res;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);

#if _debug == 1
  freopen("input.inp", "r", stdin);

#elif _debug == 2
  freopen("input.inp", "r", stdin);

#else

#endif // _debug

  int t;
  cin >> t;
  while (t--) {
    int n, q;
    cin >> n >> q;

    clear_trie(0);
    for (int i = 1; i <= n; i++)
      cin >> A[i];


    for (int i = 1; i <= q; i++) {
      cin >> task[i].val >> task[i].l >> task[i].r;
      task[i].index = i;
    }
    sort(task + 1, task + q + 1);

    int current_r = 0;
    for (int i = 1; i <= q; i++) {
      int l = task[i].l;
      int r = task[i].r;
      while (current_r < r) {
        current_r++;
        add_trie(A[current_r], current_r);
      }

      query_res[ task[i].index ] = query_fetch(task[i].val, l);
    }

    for (int i = 1; i <= q; i++) {
      cout << query_res[i] << '\n';
    }

  }

}
