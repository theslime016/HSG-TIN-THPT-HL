#include <bits/stdc++.h>
using namespace std;

struct child {
  int a, b, c;
};

struct uf {
  int n;
  vector<int> data[5];
  uf(int n) {
    this->n = n;
    for (int i = 1; i <= 3; i++) {
      data[i].assign(n + 1, 0);
    }
  }

  void update(int type, int index, int val) {
    if (index == 0)
      return;
    for (int i = index; i <= n; i += i & -i) {
      data[type][i] += val;
    }
  }

  child fetch(int index) {
    child pref{0, 0, 0};
    for (int i = index; i > 0; i -= i & -i) {
      pref.a += data[1][i];
      pref.b += data[2][i];
      pref.c += data[3][i];
    }
    return pref;
  }

  void preprocess() {
    for (int i = 1; i <= 3; i++) {
      for (int j = 1; j <= n; j++) {
        int parent = j + (j & -j);
        if (parent <= n)
          data[i][parent] += data[i][j];
      }
    }
  }
};

int main() {
  cin.tie(0)->sync_with_stdio(false);

  freopen("SECURE.INP", "r", stdin);
  freopen("SECURE.OUT", "w", stdout);

  int n, q;
  cin >> n >> q;

  string S;
  S.resize(n + 1);
  uf BIT(n);
  for (int i = 1; i <= n; i++) {
    cin >> S[i];
    int type = -1;
    if (isupper(S[i])) {
      type = 1;
    } else if (islower(S[i])) {
      type = 2;
    } else if (isdigit(S[i])) {
      type = 3;
    }
    BIT.data[type][i]++;
  }

  BIT.preprocess();
  auto swp = [&](int x, int y) {
    int type = -1;
    if (isupper(S[x])) {
      type = 1;
    } else if (islower(S[x])) {
      type = 2;
    } else if (isdigit(S[x])) {
      type = 3;
    }
    BIT.update(type, x, -1);
    BIT.update(type, y, 1);
  };

  while (q--) {
    int t, l, r;
    cin >> t >> l >> r;
    if (t == 1) {
      swp(l, r);
      swp(r, l);
      swap(S[l], S[r]);
    } else if (t == 2) {
      child sr = BIT.fetch(r);
      child sl = BIT.fetch(l - 1);
      cout << (sr.a - sl.a > 0 && sr.b - sl.b > 0 && sr.c - sl.c > 0 &&
               r - l + 1 >= 6)
           << '\n';
    }
  }

  return 0;
}
