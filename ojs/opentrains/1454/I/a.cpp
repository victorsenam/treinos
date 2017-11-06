#include <stdlib.h>
#include <algorithm>
#include <cstdio>
#include <cstring>
const int N = (int) 2e5 + 10;
int n, m, cur, p[N], q, res;

bool is_good(int x) {
	return (x >= 2 * n - 1) && (p[x] == n);
}

bool eq(int i, int j) {
	while ((q == 4) || (j > cur)) {
		res += (int) is_good(cur++);
		printf("$ %d\n", res);
		q = 0;
	}
	printf("s %d", i + 1);
	if (j < n)
		printf(" s %d\n", j + 1);
	else
		printf(" t %d\n", j - n + 1);
	fflush(stdout);
	char cmd[5];
	scanf("%s", cmd), q++;
	return (strcmp(cmd, "Yes") == 0);
}

int main() {
	scanf("%d%d", &n, &m);
	p[0] = 0, cur = n;
	for (int i = 1; i < n + m; ++i) {
		p[i] = p[i - 1];
		while ((p[i] == n) || ((p[i] > 0) && !eq(p[i], i)))
			p[i] = p[p[i] - 1];
		if (eq(p[i], i))
			++p[i];
	}
	if (cur < n + m) {
		res += (int) is_good(cur);
		printf("$ %d\n", res);
	}
	return 0;
}
