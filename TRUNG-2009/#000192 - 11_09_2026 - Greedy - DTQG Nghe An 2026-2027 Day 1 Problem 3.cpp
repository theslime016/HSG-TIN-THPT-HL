#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5 + 5;
const int inf = 1e6;
int n, k;
int B[maxn];
pair<int, int> A[maxn]; // val - index
vector<pair<int, int>> selected; // value - current index
int cnt_select = 0;
bool init_select() {
    for (int i = 1; i <= n; i++) {
        int minval = A[i].first;
        int minindex = -1;
        for (int j = i+1; j <= n; j++) {
            if (A[j].first <= minval) {
                minval = A[j].first;
                minindex = j;
            }
        }
        if (minval < A[i].first) {
            cnt_select = 2;
            A[i].second = true;
            A[minindex].second = true;
            swap(A[i], A[minindex]);
            swap(i, minindex);
            selected.push_back({A[i].first, i});
            selected.push_back({minval, minindex});
            return true;
        }
    }
    return false;
}

bool swap_local() {
    // sort selected
    bool change = false;
    for (int i = 1; i <= n; i++) {
        if (!A[i].second) continue;
        int minval = A[i].first;
        int minindex = -1;
        for (int j = i+1; j <= n; j++) {
            if (!A[j].second) continue;
            if (A[j].first <= minval) {
                minval = A[j].first;
                minindex = j;
            }
        }
        if (minval < A[i].first) {
            swap(A[i], A[minindex]);
            change = true;
        }
    }
    return change;
}

bool new_group_old() {
    // selected ->(group) min + !selected
    int found = false;
    for (int i = 1; i <= n; i++) {
        if (!A[i].second) continue;
        int minval = A[i].first;
        int minindex = -1;
        for (int j = i+1; j <= n; j++) {
            if (A[j].second) continue;
            if (A[j].first <= minval) {
                minval = A[j].first;
                minindex = j;
            }
        }
        if (minval < A[i].first) {
            A[minindex].second = true;
            cnt_select++;
            swap(A[i], A[minindex]);
            found = true;
            break;
        }
    }
    return found;
}

bool new_select_old(int selected_only) {
    // first !selected ->(group) min (selected/!selected)
    bool found = false;
    for (int i = 1; i <= n; i++) {
        if (A[i].second) continue;
        int minval = A[i].first;
        int minindex = -1;
        for (int j = i+1; j <= n; j++) {
            if (selected_only && !A[j].second) continue;
            if (A[j].first < minval) {
                minval = A[j].first;
                minindex = j;
            }
        }
        if (minval < A[i].first) {
            A[i].second = true;
            cnt_select++;
            if (A[minindex].second == false) {
                A[minindex].second = true;
                cnt_select++;
            }
            swap(A[i], A[minindex]);
            found = true;
            break;
        } else {
            int maxval = A[i].first;
            int maxindex = -1;
            for (int j = 1; j < i; j++) {
                if (selected_only && !A[j].second) continue;
                if (A[j].first >= maxval) {
                    maxval = A[j].first;
                    maxindex = j;
                }
            }
            if (maxval > A[i].first) {
                A[i].second = true;
                cnt_select++;
                if (A[maxindex].second == false) {
                    A[maxindex].second = true;
                    cnt_select++;
                }
                swap(A[i], A[maxindex]);
                found = true;
                break;
            }
        }
    }
    return found;
}

bool new_select_old2(bool selected_only) {
    bool found = false;
    for (int i = 1; i <= n; i++) {
        int minval = A[i].first;
        int minindex = -1;
        for (int j = i+1; j <= n; j++) {
            if (A[i].second && A[j].second) continue;
            if (selected_only && !A[i].second && !A[j].second) continue;
            if (A[j].first <= minval) {
                minval = A[j].first;
                minindex = j;
            }
        }
        if (minval < A[i].first) {
            if (!A[i].second) {
                A[i].second = true;
                cnt_select++;
            }
            if (!A[minindex].second) {
                A[minindex].second = true;
                cnt_select++;
            }
            swap(A[i], A[minindex]);
            found = true;
            break;
        }
    }
    return found;
}

bool new_selected() {
    // selected ->(group) !selected
    bool found = false;
    for (int i = 1; i <= n; i++) {
        if (!A[i].second) continue;
        int maxval = A[i].first;
        int maxindex = -1;
        for (int j = 1; j < i; j++) {
            if (A[j].second) continue;
            if (A[j].first > maxval) {
                maxval = A[j].first;
                maxindex = j;
                break;
            }
        }
        if (maxval > A[i].first) {
            A[maxindex].second = true;
            cnt_select++;
            swap(A[i], A[maxindex]);
            found = true;
            break;
        } else {
            int minval = A[i].first;
            int minindex = -1;
            for (int j = i+1; j <= n; j++) {
                if (A[j].second) continue;
                if (A[j].first <= minval) {
                    minval = A[j].first;
                    minindex = j;
                }
            }
            if (minval < A[i].first) {
                A[minindex].second = true;
                cnt_select++;
                swap(A[i], A[minindex]);
                found = true;
                break;
            }
        }
    }
    return found;
}

bool new_group() {
    // first ->(group) !selected
    bool found = false;
    for (int i = 1; i <= n; i++) {
        if (A[i].second) continue;
        int minval = A[i].first;
        int minindex = -1;
        for (int j = i+1; j <= n; j++) {
            if (A[j].second) continue;
            if (A[j].first <= minval) {
                minval = A[j].first;
                minindex = j;
            }
        }
        if (minval < A[i].first) {
            A[i].second = A[minindex].second = true;
            cnt_select += 2;
            swap(A[i], A[minindex]);
            found = true;
            break;
        }
    }
    return found;
}

bool loop() {
    bool found = false;
    for (int i = 1; i <= n; i++) {
        if (A[i].second == 0) {
            int selected_only = cnt_select + 2 > k;
            int minval = A[i].first;
            int minindex = -1;
            int flag = 0;
            for (int j = i+1; j <= n; j++) {
                if (selected_only && !A[j].second) continue;
                if (A[j].second) {
                    if (A[j].first < minval) {
                        flag = 1;
                        minval = A[j].first;
                        minindex = j;
                    }
                } else if (!flag) {
                    if (A[j].first <= minval) {
                        minval = A[j].first;
                        minindex = j;
                    }
                }
            }
            if (minval < A[i].first) {
                A[i].second = true;
                cnt_select++;
                if (!A[minindex].second) {
                    A[minindex].second = true;
                    cnt_select++;
                }
                swap(A[i], A[minindex]);
                found = true;
                break;
            }
        } else if (A[i].second == 1) {
            int minval = A[i].first;
            int minindex = -1;
            for (int j = i+1; j <= n; j++) {
                if (A[j].second) continue;
                if (A[j].first <= minval) {
                    minval = A[j].first;
                    minindex = j;
                }
            }
            if (minval < A[i].first) {
                A[minindex].second = true;
                cnt_select++;
                swap(A[i], A[minindex]);
                found = true;
                break;
            }
        }
    }
    return found;
}

bool detect() {
    bool found = false;
    for (int i = 1; i <= n; i++) {
        if (!A[i].second) continue;
        if (A[i].first == B[i]) {
            A[i].second = false;
            cnt_select--;
        }
    }
    return found;
}

void debugA() {
    for (int i = 1; i <= n; i++) {
        cout << A[i].first << ' ';
    }
    cout << '\n';
    for (int i = 1; i <= n; i++) {
        cout << A[i].second << ' ';
    }
    cout << '\n';
}

const int debug = 0;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    freopen("input.inp", "r", stdin);
    freopen("output.out", "w", stdout);

    cin >> n >> k;
    for (int index = 1; index <= n; index++) {
        cin >> A[index].first;
        B[index] = A[index].first;
    }

    if (k >= 2 && !init_select()) {
        for (int i = 1; i <= n; i++) {
            cout << A[i].first << ' ';
        }
        return 0;
    } else if (debug) {
        cout << "INIT" << '\n';
        debugA();
    }

    bool change = true;
    while (change) {
        change = false;
        if (cnt_select < k && loop()) {
            change = true;
            if (debug) {
                cout << "NEWPAIR" << '\n';
                debugA();
            }
        }

        if (swap_local()) {
            change = true;
            if (debug) {
                cout << "SWAPLOCAL" << '\n';
                debugA();
            }
        }

        if (detect()) {
            change = true;
            if (debug) {
                cout << "DETECT" << '\n';
                debugA();
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        cout << A[i].first << ' ';
    }
}
