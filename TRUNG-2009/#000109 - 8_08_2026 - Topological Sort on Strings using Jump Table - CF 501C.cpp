#include <bits/stdc++.h>
using namespace std;

char T[105][105];
char jump[30];
bool change[30][30];

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n;
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> T[i];
  }

  for (int i = 2; i <= n; i++) {
    int j = 0;
    for (; T[i][j] == T[i - 1][j]; j++)
      ;
    // Khác nhau nhưng chưa kết thúc
    if (T[i][j] && T[i - 1][j])
      change[T[i][j] - 'a'][T[i - 1][j] - 'a'] = true;
    if (!T[i][j] && T[i - 1][j])
      return cout << "Impossible", 0;
    // Kết thúc và size Ti < size Ti-1
  }

  iota(jump, jump + 26, 'a');
  for (int i = 1; i <= n; i++) {
    for (int j = 0; j < 26; j++) {
      for (int k = j + 1; k < 26; k++) {
        // j = last, k = current
        // Xét ngược:
        // change[current][last] = true
        // -> j có nằm trước k
        // -> swap vì j < k
        if (change[jump[j] - 'a'][jump[k] - 'a'])
          swap(jump[j], jump[k]);
      }
    }
  }

  for (int j = 0; j < 26; j++) {
    for (int k = j + 1; k < 26; k++) {
      if (change[jump[j] - 'a'][jump[k] - 'a'])
        return cout << "Impossible", 0;
    }
  }

  cout << jump;
}
