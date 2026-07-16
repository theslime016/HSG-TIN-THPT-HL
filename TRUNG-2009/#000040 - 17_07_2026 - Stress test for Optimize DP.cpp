/// Checker.cpp
#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  system(("g++ main.cpp -o gen"));
  system(("g++ test.cpp -o brute -O3 -fopenmp"));
  // system(("g++ test2.cpp -o brute"));
  system(("g++ beta.cpp -o main"));

  long long test = 313;
  for (int i = 1; i <= test; i++) {
    system("./gen");
    system("./brute");
    system("./main");
    if (system("diff output.out sample.out > /dev/null") != 0) {
      cerr << "TEST " << i << " !!!!!";
      break;
    } else {
      cerr << "TEST " << i << " PASS" << endl;
    }
  }

  return 0;
}

/// main.cpp
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

  int type = rnd(1, 100);
  int n;
  if (type <= 50) {
    n = rnd(1, 10);
  } else {
    n = rnd(100, 500);
  }

  int m = rnd(1, 20 <= n ? 20 : n), k = rnd(1, 20 <= n ? 20 : n);
  cout << n << ' ' << m << ' ' << k << '\n';
  int sz = rnd(0, 25) * 0 + 25;
  for (int i = 0; i < n; i++) {
    cout << (char)(rnd(0, sz) + 'a');
  }
  cout << '\n';
  for (int j = 0; j < m; j++) {
    cout << (char)(rnd(0, sz) + 'a');
  }

  return 0;
}

/// test.cpp
#include <bits/stdc++.h>
using namespace std;

int n, m, k;
string a, b;
atomic<long long> res(0);
void backtrack(int i = 0, int j = 0, int l = 0, bool x = false, int depth = 1) {
  if (j == m && l == k) {
    res.fetch_add(1, memory_order_relaxed);
    return;
  }
  if (i >= n || j >= m || l > k) {
    return;
  }
  if (depth <= 12) {
    if (a[i] == b[j]) {
#pragma omp task shared(res)
      {
        backtrack(i + 1, j + 1, l + 1, true, depth + 1);
      }
      if (x) {
#pragma omp task shared(res)
        {
          backtrack(i + 1, j + 1, l, true, depth + 1);
        }
      }
      backtrack(i + 1, j, l, false, depth + 1);
#pragma omp taskwait
    } else {
      backtrack(i + 1, j, l, false, depth);
    }
  } else {
    if (a[i] == b[j]) {
      backtrack(i + 1, j + 1, l + 1, true, depth);
      if (x)
        backtrack(i + 1, j + 1, l, true, depth);
    }
    backtrack(i + 1, j, l, false, depth);
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  freopen("input.inp", "r", stdin);
  freopen("sample.out", "w", stdout);
  cin >> n >> m >> k;
  cin >> a >> b;

  {
#pragma omp parallel
    {
#pragma omp single
      backtrack();
    }
  }
  cout << res;

  return 0;
}

/// test2.cpp
#include <bits/stdc++.h>
using namespace std;

int n, m, k;
string a, b;
long long res = 0;
void backtrack(int i = 0, int j = 0, int l = 0, bool x = false) {
  if (j == m && l == k) {
    res++;
    return;
  }
  if (i >= n || j >= m || l > k) {
    return;
  }
  if (a[i] == b[j]) {
    backtrack(i + 1, j + 1, l + 1, true);
    if (x)
      backtrack(i + 1, j + 1, l, true);
  }
  backtrack(i + 1, j, l, false);
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  freopen("input.inp", "r", stdin);
  freopen("sample.out", "w", stdout);
  cin >> n >> m >> k;
  cin >> a >> b;
  backtrack();
  cout << res;

  return 0;
}
