#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

const int maxn = 2e5 + 5;
const long long inf = 1e18;
struct node {
  long long data;
  long long sum;
  long long max = -inf;
  int size;
  int lazy_rev;
  int child[2];
  int parent;
} splay[maxn];

stack<int> wait;
int root = 0;
int node_count = 0;

int getdir(int index) {
  int pindex = splay[index].parent;
  return splay[pindex].child[1] == index;
}

int newNode(const long long &val, const long long &mx) {
  int index = ++node_count;
  splay[index].data = val;
  splay[index].sum = val;
  splay[index].max = mx;
  splay[index].size = 1;
  splay[index].lazy_rev = 0;
  splay[index].child[0] = splay[index].child[1] = splay[index].parent = 0;
  return index;
}

void pushup(int index) {
  if (index == 0)
    return;

  int L = splay[index].child[0];
  int R = splay[index].child[1];

  splay[index].size = splay[L].size + splay[R].size + 1;
  splay[index].sum = splay[L].sum + splay[R].sum + splay[index].data;
  splay[index].max = max({splay[index].data, splay[L].max, splay[R].max});
}

void pushdown(int index) {
  if (index != 0 && splay[index].lazy_rev != 0) {
    swap(splay[index].child[0], splay[index].child[1]);

    int L = splay[index].child[0];
    int R = splay[index].child[1];
    if (L != 0)
      splay[L].lazy_rev ^= 1;
    if (R != 0)
      splay[R].lazy_rev ^= 1;

    splay[index].lazy_rev = 0;
  }
}

void rtd(int index) {
  if (index == 0 || splay[index].parent == 0)
    return;
  int p = splay[index].parent;
  int g = splay[p].parent;

  int dir = getdir(index);
  int t = splay[index].child[dir ^ 1];
  if (t != 0)
    splay[t].parent = p;
  splay[p].child[dir] = t;

  splay[index].child[dir ^ 1] = p;
  splay[p].parent = index;
  pushup(p);
  pushup(index);

  splay[index].parent = g;
  if (g != 0) {
    if (splay[g].child[0] == p)
      splay[g].child[0] = index;
    else
      splay[g].child[1] = index;
  }
}

void splaying(int index, int target_parent = 0) {
  if (index == 0 || splay[index].parent == 0)
    return;
  while (splay[index].parent != target_parent) {
    int p = splay[index].parent;
    int g = splay[p].parent;

    if (g != 0) {
      if (getdir(index) == getdir(p))
        rtd(p);
      else
        rtd(index);
    }
    rtd(index);
  }

  if (target_parent == 0)
    root = index;
}

int search(int k) {
  if (root == 0)
    return 0;
  int cur = root;
  int last = 0;

  int fnd = 0;
  while (cur != 0) {
    pushdown(cur);
    last = cur;
    int left_size = splay[splay[cur].child[0]].size;

    if (left_size + 1 == k) {
      fnd = 1;
      break;
    } else if (left_size < k) {
      k -= left_size + 1;
      cur = splay[cur].child[1];
    } else if (left_size >= k) {
      cur = splay[cur].child[0];
    }
  }

  splaying(last);
  if (!fnd)
    return 0;
  else
    return last;
}

void insert(const long long &val = 0, const long long &mx = -inf) {
  int newnode = newNode(val, mx);
  if (root == 0) {
    root = newnode;
    return;
  }

  search(newnode);
  splay[root].child[1] = newnode;
  splay[newnode].parent = root;
  splaying(newnode);
}

int fetch(int l, int r) {
  if (l - 1 == 0 && r + 1 > node_count)
    return root;

  if (l - 1 == 0) {
    splaying(r + 1);
    return splay[root].child[0];
  }
  if (r + 1 == 0) {
    splaying(l - 1);
    return splay[root].child[1];
  }

  splaying(l - 1);
  splaying(r + 1);

  return splay[l - 1].child[1];
}

void ranker() {
  deque<pair<int, int>> dq; // rank - index
  dq.push_back({1, root});
  int timer = 0;
  while (!dq.empty()) {
    auto [rank, index] = dq.front();
    dq.pop_front();

    if (rank != timer) {
      cout << endl << "rank:" << rank << ' ';
    }
    timer = rank;
    cout << index << "->" << splay[index].data << ' ';
    if (splay[index].child[0] != 0)
      dq.push_back({rank + 1, splay[index].child[0]});
    if (splay[index].child[1] != 0)
      dq.push_back({rank + 1, splay[index].child[1]});
  }
  cout << '\n';
}

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n;
  cin >> n;
  for (int i = 0; i < n; i++) {
    int val;
    cin >> val;
    insert(val, val);
  }

  int g = fetch(1, 3);
  cout << splay[g].sum << '\n';
  ranker();

  // 4 -> 7
  splaying(3);
  ranker();
  splaying(8);
  ranker();
  cout << splay[3].child[1] << '\n';
  cout << splay[splay[3].child[1]].max << '\n';
}
