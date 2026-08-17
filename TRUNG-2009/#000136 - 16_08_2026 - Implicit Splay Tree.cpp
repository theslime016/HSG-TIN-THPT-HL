#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

const int maxn = 5e4 + 5;
const long long inf = 1e18;
struct node {
  long long data;
  long long sum = 0;
  long long pref = -inf;
  long long suff = -inf;
  long long res = -inf;
  int size;
  int lazy_rev;
  int child[2];
  int parent;
} splay[maxn];

int root = 0;
int node_count = 0;
int n;
stack<int> rec;

int getdir(int index) {
  int pindex = splay[index].parent;
  return splay[pindex].child[1] == index;
}

int newNode(const long long &val) {
  int index;
  if (!rec.empty()) {
    index = rec.top();
    rec.pop();
  } else {
    index = ++node_count;
  }
  splay[index].data = val;
  splay[index].sum = val;
  splay[index].pref = val;
  splay[index].suff = val;
  splay[index].res = val;
  splay[index].size = 1;
  splay[index].lazy_rev = 0;
  splay[index].child[0] = splay[index].child[1] = splay[index].parent = 0;
  return index;
}

// void swapdata(int x, int y) {
//   swap(splay[x], splay[y]);
//   swap(splay[x].parent, splay[y].parent);
//   swap(splay[x].child, splay[y].child);
// }

void init_null() { splay[0].pref = splay[0].suff = splay[0].res = -inf; }

void pushup(int index) {
  if (index == 0)
    return;

  int L = splay[index].child[0];
  int R = splay[index].child[1];

  splay[index].size = splay[L].size + splay[R].size + 1;
  splay[index].sum = splay[L].sum + splay[index].data + splay[R].sum;
  splay[index].pref = max(splay[L].pref, splay[L].sum + splay[index].data +
                                             max(splay[R].pref, 0LL));
  splay[index].suff = max(splay[R].suff, max(splay[L].suff, 0LL) +
                                             splay[index].data + splay[R].sum);
  splay[index].res = max(
      {splay[L].res, splay[R].res,
       max(splay[L].suff, 0LL) + splay[index].data + max(splay[R].pref, 0LL)});
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
  if (index == 0)
    return;
  while (splay[index].parent != target_parent && splay[index].parent != 0) {
    int p = splay[index].parent;
    int g = splay[p].parent;

    if (g != 0 && g != target_parent) {
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

void insert_segment(int pos, int newroot) {
  if (newroot == 0)
    return;

  int L = search(pos + 1);
  int R = search(pos + 2);

  splaying(L, 0);
  splaying(R, L);

  splay[R].child[0] = newroot;
  splay[newroot].parent = R;

  pushup(L);
  pushup(R);
  splaying(newroot);
}

void insert(int pos, const long long &val) {
  int newnode = newNode(val);
  insert_segment(pos, newnode);
}

int fetch(int l, int r) {
  int L = search(l);
  int R = search(r + 2);

  splaying(L, 0);
  splaying(R, root);

  return splay[R].child[0];
}

int rev(int l, int r) {
  int index = fetch(l + 1, r + 1);
  splay[index].lazy_rev ^= 1;
  pushdown(index);
  return index;
}

void del(int l, int r) {
  int index = fetch(l, r);
  int parent = splay[index].parent;
  splay[parent].child[0] = 0;

  stack<int> wait;
  wait.push(index);
  while (!wait.empty()) {
    int a = wait.top();
    wait.pop();
    rec.push(a);
    if (splay[a].child[0] != 0)
      wait.push(splay[a].child[0]);
    if (splay[a].child[1] != 0)
      wait.push(splay[a].child[1]);
  }
}

void ranker() {
  deque<pair<int, int>> dq;
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

void inorder(int index) {
  if (index != 0) {
    pushdown(splay[index].child[0]);
    inorder(splay[index].child[0]);
    cout << splay[index].data << ' ';
    pushdown(splay[index].child[1]);
    inorder(splay[index].child[1]);
  }
}

long long A[maxn];
int build(int l, int r, int parent) {
  if (l > r)
    return 0;

  int mid = l + (r - l) / 2;
  int newnode = newNode(A[mid]);
  splay[newnode].parent = parent;

  splay[newnode].child[0] = build(l, mid - 1, newnode);
  splay[newnode].child[1] = build(mid + 1, r, newnode);

  pushup(newnode);
  return newnode;
}

// void init_dummy(int x, int y) {
//   node_count = 2;
//   splay[x].parent = y;
//   splay[y].child[0] = x;
//   root = 2;
// }

int main() {
  cin.tie(0)->sync_with_stdio(0);

  init_null();

  cin >> n;
  // init_dummy(1, 2);
  A[1] = A[n + 2] = -inf;
  for (int i = 2; i <= n + 1; i++) {
    cin >> A[i];
    // insert(A[i]);
  }

  root = build(1, n + 2, 0);

  del(1, 2);

  int index = fetch(1, 2);
  cout << splay[index].sum << '\n';

  while (!rec.empty()) {
    cout << rec.top() << ' ';
    rec.pop();
  }
  cout << '\n';

  inorder(root);
  ranker();
}
