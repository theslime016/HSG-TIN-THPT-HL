#include <bits/stdc++.h>
using namespace std;

struct uf {
  vector<int> data;
  vector<int> bucket;
  uf(int n) {
    data.assign(n + 1, 0);
    iota(data.begin(), data.end(), 0);
    bucket.assign(n + 1, 1);
  }

  int fnd(int index) {
    if (index == data[index])
      return index;
    return data[index] = fnd(data[index]);
  }

  void proc(int a, int b) {
    a = fnd(a);
    b = fnd(b);
    if (a != b) {
      if (bucket[a] > bucket[b])
        swap(a, b);
      data[b] = a;
      bucket[a] += bucket[b];
    }
  }
};

const int maxn = 1e5 + 5;
long long A[maxn];

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int q;
  cin >> q;
  while (q--) {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
      cin >> A[i];
    }

    uf dsu(n);
    stack<int> st;
    for (int i = 1; i <= n; i++) {
      while (!st.empty() && A[st.top()] < A[i])
        st.pop();
      if (!st.empty() && A[st.top()] == A[i])
        dsu.proc(st.top(), i);
      st.push(i);
    }

    for (int i = 1; i <= n; i++) {
      int g = dsu.fnd(i);
      cout << dsu.bucket[g] - 1 << ' ';
    }
    cout << '\n';
  }
}
