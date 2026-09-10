#include <bits/stdc++.h>
using namespace std;

/*
Tên bài toán: Mật Mã Đối Xứng (Longest Palindromic Substring)

Mô tả:
Một cuộn giấy da chứa một chuỗi ký tự cổ đại S. Thông điệp cốt lõi được giấu trong một đoạn con liên tiếp có tính chất đối xứng (đọc từ trái sang phải hay từ phải sang trái đều giống hệt nhau). Hãy tìm độ dài của đoạn thông điệp đối xứng dài nhất.

Dữ liệu vào (Input):
- Một dòng duy nhất chứa xâu S chỉ gồm các chữ cái tiếng Anh in thường ('a' - 'z').

Dữ liệu ra (Output):
- In ra một số nguyên duy nhất là độ dài của xâu con đối xứng dài nhất có trong S.

Giới hạn:
- Độ dài xâu S: 1 <= N <= 10^5.
- Thời gian: 1.0 giây.
- Bộ nhớ: 256 MB.

Ví dụ 1:
Input:
abacaba
Output:
7

Ví dụ 2:
Input:
forgeeksskeegfor
Output:
10
*/

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
long long rnd(long long l, long long r) {
    return uniform_int_distribution<long long>(l, r)(rng);
}

const int maxn = 1e5 + 5;
const int maxhash = 2;
/// HERE
const long long base = 300;
long long mod[maxhash] = {(long long)1e9 + 7, (long long)1e9 + 3};
long long hashing[maxhash][maxn];
long long power[maxhash][maxn];
long long revhash[maxhash][maxn];
string s, rev;
int n;

void build_hash() {
    for (int j = 0; j < maxhash; j++) {
        power[j][0] = 1;
    }
    n = s.size() - 1; // padding
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < maxhash; j++) {
            hashing[j][i] = (hashing[j][i-1]*base + s[i])%mod[j];
            revhash[j][i] = (revhash[j][i-1]*base + rev[i])%mod[j];
            power[j][i] = (power[j][i-1]*base)%mod[j];
        }
    }
}

bool verify(int l, int r) {
    for (int ver = 0; ver < maxhash; ver++) {
        long long current = (hashing[ver][r] - (hashing[ver][l-1]*power[ver][r-l+1])%mod[ver] + mod[ver])%mod[ver];
        int new_l = n-r+1;
        int new_r = n-l+1;
        long long other = (revhash[ver][new_r] - (revhash[ver][new_l-1]*power[ver][new_r-new_l+1])%mod[ver] + mod[ver])%mod[ver];
        if (current != other) return false;
    }
    return true;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    freopen("input.inp", "r", stdin);

    cin >> s;
    rev = s;
    s = '-' + s;
    reverse(rev.begin(), rev.end());
    rev = '-' + rev;

    build_hash();
    int res = 1;
    for (int i = 1; i <= n; i++) {
        int low = 0, high = min(i-1, n-i), best = 0;
        while (low <= high) {
            int len = low + (high - low)/2;
            if (verify(i - len, i + len)) {
                best = len;
                low++;
            } else {
                high--;
            }
        }
        res = max(res, best * 2 + 1);

        if (s[i] != s[i+1]) continue;
        low = 0, high = min(i-1, n-i+1), best = 0;
        while (low <= high) {
            int len = low + (high - low)/2;
            if (verify(i - len, i + len + 1)) {
                best = len;
                low++;
            } else {
                high--;
            }
        }
        res = max(res, (best+1)*2);
    }
    cout << res;
}
