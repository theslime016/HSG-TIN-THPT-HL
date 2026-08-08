#include <bits/stdc++.h>
using namespace std;

vector<int> adj[30]{};
int indeg[30]{};
bool state[30]{};

#define debugr(x) cout << #x << " = " << (x) << '\n'
#define debugl cout << '\n'

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n;
  cin >> n;
  string last, current;
  // Binary Search tìm vị trí thay đổi sớm nhất (first F từ trái sang phải):
  // Nếu một trong 2 là prefix thì xếp theo độ dài
  // -> Nếu là prefix ở đằng sau khi không có kết quả
  // -> Nếu là same string hoặc prefix đằng trước thì bỏ qua

  // DAG, nối 2 vị trí khác nhau lại với nhau: Tức là cái char đằng trước trỏ
  // đến char đằng sau
  vector<pair<int, int>> query;
  query.reserve(n);
  for (int i = 1; i <= n; i++) {
    cin >> current;
    if (!last.empty()) {
      int mx = min(last.size(), current.size());
      int index = 0;
      for (; index < mx; index++) {
        if (last[index] != current[index]) {
          int findex = last[index] - 'a';
          int sindex = current[index] - 'a';
          query.push_back({findex, sindex});
          break;
        }
      }

      if (index == mx && current.size() < last.size()) {
        cout << "Impossible";
        return 0;
      }
    }
    swap(last, current);
  }

  sort(query.begin(), query.end());
  query.erase(unique(query.begin(), query.end()), query.end());
  for (auto &a : query) {
    adj[a.first].push_back(a.second);
    indeg[a.second]++;
  }

  deque<int> st;
  for (int i = 0; i <= 'z' - 'a'; i++) {
    if (!indeg[i]) {
      st.push_back(i);
    }
  }

  vector<int> rank;
  rank.reserve(30);
  while (!st.empty()) {
    int a = st.front();
    st.pop_front();
    rank.push_back(a);
    state[a] = 1;

    for (int x : adj[a]) {
      indeg[x]--;
      if (!indeg[x]) {
        st.push_back(x);
      }
    }
  }

  for (int i = 0; i <= 'z' - 'a'; i++) {
    if (indeg[i] > 0) {
      cout << "Impossible";
      return 0;
    }
  }

  for (int i = 0; i <= 'z' - 'a'; i++) {
    if (!state[i]) {
      rank.push_back(i);
    }
  }

  for (int x : rank)
    cout << char('a' + x);
}
