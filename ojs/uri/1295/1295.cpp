#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long  ll;
typedef pair<ll,ll> pii;
#define pb push_back

// area de calota na altura h : 2.pi.R.h
// volume de calota na altura h : pi.h/6 * (3r^2 + h^2)

// XXX marks risky behaviour and TODO marks untested functions
typedef double cood; cood eps = 1e-4;
const double pi = acos(-1.);
inline ll sq (ll x) { return x*x; }
inline double sq (double x) { return x*x; }
struct vec { // vector
	cood x, y;
	vec () : x(0), y(0) {} vec (cood a, cood b) : x(a), y(b) {}
	inline cood operator * (vec o) { return x * o.x + y * o.y; }

	inline cood sq (vec o = vec()) { return ::sq(x-o.x) + ::sq(y-o.y); }
	inline double nr (vec o = vec()) { return sqrt(sq(o)); }
};

const double INF = 1e8;
const int N = 1e4+7;

int n;
vec v[N];
int p[N], q[N];
double res;

double solve (int l, int r) {
	if (l + 1 >= r) return res;

	int m = (l+r+1)/2;
	double rx = v[p[m-1]].x;
	int a = m, b = r;
	res = min({ res, solve(l, a), solve(m, b) });

	int s = l;
	int j = m;
	for (int i = l; i < a; i++) {
		while (j < b && v[p[i]].y > v[p[j]].y) { q[s++] = p[j++]; }
		q[s++] = p[i];
	}
	while (j < b) q[s++] = p[j++];
	s = l;
	for (int i = l; i < r; i++) {
		p[i] = q[i];
		if (abs(v[p[i]].x - rx) >= res) continue;
		for (int j = s - 1; j >= l && v[p[i]].y - v[q[j]].y < res; j--)
			res = min(res, v[p[i]].nr(v[q[j]]));
		q[s++] = p[i];
	}
	return res;
}

int main () {
	while (scanf("%d", &n)) {
		if (!n) break;
		for (int i = 0; i < n; i++) 
			scanf("%lf %lf", &v[i].x, &v[i].y);
		sort(v,v+n,[](vec a, vec b) {return a.x < b.x;});
		for (int i = 0; i < n; i++)
			p[i] = i;
		res = INF;
		double res = solve(0, n);
		if (res > 1e4) printf("INFINITY\n");
		else printf("%.4lf\n",res);
	}
}
