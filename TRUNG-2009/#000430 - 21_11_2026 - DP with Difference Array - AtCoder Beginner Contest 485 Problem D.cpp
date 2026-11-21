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

const int maxn = 3e5 + 5;

int n;

char A[maxn];
int diff[maxn];

int solve() {

  int i = 0;
  {
    int cnt[3] {};
    while (i + 1 <= n && (!cnt[0] || !cnt[1] || !cnt[2])) {
      cnt[ A[++i] - 'A' ]++;
    }

    if (!cnt[0] || !cnt[1] || !cnt[2]) {
      return -1;
    }
  }

  int j2 = n + 1;
  {
    int cnt[3] {};
    while (j2 - 1 >= 1 && (!cnt[0] || !cnt[1] || !cnt[2])) {
      cnt[ A[--j2] - 'A' ]++;
    }

    if (!cnt[0] || !cnt[1] || !cnt[2]) {
      return -1;
    }
  }

  #if _debug == 1
  debug(i, j2);
  #endif // _debug

  if (j2 < i) {
    return -1;
  }

  int cnt[3] {};
  for (int j1 = i; i < j2; i++) {
    while (j1 + 1 <= n && (!cnt[0] || !cnt[1] || !cnt[2])) {
      cnt[ A[++j1] - 'A' ]++;
    }
    #if _debug == 1
    debug(i, j1, j2);
    #endif // _debug

    if (j1 < j2 && cnt[0] && cnt[1] && cnt[2]) {
      diff[j1]++;
      diff[j2]--;
    } else {
      break;
    }

    cnt[ A[i + 1] - 'A' ]--;
  }
  return 0;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);

#if _debug == 1
  freopen("input.inp", "r", stdin);

#elif _debug == 2
  freopen("input.inp", "r", stdin);

#else

#endif // _debug

  cin >> n;
  for (int i = 1; i <= n; i++)
    cin >> A[i];

  int val = solve();

  #if _debug == 1
  newline;
  cerr << "diff: ";
  newline;
  long long current = 0;
  for (int k = 1; k <= n; k++) {
    current += diff[k];
    cout << current << ' ';
  }
  newline;
  #endif // _debug

  long long res = 0;
  for (int i = 1; i <= n; i++) {
    diff[i] += diff[i-1];
    res += diff[i];
  }

  cout << res;
}
