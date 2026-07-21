#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  system("g++ test.cpp -o gen");
  system("g++ test2.cpp -o brute -O3 -fopenmp");
  system(
      "g++ undefined.cpp -o main -Wall -Wextra -fsanitize=undefined,address");
  int test = 1000;
  for (int i = 1; i <= test; i++) {
    system("./gen");
    system("./brute");
    system("./main");
    if (system("diff output.out output.ans > /dev/null") != 0) {
      cerr << "TEST " << i << "!!!!!!!!!!!!";
      break;
    } else {
      cerr << "TEST " << i << "PASS\n";
    }
  }

  return 0;
}



/// test.cpp
#include <bits/stdc++.h>
using namespace std;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
long long rnd(long long l, long long r) {
  return uniform_int_distribution<long long>(l, r)(rng);
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  freopen("input.inp", "w", stdout);

  long long a, b;
  int t = rnd(1, 100);
  if (t <= 20) {
    a = rnd(1, 100);
    b = rnd(1, 1000);
  }

  // else if (t <= 40) {
  //   a = rnd(100, 1000);
  //   b = rnd(1000, 10'000);
  // }

  else {
    a = rnd(1000, 1000'00);
    b = rnd(10'000, 1e14);
  }

  int n = rnd(1, a);
  long long r = rnd(1, b), l = rnd(1, min(a, r));
  cout << n << ' ' << l << ' ' << r << '\n';
  for (int i = 1; i <= n; i++) {
    cout << rnd(1, 1e5) << ' ';
  }

  return 0;
}


/// test2.cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  freopen("input.inp", "r", stdin);
  freopen("output.out", "w", stdout);

  int n;
  long long l, r;
  cin >> n >> l >> r;
  vector<long long> pref(n + 1, 0);
  long long res = 0;
  for (int i = 1; i <= n; i++) {
    long long x;
    cin >> x;
    pref[i] = pref[i - 1] + x;
  }

#pragma omp parallel for reduction(+ : res) schedule(dynamic)
  for (int i = 1; i <= n; i++) {
    for (int j = 0; j < i; j++) {
      long long val = pref[i] - pref[j];
      if (val >= l && val <= r)
        res++;
    }
  }
  cout << res;

  return 0;
}
