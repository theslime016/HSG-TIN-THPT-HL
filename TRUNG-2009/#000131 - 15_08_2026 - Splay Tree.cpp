#include <bits/stdc++.h>
using namespace std;

struct node {
  int data;
  node *left;
  node *right;
  node *parent;

  node() = default;
  node(int n) {
    data = n;
    left = right = parent = {};
  }
};

void rotateDynamic(node *x) {
  if (x == nullptr || x->parent == nullptr)
    return;
  node *p = x->parent;
  node *g = p->parent;

  if (p->left == x) {
    p->left = x->right;
    if (x->right)
      x->right->parent = p;
    x->right = p;
  } else {
    p->right = x->left;
    if (x->left)
      x->left->parent = p;
    x->left = p;
  }

  p->parent = x;
  x->parent = g;

  if (g != nullptr) {
    if (g->left == p)
      g->left = x;
    else
      g->right = x;
  }
}

node *splay(node *x, node *target_parent) {
  while (x->parent != target_parent) {
    node *p = x->parent;
    node *g = p->parent;
    if (g != target_parent) {
      bool leftp = (p->left == x);
      bool leftg = (g->left == p);
      if (leftp == leftg) {
        // zig zig
        rotateDynamic(p);
      } else {
        // zig zag
        rotateDynamic(x);
      }
    }
    rotateDynamic(x);
  }
  return x;
}

void search(node *root, const long long &val) {
  if (root == nullptr)
    return;
  if (root->data == val)
    throw splay(root, nullptr);

  if (root->data < val) {
    search(root->right, val);
    splay(root->right, nullptr);
  } else {
    search(root->left, val);
    splay(root->left, nullptr);
  }
  throw;
}

node *insert(node *root, const long long &val) {
  if (root == nullptr) {
    return new node(val);
  }

  node *cur = root;
  node *p = nullptr;

  while (cur != nullptr) {
    p = cur;
    if (cur->data < val)
      cur = cur->right;
    else if (cur->data > val)
      cur = cur->left;
    else
      return root;
  }

  node *newnode = new node(val);
  newnode->parent = p;
  if (p->data < val)
    p->right = newnode;
  else
    p->left = newnode;

  return splay(newnode, nullptr);
}

node *del(node *root, const long long &val) {
  try {
    search(root, val);
  } catch (node *res) {
    root = res;
  }

  node *l = root->left;
  node *r = root->right;
  node *newroot = nullptr;
  if (l != nullptr) {
    newroot = l;
    while (newroot->right != nullptr) {
      newroot = newroot->right;
    }
    l->parent = nullptr;
    splay(newroot, nullptr);
    newroot->right = r;
    if (r)
      r->parent = newroot;
  } else if (r != nullptr) {
    newroot = r;
    while (newroot->left != nullptr) {
      newroot = newroot->left;
    }
    r->parent = nullptr;
    splay(newroot, nullptr);
    newroot->left = l;
    if (l)
      l->parent = newroot;
  }

  delete root;
  return newroot;
}

void preOrder(node *root) {
  if (root != nullptr) {
    preOrder(root->left);
    cout << root->data << ' ';
    preOrder(root->right);
  }
}

int main() {
  cin.tie(0)->sync_with_stdio(0);

  freopen("input.inp", "r", stdin);

  int n;
  cin >> n;
  node *root = nullptr;
  for (int i = 0; i < n; i++) {
    int val;
    cin >> val;
    root = insert(root, val);
  }

  node *A, *B = {};
  try {
    search(root, 90);
  } catch (node *res) {
    root = A = res;
  }

  try {
    search(root, 76);
  } catch (node *res) {
    root = B = res;
  }

  try {
    search(root, 45);
  } catch (node *res) {
    root = res;
  };

  root = del(root, 8);

  splay(A, B->parent);

  while (root->parent != nullptr) {
    root = root->parent;
  }

  preOrder(root);

  deque<pair<int, node *>> dq; // rank - node*
  dq.push_back({1, root});

  int timer = 0;
  while (!dq.empty()) {
    auto [rank, a] = dq.front();
    dq.pop_front();

    if (rank != timer) {
      cout << '\n' << "rank:" << rank << ' ';
    }
    timer = rank;

    cout << a->data << ' ';
    if (a->left != nullptr)
      dq.push_back({rank + 1, a->left});
    if (a->right != nullptr)
      dq.push_back({rank + 1, a->right});
  }
}
