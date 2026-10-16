#include <bits/stdc++.h>
using namespace std;

const int maxn = 2e5 + 5;
long long S[maxn], T[maxn];
int new_T[maxn];

int fenwick[maxn];
void update(int index, int val) {
  for (; index > 0; index -= index & -index) {
    fenwick[index] += val;
  }
}

int fetch(int index) {
  int res = 0;
  for (; index < maxn; index += index & -index) {
    res += fenwick[index];
  }
  return res;
}

#define _debug 1
int main() {
  cin.tie(0)->sync_with_stdio(0);

  #if _debug == 1
  freopen("input.inp", "r", stdin);
  #else

  #endif // _debug

  int n;
  cin >> n;

  for (int i = 1; i <= n; i++) cin >> S[i];

  vector<long long> T_compress;
  T_compress.reserve(n);
  for (int i = 1; i <= n; i++) {
    cin >> T[i];
    T_compress.push_back(T[i]);
  }

  sort(T_compress.begin(), T_compress.end());

  #if _debug == 1

  cout << "norm S: ";
  for (int i = 1; i <= n; i++) cout << S[i] << ' ';
  cout << '\n';
  cout << "norm T: ";
  for (int i = 1; i <= n; i++) cout << T[i] << ' ';
  cout << '\n';

  cout << "T_compress: ";
  for (long long x : T_compress) cout << x << ' ';
  cout << '\n';

  #endif // _debug


  for (int i = 1; i <= n; i++) {
    new_T[i] = n - (lower_bound(T_compress.begin(), T_compress.end(), T[i]) - T_compress.begin());
  }


  sort(S + 1, S + n + 1);
  sort(T + 1, T + n + 1);

  #if _debug == 1
  cout << "S: ";
  for (int i = 1; i <= n; i++) {
    cout << S[i] << ' ';
  } cout << '\n';

  cout << "T: ";
  for (int i = 1; i <= n; i++) {
    cout << T[i] << ' ';
  } cout << '\n';

  cout << "new_T: ";
  for (int i = 1; i <= n; i++) {
    cout << new_T[i] << ' ';
  } cout << '\n';

  #endif // _debug


  long long res = 0;
  for (int i = 1; i <= n; i++) {
    res += abs(S[i] - T[i]);
  }

  #if _debug == 1
  cout << "proc1: " << res << '\n';
  #endif // _debug

  for (int i = 1; i <= n; i++) {
    int val = fetch(i);
    res += val * (S[i] - S[i-1] + 1);
    update(new_T[i], 1);
  }
  cout << res;
}
