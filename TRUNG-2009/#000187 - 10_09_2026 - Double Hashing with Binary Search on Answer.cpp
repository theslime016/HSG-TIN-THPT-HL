#include <bits/stdc++.h>
using namespace std;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
long long rnd(long long l, long long r) {
    return uniform_int_distribution<long long>(l, r)(rng);
}

const int maxn = 1e5 + 5;
const long long base = rnd(300, 500);
const long long mod1 = 1e9 + 7;
const long long mod2 = 1e9 + 9;
long long power1[maxn];
long long power2[maxn];

long long hashA1[maxn];
long long hashA2[maxn];

long long hashB1[maxn];
long long hashB2[maxn];

string A, B;
int n, m;
void build_hash() {
    if (A.size() < B.size()) swap(A, B);
    n = A.size();
    m = B.size();
    A = '#' + A;
    B = '#' + B;
    power1[0] = power2[0] = 1;
    for (int i = 1; i <= n; i++) {
        hashA1[i] = (hashA1[i-1]*base + A[i])%mod1;
        hashA2[i] = (hashA2[i-1]*base + A[i])%mod2;

        power1[i] = (power1[i-1]*base)%mod1;
        power2[i] = (power2[i-1]*base)%mod2;
    }

    for (int i = 1; i <= m; i++) {
        hashB1[i] = (hashB1[i-1]*base + B[i])%mod1;
        hashB2[i] = (hashB2[i-1]*base + B[i])%mod2;
    }
}

bool verify(int l, int r) {
    long long HA1 = (hashA1[r] - (hashA1[l-1]*power1[r-l+1])%mod1 + mod1)%mod1;
    long long HB1 = (hashB1[r] - (hashB1[l-1]*power1[r-l+1])%mod1 + mod1)%mod1;
    if (HA1 != HB1) return false;
    long long HA2 = (hashA2[r] - (hashA2[l-1]*power2[r-l+1])%mod2 + mod2)%mod2;
    long long HB2 = (hashB2[r] - (hashB2[l-1]*power2[r-l+1])%mod2 + mod2)%mod2;
    return HA2 == HB2;
}

pair<long long, long long> get_hashA(int l, int r) {
    long long HA1 = (hashA1[r] - (hashA1[l-1]*power1[r-l+1])%mod1 + mod1)%mod1;
    long long HA2 = (hashA2[r] - (hashA2[l-1]*power2[r-l+1])%mod2 + mod2)%mod2;
    return {HA1, HA2};
}

pair<long long, long long> get_hashB(int l, int r) {
    long long HB1 = (hashB1[r] - (hashB1[l-1]*power1[r-l+1])%mod1 + mod1)%mod1;
    long long HB2 = (hashB2[r] - (hashB2[l-1]*power2[r-l+1])%mod2 + mod2)%mod2;
    return {HB1, HB2};
}

bool check(int len) {
    len--;
    vector<pair<long long, long long>> ss;
    ss.reserve(n-len+1);
    for (int l = 1; l <= n - len; l++) {
        int r = l + len;
        auto [HA1, HA2] = get_hashA(l, r);
        ss.push_back(make_pair(HA1, HA2));
    }

    sort(ss.begin(), ss.end());
    for (int l = 1; l <= m - len; l++) {
        int r = l + len;
        auto [HB1, HB2] = get_hashB(l, r);
        if (binary_search(ss.begin(), ss.end(), make_pair(HB1, HB2))) return true;
    }
    return false;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    freopen("input.inp", "r", stdin);

    cin >> A >> B;
    build_hash();

    int len = 0;
    int maxlen = min(n, m);
    for (int diff = maxlen - len; diff > 0; diff /= 2) {
        while (diff + len <= maxlen && check(diff + len)) {
            len += diff;
        }
    }
    cout << len;
}
