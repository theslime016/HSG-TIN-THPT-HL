#include <bits/stdc++.h>
using namespace std;

const int maxn = 2e4 + 5;
int A[maxn];
int get_index[maxn];
int cnt[maxn];
int res[maxn];

int head[maxn];
int previous[maxn], nxt[maxn];
int max_freq;

void del_node(int val, int freq) {
  if (previous[val] != -1) nxt[previous[val]] = nxt[val];

  if (nxt[val] != -1) previous[ nxt[val] ] = previous[val];
  else head[freq] = previous[val];
}

void insert_node(int val, int freq) {
  previous[val] = head[freq];
  nxt[val] = -1;
  if (head[freq] != -1) nxt[ head[freq] ] = val;
  head[freq] = val;
}

void add(int val) {
  int freq = cnt[val];
  del_node(val, freq);

  cnt[val]++;
  freq++;

  insert_node(val, freq);
  if (freq > max_freq) max_freq = freq;
}

void remv(int val) {
  int freq = cnt[val];
  del_node(val, freq);

  if (freq == max_freq && head[freq] == -1) max_freq--;
  freq--;
  cnt[val]--;

  insert_node(val, freq);
}

struct QUERY {
  int l, r;
  int lim;
  int index;

  friend bool operator<(const QUERY& a, const QUERY& b) {
    if (get_index[a.l] != get_index[b.l]) return a.l < b.l;
    else if (get_index[a.l] & 1) return a.r < b.r;
    else return a.r > b.r;
  }
} task[maxn];

#define _debug 1
int main() {
  cin.tie(0)->sync_with_stdio(0);

  #if _debug == 1
  freopen("input.inp", "r", stdin);
  #else

  #endif // _debug

  memset(head, -1, sizeof head);
  memset(previous, -1, sizeof previous);
  memset(nxt, -1, sizeof nxt);
  memset(res, -1, sizeof res);

  for (int i = 0; i < maxn; i++) {
    insert_node(i, 0);
  }

  int n, q;
  cin >> n >> q;
  int sz = max(1, n / (int)sqrt(q));
  for (int i = 1; i <= n; i++) {
    cin >> A[i];
    get_index[i] = (i-1)/sz + 1;
  }

  for (int i = 1; i <= q; i++) {
    cin >> task[i].l >> task[i].r >> task[i].lim;
    task[i].index = i;
  }
  sort(task + 1, task + q + 1);

  int pt1 = 1;
  int pt2 = 0;
  for (int i = 1; i <= q; i++) {
    while (pt1 > task[i].l) {pt1--; add(A[pt1]);}
    while (pt2 < task[i].r) {pt2++; add(A[pt2]);}

    while (pt1 < task[i].l) {remv(A[pt1]); pt1++;}
    while (pt2 > task[i].r) {remv(A[pt2]); pt2--;}

    if (max_freq >= task[i].lim && head[max_freq] != -1) {
      res[task[i].index] = head[max_freq];
    }
  }

  for (int i = 1; i <= q; i++) cout << res[i] << '\n';

}
