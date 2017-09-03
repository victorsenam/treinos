#include <bits/stdc++.h>
#define cout if (0) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 23;
const double eps = 5e-6;

struct res_ty {
	int i, j;
	ll x;
	bool operator < (const res_ty & ot) const {
		return x < ot.x;
	}
};

int ts;
ll m, s, h;
ll n;
double v[N];
double curs;
int vs;

ll sq (ll x)
{ return x*x; }
double sq (double x)
{ return x*x; }

void adjust (int i) {
	while (i < n - 1 && v[i] > v[i+1]) {
		swap(v[i], v[i+1]);
		i++;
	}
	while (i > 0 && v[i-1] > v[i]) {
		swap(v[i], v[i-1]);
		i--;
	}
}

ll build (int z, int e, int c, bool pr = 0) {
	ll x = m * n;
	ll s = 0;
	vs = 0;
	for (int i = 0; i < z; i++) {
		v[vs++] = 0;
		s += sq(m);
	}
	for (int i = 0; i < e; i++) {
		v[vs++] = h;
		x -= h;
		s += sq(m - h);
	}
	for (int i = 0; i < c; i++) {
		v[vs++] = 100;
		x -= 100;
		s += sq(m - 100);
	}

	s += sq(m - x);
	v[vs++] = x;
	adjust(vs-1);

	if (pr)
		cout << x << endl;

	assert(vs == n);
	if (v[vs/2] != h || x < -eps || x > 100 + eps)
		return -1;
	return s;
}

double calc () {
	double s = 0.;
	for (int i = 0; i < n; i++)
		s += sq(v[i] - m);
	return s;
}

double calc (double fr, double to) {
	return sq(fr - m) - sq(to - m);
}

double bring (int i, int j, double hi, double w) {
	//cout << "try bringing " << v[i] << " " << v[j] << " needs " << w << endl;
	if (w < eps) return 0.;
	hi = min(hi, (v[j] - v[i])*.5);
	//cout << "at most " << hi << endl;

	double p = v[i] + hi;
	double q = v[j] - hi;

	double rs = calc(v[i],p) + calc(v[j],q);
	//cout << "full saves " << rs << endl;
	if (rs + eps < w) {
		v[i] = p; 
		adjust(i);
		v[j] = q;
		adjust(j);
		//cout << "go full" << endl;
	} else {
		double lo = 0;
		int qs = 70;
		while (qs--) {
			double md = (lo + hi)*.5;
			double p = v[i] + md;
			double q = v[j] - md;

			if (sq(v[i] - m) + sq(v[j] - m) - sq(p - m) - sq(q - m) < w)
				lo = md;
			else
				hi = md;
		}

		rs = calc(v[i],v[i]+lo) + calc(v[j],v[j]-lo);
		v[i] += lo;
		adjust(i);
		v[j] -= lo;
		adjust(j);
		//cout << "partial " << lo << " saves " << rs << endl;
	}

	return rs;
}

int main () {
#ifdef ONLINE_JUDGE
	freopen("stats.in", "r", stdin);
	freopen("stats.out", "w", stdout);
#endif
	scanf("%d", &ts);

	while (ts--) {
		scanf("%lld %lld %lld", &m, &s, &h);

		if (m == h && s == 0) {
			printf("%d %lld\n", 1, m);
			continue;
		}

			
		bool ok = 0;
		for (n = 3; n <= 19; n += 2) {
			res_ty mx({0,0,-1});
			for (int i = 0; i < n; i++)
				for (int j = 1; j + i < n; j++)
					mx = max(mx, res_ty({i,j,build(i, j, n - i - j -1)}));

			ll os = s*s*n;

			if (mx.x + eps < os)
				continue;
			cout << n << ": " << mx.i << " " << mx.j << " " << mx.x << endl;

			double curs = build(mx.i, mx.j, n - mx.i - mx.j - 1, 1);
			double df;
			do {
				df = bring(0, n-1, min({ abs(v[0] - h), abs(v[n-1] - h) }), curs - os);
				curs -= df;
			} while (df > eps);

			do {
				df = bring(0, n/2-1, 1./0., curs - os);
				curs -= df;
			} while (df > eps);

			do { 
				df = bring(n/2 + 1, n-1, 1./0., curs - os);
				curs -= df;
			} while (df > eps);

			if (curs < os + eps) {
				ok = 1;
				printf("%lld", n);
				for (int i = 0; i < n; i++)
					printf(" %.20f", v[i]);
				printf("\n");
				break;
			}
		}

		if (!ok) 
			printf("-1\n");
	}
}
