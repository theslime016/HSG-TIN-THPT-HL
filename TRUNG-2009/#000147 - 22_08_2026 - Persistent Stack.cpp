#include <bits/stdc++.h>
using namespace std;

/*
Cho q truy vấn, mỗi truy vấn i cần tạo ra một version i theo một trong 2 cách
1 v x: Lấy version v rồi push x lên
2 v: Lấy ra version v rồi pop và in ra phần tử đầu tiên
*/

struct node {
  int val;
  int prevv;
};

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int q;
  cin >> q;

  vector<node> timeline(q);
  for (int i = 1; i <= q; i++) {
    int t;
    cin >> t;
    if (t == 1) {
      int ver;
      int x;
      cin >> ver >> x;
      timeline[i].val = x;
      timeline[i].prevv = ver;
    } else {
      int ver;
      cin >> ver;
      int last = timeline[ver].prevv;
      timeline[i] = timeline[last];
      cout << timeline[ver].val << '\n';
    }
  }
}
