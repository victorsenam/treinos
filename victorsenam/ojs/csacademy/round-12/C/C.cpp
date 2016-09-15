#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef int64_t ll;

#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}

const int N = 1e5+7;

int h[N], w[N], p[N];
int n;

bool cmp_t (int i, int j)  {
	return (w[i] > w[j]);
}

int main () {
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%d %d", w+i, h+i);
		p[i] = i;
	}

	sort(p, p+n, cmp_t);

	int allmin = 0;
	int currmin = 0;
	int res = 0;

	for (int _i = 0; _i < n; _i++) {
		int i = p[_i];
		
		if (_i && w[i] != w[p[_i-1]])
			allmin = currmin;

		if (h[i] >= allmin)
			res++;

		currmin = max(currmin, h[i]);
	}

	printf("%d\n", res);
}
