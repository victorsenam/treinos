#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef int64_t ll;

#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}

const int N = 1e3+7;
const int S = 5e4+7;

int pd[3][S];
int n, s;
int p[N];
int a[N], c[N];

bool cmp_t (int i, int j) {
	if (a[i] != a[j]) return a[i] < a[j];
	return c[i] < c[j];
}

int get (int i, int j) {
	if (j < 0 || j > s) return -N;
	return pd[i][j];
}

int main () {
	//freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);
	memset(pd, -1, sizeof pd);
	scanf("%d %d", &n, &s);

	for (int i = 0; i < n; i++) {
		scanf("%d %d", a+i, c+i);
		p[i] = i;
	}

	sort(p, p+n, cmp_t);

	pd[1][0] = pd[2][0] = 0;

	int ls = p[0];
	for (int _i = 0; _i < n; _i++) {
		int i = p[_i];

		for (int j = 0; j <= s; j++) {
			pd[1][j] = max(pd[1][j], pd[0][j]);
			if (a[i] != a[ls]) {
				pd[2][j] = max(pd[2][j], pd[0][j]);
			}
		}

		for (int j = 0; j <= s; j++) {
			int & me = pd[0][j];
			me = -1;

			if (get(1, j-c[i]) >= 0)
				me = max(me, get(1, j-c[i]));
			if (get(1, j) >= 0)
				me = max(me, get(1, j));
			if (get(2, j-c[i]) >= 0)
				me = max(me, get(2, j-c[i]) + 1);
		}

		ls = i;
	}
	
	int res = get(0, s);
	if (res < 0) printf("Impossible\n");
	else printf("%d\n", res);
}
