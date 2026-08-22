#include <bits/stdc++.h>
using namespace std;

#define leftc(x) (x << 1)
#define rightc(x) (x << 1 | 1)

const int maxn = 2e5 + 5;
struct node {
  long long sum;
  long long lazy;
} segment[maxn * 4];
long long A[maxn];

void pushup(int index) {
  segment[index].sum = segment[leftc(index)].sum + segment[rightc(index)].sum;
}

void pushdown(int index, int l, int r) {
  if (segment[index].lazy) {
    int mid = l + (r - l) / 2;
    long long tag = segment[index].lazy;

    segment[leftc(index)].sum += tag * (mid - l + 1);
    segment[rightc(index)].sum += tag * (r - mid);

    segment[leftc(index)].lazy += tag;
    segment[rightc(index)].lazy += tag;

    segment[index].lazy = 0;
  }
}

void build(int index, int l, int r) {
  segment[index].lazy = 0;
  if (l == r) {
    segment[index].sum = A[l];
    return;
  }
  int mid = l + (r - l) / 2;
  build(leftc(index), l, mid);
  build(rightc(index), mid + 1, r);
  pushup(index);
}

void update(int index, int l, int r, int ql, int qr, const long long &val) {
  if (l > qr || r < ql)
    return;
  if (l >= ql && r <= qr) {
    segment[index].sum += val * (r - l + 1);
    segment[index].lazy += val;
    return;
  }

  pushdown(index, l, r);
  int mid = l + (r - l) / 2;
  update(leftc(index), l, mid, ql, qr, val);
  update(rightc(index), mid + 1, r, ql, qr, val);
  pushup(index);
}

long long fetch(int index, int l, int r, int ql, int qr) {
  if (l > qr || r < ql)
    return 0;
  if (l >= ql && r <= qr) {
    return segment[index].sum;
  }

  pushdown(index, l, r);

  int mid = l + (r - l) / 2;
  return fetch(leftc(index), l, mid, ql, qr) +
         fetch(rightc(index), mid + 1, r, ql, qr);
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  int n, q;
  cin >> n >> q;
  for (int i = 1; i <= n; i++)
    cin >> A[i];
  build(1, 1, n);

  while (q--) {
    int type;
    cin >> type;
    if (type == 1) {
      int l, r;
      long long val;
      cin >> l >> r >> val;
      update(1, 1, n, l, r, val);
    } else {
      int k;
      cin >> k;
      cout << fetch(1, 1, n, k, k) << '\n';
    }
  }
}
