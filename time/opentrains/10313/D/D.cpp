#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef int64_t ll;

double eps = 1e-9;

const int N = 1e5 + 7;

#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}

double r[N], w[N];
int p[N];
double d;
int n;

bool cmp_t (int i, int j) {
	return w[i] < w[j];
}

bool solve (double att) {
	double lf = d;
	for (int _i = 0; lf > 0. && _i < n; _i++) {
		int i = p[_i];
		if (att >= r[i]) continue;

		lf -= (r[i]-att)/w[i];
		att = r[i];
	}

	return !(lf > 0.);
}

int main () {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	scanf("%lf %d", &d, &n);

	for (int i = 0; i < n; i++) {
		double aux;
		scanf("%lf %lf %lf", &aux, w+i, r+i);
		w[i] *= aux; r[i] *= aux;
		p[i] = i;
	}

	sort(p, p+n, cmp_t);

	double lo = 0.;
	double hi = 2e6;

	while (hi - lo > eps) {
		double mid = (lo + hi)*.5;

		if (solve(mid))
			lo = mid;
		else
			hi = mid;
	}

	printf("%.20f\n", lo);
}
