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
  vector<int> data;
  vector<int> bucket;

  uf(int n) {
    bucket.assign(n + 1, 1);
    data.resize(n + 1);
    iota(data.begin(), data.end(), 0);
  }

  void clear() {
    iota(data.begin(), data.end(), 0);
    fill(bucket.begin(), bucket.end(), 1);
  }

  int find(int index) {
    if (data[index] == index)
      return index;
    return data[index] = find(data[index]);
  }

  void compress(int a, int b) {
    a = find(a);
    b = find(b);
    if (a != b) {
      // sizeof a >= sizeof b
      if (bucket[a] < bucket[b])
        swap(a, b);
      bucket[a] += bucket[b];
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

  vector<pair<int, int>> edges(m + 1);
  for (int i = 1; i <= m; i++) {
    cin >> edges[i].first >> edges[i].second;
  }

  vector<pair<int, int>> query(q + 1);
  vector<stack<int>> wait(m + 1);
  int temp_mid = 1 + (m - 1) / 2;
  for (int i = 1; i <= q; i++) {
    cin >> query[i].first >> query[i].second;
    wait[temp_mid].push(i);
  }

  vector<int> L(q + 1, 1), R(q + 1, m), res(q + 1, -1);

  bool found = true;
  uf dsu(n);
  while (found) {
    found = false;

    for (int i = 1; i <= m; i++) {
      dsu.compress(edges[i].first, edges[i].second);
      while (!wait[i].empty()) {
        found = true;
        int index = wait[i].top();
        wait[i].pop();

        int mid = L[index] + (R[index] - L[index]) / 2;
        if (dsu.find(query[index].first) == dsu.find(query[index].second)) {
          R[index] = mid - 1;
          res[index] = mid;
        } else {
          L[index] = mid + 1;
        }

        int new_mid = L[index] + (R[index] - L[index]) / 2;
        if (L[index] <= R[index])
          wait[new_mid].push(index);
      }
    }

    dsu.clear();
  }

  for (int i = 1; i <= q; i++)
    cout << res[i] << '\n';
}
