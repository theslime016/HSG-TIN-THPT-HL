#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5 + 5;
long long x[maxn], y[maxn];
int n, q;

double get_dist(int i, int j) {
    double r1 = abs(x[i]-x[j]);
    double r2 = abs(y[i]-y[j]);
    return sqrt(r1*r1 + r2*r2);
}

double get_chicken(long long a, long long b, int i) {
    double r1 = abs(a - x[i]);
    double r2 = abs(b - y[i]);
    return sqrt(r1*r1 + r2*r2);
}

double get_area(double a, double b, double c) {
    double p = (a + b + c)/2;
    return sqrt(p * (p-a) * (p-b) * (p-c));
}

#define _debug 1

int main() {
    cin.tie(0)->sync_with_stdio(0);

    #if _debug == 1
    freopen("input.inp", "r", stdin);
    #else

    #endif // _debug

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> x[i] >> y[i];
    }

    cin >> q;
    int res = 0;
    while (q--) {
        long long a, b;
        cin >> a >> b;
        int flag = 1;
        for (int i = 1; i <= n && flag; i++) {
            for (int j = i+1; j <= n && flag; j++) {
                for (int k = j+1; k <= n && flag; k++) {
                    double dog = get_area(get_dist(i, j), get_dist(j, k), get_dist(i, k));
                    double chicken1 = get_area(get_chicken(a, b, i), get_chicken(a, b, j),
                                               get_dist(i, j));
                    double chicken2 = get_area(get_chicken(a, b, k), get_chicken(a, b, j),
                                               get_dist(k, j));
                    double chicken3 = get_area(get_chicken(a, b, i), get_chicken(a, b, k),
                                               get_dist(i, k));
                    if (dog >= chicken1 + chicken2 + chicken3) {
                        res++;
                        flag = 0;
                        break;
                    }
                }
            }
        }
    }

    cout << res;
}
