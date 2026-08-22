#include <bits/stdc++.h>
using namespace std;

/*
chỉ có hoặc không beauty
số lần xuất hiện của mỗi letters chia hết cho k thì là beautiful
cần string nhỏ nhất + có beautiful + lớn hơn hoặc bằng k
so sánh từ trái sang phải
dài N
*/

/*
NLogN hoặc N căn N
- Ý tưởng: Xây string mới từ string cũ luôn, cũng có n chữ số
- prebuild: Tìm số lượng của mỗi char
- Greedy: Xây từ đầu xuống cuối, char hiện tại phải >= char gốc
- Cần xuất hiện ít nhất là bội của k lần
- Dư k-1?

Xảy ra 2 trường hợp:
- Char hiện tại bằng char gốc: Mấy char sau bị giới hạn dưới bởi char gốc
- Char hiện tại lớn hơn char gốc: Mấy char sau nhảy loạn xạ, không bị giới hạn
gì

Vì là xây từ đầu xuống cuối vậy nên phải ưu tiên char bé trước char lớn
Có 2 loại char:
Loại char xuất hiện: Cần xuất hiện với số lần là bội của k

*/

/*
Hoặc là ghép từ prefix, hoặc là tạo mới
Tại điểm i, điều kiện để construct char x là:
->Nếu số lượng còn lại của nó = 0 thì số lượng cần bị dội lên là k
Và số lượng char còn lại (tức rem) phải >=
->Nếu số lượng còn lại của nó != 0 thì chỉ cần trừ đi 1

->Nếu có strict: Char đó phải >= char hiện tại
->Nếu không có strict: Chọn từ bé đến lớn

->Điều kiện kết thúc là construct đến n+1 và không còn char nào cần construct
thêm
*/

/*
Giả định: Char đầu chỉ có thể là char hiện tại hoặc char + 1
Giả định: Chỉ có thể construct khi n chia hết cho k và n >= k
*/

string s;
int n, k;
namespace brute {

string temp = "";
int f[30];
bool check() {
  bool greater = true;
  bool beauty = true;
  for (int i = 0; i < n; i++) {
    if (s[i] != temp[i]) {
      if (s[i] < temp[i]) {
        greater = true;
      } else if (s[i] > temp[i]) {
        greater = false;
      }
      break;
    }
  }

  memset(f, 0, sizeof f);

  for (char x : temp) {
    f[x - 'a']++;
  }

  for (char x = 'a'; x <= 'z'; x++) {
    if ((f[x - 'a'] > 0 && f[x - 'a'] < k) || f[x - 'a'] % k != 0) {
      beauty = false;
      break;
    }
  }

  return greater && beauty;
}

bool build() {
  if (temp.size() == n) {

    if (check()) {
      cout << s << '-' << temp << '\n';
      return true;
    }
    return false;
  }

  for (char x = 'a'; x <= 'z'; x++) {
    temp.push_back(x);
    if (build())
      return true;
    temp.pop_back();
  }
  return false;
}

void solve() {
  temp = "";
  if (!build()) {
    cout << -1 << '\n';
  }
}
} // namespace brute

int main() {
  cin.tie(0)->sync_with_stdio(0);

  freopen("input.inp", "r", stdin);
  freopen("output.out", "w", stdout);

  int t;
  cin >> t;
  while (t--) {
    cin >> n >> k;
    cin >> s;
    brute::solve();
  }
}
