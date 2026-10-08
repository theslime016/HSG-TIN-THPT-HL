const int maxn = 2e4 + 5;
const int padding = 32768;
int n;

class MajorityChecker {
private:
pair<int, int> segment[padding << 2];
vector<int> occur[maxn];

public:
    pair<int, int> merge(const pair<int, int>& a, const pair<int, int>& b) {
        if (a.first == b.first) return {a.first, a.second + b.second};
        else if (a.second >= b.second) return {a.first, a.second - b.second};
        else return {b.first, b.second - a.second};
    }

    MajorityChecker(vector<int>& arr) {
        n = arr.size();
        for (int index = 1; index <= n; index++) {
            segment[padding + index] = {arr[index-1], 1};
            occur[ arr[index-1] ].push_back(index);
        }

        for (int index = padding - 1; index > 0; index--) {
            segment[index] = merge(segment[index << 1], segment[index << 1 | 1]);
        }
    }

    pair<int, int> fetch(int l, int r, int lim) {
        int s = padding + l - 1;
        int t = padding + r + 1;

        pair<int, int> res = {0, 0};
        for (; s ^ t ^ 1; s >>= 1, t >>= 1) {
            if (~s & 1) res = merge(res, segment[s ^ 1]);
            if (t & 1) res = merge(res, segment[t ^ 1]);
        }
        return res;
    }
    
    int query(int left, int right, int threshold) {
        left++;
        right++;
        auto [res, cnt] = fetch(left, right, threshold);
        int start = lower_bound(occur[res].begin(), occur[res].end(), left) - occur[res].begin();
        int stop = upper_bound(occur[res].begin(), occur[res].end(), right) - occur[res].begin() - 1;
        if (stop - start + 1 >= threshold) return res;
        else return -1;
    }
};
