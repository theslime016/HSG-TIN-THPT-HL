#include <bits/stdc++.h>
using namespace std;

const int maxn = 5e4 + 5;
int n, q;
long long A[maxn];
vector<int> B;
long long segment[4 * maxn];
long long fenwick[maxn];
void make_segment(int index, int l, int r) {
  if (l == r) {
    segment[index] = 0;
    return;
  }

  memset(fenwick, 0, sizeof fenwick);
  for (int i = r; i >= l; i--) {
    int fnd = lower_bound(B.begin(), B.end(), A[i]) - B.begin() + 1;
    for (int j = fnd - 1; j > 0; j -= j & -j) {
      segment[index] += fenwick[j];
    }

    for (int j = fnd; j < maxn; j += j & -j) {
      fenwick[j]++;
    }
  }

  int mid = l + (r - l) / 2;
  make_segment(index * 2, l, mid);
  make_segment(index * 2 + 1, mid + 1, r);
}

long long fetch(int index, int l, int r, int ql, int qr) {
  if (l > qr || r < ql)
    return 0;
  if (l >= ql && r <= qr)
    return segment[index];

  int mid = l + (r - l) / 2;
  return fetch(index * 2, l, mid, ql, qr) +
         fetch(index * 2 + 1, mid + 1, r, ql, qr);
}

int main() {
  cin.tie(0)->sync_with_stdio(0);

  cin >> n >> q;
  B.reserve(n);

  for (int i = 1; i <= n; i++) {
    cin >> A[i];
    B.push_back(A[i]);
  }
  sort(B.begin(), B.end());
  B.erase(unique(B.begin(), B.end()), B.end());

  make_segment(1, 1, n);

  cerr << segment[1];

  while (q--) {
    int l, r;
    cin >> l >> r;
    cout << fetch(1, 1, n, l, r) << '\n';
  }
}
