#include <bits/stdc++.h>
using namespace std;

#define _debug 0

#if _debug == 1
#define debug(x) cerr << #x << ':' << (x) << ' ';
#define newline cerr << '\n';

#else
#define debug(x)
#define newline

#endif // _debug

const int maxn = 3e5 + 5;
vector<int> A[maxn];
long long req[maxn];
long long res[maxn];

struct TASK {
  int l, r;
  long long val;
} task[maxn];

struct POS {
  int l, r;
  int index;
};
vector<POS> wait[maxn];

long long fenwick[maxn];

void update(int index, const long long& val) {
  for (; index < maxn; index += index & -index) {
    fenwick[index] += val;
  }
}

long long fetch(int index) {
  long long res = 0;
  for (; index > 0; index -= index & -index) {
    res += fenwick[index];
  }
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

  int n, m;
  cin >> n >> m;
  for (int i = 1; i <= m; i++) {
    int x;
    cin >> x;
    A[x].push_back(i);
  }

  for (int i = 1; i <= n; i++) cin >> req[i];

  int k;
  cin >> k;
  for (int i = 1; i <= k; i++) {
    cin >> task[i].l >> task[i].r >> task[i].val;
  }

  for (int i = 1; i <= n; i++) {
    int mid = (k + 1) >> 1;
    wait[mid].push_back({1, k, i});
  }


  memset(res, -1, sizeof res);
  POS temp;
  int proc = n;
  while (proc > 0) {

    memset(fenwick, 0, sizeof fenwick);
    for (int i = 1; i <= k; i++) {
      if (task[i].l <= task[i].r) {
        update(task[i].l, task[i].val);
        update(task[i].r + 1, -task[i].val);
      } else {
        update(task[i].l, task[i].val);

        update(1, task[i].val);
        update(task[i].r + 1, -task[i].val);
      }

      while (!wait[i].empty()) {
        temp = wait[i].back();
        wait[i].pop_back();

        int mid = temp.l + ((temp.r - temp.l) >> 1);
        long long get = 0;
        for (int x : A[temp.index]) {
          get += fetch(x);
          if (get >= req[temp.index]) break;
        }

#if _debug == 1

        debug(i);
        debug(get);
        newline;

#endif // _debug

        if (get >= req[temp.index]) {
          res[temp.index] = i;
        }

        if (temp.l == temp.r) {
          proc--;
          continue;
        }

        int l, r;
        if (get >= req[temp.index]) {
          l = temp.l;
          r = mid;
        } else {
          l = mid + 1;
          r = temp.r;
        }
        int new_mid = l + ((r - l) >> 1);
        wait[new_mid].push_back({l, r, temp.index});
      }


    }


  }

  for (int i = 1; i <= n; i++) {
    if (res[i] == -1) cout << "NIE" << '\n';
    else cout << res[i] << '\n';
  }

}
