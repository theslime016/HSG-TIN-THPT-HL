#include <bits/stdc++.h>
using namespace std;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
long long rnd(long long l, long long r) {
  return uniform_int_distribution<long long>(l, r)(rng);
}

int main() {
  cin.tie(0)->sync_with_stdio(0);

  system("g++ main5.cpp -o main");
  int x = 6;

  vector<string> choice = {"0 1 1 1", "1 0 1 1", "1 1 0 1",
                           "1 1 1 0", "0 0 1 1",
                           "0 1 0 1", "0 1 1 0", "1 0 0 1",
                           "1 0 1 0", "1 1 0 0", "1 0 0 0",
                           "0 1 0 0", "0 0 1 0", "0 0 0 1"
                          };
  int test = 1;
  for (int n = 3; n <= x; n++) {
    for (int m = 3; m <= x; m++) {
      vector<string> task;
      auto make_dfs = [&](int index, const auto& self) -> void {
        if (index == n*m + 1) {

          ofstream f("input.inp", ios::trunc);
          f << n << ' ' << m << '\n';
          for (const string& temp : task) {
            f << temp << '\n';
          }
          f.close();

          system("./main");
          if (system("diff output.out output.ans > /dev/null") != 0) {
            cerr << "TEST " << test << "!!!!!";
            exit(0);
          } else {
            cerr << "TEST " << test << "+++" << '\n';
          }

          test++;

          return;
        }

        /*
        int i = rnd(0, choice.size() - 1);
        task.push_back(choice[i]);
        self(index + 1, self);
        task.pop_back();

        return;
        */

        task.push_back( "0 1 1 1" );
        self(index + 1, self);
        task.pop_back();

        task.push_back( "1 0 1 1" );
        self(index + 1, self);
        task.pop_back();

        task.push_back( "1 1 0 1" );
        self(index + 1, self);
        task.pop_back();

        task.push_back( "1 1 1 0" );
        self(index + 1, self);
        task.pop_back();

        ///

        task.push_back( "0 0 1 1" );
        self(index + 1, self);
        task.pop_back();

        task.push_back( "0 1 0 1" );
        self(index + 1, self);
        task.pop_back();

        task.push_back( "0 1 1 0" );
        self(index + 1, self);
        task.pop_back();

        task.push_back( "1 0 0 1" );
        self(index + 1, self);
        task.pop_back();

        task.push_back( "1 0 1 0" );
        self(index + 1, self);
        task.pop_back();

        task.push_back( "1 1 0 0" );
        self(index + 1, self);
        task.pop_back();

        ///

        task.push_back( "1 0 0 0" );
        self(index + 1, self);
        task.pop_back();

        task.push_back( "0 1 0 0" );
        self(index + 1, self);
        task.pop_back();

        task.push_back( "0 0 1 0" );
        self(index + 1, self);
        task.pop_back();

        task.push_back( "0 0 0 1" );
        self(index + 1, self);
        task.pop_back();
      };

      make_dfs(1, make_dfs);

    }
  }

}
