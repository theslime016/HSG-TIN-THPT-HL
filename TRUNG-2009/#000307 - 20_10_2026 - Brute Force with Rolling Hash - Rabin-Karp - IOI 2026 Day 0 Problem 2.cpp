#include <bits/stdc++.h>
using namespace std;

#define _debug 0

#if _debug == 1
#define debug(x) cerr << #x << ':' << (x) << ' ';
#define newline cerr << '\n';

#else
#define debug(x)
#define newline

#endif // _debug

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
long long rnd(long long l, long long r) {
  return uniform_int_distribution<long long>(l, r)(rng);
}

string A;
int n;

const int inf = 1e9;
const int maxn = 1e3 + 5;
const int base = rnd(300, 500);
const long long mod = 1e9 + 7;
long long hashing[maxn];
long long power[maxn];

void make_hash() {
  power[0] = 1;
  for (int i = 1; i <= n; i++) {
    hashing[i] = ((hashing[i-1] * base) % mod + A[i]) % mod;
    power[i] = (power[i-1] * base) % mod;
  }
}

long long get_hash(int l, int r) {
  return ((hashing[r] - (hashing[l-1] * power[r - l + 1])%mod) + mod) % mod;
}

bool check(int index, int len) {
  int i = index;
  int j = index + len;


  return get_hash(i, i + len - 1) == get_hash(j, j + len - 1);


  for (; len > 0; len--, i++, j++) {
    if (A[i] != A[j]) return false;
  }
  return true;
}

int count_duplicated(string S) {
  swap(A, S);

  n = A.size();
  A = '-' + A;
  make_hash();

  vector<string> t;
  int n = A.size();
  for (int len = 1; len <= n/2; len++) {
    for (int i = 1; i + 2*len - 1 <= n; i++) {
      if (check(i, len)) {
        t.push_back(A.substr(i, 2*len));
      }
    }

  }

  sort(t.begin(), t.end());
  t.erase(unique(t.begin(), t.end()), t.end());
  return t.size();
}



string find_weakest() {
    return "0110011100010111001011000111001011100010110001110010110001011100101100111000101110010110001110010111";
}

string find_strongest() {
    return "0101111111011111111011111110111111110111111101111110111111101111110111110111111011111011110111011010";
}

#if _debug == 1

void check1() {
  string temp;
  cin >> temp;
  cout << count_duplicated(temp);
}

void make_test2() {
  int max_string_len = 16;
  for (int string_len = 1; string_len <= max_string_len; string_len++) {
    debug(string_len);
    newline;
    string temp(string_len, '0');
    vector<string> best_max, best_min;
    int max_cnt = 0;
    int min_cnt = inf;
    while (true) {

      int cnt = count_duplicated(temp);
      if (cnt > max_cnt) {
        best_max.clear();
        best_max.push_back(temp);
        max_cnt = cnt;
      } else if (cnt == max_cnt) {
        best_max.push_back(temp);
      }

      if (cnt < min_cnt) {
        best_min.clear();
        best_min.push_back(temp);
        min_cnt = cnt;
      } else if (cnt == min_cnt) {
        best_min.push_back(temp);
      }

#if _debug == 2
      debug(temp);
      debug(count_duplicated(temp));
      newline;
#endif

      int i = n - 1;
      while (i >= 0 && temp[i] == '1') {
        temp[i--] = '0';
      }

      if (i < 0) break;
      temp[i] = '1';

    }

    sort(best_max.begin(), best_max.end());
    sort(best_min.begin(), best_min.end());

    debug(max_cnt);
    for (const string& best : best_max) debug(best);
    newline;
    newline;
    debug(min_cnt);
    for (const string& best : best_min) debug(best);

    newline;
    newline;
  }
}

int main() {
  cin.tie(0)->sync_with_stdio(0);

  freopen("input.inp", "r", stdin);

  make_test2();

}

#endif // _debug

