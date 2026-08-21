#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  // freopen("input.inp", "r", stdin);

  int n, m;
  cin >> n >> m;
  int r = 1, c = 1;
  while (r < n)
    r <<= 1;
  c = r;

  vector<vector<long long>> A(2 * r, vector<long long>(2 * c, 0));
  vector<vector<char>> B(n + 1, vector<char>(n + 1));
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      cin >> B[i][j];
      // cerr << B[i][j];
      if (B[i][j] == '*')
        A[2 * i - 1][2 * j - 1]++;
    }
    // cerr << '\n';
  }

  // for (int i = 1; i < 2 * r; i++) {
  //   for (int j = 1; j < 2 * c; j++) {
  //     if (i == 15 && j == 17)
  //       cerr << 'h';
  //     cerr << A[i][j] << ' ';
  //   }
  //   cerr << '\n';
  // }

  int root_r = r;
  int root_c = c;

  auto prebuild = [&](auto &self, int row, int index) -> long long {
    if (index & 1) {
      return A[row][index];
    }

    int step = (index & -index) / 2;
    int lindex = index - step;
    int rindex = index + step;
    if (step > 0) {
      A[row][index] += self(self, row, lindex);
      A[row][index] += self(self, row, rindex);
    }
    return A[row][index];
  };

  for (int i = 1; i < 2 * r; i++) {
    prebuild(prebuild, i, root_c);
  }

  auto build = [&](auto &self, int index, int col) -> long long {
    if (index & 1) {
      return A[index][col];
    }

    int step = (index & -index) / 2;
    int lindex = index - step;
    int rindex = index + step;
    if (step > 0) {
      A[index][col] += self(self, lindex, col);
      A[index][col] += self(self, rindex, col);
    }
    return A[index][col];
  };

  for (int i = 1; i < 2 * c; i++) {
    build(build, root_r, i);
  }

  auto yfetch = [&](auto &self, int row, int lindex, int y1,
                    int y2) -> long long {
    int lsb = lindex & -lindex;
    int lbound = lindex - lsb + 1;
    int rbound = lindex + lsb - 1;
    if (lbound > y2 || rbound < y1)
      return 0;
    if (lbound >= y1 && rbound <= y2) {
      // cerr << "yfetch " << row << ' ' << lindex << ' ' << A[row][lindex]
      //      << '\n';
      return A[row][lindex];
    }

    int step = lsb / 2;
    int left = lindex - step;
    int right = lindex + step;
    long long res = 0;
    if (step > 0) {
      res += self(self, row, left, y1, y2);
      res += self(self, row, right, y1, y2);
    }
    return res;
  };

  auto xfetch = [&](auto &self, int rindex, int x1, int y1, int x2,
                    int y2) -> long long {
    int lsb = rindex & -rindex;
    int lbound = rindex - lsb + 1;
    int rbound = rindex + lsb - 1;
    // cerr << 'b' << lbound << ' ' << rbound << '\n';
    if (lbound > x2 || rbound < x1)
      return 0;

    if (lbound >= x1 && rbound <= x2) {
      // cerr << "xfetch " << rindex << '\n';
      return yfetch(yfetch, rindex, root_c, y1, y2);
    }

    int step = lsb / 2;
    int left = rindex - step;
    int right = rindex + step;
    // cerr << 'i' << left << ' ' << right << '\n';
    long long res = 0;
    if (step > 0) {
      res += self(self, left, x1, y1, x2, y2);
      res += self(self, right, x1, y1, x2, y2);
    }
    return res;
  };

  auto yupdate = [&](auto &self, int row, int lindex, int y,
                     const long long &val) -> void {
    if (lindex & 1) {
      if (row & 1) {
        A[row][lindex] += val;
      } else {
        int step = (row & -row) / 2;
        int left_r = row - step;
        int right_r = row + step;
        A[row][lindex] = A[left_r][lindex] + A[right_r][lindex];
      }
      return;
    }

    int step = (lindex & -lindex) / 2;
    int left = lindex - step;
    int right = lindex + step;
    if (y < lindex) {
      self(self, row, left, y, val);
    } else {
      self(self, row, right, y, val);
    }
    A[row][lindex] = A[row][left] + A[row][right];
  };

  auto xupdate = [&](auto &self, int rindex, int x, int y,
                     const long long &val) -> void {
    if (rindex & 1) {
      yupdate(yupdate, rindex, root_c, y, val);
      return;
    }

    int step = (rindex & -rindex) / 2;
    int left = rindex - step;
    int right = rindex + step;
    if (x < rindex) {
      self(self, left, x, y, val);
    } else {
      self(self, right, x, y, val);
    }
    yupdate(yupdate, rindex, root_c, y, 0);
  };

  auto get_index = [](int index) { return 2 * index - 1; };
  while (m--) {
    int type;
    cin >> type;
    if (type == 1) {
      int x, y;
      cin >> x >> y;
      int val = 0;
      if (B[x][y] == '.') {
        B[x][y] = '*';
        val = 1;
      } else {
        B[x][y] = '.';
        val = -1;
      }
      x = get_index(x);
      y = get_index(y);
      xupdate(xupdate, root_r, x, y, val);
    } else {
      int x1, y1, x2, y2;
      cin >> x1 >> y1 >> x2 >> y2;
      x1 = get_index(x1);
      x2 = get_index(x2);
      y1 = get_index(y1);
      y2 = get_index(y2);
      cout << xfetch(xfetch, root_r, x1, y1, x2, y2) << '\n';
    }
  }

  // for (int i = 1; i <= n; i++) {
  //   for (int j = 1; j <= n; j++) {
  //     if (i == 8 && j == 9)
  //       cerr << 'h';
  //     cerr << B[i][j] << ' ';
  //   }
  //   cerr << '\n';
  // }

  // cerr << '\n';
  // for (int i = 1; i < 2 * r; i++) {
  //   for (int j = 1; j < 2 * c; j++) {
  //     if (i == 15 && j == 17)
  //       cerr << 'h';
  //     cerr << A[i][j] << ' ';
  //   }
  //   cerr << '\n';
  // }
}
