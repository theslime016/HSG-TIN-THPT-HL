#include <bits/stdc++.h>
using namespace std;

/*
Có N thành phố trên toàn quốc. Ban đầu, các thành phố này hoàn toàn bị cô lập,
không có đường đi lại với nhau. Bộ Giao thông vận tải ban hành một dự án xây
dựng cầu đường kéo dài trong M tháng. Mỗi tháng, họ sẽ hoàn thành và đưa vào sử
dụng đúng một tuyến đường hai chiều nối giữa hai thành phố u và v.

Trong thời gian này, ban quản lý nhận được Q câu hỏi từ người dân. Người dân thứ
i hỏi: "Vào tháng thứ mấy thì tôi có thể bắt đầu di chuyển từ thành phố A đến
thành phố B bằng đường bộ?"

Yêu cầu: Hãy trả lời câu hỏi của Q người dân. Nếu đến khi kết thúc dự án mà vẫn
không thể đi được, in ra -1.

input:
5 4 3
1 2
2 3
4 5
3 5

1 3
1 5
1 4

output:
2
4
4
*/

struct uf {
  int n;
  vector<int> data;

  uf(int n) {
    this->n = n;
    data.resize(n + 1);
    iota(data.begin(), data.end(), 0);
  }

  void clear() { iota(data.begin(), data.end(), 0); }

  int find(int index) {
    if (data[index] == index)
      return index;
    return data[index] = find(data[index]);
  }

  void compress(int a, int b) {
    a = find(a);
    b = find(b);
    if (a != b) {
      if (a < b)
        swap(b, a);
      data[b] = a;
    }
  }
};

#define debugr(x) cout << #x << " = " << (x) << '\n'
#define debugl cout << '\n'

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n, m, q;
  cin >> n >> m >> q;

  struct ed {
    int a, b;
  };

  vector<ed> edges(m);
  for (ed &x : edges) {
    cin >> x.a >> x.b;
  }

  struct que {
    int x, y;
    int init;
    int l, r;
    int id;
  };

  vector<stack<que>> query(m + 1);
  vector<que> initque(q);
  for (int i = 0; i < q; i++) {
    int a, b;
    cin >> a >> b;
    que current = {a, b, i, 1, m, -1};
    initque[i] = current;
    query[current.l + (current.r - current.l) / 2].push(current);
  }

  for (auto a : initque) {
    cout << a.x << ' ' << a.y << ' ' << a.init << ' ' << a.l << ' ' << a.r
         << ' ' << a.id << '\n';
  }

  uf dsu(n);
  // Build DSU dần dần theo edges
  // Mỗi timer ta kiểm tra Query
  // Nếu Query chưa thể tới -> nó nằm ở đoạn sau (mid+1 -> m)
  // Nếu Query đã tới được -> nó nằm ở đây trở về trước (0 -> mid)
  bool find = true;
  while (find) {
    int timer = 1;
    find = false;
    // Build DSU
    for (ed &e : edges) {
      dsu.compress(e.a, e.b);

      // Kiểm tra Query
      while (!query[timer].empty()) {
        find = true;
        que current = query[timer].top();
        query[timer].pop();

        // Kiểm tra điều kiện tại mid của mỗi Query
        // Đẩy l r
        // FFFFTTTTT
        int mid = current.l + (current.r - current.l) / 2;
        if (dsu.find(current.x) == dsu.find(current.y)) {
          current.r = mid - 1;
          current.id = mid;
        } else {
          current.l = mid + 1;
        }

        // tính mid và push lại vào Query
        if (current.l <= current.r) {
          int new_mid = current.l + (current.r - current.l) / 2;
          query[new_mid].push(current);
        }

        // cập nhật lại state
        initque[current.init] = current;
      }
      timer++;
    }
    dsu.clear();
  }

  for (const que &q : initque) {
    cout << q.id << '\n';
  }
}
