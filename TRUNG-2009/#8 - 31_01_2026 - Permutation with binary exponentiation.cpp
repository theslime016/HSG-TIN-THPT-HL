#include <bits/stdc++.h>

// Đề bài: Cho array A có n element nguyên dương a, in ra A sau khi áp dụng permutation P (được biểu diễn dưới dạng array 0-index) k lần.
// Constraints: 1 <= n, a, k <= 1e6
// - Input:
// + Dòng 1: Số nguyên dương n, k
// + Dòng 2: n phần tử của A
// + Dòng 3: n phần tử của P
// - Output: n phần tử của A sau khi áp dụng P k lần

// - Input:
// 5 1000000
// 10 20 30 40 50
// 1 2 0 4 3
// - Output:
// 30 10 20 40 50

std::vector<int> new_permutation;
void applyPermutation(std::vector<int>& array, std::vector<int>& nextIndex, bool combine = false) {
	for (int i = 0; i < (int)array.size(); i++) {
		if (combine) new_permutation[i] = array[nextIndex[i]];
		else new_permutation[nextIndex[i]] = array[i];
	}
	array.swap(new_permutation);
}

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	// freopen("input.inp", "r", stdin);
	// freopen("output.out", "w", stdout);
	// freopen("error.err", "w", stderr);
	
	int n, k; std::cin >> n >> k;
	std::vector<int> A(n), P(n);
	new_permutation.resize(n);
	for (int i = 0; i < n; i++) std::cin >> A[i];
	for (int i = 0; i < n; i++) std::cin >> P[i];

	while (k > 0) {
		if (k & 1) {
			applyPermutation(A, P, false);
		}
		applyPermutation(P, P, true);
		k >>= 1;
	}

	for (const int& x : A) std::cout << x << ' ';

	return 0;
}
