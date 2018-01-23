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
	inline vec operator - (vec o) { return {x - o.x, y-o.y}; }
	inline vec operator + (vec o) { return {x + o.x, y+o.y}; }
	inline vec operator * (cood o) { return {x*o, y*o}; }
	inline vec operator / (cood o) { return {x/o, y/o}; }
	inline cood operator ^ (vec o) { return x*o.y - y*o.x; }
	inline cood operator * (vec o) { return x*o.x + y*o.y; }
	inline bool operator < (vec o) { return (x!=o.x)?x<o.x:y<o.y; }

	inline cood cross(vec a, vec b) { return ((*this)-a)^((*this)-b); }
	inline cood inner(vec a, vec b) { return ((*this)-a)*((*this)-b); }

	inline int ccw (vec a, vec b) { cood o = cross(a,b); return (eps < o) - (o < -eps); }
	inline int dir (vec a, vec b) { cood o = inner(a,b); return (eps < o) - (o < -eps); }
	inline cood sq (vec o = vec()) { return inner(o,o); }
	inline double nr (vec o = vec()) { return sqrt(sq(o)); }
	inline vec proj (vec a, vec b) { return a + (b-a)*(a.inner((*this),b) / a.sq(b)); }
	inline vec rotate (double a) { return vec(cos(a) * x - sin(a)*y, sin(a)*x + cos(a)*y); }
	inline vec rot90 () { return vec(-y,x); }

	inline double angle(vec a, vec b) { return atan2(cross(a, b), inner(a, b)); }
};

struct lin {
	cood a, b, c;
	lin () {} lin(cood x, cood y, cood z) : a(x), b(y), c(z) {}
	lin (vec s, vec t) : a(t.y - s.y), b(s.x - t.x), c(a*s.x + b*s.y) {}

	vec inter (lin o) {
		cood d = a*o.b - o.a*b;
		if (-eps <= d && d <= eps) throw 1;
		return vec((o.b*c - b*o.c)/d, (a*o.c - o.a*c)/d);
	}
};

inline vec furt (vec * p, int n, vec d) {
	if (n == 1) return p[0];
	int s, t;
	ll cur = p[0]*d;
	vec mx = p[0];
	if (p[1]*d >= cur) {
		int lo = 1, hi = n-1;
		while (lo < hi) {
			int md = (lo+hi+1)/2;
			if (p[md]*d >= cur) lo = md;
			else hi = md-1;
		}
		s = 1; t = lo;
	} else {
		int lo = 1, hi = n-1;
		while (lo < hi) {
			int md = (lo+hi)/2;
			if (p[md]*d >= cur) hi = md;
			else lo = md+1;
		}
		s = lo; t = n-1;
	}

	while (s < t) {
		int md = (s+t)/2;

		if (p[md]*d < p[md+1]*d) s = md+1;
		else t = md;
	}
	if (p[s]*d > cur) mx = p[s];
	return mx;
}

const int N = 2e5+7;

int n;
vec v[N];
int m;
int us;
char str[10];

template<class num> inline void rd(num &x) {
	char c;
	while (isspace(c=getchar()));
	bool neg = false;
	if(!isdigit(c)) neg = (c == '-'), x = 0;
	else x = c-'0';
	while (isdigit(c = getchar()))
		x = (x << 3) + (x << 1) + c - '0';
	if (neg) x = -x;
}

inline void rds (char * s) {
	char c;
	while (isspace(s[0]=getchar()));
	s++;
	while (!isspace(s[0]=getchar())) s++;
	s[0] = 0;
}

inline int convex_hull1 (vec * v, int n, int border_in) {
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

int convex_hull (vec * w, vec * v, int n) {
	if (n <= 4) { 
		for (int k = 0; k < n; k++) w[k] = v[k];
		return convex_hull1(w, n, 0);
	}
	int s = 0;
	for (int i = 0; i < n; i++) {
		if (s && w[s-1].x == v[i].x && w[s-1].y == v[i].y) continue;
		while (s >= 2 && w[s-1].ccw(w[s-2],v[i]) > 0) s--;
		w[s++] = v[i];
	}
	int k = s;
	for (int i = n-2; i >= 0; i--) {
		if (s && w[s-1].x == v[i].x && w[s-1].y == v[i].y) continue;
		while (s > k && w[s-1].ccw(w[s-2],v[i]) > 0) s--;
		w[s++] = v[i];
	}
	return s;
}

vec w[N];

int main () {
	rd(n);

	for (int i = 0; i < n; i++) {
		rd(w[i].x);
		rd(w[i].y);
	}
	sort(w, w+n);
	n = convex_hull(v,w,n);
	
	rd(m);
	int sq = sqrt(m*log(m));

	for (int i = 0; i < m; i++) {
		rds(str);
		rd(v[n+us].x);rd(v[n+us].y);
		
		if (str[0] == 'g') {
			ll mx = furt(v, n, v[n+us])*v[n+us];
			for (int j = 0; j < us; j++) mx = max(mx, v[n+us]*v[n+j]);
			printf("%lld\n", mx);
		} else {
			us++;
			if (us == sq) {
				sort(v+n,v+n+us);
				merge(v,v+n,v+n,v+n+us,w);
				n += us;
				n = convex_hull(v,w,n);
				us = 0;
			}
		}
	}
}
