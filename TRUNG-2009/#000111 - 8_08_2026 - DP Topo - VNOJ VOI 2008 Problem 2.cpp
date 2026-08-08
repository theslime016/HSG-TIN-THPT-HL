#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e3 + 5;
int indeg[maxn];
int dp[maxn];
vector<int> adj[maxn];

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n;
  cin >> n;

  vector<int> A(n);
  set<int> S; // value
  for (int i = 0; i < n; i++) {
    cin >> A[i];
    S.insert(A[i]);
  }

  // Tạo tập cạnh
  sort(A.begin(), A.end());
  for (int i = 0; i < n; i++) {
    for (int j = i + 1; j < n; j++) {
      int val = A[i] + A[j];
      if (S.count(val)) {
        int index_val = lower_bound(A.begin(), A.end(), val) - A.begin();
        indeg[index_val] += 2;
        adj[i].push_back(index_val);
        adj[j].push_back(index_val);
      }
    }
  }

  // DP Topo
  stack<int> st;
  int res = 1;
  for (int i = 0; i <= n; i++) {
    dp[i] = 1;
    if (!indeg[i]) {
      st.push(i);
    }
  }

  while (!st.empty()) {
    int a = st.top();
    st.pop();

    for (int x : adj[a]) {
      dp[x] = max(dp[x], dp[a] + 1);
      res = max(res, dp[x]);
      indeg[x]--;
      if (!indeg[x]) {
        st.push(x);
      }
    }
  }

  cout << res;
}
