#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

typedef ll cood; cood eps = 0;
const double pi = acos(-1.);
inline ll sq (ll x) { return x*x; }
inline double sq (double x) { return x*x; }

struct vec {
	cood x, y;
	vec () : x(0),y(0) {} vec(cood a, cood b) : x(a),y(b) {}
	inline vec operator - (const vec & o) const { return {x - o.x, y-o.y}; }
	inline vec operator + (const vec & o) const { return {x + o.x, y+o.y}; }
	inline vec operator * (const cood & o) const { return {x*o, y*o}; }
	inline vec operator / (const cood & o) const { return {x/o, y/o}; }
	inline cood operator ^ (const vec & o) const { return x*o.y - y*o.x; }
	inline cood operator * (const vec & o) const { return x*o.x + y*o.y; }

	inline cood cross(const vec & a, const vec & b) const { return ((*this)-a)^((*this)-b); }
	inline cood inner(const vec & a, const vec & b) const { return ((*this)-a)*((*this)-b); }

	inline int ccw (const vec & a, const vec & b) const { cood o = cross(a,b); return (eps < o) - (o < -eps); }
	inline int dir (const vec & a, const vec & b) const { cood o = inner(a,b); return (eps < o) - (o < -eps); }
	inline cood sq (vec o = vec()) { return inner(o,o); }
	inline double nr (vec o = vec()) { return sqrt(sq(o)); }
	inline vec proj (vec a, vec b) { return a + (b-a)*(a.inner((*this),b) / a.sq(b)); }
	inline vec rotate (double a) { return vec(cos(a) * x - sin(a)*y, sin(a)*x + cos(a)*y); }
	inline vec rot90 () { return vec(-y,x); }

	inline double angle(vec a, vec b) { return atan2(cross(a, b), inner(a, b)); }
	inline bool operator < (const vec & o) const { return (x!=o.x)?x<o.x:y<o.y; }
};
ostream & operator << (ostream & os, vec v) {
	return os << "(" << v.x << "," <<v.y << ")";
}

struct lin {
	cood a, b, c;
	inline lin () {} inline lin(cood x, cood y, cood z) : a(x), b(y), c(z) {}
	inline lin (vec s, vec t) : a(t.y - s.y), b(s.x - t.x), c(a*s.x + b*s.y) {}

	inline vec nor () { return vec(a,b); }

	vec inter (lin o) {
		cood d = a*o.b - o.a*b;
		if (-eps <= d && d <= eps) throw 1;
		return vec((o.b*c - b*o.c)/d, (a*o.c - o.a*c)/d);
	}
};

inline pair<vec,vec> furt (vec * p, int n, vec d) {
	vec mn = p[0], mx = p[0];
	if (n <= 4) {
		for (int k = 1; k < n; k++) {
			if (p[k]*d > mx*d) mx = p[k];
			if (p[k]*d < mn*d) mn = p[k];
		}
		return pair<vec,vec>(mn,mx);
	}
	bool sw = 0;
	if (p[1]*d < p[0]*d) {
		sw = 1;
		d = vec(0,0) - d;
	}

	int lo = 1, hi = n;
	while (lo < hi) {
		int md = (lo+hi+1)/2;
		if (p[md]*d >= p[0]*d) lo = md;
		else hi = md-1;
	}

	int di = lo;

	lo = 1, hi = di-1;
	while (lo < hi) {
		int md = (lo+hi)/2;
		if (p[md]*d < p[md+1]*d) lo = md+1;
		else hi = md;
	}
	if (p[lo]*d >= mx*d) mx = p[lo];

	lo = di, hi = n-1;
	while (lo < hi) {
		int md = (lo+hi)/2;
		if (p[md]*d > p[md+1]*d) lo = md+1;
		else hi = md;
	}
	if (lo < n && p[lo]*d <= mn*d) mn = p[lo];

	if (sw) swap(mn,mx);
	return pair<vec,vec>(mn,mx);
}

int convex_hull (vec * v, int n, int border_in) {
	swap(v[0], *max_element(v,v+n));
	sort(v+1, v+n, [&v] (vec a, vec b) {
		int o = b.ccw(v[0],a);
		if (o) return (o == 1);
		return v[0].sq(a) < v[0].sq(b);
	});
	if (border_in) {
		int s = n-1;
		while (s>1 && v[s].ccw(v[s-1],v[0]) == 0) s--;
		for (int i = s; i < n-1-(i-s); i++) swap(v[i], v[n-1-(i-s)]);
	}
	int s = 0;
	for (int i = 0; i < n; i++) {
		if (s && v[s-1].x == v[i].x && v[s-1].y == v[i].y) continue;
		while (s >= 2 && v[s-1].ccw(v[s-2],v[i]) >= border_in) s--;
		swap(v[s++], v[i]);
	}
	return s;
}

const int N = 12007;

int n, m;
vec v[N];
vec u[N];

int main () {
	scanf("%d", &n);
	m = n;
	for (int i = 0; i < n; i++) {
		scanf("%lld %lld", &v[i].x, &v[i].y);
		u[i] = v[i];
	}
	
	n = convex_hull(v,n,1);
	for (int i = n; i < n+n; i++)
		v[i] = v[i-n];

	ll area = 0;
	for (int i = 0; i < n; i++) {
		sort(u, u+m, [i] (const vec & a, const vec & b) {
			return a.ccw(v[i],b) < 0;
		});

		int bef = i, aft = i;

		for (int j = 0; j < m; j++) {
			while (bef + 1 < n+i && v[bef+1].ccw(v[i],u[j]) <= 0 && v[i].cross(v[bef+1],u[j]) >= v[i].cross(v[bef],u[j]))
				bef++;
			while (aft + 1 < n+i && (v[aft].ccw(v[i],u[j]) <= 0 || v[i].cross(u[j],v[aft+1]) >= v[i].cross(u[j],v[aft])))
				aft++;

			//cout << v[i] << " and " << u[j] << " with " << v[bef] << " and " << v[aft] << " for " << v[i].cross(v[bef],u[j]) + v[i].cross(u[j],v[aft]) << endl;
			if (v[i].ccw(v[bef],u[j])*v[i].ccw(u[j],v[aft]))
				area = max(area, v[i].cross(v[bef],u[j]) + v[i].cross(u[j],v[aft]));
		}
	}

	printf("%lld.%lld\n", area/2, (area%2)*5);
}
