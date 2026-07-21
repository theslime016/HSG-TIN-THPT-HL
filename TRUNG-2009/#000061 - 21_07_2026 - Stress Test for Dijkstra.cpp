#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  system("g++ undefined.cpp -o gen");
  system("g++ test2.cpp -o brute");
  system("g++ main.cpp -o main -Wall -Wextra -fsanitize=undefined,address");
  int test = 100;
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



/// undefined.cpp
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

  int a = 0;
  int s = rnd(1, 100);
  // a = rnd(1, 10);
  if (s <= 40) {
    a = rnd(1, 10);
  } else if (s <= 60) {
    a = rnd(10, 100);
  } else {
    a = rnd(100, 10000);
  }

  int n = rnd(1, a), m = rnd(1, a);
  cout << n << ' ' << m << '\n';
  int w = rnd(1, max(1, (int)log2(a)));
  cout << w << '\n';
  while (w--) {
    int type = rnd(1, 2);
    int r1, r2, c1, c2;
    if (type == 1) {
      r1 = r2 = rnd(1, n);
      c1 = rnd(1, m);
      c2 = rnd(c1, m);
    } else {
      c1 = c2 = rnd(1, m);
      r1 = rnd(1, n);
      r2 = rnd(r1, n);
    }
    cout << r1 << ' ' << c1 << ' ' << r2 << ' ' << c2 << '\n';
  }

  return 0;
}
