#include <bits/stdc++.h>

// Cho string S, xac dinh cac substring thoa man:
// Co size <= 6
// Co it nhat 1 character in hoa ('A' -> 'Z')
// Co it nhat 1 character in thuong ('a' -> 'z')
// Co it nhat 1 chu so thap phan ('0' -> '9')

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    freopen("input.inp", "r", stdin);
    freopen("output.out", "w", stdout);
    // freopen("error.err", "w", stderr);

    std::string S; std::cin >> S;
    int n = S.size();
    int upper = 0, lower = 0, digit = 0;
    for (int l = 0, r = 0; r < n; r++) {
        if (isupper(S[r])) upper++;
        else if (islower(S[r])) lower++;
        else if (isdigit(S[r])) digit++;
        
        if (r-l+1 < 6) continue;
        if (!upper || !lower || !digit) continue;
        
        for (int end = r; end < n; end++) {
            std::cout << std::string_view(S.data() + l, end-l+1) << '\n';
        }

        if (isupper(S[l])) upper--;
        else if (islower(S[l])) lower--;
        else if (isdigit(S[l])) digit--;

        l++;
    }

    return 0;
}