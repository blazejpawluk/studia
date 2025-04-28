#include <iostream>

int comps;

bool eq(int a, int b) {
	comps++;
	return a==b;
}

bool gt(int a, int b) {
	comps++;
	return a>b;
}

bool lt(int a, int b) {
	comps++;
	return a<b;
}

std::pair<int, int> firstLastXRec(int* A, int l, int r, int x) {
	std::pair<int, int> result;
	result.first = -1;
	result.second = -1;

	// std::cout << "\nl:" << l << ", r:" << r << std::endl;

	if (l >= r) {
		if (eq(A[l], x)) {
			result.first = l;
			result.second = l;
		}
		return result;
	}

	int s = (l+r)/2;
	// std::cout << "\tA[l..r]:";
	// for (int i = l; i <= r; i++) {
	// 	std::cout << A[i] << ",";
	// }
	// std::cout << " s:" << s << ", A[s]:" << A[s] << std::endl;

	if (gt(A[s], x)) return firstLastXRec(A, l, s-1, x);
	if (lt(A[s], x)) return firstLastXRec(A, s+1, r, x);

	if (eq(A[r], x)) result.second = r;
	else if (!eq(A[s+1], x)) result.second = s;
	else result.second = firstLastXRec(A, s+1, r-1, x).second;

	if (eq(A[l], x)) result.first = l;
	else if (l==s || !eq(A[s-1], x)) result.first = s;
	else result.first = firstLastXRec(A, l+1, s-1, x).first;

	return result;
}

std::pair<int, int> firstLastX(int* A, int n, int x) {
	return firstLastXRec(A, 0, n - 1, x);
}

int main() {
	int n;
	std::cout << "n: ";
	std::cin >> n;

	int A[n];
	std::cout << "A[n]: ";
	for (int i = 0; i < n; i++) {
		std::cin >> A[i];
	}

	int x;
	std::cout << "x: ";
	std::cin >> x;

	std::pair<int, int> result = firstLastX(A, n, x);
	std::cout << "\nfirst index: " << result.first << std::endl;
	std::cout << "last index: " << result.second << std::endl;
	std::cout << "comps: " << comps << std::endl;

	return 0;
}