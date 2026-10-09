mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

class MajorityChecker {
private:
static const int maxn = 2e4 + 5;
int n;
vector<int> A;
vector<int> occur[maxn];
public:
    MajorityChecker(vector<int>& arr) {
        n = arr.size();
        A.assign(n+1, 0);
        for (int i = 1; i <= n; i++) {
            A[i] = arr[i-1];
            occur[ A[i] ].push_back(i);
        }
    }

    int rnd(int l, int r) {
        return uniform_int_distribution<>(l, r)(rng);
    }
    
    int query(int left, int right, int threshold) {
        left++;
        right++;
        for (int i = 1; i <= 20; i++) {
            int pt = rnd(left, right);
            int val = A[pt];
            int start = lower_bound(occur[val].begin(), occur[val].end(), left) - occur[val].begin();
            int stop = upper_bound(occur[val].begin(), occur[val].end(), right) - occur[val].begin() - 1;
            if (stop - start + 1 >= threshold) return val;
        }
        return -1;
    }
};
