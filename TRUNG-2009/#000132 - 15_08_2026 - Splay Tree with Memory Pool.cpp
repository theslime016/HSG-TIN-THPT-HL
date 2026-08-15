#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

const int maxn = 2e5 + 5;
struct node {
  long long data;
  int child[2];
  int parent;
} splay[maxn];

stack<int> wait;
long long nev = 0;
long long root = 0;
int node_count = 0;

int newNode(const long long &val) {
  int index = nev;
  if (!wait.empty()) {
    index = wait.top();
    wait.pop();
  } else
    index = ++node_count;
  splay[index].data = val;
  splay[index].child[0] = splay[index].child[1] = splay[index].parent = nev;
  return index;
}

int getdir(int index) {
  int pindex = splay[index].parent;
  return splay[pindex].child[1] == index;
}

void rtd(int index) {
  if (index == nev || splay[index].parent == nev)
    return;
  int p = splay[index].parent;
  int g = splay[p].parent;

  int dir = getdir(index);
  int t = splay[index].child[dir ^ 1];
  if (t != nev)
    splay[t].parent = p;
  splay[p].child[dir] = t;

  splay[index].child[dir ^ 1] = p;
  splay[p].parent = index;

  splay[index].parent = g;
  if (g != nev) {
    if (splay[g].child[0] == p)
      splay[g].child[0] = index;
    else
      splay[g].child[1] = index;
  }
}

void splaying(int index, int target_parent = nev) {
  if (index == nev)
    return;
  while (splay[index].parent != target_parent) {
    int p = splay[index].parent;
    int g = splay[p].parent;

    if (g != nev) {
      if (getdir(index) == getdir(p))
        rtd(p);
      else
        rtd(index);
    }
    rtd(index);
  }

  if (target_parent == nev)
    root = index;
}

void insert(const long long &val) {
  if (root == nev) {
    root = newNode(val);
    return;
  }

  int cur = root, p = nev;
  while (cur != nev) {
    p = cur;
    if (splay[cur].data == val) {
      splaying(cur);
      return;
    }

    if (splay[cur].data > val) {
      cur = splay[cur].child[0];
    } else {
      cur = splay[cur].child[1];
    }
  }

  int newnode = newNode(val);
  splay[newnode].parent = p;
  int dir = (splay[p].data < val);
  splay[p].child[dir] = newnode;

  splaying(newnode);
}

int search(const long long &val) {
  if (root == nev)
    return nev;
  int cur = root;
  int last = nev;

  while (cur != nev) {
    last = cur;
    if (splay[cur].data > val) {
      cur = splay[cur].child[0];
    } else if (splay[cur].data < val) {
      cur = splay[cur].child[1];
    } else {
      break;
    }
  }

  splaying(last);
  if (last == nev || splay[last].data != val)
    return nev;
  else
    return last;
}

void del(const long long &val) {
  int index = search(val);
  if (index == nev)
    return;

  int L = splay[index].child[0];
  int R = splay[index].child[1];
  wait.push(index);

  if (L == nev) {
    if (R != nev) {
      root = R;
      splay[R].parent = nev;
    }
    return;
  }
  if (R == nev) {
    if (L != nev) {
      root = L;
      splay[L].parent = nev;
    }
    return;
  }

  splay[L].parent = splay[R].parent = nev;
  int maxL = L;
  while (splay[maxL].child[1] != nev) {
    maxL = splay[maxL].child[1];
  }

  splaying(maxL);
  splay[maxL].child[1] = R;
  splay[R].parent = maxL;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n;
  cin >> n;
  for (int i = 0; i < n; i++) {
    int val;
    cin >> val;
    insert(val);
  }

  cout << search(32) << ' ' << search(90);

  splaying(4);
  splaying(2);
  splaying(7);

  del(45);

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
    if (splay[index].child[0] != nev)
      dq.push_back({rank + 1, splay[index].child[0]});
    if (splay[index].child[1] != nev)
      dq.push_back({rank + 1, splay[index].child[1]});
  }
}
