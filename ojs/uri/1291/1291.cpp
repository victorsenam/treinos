#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

double pi = acos(-1.);
double a, A, T;
double z, x;

bool solve (double y) {
	x = (T - A - y)/2;
	z = (A + A - T - 2*y);

	cout << x << " " << y << " " <<  z << " | " << 4*(x+y) + z << endl;
	
	return (x >= 0 && z >= 0 && 4*(x+y) + z <= T && y <= z);
}

int main () {
	scanf("%lf", &a);

	A = pi*a*a/4;
	T = a*a;
	cout << T << endl;

	double lo = 0, hi = A;
	int ts = 10;

	while (ts--) {
		double md = (lo + hi)/2;
		if (solve(md))
			lo = md;
		else
			hi = md;
	}

	printf("%.3f %.3f %.3f\n", 4*x, 4*lo, z);
}
