#include <bits/stdc++.h>
using namespace std;

long long random(long long l, long long r, mt19937_64 &rng)
{
  return uniform_int_distribution<long long>(l, r)(rng);
}

int main(int argc, char *argv[])
{
  ios::sync_with_stdio(false);
  cin.tie(0);

  freopen("LIXI.INP", "w", stdout);

  long seed = (argc > 1) ? stoll(argv[1]) : (chrono::steady_clock::now().time_since_epoch().count());
  mt19937_64 rng(seed);
  cerr << seed << '\n';

  int n = random(1, 1'000'000, rng);
  cout
      << n << '\n';
  for (long long i = 0; i < n; i++)
  {
    int a = random(1, 1'000'000, rng);
    cout << a << ' ';
  }

  return 0;
}