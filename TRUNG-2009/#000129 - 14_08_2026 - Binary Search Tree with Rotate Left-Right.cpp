#include <bits/stdc++.h>
using namespace std;

struct node {
  long long data;
  node *left;
  node *right;

  node() = default;
  node(long long val) {
    data = val;
    left = right = {};
  }
};

node *insert(node *root, const long long &val) {
  if (root == nullptr) {
    return new node(val);
  }

  if (root->data < val) {
    root->right = insert(root->right, val);
  } else if (root->data > val) {
    root->left = insert(root->left, val);
  }

  return root;
}

bool search(node *root, const long long &val) {
  if (root == nullptr)
    return false;
  if (root->data == val)
    return true;

  if (root->data < val) {
    return search(root->right, val);
  } else {
    return search(root->left, val);
  }
}

void idT(node *root) {
  if (root != nullptr) {
    idT(root->left);
    cout << root->data << ' ';
    idT(root->right);
  }
}

node *findMin(node *root) {
  if (root != nullptr && root->left != nullptr) {
    root = findMin(root->left);
  }
  return root;
}

node *findMax(node *root) {
  if (root != nullptr && root->right != nullptr) {
    root = findMax(root->right);
  }
  return root;
}

node *del(node *root, const long long &val) {
  if (root == nullptr)
    return root;

  if (val > root->data) {
    root->right = del(root->right, val);
  } else if (val < root->data) {
    root->left = del(root->left, val);
  } else {
    if (root->left == nullptr) {
      node *temp = root->right;
      delete root;
      return temp;
    } else if (root->right == nullptr) {
      node *temp = root->left;
      delete root;
      return temp;
    }

    node *temp = findMin(root->right);
    root->data = temp->data;
    root->right = del(root->right, temp->data);
  }
  return root;
}

node *rotateLeft(node *x) {
  node *y = x->right;
  node *t = y->right;

  y->left = x;
  x->right = t;
  return y;
}

node *rotateRight(node *x) {
  node *y = x->left;
  node *t = y->left;

  y->left = x;
  x->left = t;
  return y;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  int n;
  cin >> n;

  node *root = nullptr;
  for (int i = 0; i < n; i++) {
    int a;
    cin >> a;
    root = insert(root, a);
  }

  cout << search(root, 12) << '\n';
  cout << (*findMax(root)).data << '\n';
  cout << (*findMin(root)).data << '\n';
  del(root, 76);
  idT(root);

  root = rotateRight(root);
  deque<pair<int, node *>> dq; // rank - node
  dq.push_front({1, root});
  int timer = 0;

  while (!dq.empty()) {
    auto [rank, a] = dq.front();
    dq.pop_front();
    if (rank != timer)
      cout << '\n' << "rank:" << rank << ' ';
    cout << a->data << ' ';

    timer = rank;
    if (a->left != nullptr)
      dq.push_back({rank + 1, a->left});
    if (a->right != nullptr)
      dq.push_back({rank + 1, a->right});
  }
}
