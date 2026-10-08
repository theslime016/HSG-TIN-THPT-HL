const int maxn = 2e4 + 5;
const int padding = 32768;
long long segment[maxn << 2];
int cnt[maxn];
int A[maxn];
int n;

class MajorityChecker {
public:
    int fetch(int l, int r, int lim) {
        int s = l + padding - 1;
        int t = r + padding + 1;

        for (; s ^ t ^ 1; s >>= 1, t >>= 1) {
            if ((~s & 1) && segment[s ^ 1] >= lim) {
                int pt = s ^ 1;
                while (pt < padding) {
                    if (segment[pt << 1] >= lim) pt <<= 1;
                    else pt <<= 1, pt |= 1;
                }
                return A[pt - padding];
            }

            if ((t & 1) && segment[t ^ 1] >= lim) {
                int pt = t ^ 1;
                while (pt < padding) {
                    if (segment[pt << 1] >= lim) pt <<= 1;
                    else pt <<= 1, pt |= 1;
                }
                return A[pt - padding];
            }
        }

        return -1;
    }

    MajorityChecker(vector<int>& arr) {
        n = arr.size();
        for (int i = 1; i <= n; i++) {
            A[i] = arr[i-1];
            cnt[ A[i] ]++;
            int index = i + padding;
            segment[index] = cnt[A[i]];
        }

        for (int index = padding - 1; index > 0; index--) {
            segment[index] = max(segment[index << 1], segment[index << 1 | 1]);
        }
    }
    
    int query(int left, int right, int threshold) {
        return fetch(left, right, threshold);
    }
};
