#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 1e5+7;
const double eps = 1e-8;

int n;
double a[N], b[N];
double x[2], y[2];
int p[N];

void go (double a, double b, double c, double d) {
	double x = (b-d)/(a-c);
	if (x == 0./0. || abs(x) == 1./0.)
		assert(false);
	double y = a*x - b;

	::x[0] = min(::x[0], x);
	::x[1] = max(::x[1], x);
	::y[0] = min(::y[0], y);
	::y[1] = max(::y[1], y);
}

int main () {
	x[0] = y[0] = 1./0.;
	x[1] = y[1] = -x[0];

	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%lf %lf", &a[i], &b[i]);
		p[i] = i;
	}

	sort(p, p+n, [] (int i, int j) {
		if (abs(a[i] - a[j]) < eps)
			return b[i] < b[j];
		return a[i] < a[j];
	});

	int l = -1, r = -1;
	int nl = p[0], nr = p[0];
	for (int _i = 0; _i < n; _i++) {
		int i = p[_i];
		if (abs(a[i] - a[nl]) < eps) {
			nr = i;
		} else {
			l = nl; r = nr;
			nl = nr = i;
		}

		if (l != -1) {
			go(a[l], b[l], a[i], b[i]);
			go(a[r], b[r], a[i], b[i]);
		}
	}

	printf("%.20f %.20f %.20f %.20f\n", x[0], y[0], x[1], y[1]);
}
