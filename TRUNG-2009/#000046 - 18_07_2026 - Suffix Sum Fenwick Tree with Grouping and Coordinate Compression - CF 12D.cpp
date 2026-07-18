#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
#ifndef NDEBUG
#define NDEBUG
#endif

struct lady {
  long long a, b, c;
};

struct FWT {
  int n;
  vector<long long> data;
  FWT(int num) {
    this->n = num;
    this->data.assign(num + 1, 0);
  }

  // long long query(int i) {
  //   long long pref = 0;
  //   for (; i > 0; i -= i & (-i)) {
  //     pref += data[i];
  //   }
  //   return pref;
  // }

  void process(int index, long long value) {
    for (; index <= n; index += index & (-index)) {
      data[index] = max(data[index], value);
    }
  }

  long long fetch(int index) {
    long long max_val = -1;
    for (; index > 0; index -= index & (-index)) {
      max_val = max(max_val, data[index]);
    }
    return max_val;
  }

  // void process(int index, long long value) {
  //   for (; index > 0; index -= index & (-index)) {
  //     data[index] = max(data[index], value);
  //   }
  // }

  // long long fetch(int index) {
  //   long long max_val = -1;
  //   for (; index <= n; index += index & (-index)) {
  //     max_val = max(max_val, data[index]);
  //   }
  //   return max_val;
  // }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int n;
  cin >> n;
  vector<lady> A(n);
  {
    vector<long long> B(n);

    for (int i = 0; i < n; i++)
      cin >> A[i].a;
    for (int i = 0; i < n; i++)
      cin >> A[i].c;
    for (int i = 0; i < n; i++) {
      cin >> A[i].b;
      B[i] = A[i].b;
    }

    sort(B.begin(), B.end(), greater<long long>());
    // sort(B.begin(), B.end());
    B.erase(unique(B.begin(), B.end()), B.end());
    for (auto &x : A) {
      auto it = lower_bound(B.begin(), B.end(), x.b, greater<long long>());
      // auto it = lower_bound(B.begin(), B.end(), x.b);
      x.b = (it - B.begin()) + 1;
      // cout << x.b << ' ';
    }
    // cout << endl << endl;
  }

  sort(A.begin(), A.end(), [](auto &x, auto &y) { return x.a > y.a; });

  // for (const auto &x : A)
  //   cout << x.a << ' ' << x.b << ' ' << x.c << '\n';
  // cout << '\n';

  FWT BIT(n);
  long long res = 0;
  int i = 0;
  while (i < n) {
    int j = i;
    while (j < n && A[i].a == A[j].a)
      j++;
    for (int k = i; k < j; k++) {
      if (BIT.fetch(A[k].b - 1) > A[k].c)
        // if (BIT.fetch(A[k].b + 1) > A[k].c)
        res++;
    }
    for (int k = i; k < j; k++) {
      BIT.process(A[k].b, A[k].c);
    }

    // for (int index = 1; index < BIT.data.size(); index++)
    //   cout << BIT.data[index] << ' ';
    // cout << '\n';

    i = j;
  }
  cout << res;

  return 0;
}
