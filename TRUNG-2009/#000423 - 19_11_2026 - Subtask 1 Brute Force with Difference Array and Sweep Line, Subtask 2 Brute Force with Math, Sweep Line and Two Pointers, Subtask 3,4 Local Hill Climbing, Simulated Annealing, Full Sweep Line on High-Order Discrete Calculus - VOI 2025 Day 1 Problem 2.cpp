#include <bits/stdc++.h>
using namespace std;

#define _debug 0

#if _debug == 1
void logout() {
  cerr << endl;
}
template<typename H, typename... T>
void logout(H h, T... t) {
  cerr << h << ", ";
  logout(t...);
}
#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:" << endl, logout(__VA_ARGS__)
#define debugtitle cerr << __PRETTY_FUNCTION__ << " line: " << __LINE__ << endl
#define newline cerr << endl

#else
#define debug(...) (void(0))
#define debugtitle (void(0))
#define newline (void(0))

#endif // _debug

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
long long rnd(long long l, long long r) {
  return uniform_int_distribution<long long>(l, r)(rng);
}
long double frnd(long double l, long double r) {
  return uniform_real_distribution<long double>(l, r)(rng);
}

const int maxk = 2005;
const long long inf = 1e18;

long long n;
int k;

pair<long long, long long> task[maxk];

long long f(long long x0, long long x1) {
  return 2 * x1 - x0;
}

struct SUB1 {
  map<long long, int> diff;

  void add(long long p, long long x1, long long x2) {
    long long start = f(p, x1);
    long long end = f(p, x2);
    diff[start]++;
    diff[end]--;
  }

  long long res = 0;
  void check(long long a, long long b) {
    diff.clear();
    for (int i = 1; i < k; i++) {
      long long l = task[i].second;
      long long r = task[i+1].first;
      add(a, l, r);
      add(b, l, r);
    }
    if (task[1].first != 0) {
      add(a, 0, task[1].first);
      add(b, 0, task[1].first);
    }
    if (task[k].second != n) {
      add(a, task[k].second, n);
      add(b, task[k].second, n);
    }

    int cnt = 0;
    long long current = 0;
    long long last_x = inf;
    for (const auto& x : diff) {
      cnt += x.second;
      if (last_x != inf)
        current += x.first - last_x;
      if (cnt > 0) {
        last_x = x.first;
      } else {
        last_x = inf;
      }
    }
    res = max(res, current);
  }

  void solve() {
    for (long long i = 0; i <= n; i++) {
      for (long long j = i + 1; j <= n; j++) {
        check(i, j);
      }
    }
    cout << res;
  }
} sub1;

struct SUB2 {
  vector<pair<long long, long long>> diff1, diff2;
  vector<pair<long long, long long>> A;

  void add(long long p, long long x1, long long x2, int type) {
    long long left = f(p, x1);
    long long right = f(p, x2);
    if (type == 1) {
      diff1.push_back({left, right});
    } else if (type == 2) {
      diff2.push_back({left, right});
    }
  }

  long long check(long long a, long long b) {
    diff1.clear();
    diff2.clear();
    A.clear();
    if (task[1].first != 0) {
      add(a, 0, task[1].first, 1);
      add(b, 0, task[1].first, 2);
    }
    for (int i = 1; i < k; i++) {
      add(a, task[i].second, task[i+1].first, 1);
      add(b, task[i].second, task[i+1].first, 2);
    }
    if (task[k].second != n) {
      add(a, task[k].second, n, 1);
      add(b, task[k].second, n, 2);
    }

    int l = 0, r = 0;
    while (l < diff1.size() && r < diff2.size()) {
      if (diff1[l] < diff2[r]) {
        A.push_back(diff1[l++]);
      } else {
        A.push_back(diff2[r++]);
      }
    }

    while (l < diff1.size())
      A.push_back(diff1[l++]);
    while (r < diff2.size())
      A.push_back(diff2[r++]);

    if (A.empty())
      return 0;

    long long local = 0;
    pair<long long, long long> current = A.front();
    for (int i = 1; i < A.size(); i++) {
      if (A[i].first <= current.second) {
        current.first = min(current.first, A[i].first);
        current.second = max(current.second, A[i].second);
      } else {
        local += current.second - current.first;
        current = A[i];
      }
    }
    local += current.second - current.first;
    return local;
  }

  void solve() {
    long long res = 0;
    for (long long i = 0; i <= n; i++) {
      for (long long j = i + 1; j <= n; j++) {
        res = max(res, check(i, j));
      }
    }
    cout << res;
  }
} sub2;

struct HEURISTIC {
  vector<pair<long long, long long>> diff;
  void add(long long l, long long r) {
    diff.push_back({f(0, l), f(0, r)});
  }

  long long total_len = 0;
  void create() {
    diff.clear();
    if (task[1].first != 0)
      add(0, task[1].first);
    for (int i = 1; i < k; i++) {
      add(task[i].second, task[i+1].first);
    }
    if (task[k].second != n)
      add(task[k].second, n);

    for (const auto& x : diff)
      total_len += x.second - x.first;
  }

  long long check(long long d) {
    long long overlap = 0;
    for (int i = 0, j = 0; i < diff.size() && j < diff.size(); ) {
      long long l1 = diff[i].first;
      long long r1 = diff[i].second;
      long long l2 = diff[j].first - d;
      long long r2 = diff[j].second - d;

      long long left = max(l1, l2), right = min(r1, r2);
      if (left < right)
        overlap += right - left;
      if (r1 < r2)
        i++;
      else
        j++;
    }
    return 2 * total_len - overlap;
  }

  long long get_d() {
    int i = rnd(0, diff.size() - 1);
    int j = rnd(0, diff.size() - 1);
    if (i > j)
      swap(i, j);
    long long cand[] = {
      diff[j].first - diff[i].first,
      diff[j].first - diff[i].second,
      diff[j].second - diff[i].first,
      diff[j].second - diff[i].second,
    };
    long long d = cand[rnd(0, 3)];
    return max(1LL, min(n, d));
  }

  long long hill_climb(long long d, long long val) {
    for (long long step : {
           10000, 1000, 100, 10, 1
         }) {
      bool found = true;
      while (found) {
        if ((double)clock() / CLOCKS_PER_SEC > 1.99)
          return val;
        found = false;
        for (long long dir : {
               -1, 1
             }) {
          long long new_d = d + dir * step;
          if (new_d < 1 || new_d > n)
            continue;

          long long new_val = check(new_d);
          if (new_val > val) {
            val = new_val;
            d = new_d;
            found = true;
          }
        }
      }
    }

    return val;
  }

  long long res = 0;
  long long best_d = 0;
  void simulate() {
    int break_point = !diff.empty() && rnd(0, 1);
    long long d = break_point ? get_d() : rnd(1, n);
    long long current = check(d);
    long long best = current;

    double T = break_point ? max(1000LL, n / 1000) : n;
    double cooling_rate = 0.99;
    int step = 0;
    long long local_best_d = d;
    while (T > 1) {
      long long jump = (long long)T;
      if ((++step & 63) == 0 && (double)clock() / CLOCKS_PER_SEC > 1.975)
        break;

      long long new_d = d + rnd(-jump, jump);
      new_d = max(1LL, min(n, new_d));

      long long new_val = check(new_d);
      if (new_val > best) {
        best = new_val;
        local_best_d = new_d;
      }

      long long delta = current - new_val;
      if (delta < 0 || exp(-delta / T) > frnd(0, 1)) {
        current = new_val;
        d = new_d;
      }

      T *= cooling_rate;
    }

    if (best > res) {
      res = best;
      best_d = local_best_d;
    }
  }

  void solve() {
    create();
    res = check(0);
    best_d = 0;
    long long temp = check(n);
    if (temp > res) {
      res = temp;
      best_d = n;
    }

    while ((double)clock() / CLOCKS_PER_SEC <= 1.975) {
      simulate();
    }
    res = max(res, hill_climb(best_d, res));

    cout << res;
  }

} heuristic;

struct FULL : HEURISTIC {
  vector<pair<long long, int>> events; /// d, f''(d)

  void solve() {
    create();
    if (diff.empty()) {
      cout << 0;
      return;
    }

    for (int i = 0; i < diff.size(); i++) {
      long long a = diff[i].first;
      long long b = diff[i].second;
      for (int j = i; j < diff.size(); j++) {
        long long c = diff[j].first;
        long long e = diff[j].second;

        events.push_back({c - b, 1});
        events.push_back({c - a, -1});

        events.push_back({e - b, -1});
        events.push_back({e - a, 1});
      }
    }
    events.push_back({1LL, 0});
    events.push_back({n, 0});

    sort(events.begin(), events.end());

    long long f = 0;
    long long s = 0;
    long long overlap = inf;
    long long last_d = inf;
    for (const auto& x : events) {
      long long d = x.first;
      int val = x.second;
      if (d != last_d && last_d != inf) {
        long long len = d - last_d;
        f += len * s;
        if (d >= 1LL && d <= n)
          overlap = min(overlap, f);
      }

      s += val;
      last_d = d;
    }
    long long res = 2*total_len - overlap;

    cout << res;
  }
} full;

int main() {
  cin.tie(0)->sync_with_stdio(0);

#if _debug == 1
  freopen("input.inp", "r", stdin);

#elif _debug == 2
  freopen("input.inp", "r", stdin);

#else
  freopen("ROAI.INP", "r", stdin);
  freopen("ROAI.OUT", "w", stdout);

#endif // _debug

  cin >> n >> k;
  for (int i = 1; i <= k; i++)
    cin >> task[i].first >> task[i].second;


  if (n <= 200) {
    sub1.solve();
    return 0;
  }

  if (n <= 2000 && k <= 20) {
    sub2.solve();
    return 0;
  }

  if (n <= 20000 || k == 500) {
    heuristic.solve();
    return 0;
  }

  full.solve();
}
