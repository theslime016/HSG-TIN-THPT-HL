#include <bits/stdc++.h>
using namespace std;

const int maxn = 4e3 + 5;
const int maxedge = 4e5 + 5;
struct edge
{
  int a, b;
  long long w;
  bool operator<(const edge &other) const
  {
    return this->w < other.w;
  }
} task[maxedge];

struct uf
{
  int n;
  long long res;
  vector<int> data;
  vector<int> bucket;
  uf(int n)
  {
    this->n = n;
    this->res = 0;
    data.assign(n + 1, 0);
    iota(data.begin(), data.end(), 0);
    bucket.assign(n + 1, 1);
  }

  void reset()
  {
    this->res = 0;
    iota(data.begin(), data.end(), 0);
    bucket.assign(n + 1, 1);
  }

  int fnd(int index)
  {
    if (data[index] == index)
      return index;
    return data[index] = fnd(data[index]);
  }

  void proc(const edge &x)
  {
    int a = fnd(x.a);
    int b = fnd(x.b);
    if (a != b)
    {
      if (bucket[a] < bucket[b])
        swap(a, b);
      bucket[a] += bucket[b];
      data[b] = a;
      res += x.w;
    }
  }
};

int n, m, q;

int main()
{
  cin.tie(0)->sync_with_stdio(0);

  cin >> n >> m;
  for (int i = 1; i <= m; i++)
  {
    cin >> task[i].a >> task[i].b >> task[i].w;
  }

  sort(task + 1, task + m + 1);

  int q;
  cin >> q;
  uf dsu(n);
  while (q--)
  {
    int a, b;
    cin >> a >> b;
    dsu.reset();
    dsu.proc({a, b, 0});
    for (int i = 1; i <= m; i++)
    {
      dsu.proc(task[i]);
    }
    cout << dsu.res << '\n';
  }
}
