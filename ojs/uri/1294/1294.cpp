#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

double x, y;

double solve (double z) {
	return (x-z-z)*(y-z-z)*z;
}

int main () {
	while (scanf("%lf %lf", &x, &y) != EOF) {
		double lo = 0, hi = min(x/2,y/2);
		int ts = 80;
		while (ts--) {
			double q1 = (lo+lo+hi)/3;
			double q2 = (lo+hi+hi)/3;
			if (solve(q1) <= solve(q2))
				lo = q1;
			else
				hi = q2;
		}

		printf("%.3f 0.000", lo);
		printf(" %.3f", min(x,y)/2);
		printf("\n");
	}
}
