/*late in autumn*/
#include <bits/stdc++.h>
using namespace std;

struct uf {
  int n;
  int timer;
  vector<int> data;
  stack<pair<int, int>> timeline; // index : old data[index]
  stack<int> tag;

  uf(int n) {
    this->n = n;
    this->timer = 0;
    data.assign(n + 1, 0);
    iota(data.begin(), data.end(), 0);
  }

  int fetch(int index) {
    if (index == data[index])
      return index;
    int newval = fetch(data[index]);
    if (newval != data[index]) {
      timeline.push({index, data[index]});
      tag.push(timer);
    }
    return data[index] = newval;
  }

  void compress(int a, int b) {
    timer++;
    a = fetch(a);
    b = fetch(b);
    if (a != b) {
      timeline.push({a, data[a]});
      data[a] = b;
    }
  }

  void rollback(int step) {
    int last_id = -1;
    while (step > 0 && !timeline.empty()) {
      auto [index, val] = timeline.top();
      timeline.pop();
      data[index] = val;

      int id = tag.top();
      tag.pop();
      if (id != last_id) {
        last_id = id;
        step--;
      }
    }
  }
};

int main() { cin.tie(0)->sync_with_stdio(0); }
