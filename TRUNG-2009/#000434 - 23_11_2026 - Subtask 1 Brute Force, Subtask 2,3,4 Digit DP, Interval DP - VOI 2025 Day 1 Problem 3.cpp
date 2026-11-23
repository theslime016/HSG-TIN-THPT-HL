#include <bits/stdc++.h>
using namespace std;

#define _debug 0

#if _debug == 1
void logout() {
  cerr << endl;
}
template<typename H, typename... T>
void logout(H h, T... t) {
  cerr << h << ", ";
  logout(t...);
}
#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:" << endl, logout(__VA_ARGS__)
#define debugtitle cerr << __PRETTY_FUNCTION__ << " line: " << __LINE__ << endl
#define newline cerr << endl

#else
#define debug(...) (void(0))
#define debugtitle (void(0))
#define newline (void(0))

#endif // _debug

const int maxt = 5e4 + 5;
const long long mod = 1e9 + 7;
int t, k;
pair<string, string> task[maxt];

struct SUB1 {
  bool is_subtask() {
    if (t > 10)
      return false;
    for (int i = 1; i <= t; i++) {
      if (task[i].second.size() > 7)
        return false;
    }
    return true;
  }

  int cnt[20];
  long long W(long long x) {
    memset(cnt, 0, sizeof cnt);
    cnt[0] = 1;

    long long res = 0;

    int last_char = -1;
    int pref = 0;
    while (x > 0) {
      int current_char = x%10;

      pref ^= current_char;
      res = (res + cnt[pref])%mod;
      cnt[pref]++;

      if (last_char != -1) {
        if ((current_char + last_char)%5 == 0) {
          return 0;
        }
      }

      last_char = current_char;
      x /= 10;
    }

    return res;
  }

  long long get_num(const string& x) {
    long long res = 0;
    for (char c : x) {
      res *= 10;
      res += c - '0';
    }
    return res;
  }

  void solve() {
    for (int i = 1; i <= t; i++) {
      long long res = 0;
      long long left = get_num(task[i].first);
      long long right = get_num(task[i].second);
      for (long long j = left; j <= right; j++) {
        long long val = W(j)%mod;
        if (k == 2)
          val = (val * val)%mod;
        res = (res + val)%mod;
      }

      cout << res << '\n';
    }
  }
} sub1;


struct SUB234 {
  long long dp[1005][5][16][3];
  long long dp_tight[1005][16][3];
  int visited[1005][16][3];
  int timer = 0;
  /// pos - last_rem(%5) - current_prefix_xor - state

  /// state: 0:none 1:open 2:end

  string num;
  long long make_dp(int index, int last_rem, int current_xor, int state, int flag_tight, int flag_head) {
    int pos = (int)num.size() - index;
    if (pos == 0) {
      return !flag_head && (state == 2);
    }

    if (flag_tight) {
      if (visited[pos][current_xor][state] == timer)
        return dp_tight[pos][current_xor][state];
    } else if (!flag_head
               && dp[pos][last_rem][current_xor][state] != -1) {
      return dp[pos][last_rem][current_xor][state];
    }

    long long res = 0;
    int lim = flag_tight ? (num[index] - '0') : 9;
    for (int c = 0; c <= lim; c++) {
      int new_flag_head = flag_head && (c == 0);
      int new_flag_tight = flag_tight && (c == lim);

      int new_rem = c%5;
      int new_xor = current_xor ^ c;

      if (new_flag_head) {
        res = (res + make_dp(index + 1, 0, 0, 0,
                             new_flag_tight, 1)) % mod;
        continue;
      }

      if (!flag_head && (last_rem + c)%5 == 0)
        continue;

      if (state == 0) {
        /// none -> none/open
        long long to_none = make_dp(index + 1, new_rem, 0, 0,
                                    new_flag_tight, new_flag_head);

        long long to_open = make_dp(index + 1, new_rem,
                                    new_xor, 1, new_flag_tight, new_flag_head);

        /// none -> open+end
        long long to_end = 0;
        if (c == 0) {
          to_end = make_dp(index + 1, 0, 0, 2, new_flag_tight, new_flag_head);
        }

        res = (res + to_none) % mod;
        res = (res + to_open) % mod;
        res = (res + to_end) % mod;



      } else if (state == 1) {
        /// open -> open
        long long to_open = make_dp(index + 1, new_rem,
                                    new_xor, 1, new_flag_tight, new_flag_head);

        /// open -> end
        long long to_end = 0;
        if (new_xor == 0) {
          to_end = make_dp(index + 1, new_rem, 0, 2,
                           new_flag_tight, new_flag_head);
        }

        res = (res + to_open) % mod;
        res = (res + to_end) % mod;



      } else if (state == 2) {
        /// end -> end
        long long to_end = make_dp(index + 1, new_rem, current_xor, 2, new_flag_tight, new_flag_head);

        res = (res + to_end) % mod;
      }

//#if _debug == 1
//      debugtitle;
//      debug(index, pos);
//      debug(last_rem, current_xor, state);
//      debug(flag_head, flag_tight);
//      debug(res);
//      newline;
//
//      debug(c, lim);
//      debug(new_flag_head, new_flag_tight);
//      debug(new_rem, new_xor);
//      debug(res);
//      newline;
//      newline;
//#endif // _debug

    }

    if (flag_tight) {
      visited[pos][current_xor][state] = timer;
      dp_tight[pos][current_xor][state] = res;
    } else if (!flag_head) {
      dp[pos][last_rem][current_xor][state] = res;
    }

    return res;
  }

  string subtract_one(const string& x) {
    if (x == "1")
      return "0";

    string res = "";
    int sub = -1;
    int index = (int)x.size() - 1;

    while (index >= 0) {
      int c = x[index] - '0' + sub;
      index--;
      if (c < 0) {
        res.push_back('9');
        sub = c;
      } else {
        res.push_back(c + '0');
        sub = 0;
      }
    }

    while (!res.empty() && res.back() == '0')
      res.pop_back();

    reverse(res.begin(), res.end());
    return res;
  }

  long long query_fetch(const string& x) {
    num = x;
    timer++;
    return make_dp(0, 0, 0, 0, 1, 1);
  }

  void solve() {
    memset(dp, -1, sizeof dp);
    for (int i = 1; i <= t; i++) {
      long long v1 = query_fetch(task[i].second);
      long long v2 = query_fetch(subtract_one(task[i].first));

      long long res = ((v1 - v2)%mod + mod)%mod;
      cout << res << '\n';
    }
  }

  bool is_subtask() {
    return k == 1;
  }

} sub234;


int main() {
  cin.tie(0)->sync_with_stdio(0);

  freopen("PNUM.INP", "r", stdin);
  freopen("PNUM.OUT", "w", stdout);

  cin >> k >> t;
  for (int i = 1; i <= t; i++) {
    cin >> task[i].first >> task[i].second;
  }

  if (sub234.is_subtask())
    return sub234.solve(), 0;

//  if (sub1.is_subtask())
  return sub1.solve(), 0;
}
