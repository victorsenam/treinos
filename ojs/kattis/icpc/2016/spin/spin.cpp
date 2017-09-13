#include <bits/stdc++.h>
#define debug if (1)

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

// NOT STANDART FROM HERE

// area de calota 2.pi.R.h (h altura)
// volume de calota pi.h/6 * (3r^2 + h^2)

typedef double cood;
cood eps = 1e-8;
// tests for double were made with eps = 1e-8

const double pi = acos(-1.);
const int N = 1e6+7;

struct vec { // vector
	// === BASIC ===
	cood x, y;

	vec () : x(0), y(0) {}
	vec (cood a, cood b) : x(a), y(b) {}
	friend ostream& operator<<(ostream& os, vec o);

	vec operator - (vec o)
	{ return vec(x - o.x, y - o.y); }
	vec operator + (vec o)
	{ return vec(x + o.x, y + o.y); }
	vec operator * (cood o)
	{ return vec(x * o, y * o); }
	vec operator / (cood o)
	{ return vec(x / o, y / o); }
	cood operator ^ (vec o)
	{ return x * o.y - y * o.x; }
	cood operator * (vec o)
	{ return x * o.x + y * o.y; }

	cood sq (vec o = vec())
	{ return ((*this)-o)*((*this)-o); }
	double nr (vec o = vec())
	{ return sqrt(sq(o)); }

	cood ar (vec a, vec b) // ccw signed area (positive if this is to the left of ab)
	{ return (b - a) ^ ((*this) - a); }
	int sd (vec a, vec b) // which side is this from ab? (-1 left, 0 over, 1 right)
	{ cood o = ar(a, b); return (o < -eps) - (eps < o); }

	cood pr (vec a, vec b)
	{ return (a-(*this)) * (b-(*this)); }
	int dr (vec a, vec b)
	{ cood o = pr(a, b); return (o < -eps) - (eps < o); }

	// === ADVANCED ===
	// rotate ccw by a (fails with ll)
	vec rotate (double a)
	{ return vec(cos(a) * x - sin(a) * y, sin(a) * x + cos(a) * y); }

	// on which half plane is this point?
	// 0 is upper half plane (y > 0) and (x,0) where x >= 0, 1 is otherwise
	inline bool halfplane ()
	{ return (y < eps || (abs(y) <= eps && x < eps)); }

	// full ordering (ccw angle from this+(1,0), distance to this)
	// is a < b?
	// PRECISION : ok with double if norm in [-1e9,5e3]
	bool compare (vec a, vec b) {
		if ((a-(*this)).halfplane() != (b-(*this)).halfplane())
			return (b-(*this)).halfplane();
		int o = sd(a,b);
		if (o) return o < 0;
		return a.dr((*this),b) > 0;
	}

	// is this inside segment st? (tip of segment included, change for < -eps otherwise)
	bool in_seg (vec s, vec t)
	{ return (sd(s, t) == 0) && !(eps < ((*this) - s) * ((*this) - t)); }
};
ostream& operator<<(ostream& os, vec o)
{ return os << '(' << o.x << ", " << o.y << ')'; }

// tests TODO
struct lin { // line
	cood a, b, c;

	lin () {}
	lin (cood x, cood y, cood z) : a(x), b(y), c(z) {}
	lin (vec s, vec t) : a(t.y - s.y), b(s.x - t.x), c(a * s.x + b * s.y) {}

	// parallel to this through p
	lin parll (vec p) { return lin(a, b, a * p.x + b * p.y); }

	// line intersection
	vec inter (lin o) {
		cood d = a * o.b - o.a * b;
		if (d < eps && -eps < d) throw 0; // parallel
		return vec((o.b * c - b * o.c) / d, (a * o.c - o.a * c) / d);
	}
};

int n;
int as, bs;
vec a[N], b[N];
int p[N];
vec env[2][N];
int es[2];

pair<double, bool> c[N];
int cs;

double aval (vec v, double al)
{ return v.x * cos(al) + v.y * sin(al); }

// avalia env k no angulo al
double get (int k, double al) {
	int lo = 0, hi = es[k]-1;
	while (lo < hi) {
		int md = (lo + hi)/2;
		
		if (aval(env[k][md], al) <= aval(env[k][md+1], al))
			hi = md;
		else
			lo = md+1;
	}

	return aval(env[k][lo], al);
}

pair<double, double> inters (int k, vec v) {
	double lo = 0., hi = pi;
	
	// minimo da dif
	int ts = 70;
	while (ts--) {
		double q = (lo+hi)/3.;

		double r1 = aval(v, q) - get(k, q);
		double r2 = aval(v, q+q) - get(k, q+q);

		if (r1 < r2)
			hi = q+q;
		else
			lo = q;
	}

	double cen = lo;
	pair<double,double> res;

	// primeira inter
	lo = 0.;
	hi = max(cen - eps, 0.);
	ts = 70;
	while (ts--) {
		double md = (lo+hi)/2.;

		if (aval(v,md) < get(k,md))
			lo = md;
		else
			hi = md;
	}
	res.first = lo;
	if (v.x >= env[k][es[k]-1].x)
		res.first = 0./0.;

	// segunda inter
	lo = min(cen + eps, pi);
	hi = pi;
	ts = 70;
	while (ts--) {
		double md = (lo+hi)/2.;

		if (aval(v,md) < get(k,md))
			hi = md;
		else
			lo = md;
	}
	res.second = lo;
	if (v.x <= env[k][0].x)
		res.second = 0./0.;

	return res;
}

int main () {
	scanf("%d", &n);

	for (int i = 0; i < n; i++) {
		vec v;
		int t;
		scanf("%lf %lf %d", &v.x, &v.y, &t);

		if (!t)
			b[bs++] = v;
		else
			a[as++] = v;
	}

	sort(a, a+as, [] (vec a, vec b) {
		return a.x < b.x;
	});

	for (int k = 0; k < 2; k++) {
		es[k] = 0;
		for (int i = 0; i < as; i++) {
			if (es[k] && env[k][es[k]-1].x == a[i].x)
				env[k][es[k]-1].y = min(env[k][es[k]-1].y, a[i].y);
			else
				env[k][es[k]++] = a[i];

			a[i].x = -a[i].x;
			a[i].y = -a[i].y;
		}

		for (int i = 0; i + i < as; i++)
			swap(a[i], a[as-i-1]);
	}

	int k = 0;
	for (int i = 0; i < bs; i++) {
		for (int j = 0; j < 2; j++) {
			pair<double,double> it = inters(j,b[i]);
			c[cs].first = it.first + eps;
			c[cs].second = 1;
			if (c[cs].first == c[cs].first)
				cs++;
			else
				k++;

			c[cs].first = it.second - eps;
			c[cs].second = 0;
			if (c[cs].first == c[cs].first)
				cs++;
		}
	}

	sort(c, c+cs);

	int rs = k;
	for (int i = 0; i < cs; i++) {
		if (c[i].second)
			k--;
		else
			k++;
		rs = min(rs, k);
	}

	printf("%d\n", rs + as);
}
