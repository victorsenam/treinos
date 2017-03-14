#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef int64_t ll;

#define debug(...) {fprintf(stderr, __VA_ARGS__); fflush(stderr);}

const int p[2][4] = 
{
	{2, 4, 4, 6},
	{4, 2, 5, 3}
};

int g[4];

int isin (int k) {
	if (p[k][0] < g[0]) return 0;
	if (p[k][1] < g[1]) return 0;
	if (p[k][2] > g[2]) return 0;
	if (p[k][3] > g[3]) return 0;
	return 1;
}

int main () {
	printf("%d\n", 6);
	fflush(stdout);
	char c;
	while (scanf(" %c", &c) && c == '?') {
		scanf("%d %d %d %d", &g[0], &g[1], &g[2], &g[3]);
		int ss = isin(0) + isin(1);
		printf("%d\n", ss);
		fflush(stdout);
	}
}
