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

const int maxn = 1e3 + 5;
int A[maxn][maxn];
int B[maxn << 1][maxn << 1];
int n, m;

void init(int N, int M) {
  n = N;
  m = M;
}

int get_index(int a) {
  return (a << 1);
}

int get_rev_index(int a) {
  return (a >> 1);
}

struct PROFILE {
  int up_left, up_right, down_left, down_right;
  PROFILE(int TL, int TR, int BL, int BR) {
    up_left = up_right = down_left = down_right = 0;

    int cnt = TL + TR + BL + BR;

    if (cnt == 3) {
      if (!TL) down_right = 1;
      if (!TR) down_left = 1;
      if (!BL) up_right = 1;
      if (!BR) up_left = 1;
    } else if (cnt == 2) {
      if (TL && BR) {
        down_left = 1;
        up_right = 1;
      }

      if (TR && BL) {
        down_right = 1;
        up_left = 1;
      }

      if (TL && TR) {
        up_left = 1;
        up_right = 1;
      }

      if (BL && BR) {
        down_left = 1;
        down_right = 1;
      }

    } else {
      if (TL) up_left = 1;
      if (TR) up_right = 1;
      if (BL) down_left = 1;
      if (BR) down_right = 1;
    }

  }
};

int place_left(int level) {
  for (int left_index = 0; left_index < m; left_index++) {
    if (A[level][left_index] == 0) {
      return left_index;
    }
  }
  return -1;
}

int place_right(int level) {
  for (int right_index = m - 1; right_index >= 0; right_index--) {
    if (A[level][right_index] == 0) {
      return right_index;
    }
  }
  return -1;
}

pair<int, int> place_down_left(const PROFILE& x) {
  /// find down
  int down_index = n - 1;
  while (down_index >= 0) {
    int left_index = place_left(down_index);
    if (left_index != -1) return {down_index, left_index};
    down_index--;
  }

  return {-1, -1};
}

pair<int, int> place_down_right(const PROFILE& x) {
  /// find down
  int down_index = n - 1;
  while (down_index >= 0) {
    int right_index = place_right(down_index);
    if (right_index != -1) return {down_index, right_index};
    down_index--;
  }

  return {-1, -1};
}


pair<int, int> place_up_left(const PROFILE& x) {
  /// find up
  int up_index = 0;
  while (up_index < n) {
    int left_index = place_left(up_index);
    if (left_index != -1) return {up_index, left_index};
    up_index++;
  }

  return {-1, -1};
}

pair<int, int> place_up_right(const PROFILE& x) {
  /// find up
  int up_index = 0;
  while (up_index < n) {
    int right_index = place_right(up_index);
    if (right_index != -1) return {up_index, right_index};
    up_index++;
  }

  return {-1, -1};
}

bool check(int x, int y, int lim_x, int lim_y) {
  for (int i = max(0, x); i <= lim_x; i++) {
    for (int j = max(0, y); j <= lim_y; j++) {
      if (i+1 < n && j + 1 < m) {
        if (B[i][j] && B[i+1][j] && B[i][j+1] && B[i+1][j+1]) return false;

        int TL = A[get_rev_index(i)][get_rev_index(j)] ? B[i][j] : 1;
        int TR = A[get_rev_index(i)][get_rev_index(j+1)] ? B[i][j+1] : 1;
        int BL = A[get_rev_index(i+1)][get_rev_index(j)] ? B[i+1][j+1] : 1;
        int BR = A[get_rev_index(i+1)][get_rev_index(j+1)] ? B[i+1][j+1] : 1;

        if (TL && TR && BL && BR) return false;
      }
    }
  }
  return true;
}

pair<int, int> receive_block(int TL, int TR, int BL, int BR) {
  PROFILE x(TL, TR, BL, BR);

  vector<pair<int, int>> cand;
  if (x.down_left) cand.push_back(place_down_left(x));
  if (x.down_right) cand.push_back(place_down_right(x));
  if (x.up_left) cand.push_back(place_up_left(x));
  if (x.up_right) cand.push_back(place_up_right(x));

#if _debug == 1
  for (const pair<int, int>& pos : cand) {
    debug(pos.first);
    debug(pos.second);
    newline;
  }

#endif // _debug

  for (const pair<int, int>& pos : cand) {
    if (pos.first == -1 || pos.second == -1) continue;
    int i = get_index(pos.first);
    int j = get_index(pos.second);
    B[i][j] = TL;
    B[i][j+1] = TR;
    B[i+1][j] = BL;
    B[i+1][j+1] = BR;
    A[pos.first][pos.second] = 1;
    if (check(i-1, j-1, i+1, j+1)) {
      return {i, j};
    }
    A[pos.first][pos.second] = 0;
    B[i][j] = B[i+1][j] = B[i][j+1] = B[i+1][j+1] = 0;
  }
  return {-1, -1};
}

#if _debug == 1

struct BLOCK {
  int TL, TR, BL, BR;
};

void test() {
  memset(A, 0, sizeof A);

  cin >> n >> m;

  int test_cnt = n*m;

  for (int i = 1; i <= test_cnt; i++) {
    int TL, TR, BL, BR;
    cin >> TL >> TR >> BL >> BR;
    PROFILE x(TL, TR, BL, BR);

    pair<int, int> pos = receive_block(TL, TR, BL, BR);

    debug(TL);
    debug(TR);
    debug(BL);
    debug(BR);
    newline;
    debug(x.down_left);
    debug(x.down_right);
    debug(x.up_left);
    debug(x.up_right);
    newline;
    newline;
  }

  newline;
  debug("AFTER");
  newline;
  for (int i = 0; i < 2*n; i++) {
    for (int j = 0; j < 2*m; j++) {
      cerr << B[i][j] << ' ';
    }
    cerr << '\n';
  }


  for (int i = 0; i < 2*n - 1; i++) {
    for (int j = 0; j < 2*m - 1; j++) {
      if (B[i][j] && B[i+1][j] && B[i][j+1] && B[i+1][j+1]) {
        cout << 0;
        return;
      }
    }
  }

  cout << 1;

}

int main() {
  cin.tie(0)->sync_with_stdio(0);

  freopen("input.inp", "r", stdin);

  test();

}
#endif
