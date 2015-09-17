#include <bits/stdc++.h>

using namespace std;

const int N = 2004;
int n;
double a[N];
double l, w;
double memo[N][N];
int vis[N][N];
int turn;

double pd (int e, int d) {
	if (e + d >= n)
		return 0.0;
	
	double & me = memo[e][d];

	if (vis[e][d] == turn)
		return me;
	vis[e][d] = turn;

	double ce = abs(a[e+d] - (l/((n/2)-1))*e);
	double cd = a[e+d] - (l/((n/2)-1))*d;
	cd = sqrt(cd*cd + w*w);

	if (e < n/2 && d < n/2)
		me = min(pd(e+1, d) + ce, pd(e, d+1) + cd);
	else if (e < n/2)
		me = pd(e+1, d) + ce;
	else
		me = pd(e, d+1) + cd;
	
	return me;
}

int main () {
	while (scanf("%d", &n) != EOF) {
		scanf("%lf %lf", &l, &w);
		for (int i = 0; i < n; i++)
			scanf("%lf", a+i);
		sort(a, a+n);
		
		turn++;
		printf("%.8f\n", pd(0, 0));
	}
}
