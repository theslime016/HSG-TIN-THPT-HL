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
int n, m;

void init(int N, int M) {
  n = N;
  m = M;
}

int get_index(int a) {
  return (a << 1);
}

struct PROFILE {
  int up, down, left, right;
  PROFILE(int TL, int TR, int BL, int BR) {
    up = down = left = right = 0;

    int cnt = TL + TR + BL + BR;

    if (cnt == 3) {
      up = TL && TR;
      down = BL && BR;

      left = TL && BL;
      right = TR && BR;
    } else if (cnt == 2) {
      if (TL && BR) {
        if (BL) {
          down = left = 1;
        } else {
          up = right = 1;
        }
      }

      if (TR && BL) {
        if (BR) {
          down = right = 1;
        } else {
          up = left = 1;
        }
      }

    } else {
      if (TL) {
        up = left = 1;
      } else if (TR) {
        up = right = 1;
      } else if (BL) {
        down = left = 1;
      } else {
        down = right = 1;
      }
    }

  }
};

int place_left(const PROFILE& x, int level) {
  for (int left_index = 0; left_index < m; left_index++) {
    if (A[level][left_index] == 0) {
      A[level][left_index] = 1;
      return left_index;
    }
  }
  return -1;
}

int place_right(const PROFILE& x, int level) {
  for (int right_index = m - 1; right_index >= 0; right_index--) {
    if (A[level][right_index] == 0) {
      A[level][right_index] = 1;
      return right_index;
    }
  }
  return -1;
}

pair<int, int> place_down(const PROFILE& x) {
  /// find down
  int down_index = n - 1;
  while (down_index >= 0) {

    if (x.left) {
      int left_index = place_left(x, down_index);
      if (left_index != -1) return {get_index(down_index), get_index(left_index)};
    } else {
      int right_index = place_right(x, down_index);
      if (right_index != -1) return {get_index(down_index), get_index(right_index)};
    }

    down_index--;
  }

  return {-1, -1};
}

pair<int, int> place_up(const PROFILE& x) {
  /// find up
  int up_index = 0;
  while (up_index < n) {

    if (x.left) {
      int left_index = place_left(x, up_index);
      if (left_index != -1) return {get_index(up_index), get_index(left_index)};
    } else {
      int right_index = place_right(x, up_index);
      if (right_index != -1) return {get_index(up_index), get_index(right_index)};
    }

    up_index++;
  }

  return {-1, -1};
}

pair<int, int> receive_block(int TL, int TR, int BL, int BR) {
  PROFILE x(TL, TR, BL, BR);

  if (x.down) return place_down(x);
  else return place_up(x); /// if x.up == 1 || (x.down == 0 || x.up == 0)

}

#if _debug == 1

struct BLOCK {
  int TL, TR, BL, BR;
};

BLOCK B[maxn][maxn];

void test() {
  memset(A, 0, sizeof A);

  cin >> n >> m;

  int test_cnt = n*m;

  for (int i = 1; i <= test_cnt; i++) {
    int TL, TR, BL, BR;
    cin >> TL >> TR >> BL >> BR;
    PROFILE x(TL, TR, BL, BR);

    pair<int, int> pos = x.down ? place_down(x) : place_up(x);

    B[pos.first >> 1][pos.second >> 1] = {TL, TR, BL, BR};

    debug(TL);
    debug(TR);
    debug(BL);
    debug(BR);
    newline;
    debug(x.up);
    debug(x.down);
    debug(x.left);
    debug(x.right);
    newline;
    debug(pos.first);
    debug(pos.second);
    newline;
    newline;

  }

  newline;
  debug("AFTER");
  newline;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      cout << B[i][j].TL << ' ' << B[i][j].TR << ' ';
    }
    cout << '\n';
    for (int j = 0; j < m; j++) {
      cout << B[i][j].BL << ' ' << B[i][j].BR << ' ';
    }
    cout << '\n';
  }

}

int main() {
  cin.tie(0)->sync_with_stdio(0);

  freopen("input.inp", "r", stdin);
  test();


}
#endif
