#include <bits/stdc++.h>

// Cho 1 string S (co the chua ca newline va space), kiem tra cac dieu kien sau:
// Palindrome
// So luong word (duoc phan tach boi newline va space)

// Sau do in ra cac string duoc trich tu string goc voi dieu kien sau (thu tu cac character van duoc giu nguyen):
// String chi chua chu in hoa
// String chi chua chu in thuong
// String chi chua chu so thap phan


// Input:
// AbC
// 123 xyZ
// 456

//Output:
// false
// 4
// ACZ
// bxy
// 123456

bool isPalindrome(const std::string& str) {
    int l = 0, r = str.size()-1;
    while (l < r) {
        if (str[l] != str[r]) return false;
        l++, r--;
    }
    return true;
}

int countWord(const std::string& str) {
    std::stringstream ss;
    std::string temp;
    int word = 0;
    ss << str;
    while (ss >> temp) word++;
    return word;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    freopen("input.inp", "r", stdin);
    freopen("output.out", "w", stdout);
    // freopen("error.err", "w", stderr);

    std::string S, line;
    while (std::getline(std::cin, line)) {
        S += line;
        S += '\n';
    } S.pop_back();

    std::cout << std::boolalpha << isPalindrome(S) << '\n';
    std::cout << countWord(S) << '\n';

    std::string upper, lower, digit;
    for (int i = 0, n = S.size(); i < n; i++) {
        if (isupper(S[i])) upper.push_back(S[i]);
        if (islower(S[i])) lower.push_back(S[i]);
        if (isdigit(S[i])) digit.push_back(S[i]);
    }
    std::cout << upper << '\n' << lower << '\n' << digit;

    return 0;
}