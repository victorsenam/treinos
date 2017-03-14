#include <bits/stdc++.h>

using namespace std;

const int N = 1007;

int memo[N][N];
int v[N];
int n;

int pd (int e, int d) {
	if (e > d)
		return 0;
	if (e == d)
		return v[e];
	
	int & m = memo[e][d];

	if (m != -1)
		return m;
	
	if (v[e+1] >= v[d])
		m = pd(e+2, d) + v[e] - v[e+1];
	else
		m = pd(e+1, d-1) + v[e] - v[d];
	
	if (v[d-1] > v[e])
		m = max(m, pd(e, d-2) + v[d] - v[d-1]);
	else
		m = max(m, pd(e+1, d-1) + v[d] - v[e]);
	
	return m;
}

int main () {
	int t = 0;
	while(scanf("%d", &n) != EOF && n) {
		memset(memo, -1, sizeof memo);
		for (int i = 0; i < n; i++)
			scanf("%d", v+i);

		printf("In game %d, the greedy strategy might lose by as many as %d points.\n", ++t, pd(0, n-1));
	}
}
