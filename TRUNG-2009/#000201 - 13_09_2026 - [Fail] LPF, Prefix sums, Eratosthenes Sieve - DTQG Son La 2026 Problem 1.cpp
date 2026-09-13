#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e6 + 5;
int lpf[maxn];
long long sum_factor[maxn];
int prime[maxn];
int pos = 0;

const int maxprime = 2e6+5;
bitset<maxprime> is_prime;
long long pref1[maxn];
int pref2[maxn];

#define _DEBUG 0

int main() {
    cin.tie(0)->sync_with_stdio(0);

    #if _DEBUG
    freopen("input.inp", "r", stdin);
    #else
    freopen("CPNT.INP", "r", stdin);
    freopen("CPNT.OUT", "w", stdout);
    #endif

    iota(sum_factor, sum_factor+maxn, 0LL);

    for (int i = 2; i < maxn; i++) {
        if (lpf[i] == 0) {
            prime[pos++] = i;
            lpf[i] = i;
        }
        for (int j = 0; prime[j] * i < maxn; j++) {
            int nxt = prime[j] * i;
            lpf[nxt] = prime[j];
            sum_factor[nxt] += sum_factor[i];
            if (prime[j] == lpf[i]) break;
            sum_factor[nxt] += sum_factor[prime[j]];
        }
    }

    is_prime.set();
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i*i < maxprime; i++) {
        if (!is_prime[i]) continue;
        for (int j = i*i; j < maxprime; j+=i) {
            is_prime[j] = false;
        }
    }


    pref1[1] = 1;
    for (int i = 2; i*i < maxn; i++) {
        int nxt = i*i;
        pref1[nxt] += nxt;
        if (is_prime[sum_factor[nxt]+1]) pref2[nxt]++;
    }

    for (int i = 1; i < maxn; i++) {
        pref1[i] += pref1[i-1];
        pref2[i] += pref2[i-1];
    }

    int t; cin >> t;
    while (t--) {
        int l, r;
        cin >> l >> r;
        cout << pref1[r] - pref1[l-1] << ' ' << pref2[r] - pref2[l-1] << '\n';
        #if _DEBUG
        long long sum1 = 0;
        int cnt = 0;
        for (int i = l; i <= r; i++) {
            for (int j = 1; j*j <= i; j++) {
                if (j*j == i) {
                    sum1 += i;
                    long long local = 0;
                    for (int k = 1; k <= i; k++) {
                        if (i%k == 0) {
                            local += k;
                        }
                    }

                    int flag = 1;
                    for (int i = 2; i < local; i++) {
                        if (local%i == 0) {
                            flag = 0;
                            break;
                        }
                    }
                    if (flag) cnt++;
                }
            }
        }
        cout << sum1 << ' ' << cnt << '\n';
        #endif // _DEBUG
    }
}
