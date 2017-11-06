#include <stdlib.h>
#include <string.h>
#include <algorithm>
#include <cstdio>
const int M = (int) 1e9 + 7;

int fact(int n) {
	return (n == 0) ? 1 : (fact(n - 1) * 1LL * n) % M;
}

int pow2(int n) {
	return (n == 0) ? 1 : (pow2(n - 1) * 2LL) % M;
}

int main() {
	freopen("harary.in", "r", stdin);
	freopen("harary.out", "w", stdout);
	int n;
	scanf("%d", &n);
	if (n == 1)
		printf("1\n0\n0\n");
	else if (n == 2)
		printf("2\n1\n0\n");
	else if (n == 3)
		printf("12\n6\n6\n");
	else {
		int tmp = (fact(n) * 1LL * pow2(((n - 1) * (n - 2)) / 2 - 3)) % M;
		printf("%d\n%d\n%d\n", (int) ((tmp * 8LL) % M), (int) ((tmp * (n + 1LL)) % M), (int) ((tmp * 1LL * n) % M));
	}
	return 0;
}