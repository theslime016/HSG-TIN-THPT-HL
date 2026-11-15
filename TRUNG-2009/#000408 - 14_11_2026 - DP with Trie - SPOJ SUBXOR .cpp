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
#define debug_title cerr << __PRETTY_FUNCTION__ << " line: " << __LINE__ << endl
#define newline cerr << endl

#else
#define debug(...) (void(0))
#define debug_title (void(0))
#define newline (void(0))

#endif // _debug

const int maxn = 1e5 + 5;
const int maxlen = 22;

int n, k;

struct TRIE {
  int data;
  int cnt;
} trie[maxn * maxlen][2];
int trie_ptr = 0;

void clear_trie() {
  for (int i = 0; i <= trie_ptr; i++) {
    trie[i][0] = {};
    trie[i][1] = {};
  }
  trie_ptr = 0;
}

void add_trie(int num) {
  int index = 0;
  for (int i = maxlen - 1; i >= 0; i--) {
    int bit = (num >> i) & 1;

    if (!trie[index][bit].data) {
      trie[index][bit].data = ++trie_ptr;
    }

    trie[index][bit].cnt++;
    index = trie[index][bit].data;
  }
}

int fetch_trie(int num) {
  int index = 0;
  int res = 0;
#if _debug == 1
  newline;
  debug_title;
  debug(num, bitset<maxlen>(num), bitset<maxlen>(k));
#endif // _debug
  for (int i = maxlen - 1; i >= 0; i--) {
    int bit = (num >> i) & 1;
    int k_bit = (k >> i) & 1;
    debug(i, bit, k_bit, res);

    if (k_bit) {
      res += trie[index][bit].cnt;

//      if (trie[index][!bit].flag) {
//        res += trie[index][!bit].cnt;
//        break;
//      }

      index = trie[index][!bit].data;
    } else {
//      if (trie[index][bit].flag) {
//        res += trie[index][bit].cnt;
//        break;
//      }
      index = trie[index][bit].data;
    }

    if (index == 0)
      break;
  }
//  res += trie[index][bit].data;

#if _debug == 1
  debug(res);
  newline;
#endif // _debug

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
    cin >> n >> k;
    clear_trie();

    int pref = 0;
    add_trie(pref);

    long long res = 0;
    for (int i = 1; i <= n; i++) {
      int x;
      cin >> x;
      pref ^= x;

      int val = fetch_trie(pref);

      res += val;

      add_trie(pref);
    }
    cout << res << '\n';
  }

}
