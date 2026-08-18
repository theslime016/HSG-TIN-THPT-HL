#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

struct node {
  long long down, up; // constant
  int count;          // dynamic
  long long length;   // dynamic
  // value = count * length (current)

  node *left;
  node *right;

  node(long long a, long long b) {
    down = a;
    up = b;
    count = 0;
    length = 0;
    left = right = {};
  }
};

node *build(int l, int r, const vector<long long> &A) {
  if (l + 1 == r)
    return new node(A[l], A[r]);

  int mid = l + (r - l) / 2;
  node *current = new node(A[l], A[r]);

  current->left = build(l, mid, A);
  current->right = build(mid, r, A);
  return current;
}

void travel(node *root) {
  if (root == nullptr)
    return;
  travel(root->left);
  cout << root->down << "->" << root->up << ' ' << root->length << ' '
       << root->count << '\n';
  travel(root->right);
}

void insert(int l, int r, node *root) {
  if (root == nullptr)
    return;
  if (l <= root->down && root->up <= r) {
    root->count++;
    root->length = (root->up - root->down) * root->count;
    return;
  }
  insert(l, r, root->left);
  insert(l, r, root->right);
  root->length = 0;
  if (root->left != nullptr)
    root->length += root->left->length;
  if (root->right != nullptr)
    root->length += root->right->length;
}

void del(int l, int r, node *root) {
  if (root == nullptr)
    return;
  if (l <= root->down && root->up <= r) {
    root->count--;
    if (root->count == 0)
      root->length = 0;
    else
      root->length = (root->up - root->down) * root->count;
    return;
  }
  del(l, r, root->left);
  del(l, r, root->right);
  root->length = 0;
  if (root->left != nullptr)
    root->length += root->left->length;
  if (root->right != nullptr)
    root->length += root->right->length;
}

struct line {
  int op; // 0->insert/1->del
  int x;
  int down, up;
};

const long long inf = 1e15;

#define debugr(x) cout << #x << " = " << (x) << '\n'

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n;
  cin >> n;
  vector<line> query;
  vector<long long> ylevel;
  query.reserve(2 * n);
  ylevel.reserve(n + 1);
  for (int i = 1; i <= n; i++) {
    int a, b, c, d;
    cin >> a >> b >> c >> d;

    query.push_back({0, a, b, d});
    query.push_back({1, c, b, d});

    ylevel.push_back(b);
    ylevel.push_back(d);
  }

  sort(ylevel.begin(), ylevel.end());
  ylevel.erase(unique(ylevel.begin(), ylevel.end()), ylevel.end());

  node *root = build(0, (int)ylevel.size() - 1, ylevel);

  sort(query.begin(), query.end(),
       [&](const line &a, const line &b) { return a.x < b.x; });
  for (const line &t : query)
    cout << t.op << ' ' << t.x << ' ' << t.down << ' ' << t.up << '\n';

  long long res = 0;
  for (int i = 0; i < 2 * n; i++) {

    if (i > 0) {
      long long d = query[i].x - query[i - 1].x;
      res += d * root->length;
      debugr(d);
      debugr(root->length);
    }

    if (query[i].op == 0) {
      insert(query[i].down, query[i].up, root);
    } else {
      del(query[i].down, query[i].up, root);
    }

    travel(root);
    cout << '\n';
  }
  cout << res;
}
