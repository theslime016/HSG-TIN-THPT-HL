/*late in autumn*/
#include <bits/stdc++.h>
using namespace std;

/*
Title: The Timeline Graph (Đa Vũ Trụ Đồ Thị)
Description:
Cho một đồ thị có N đỉnh (đánh số từ 1 đến N), ban đầu không có cạnh nào. Bạn có
một hệ thống máy thời gian quản lý đồ thị này thông qua Q thao tác. Hệ thống duy
trì một danh sách các "Điểm neo thời gian" (Checkpoint) dạng ngăn xếp (Stack).
Có 4 loại thao tác tương ứng với các truy vấn:
- "+ u v": Thêm một cạnh nối vô hướng giữa đỉnh u và đỉnh v.
- "? u v": Kiểm tra xem đỉnh u và đỉnh v có đang liên thông với nhau không.
- "S": Đặt một Điểm neo thời gian (Save). Ghi nhận trạng thái hiện tại của đồ
thị vào hệ thống.
- "R": Hoàn tác (Rollback). Đưa toàn bộ đồ thị quay trở về trạng thái của Điểm
neo thời gian gần nhất vừa được tạo, đồng thời xóa Điểm neo đó khỏi danh sách.
Dữ liệu đảm bảo luôn có ít nhất một Điểm neo đang tồn tại khi gọi thao tác này.
Input Format:
- Dòng đầu tiên chứa hai số nguyên dương N và Q (1 <= N <= 100,000; 1 <= Q <=
200,000) lần lượt là số đỉnh của đồ thị và số lượng thao tác.
- Q dòng tiếp theo, mỗi dòng mô tả một thao tác có định dạng như sau:
  + "+ u v" (1 <= u, v <= N)
  + "? u v" (1 <= u, v <= N)
  + "S"
  + "R"
Output Format:
- Với mỗi thao tác "? u v", in ra "YES" nếu đỉnh u và đỉnh v thuộc cùng một
thành phần liên thông, ngược lại in ra "NO". Mỗi kết quả in trên một dòng riêng
biệt.
Example Input 1:
5 11
+ 1 2
+ 2 3
? 1 3
S
+ 4 5
? 1 5
+ 3 4
? 1 5
R
? 1 5
? 1 3
Example Output 1:
YES
NO
YES
NO
YES
Example Input 2:
4 11
S
+ 1 2
S
+ 3 4
? 2 3
R
+ 2 3
? 1 3
R
? 1 2
? 3 4
Example Output 2:
NO
YES
NO
NO
*/

struct uf {
  int n;
  vector<int> data;
  vector<int> bucket;
  stack<pair<int, int>> tldata;
  stack<pair<int, int>> tlbucket;
  // index - value

  uf(int n) {
    this->n = n;
    data.assign(n + 1, 0);
    iota(data.begin(), data.end(), 0);
    bucket.assign(n + 1, 1);
  }

  int fetch(int index) {
    while (index != data[index]) {
      index = data[index];
    }
    return index;
  }

  bool compress(int a, int b) {
    a = fetch(a);
    b = fetch(b);
    if (a != b) {
      if (bucket[a] < bucket[b])
        swap(a, b);

      tldata.push({b, data[b]});
      tlbucket.push({a, bucket[a]});

      data[b] = a;
      bucket[a] += bucket[b];
      return true;
    }
    return false;
  }

  int getcp() { return tldata.size(); }

  void rollback(int lastsize) {
    while (tldata.size() > lastsize) {
      auto [index, vdata] = tldata.top();
      tldata.pop();
      data[index] = vdata;

      auto [jindex, bdata] = tlbucket.top();
      tlbucket.pop();
      bucket[jindex] = bdata;
    }
  }
};

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n, q;
  cin >> n >> q;
  uf dsu(n);
  stack<int> checkpoint;
  while (q--) {
    char op;
    cin >> op;
    if (op == '+') {
      int a, b;
      cin >> a >> b;
      dsu.compress(a, b);
    } else if (op == '?') {
      int a, b;
      cin >> a >> b;
      cout << (dsu.fetch(a) == dsu.fetch(b) ? "YES" : "NO") << '\n';
    } else if (op == 'S') {
      checkpoint.push(dsu.getcp());
    } else if (op == 'R') {
      int lastcp = checkpoint.top();
      checkpoint.pop();
      dsu.rollback(lastcp);
    }
  }
}
