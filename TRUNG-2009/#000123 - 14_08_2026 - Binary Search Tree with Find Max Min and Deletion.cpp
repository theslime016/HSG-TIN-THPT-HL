#include <bits/stdc++.h>
using namespace std;

struct Node {
  long long data;
  Node *left;
  Node *right;

  Node() = default;
  Node(long long val) {
    data = val;
    left = right = {};
  }
};

Node *insert(Node *root, const long long &val) {
  if (root == nullptr) {
    return new Node(val);
  }

  if (root->data < val) {
    root->right = insert(root->right, val);
  } else if (root->data > val) {
    root->left = insert(root->left, val);
  }

  return root;
}

bool search(Node *root, const long long &val) {
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

void idT(Node *root) {
  if (root != nullptr) {
    idT(root->left);
    cout << root->data << ' ';
    idT(root->right);
  }
}

Node *findMin(Node *root) {
  if (root != nullptr && root->left != nullptr) {
    root = findMin(root->left);
  }
  return root;
}

Node *findMax(Node *root) {
  if (root != nullptr && root->right != nullptr) {
    root = findMax(root->right);
  }
  return root;
}

Node *del(Node *root, const long long &val) {
  if (root == nullptr)
    return root;

  if (val > root->data) {
    root->right = del(root->right, val);
  } else if (val < root->data) {
    root->left = del(root->left, val);
  } else {
    if (root->left == nullptr) {
      Node *temp = root->right;
      delete root;
      return temp;
    } else if (root->right == nullptr) {
      Node *temp = root->left;
      delete root;
      return temp;
    }

    Node *temp = findMin(root->right);
    root->data = temp->data;
    root->right = del(root->right, temp->data);
  }
  return root;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  int n;
  cin >> n;

  Node *root = nullptr;
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
}
