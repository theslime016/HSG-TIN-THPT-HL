#include <bits/stdc++.h>
using namespace std;

// Có khả năng là sẽ dùng tới difference array:
// Chọn một difference array sao cho tổng của 2 cột difference array là d
// Chưa biết triển khai thế nào phần này
// Nhưng hướng này có vẻ không đúng, với N quá lớn thì phải tìm ra một yếu tố
// nào đó giúp chọn thẳng ra permutation đúng cho mỗi hàng và tổng operation <=
// 1e6

// Brute Force:
// Chia thành các phần để giải quyết
// -> Tạo một tập sau khi đã swap
// -> Kiểm tra phần đó: Xem tổng cột tiếp theo có = tổng cột hiện tại + d hay
// không. Và kiểm tra xem số lượng opertation swap ít nhất có vượt quá 1e6 hay
// không
// -> Từ mỗi hàng trong tập swap chuẩn, phải tách thành số operations ít nhất để
// swap hàng ban đầu thành hàng hiện tại

#define debugr(x) cout << #x << " = " << (x) << '\n'
#define debugl cout << '\n'

const int inf = 1e6;
const int maxn = 5e4 + 5;
const int maxk = 15;
vector<vector<int>> A;

struct swp {
  int r, i, j;
};

vector<swp> res;
int n, k, d;
// Ý tưởng ban đầu ở đây là cứ swap bừa nhưng bị stack overflow vì nó cứ swap
// qua lại không kiểm soát được
bool solve(int row, int op) {
  if (row == k + 1) {
    vector<int> p(n + 1, 0);
    for (int i = 1; i <= n; i++) {
      int sum = 0;
      for (int j = 1; j <= k; j++) {
        sum += A[j][i];
      }
      p[i] = sum;
      vector<int> A(5);
      iota(A.begin(), A.end(), 1);
      do {
        for (int x : A)
          cout << x << ' ';
        cout << '\n';
      } while (next_permutation(A.begin(), A.end()));
    }

    for (int i = 1; i < n; i++) {
      if (p[i + 1] - p[i] != d)
        return false;
    }

    return true;
  }

  if (solve(row + 1, op)) {
    return true;
  }

  if (op < inf) {
    for (int i = 1; i <= n; i++) {
      for (int j = i + 1; j <= n; j++) {
        swap(A[row][i], A[row][j]);
        if (solve(row, op + 1) || solve(row + 1, op + 1)) {
          res.push_back({row, i, j});
          return true;
        }
        swap(A[row][i], A[row][j]);
      }
    }
  }
  return false;
}

vector<vector<int>> B;
vector<vector<int>> orin;
// Bây giờ bài toán chuyển thành: Tìm ra số operation cần thiết để biến row đã
// swap về ban đầu và phải nhét số operation đó vào res

// Ý tưởng ban đầu là tạo một mảng lưu index gốc của mỗi phần tử, duyệt thấy
// phần tử nào chưa đúng chỗ thì swap về chỗ cũ

bool opCheck() {
  long long oper = 0;
  for (int i = 1; i <= k; i++) {
    vector<int> S = B[i];
    for (int j = 1; j <= n; j++) {
      // debugr(j);
      // debugr(oIndex);
      // debugl;
      while (orin[i][S[j]] != j) {
        res.push_back({i, orin[i][S[j]], j});
        oper++;
        swap(S[orin[i][S[j]]], S[j]);
      }
    }
  }

  if (oper > inf) {
    res.clear();
    return false;
  }

  return true;
}

// Check cái tập sau khi đã swap: Chỉ check phần so sánh tổng với d
bool check() {
  vector<int> p(n + 1, 0);
  for (int j = 1; j <= n; j++) {
    int sum = 0;
    for (int i = 1; i <= k; i++) {
      sum += B[i][j];
    }
    p[j] = sum;
  }

  // for (int i = 1; i <= n; i++) {
  //   debugr(p[i]);
  // }

  for (int i = 1; i < n; i++) {
    if (p[i + 1] - p[i] != d) {
      return false;
    }
  }

  // for (int i = 1; i <= k; i++) {
  //   for (int j = 1; j <= n; j++) {
  //     debugr(B[i][j]);
  //   }
  //   cout << '\n';
  // }
  // cout << '\n';

  if (!opCheck())
    return false;

  return true;
}

// Tạo một tập sau khi đã swap
bool create(int row) {
  if (row > k)
    return false;
  do {
    if (row == k) {
      // for (int i = 1; i <= k; i++) {
      //   for (int j = 1; j <= n; j++) {
      //     debugr(B[i][j]);
      //   }
      //   cout << '\n';
      // }
      // cout << '\n';

      if (check())
        return true;
    } else if (create(row + 1))
      return true;
  } while (next_permutation(B[row].begin() + 1, B[row].end()));
  return false;
}

int main() {
  cin.tie(0)->sync_with_stdio(false);

  freopen("input.inp", "r", stdin);
  freopen("output.ans", "w", stdout);

  cin >> n >> k >> d;

  if (n == 1) {
    cout << -1;
    return 0;
  }

  A.assign(k + 1, vector<int>(n + 1, 0));
  B.assign(k + 1, vector<int>(n + 1, 0));
  orin.assign(k + 1, vector<int>(n + 1, 0));
  for (int i = 1; i <= k; i++) {
    iota(B[i].begin(), B[i].end(), 0);
  }

  for (int i = 1; i <= k; i++) {
    for (int j = 1; j <= n; j++) {
      cin >> A[i][j];
      orin[i][A[i][j]] = j;
    }
  }

  if (!create(1)) {
    cout << -1;
    return 0;
  }

  cout << res.size() << '\n';
  for (int i = (int)res.size() - 1; i >= 0; i--) {
    cout << res[i].r << ' ' << res[i].i << ' ' << res[i].j << '\n';
  }

  return 0;
}
