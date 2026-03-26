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

  freopen("TIEUTHU.INP", "w", stdout);

  long seed = (argc > 1) ? stoll(argv[1]) : (chrono::steady_clock::now().time_since_epoch().count());
  mt19937_64 rng(seed);
  cerr << seed << '\n';

  int n = random(1, 100, rng);
  int m = random(1, 100, rng);
  cout
      << n << '\n';
  for (int i = 0; i < m; i++)
  {
    for (int j = 0; j < n; j++)
    {
      cout << random(0, 1, rng) << ' ';
    }
    cout << '\n';
  }

  for (int i = 0; i < m; i++)
  {
    for (int j = 0; j < n; j++)
    {
      cout << random(-1'000'000, 1'000'000, rng) << ' ';
    }
    cout << '\n';
  }

  return 0;
}