#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef int64_t ll;

#define debug(...) {fprintf(stderr, __VA_ARGS__); fflush(stderr);}

int p[2][4];
int n;

int query (int k) {
	int r;
	printf("? %d %d %d %d\n", p[k][0], p[k][1], p[k][2], p[k][3]);
	fflush(stdout);
	debug("B: ? %d %d %d %d\n", p[k][0], p[k][1], p[k][2], p[k][3]);
	scanf("%d", &r);
	debug("C: %d\n", r);
	return r;
}

int isin () {
	if (p[0][0] < p[1][0]) return 0;
	if (p[0][1] < p[1][1]) return 0;
	if (p[0][2] > p[1][2]) return 0;
	if (p[0][3] > p[1][3]) return 0;
	return 1;
}

void search_val (int k, int i, int v, bool first) {
	int lo = 1;
	int hi = n;

	if (i >= 2)
		lo = p[k][i-2];
	else
		hi = p[k][i+2];

	while (lo < hi) {
		if (first) {
			p[k][i] = (lo+hi)/2;
			int res = query(k);
			if (k) res -= isin();
			if (res >= v)
				hi = p[k][i];
			else
				lo = p[k][i]+1;
		} else {
			p[k][i] = (lo+hi+1)/2;
			int res = query(k);
			if (k) res -= isin();
			if (res >= v)
			 	lo = p[k][i];
			else
				hi = p[k][i]-1;
		}
	}

	//debug("defined %d %d = %d\n", k, i, lo);
	p[k][i] = lo;
}

int main () {
	scanf("%d", &n);
	for (int i = 0; i < 2; i++) {
		p[i][0] = p[i][1] = 1;
		p[i][2] = p[i][3] = n;
	}

	for (int k = 0; k < 2; k++) {
		search_val(k, 2, 1, 1);
		search_val(k, 3, 1, 1);
		
		search_val(k, 0, 1, 0);
		search_val(k, 1, 1, 0);
	}

	printf("! %d %d %d %d %d %d %d %d\n", p[0][0], p[0][1], p[0][2], p[0][3], p[1][0], p[1][1], p[1][2], p[1][3]);
	fflush(stdout);
	debug("! %d %d %d %d %d %d %d %d\n", p[0][0], p[0][1], p[0][2], p[0][3], p[1][0], p[1][1], p[1][2], p[1][3]);
}
