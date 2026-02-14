#include <bits/stdc++.h>

// Cho string S ký tự chữ số có độ dài 0 < n <= 255. Xóa đi k ký tự (0 < k < n) để có số bé nhất
// Input:
// 65278934
// 3

// Output:
// 27834

std::string num;
int req, max_size;

std::string result = "";
bool backtrack(const std::string& A, int pos, int select) {
    if (select == req) {
        if (A < result || result == "") {
            result = A;
            return true;
        } else {
            return false;
        }
    }

    int end = (max_size - (req-select));
    // char max_char = ((int)result.size() > 0) ? (result[select]) : '9';
    bool found = false;
    for (int new_pos = pos; new_pos <= end; new_pos++) {
        // if (num[new_pos] > max_char) continue;
        if (new_pos == end) {
            if (std::string B = A + num.substr(new_pos, max_size-new_pos); B < result) {
                result = B;
                return true;
            } return found;
        }

        if (backtrack(A + num[new_pos], new_pos+1, select+1)) {
            found = true;
            // max_char = std::min(max_char, num[new_pos]);
        }
    }
    return found;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cerr.tie(nullptr);
    // freopen("input.inp", "r", stdin);
    // freopen("output.out", "w", stdout);
    // freopen("error.err", "w", stderr);

    std::cin >> num;
    int k; std::cin >> k;
    req = (int)num.size() - k;
    max_size = (int)num.size();

    for (int pos = 0; pos < max_size-k; pos++) {
        if (num[pos] == '0') {
            if (req == 1) {
                std::cout << 0;
                return 0;
            } else {
                continue;
            }
        }
        backtrack(std::string(1, num[pos]), pos+1, 1);
    }

    std::cout << result;

    // Backtrack sinh số
    // khi pos đã đạt max thì toàn bộ phần sau chính là kết quả duy nhất
    // điều kiện dừng là khi select = số lượng yêu cầu (req)

    return 0;
}
