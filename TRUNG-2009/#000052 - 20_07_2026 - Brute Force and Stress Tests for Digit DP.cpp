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
  system("g++ main.cpp -o brute -O3 -fopenmp");
  system("g++ test.cpp -o main -Wall -Wextra -fsanitize=undefined,address");
  const int test = 100;
  for (int i = 1; i <= test; i++) {
    long long l = rnd(1, 1e9);
    long long r = rnd(l, 1e9);
    int k = rnd(1, 20);
    cout << l << ' ' << r << ' ' << k << ' ' << flush;
    system("./brute");
    system("./main");
    if (system("diff output.out output.ans > /dev/null") != 0) {
      cerr << "TEST " << i << " !!!!!";
      break;
    } else {
      cerr << "TEST " << i << " PASS" << endl;
    }
  }

  return 0;
}
