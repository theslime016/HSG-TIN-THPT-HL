#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <bits/stdc++.h>
using namespace std;

const int maxn = 5e4 + 5;
const int maxnode = 300;
long long A[maxn];
int n, q;

int sz, num_block;
int get_id[maxn];
int lblock[maxnode], rblock[maxnode];
long long res[maxn];
long long fenwick[maxn];
void update(int index, const long long& val) {
  for (; index > 0; index -= index & -index) {
    fenwick[index] += val;
  }
}

long long fetch(int index) {
  long long res = 0;
  for (; index < maxn; index += index & -index) {
    res += fenwick[index];
  }
  return res;
}

struct TASK {
  int l, r;
  int index;

  bool operator<(const TASK& other) {
    int tag = get_id[this->l];
    int other_tag = get_id[other.l];
    if (tag != other_tag) return tag < other_tag;
    else if (tag & 1) return this->r < other.r;
    else return this->r > other.r;
  }

} task[maxn];

#define _debug 0
int main() {
  cin.tie(0)->sync_with_stdio(0);

#if _debug == 1
  freopen("input.inp", "r", stdin);
#else
  freopen("CHECKINV.inp", "r", stdin);
  freopen("CHECKINV.out", "w", stdout);
#endif // _debug

  cin >> n >> q;

  vector<long long> B;
  B.reserve(n);
  for (int i = 1; i <= n; i++) {
    cin >> A[i];
    B.push_back(A[i]);
  }

  sort(B.begin(), B.end());
  B.erase(unique(B.begin(), B.end()), B.end());
  for (int i = 1; i <= n; i++) {
    A[i] = lower_bound(B.begin(), B.end(), A[i]) - B.begin() + 1;
  }

  sz = max(1, n / (int)sqrt(q));
  num_block = (n-1)/sz + 1;

  for (int i = 1; i <= n; i++) {
    get_id[i] = (i-1)/sz + 1;
  }
  for (int i = 1; i <= num_block; i++) {
    lblock[i] = (i-1)*sz + 1;
    rblock[i] = min(n, i * sz);
  }

  for (int i = 1; i <= q; i++) {
    cin >> task[i].l >> task[i].r;
    task[i].index = i;
  }

  sort(task+1, task+q+1);
  int pt1 = 1, pt2 = 0;
  long long track = 0;
  for (int i = 1; i <= q; i++) {
    while (pt1 > task[i].l) {
      pt1--;
      int fnd = (A[pt1]);
      int len = pt2 - pt1;
      track += len - fetch(fnd);
      update(fnd, 1);
    }
    while (pt2 < task[i].r) {
      pt2++;
      int fnd = (A[pt2]);
      track += fetch(fnd+1);
      update(fnd, 1);
    }

    while (pt1 < task[i].l) {
      int fnd = (A[pt1]);
      int len = pt2 - pt1;
      update(fnd, -1);
      track -= len - fetch(fnd);
      pt1++;
    }
    while (pt2 > task[i].r) {
      int fnd = (A[pt2]);
      update(fnd, -1);
      track -= fetch(fnd+1);
      pt2--;
    }

    res[task[i].index] = track;
  }

  for (int i = 1; i <= q; i++) cout << res[i] << '\n';

}
