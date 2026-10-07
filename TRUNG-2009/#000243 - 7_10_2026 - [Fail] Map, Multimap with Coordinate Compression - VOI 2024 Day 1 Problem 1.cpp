#include <bits/stdc++.h>
using namespace std;

const int maxnode = 1e5 + 5;
const long long inf = 1e18;
//const int padding = 131072;

long long sum_x[maxnode];
long long sum_y[maxnode];

struct NODE {
  long long x, y;
  long long w;
  int x_compress;
  int y_compress;
} node[maxnode];

struct KEY {
  long long v1, v2;
  int index;
};

multimap<long long, int> row, col; // sum; index_compress
map<pair<int, int>, long long> occur; // x-y; w
KEY proc_x(int index, long long diff) {
  long long old_val = sum_x[ node[index].x_compress ];
  long long new_val = old_val + diff;
  row.erase(row.find(old_val));
  row.insert({new_val, -1});
  auto it = --row.end();
  KEY res = {(*it).first, (*(--it)).first, (*it).second};
  row.erase(row.find(new_val));
  row.insert({old_val, node[index].x_compress});
  return res;
}

KEY proc_y(int index, long long diff) {
  long long old_val = sum_y[ node[index].y_compress ];
  long long new_val = old_val + diff;
  col.erase(col.find(old_val));
  col.insert({new_val, -1});
  auto it = --col.end();
  KEY res = {(*it).first, (*(--it)).first, (*it).second};
  col.erase(col.find(new_val));
  col.insert({old_val, node[index].y_compress});
  return res;
}

void solve(int index, long long diff) {
  auto [xbest1, xbest2, index1] = proc_x(index, diff);
  auto [ybest1, ybest2, index2] = proc_y(index, diff);
  long long res = -inf;
  res = max({res, xbest1 + xbest2, ybest1 + ybest2});
  if (occur.count({index1, index2})) {
    res = max(res, xbest1 + ybest1 - occur[ {index1, index2}]);
  } else {
    res = max(res, xbest1 + ybest1);
  }
  cout << res << '\n';
}

#define _debug 1
int main() {
  cin.tie(0)->sync_with_stdio(0);

#if _debug == 1
  freopen("input.inp", "r", stdin);
#else
  freopen("TOWER.INP", "r", stdin);
  freopen("TOWER.OUT", "w", stdout);
#endif // _debug

  long long n;
  int m;
  int q;
  cin >> n >> m >> q;

  vector<long long> xcoor, ycoor;
  xcoor.reserve(m);
  ycoor.reserve(m);
  for (int i = 1; i <= m; i++) {
    cin >> node[i].x >> node[i].y >> node[i].w;
    xcoor.push_back(node[i].x);
    ycoor.push_back(node[i].y);
  }

  sort(xcoor.begin(), xcoor.end());
  xcoor.erase(unique(xcoor.begin(), xcoor.end()), xcoor.end());

  sort(ycoor.begin(), ycoor.end());
  ycoor.erase(unique(ycoor.begin(), ycoor.end()), ycoor.end());

  for (int i = 1; i <= m; i++) {
    int xfnd = lower_bound(xcoor.begin(), xcoor.end(), node[i].x) - xcoor.begin() + 1;
    int yfnd = lower_bound(ycoor.begin(), ycoor.end(), node[i].y) - ycoor.begin() + 1;
    sum_x[xfnd] += node[i].w;
    sum_y[yfnd] += node[i].w;
    node[i].x_compress = xfnd;
    node[i].y_compress = yfnd;
    occur.insert({{xfnd, yfnd}, node[i].w});
  }

  for (int index = 1; index <= xcoor.size(); index++) {
    row.insert({sum_x[index], index});
  }

  for (int index = 1; index <= ycoor.size(); index++) {
    col.insert({sum_y[index], index});
  }

  solve(1, 0);
  for (int i = 1; i <= q; i++) {
    int index;
    long long diff;
    cin >> index >> diff;
    solve(index, diff);
  }

}
