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
	int i;
	cood x, y;
	vec () : x(0),y(0) {} vec(cood a, cood b) : x(a),y(b) {}
	inline vec operator - (vec o) { return {x - o.x, y-o.y}; }
	inline vec operator + (vec o) { return {x + o.x, y+o.y}; }
	inline vec operator * (cood o) { return {x*o, y*o}; }
	inline vec operator / (cood o) { return {x/o, y/o}; }
	inline cood operator ^ (vec o) { return x*o.y - y*o.x; }
	inline cood operator * (vec o) { return x*o.x + y*o.y; }

	inline cood cross(vec a, vec b) { return ((*this)-a)^((*this)-b); }
	inline cood inner(vec a, vec b) { return ((*this)-a)*((*this)-b); }

	inline int ccw (vec a, vec b) { cood o = cross(a,b); return (eps < o) - (o < -eps); }
	inline int dir (vec a, vec b) { cood o = inner(a,b); return (eps < o) - (o < -eps); }
	inline cood sq (vec o = vec()) { return inner(o,o); }
	inline double nr (vec o = vec()) { return sqrt(sq(o)); }
	inline vec proj (vec a, vec b) { return a + (b-a)*(a.inner((*this),b) / a.sq(b)); }
	inline vec rotate (double a) { return vec(cos(a) * x - sin(a)*y, sin(a)*x + cos(a)*y); }
	inline vec rot90 () { return vec(-y,x); }

	inline bool operator < (const vec & o) const { return (x != o.x)?(x<o.x):(y>o.y); }
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

struct cir {
	vec c; cood r;
	cir () {} cir(vec v, cood d) : c(v), r(d) {}
	cir (vec u, vec v, vec w) {
		vec mv = (u+v)/2; lin s(mv, mv+(v-u).rot90());
		vec mw = (u+w)/2; lin t(mw, mw+(w-u).rot90());
		c = s.inter(t); r = c.nr(u);
	}

	inline bool contains (vec w) { return c.sq(w) <= sq(r) + eps; }
};

cir min_spanning_circle (vec * v, int n) {
	srand(time(NULL)); random_shuffle(v, v+n); cir c(vec(),0);
	for (int i = 0; i < n; i++) if (!c.contains(v[i])) {
		c = cir(v[i],0);
		for (int j = 0; j < i; j++) if (!c.contains(v[j])) {
			c = cir((v[i]+v[j])/2, v[i].nr(v[j])/2);
			for (int k = 0; k < j; k++) if (!c.contains(v[k])) {
				c = cir(v[i],v[j],v[k]);
			}
		}
	}
	return c;
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
		v[s++] = v[i];
	}
	return s;
}

const int N = 2e6+7;

int n;
vec v[N];

int main () {
	scanf("%d", &n);

	for (int i = 0; i < n; i++) {
		scanf("%lld %lld", &v[i].x, &v[i].y);
		v[i].i = i;
	}

	int s = convex_hull(v, n, 0);
	printf("%d\n", s);
	printf("%d", v[0].i+1);
	for (int i = 1; i < s; i++)
		printf(" %d", v[i].i+1);
	printf("\n");
	double pr = 0;
	for (int i = 0; i < s; i++)
		pr += v[i].nr(v[(i+1)%s]);
	ll ar = 0;
	for (int i = 1; i < s-1; i++)
		ar += v[0].cross(v[i],v[i+1]);
	ar = abs(ar);
	printf("%.20f\n%lld.%lld\n", pr, ar/2, (ar%2)*5);

