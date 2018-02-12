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

	inline cood cross(vec a, vec b) { return ((*this)-a)^((*this)-b); }
	inline cood inner(vec a, vec b) { return ((*this)-a)*((*this)-b); }

	inline int ccw (vec a, vec b) { cood o = cross(a,b); return (eps < o) - (o < -eps); }
	inline int dir (vec a, vec b) { cood o = inner(a,b); return (eps < o) - (o < -eps); }
	inline cood sq (vec o = vec()) { return inner(o,o); }
	inline double nr (vec o = vec()) { return sqrt(sq(o)); }
	inline vec proj (vec a, vec b) { return a + (b-a)*(a.inner((*this),b) / a.sq(b)); }
	inline vec rotate (double a) { return vec(cos(a) * x - sin(a)*y, sin(a)*x + cos(a)*y); }
	inline vec rot90 () { return vec(-y,x); }
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

typedef pair<vec,vec> pvv;
pvv res;
cood d;

void upd (pvv cur) {
	if (cur.first.sq(cur.second) < d) {
		res = cur;
		d = cur.first.sq(cur.second);
	}
}

cood closest_pair (vec * v, vec * w, int l, int r, bool sorted = 0) {
	if (l + 1 >= r) return d;
	if (!sorted) sort(v+l,v+r,[](vec a, vec b) { return a.x < b.x; });	
	int m = (l+r)/2; cood x = v[m].x;
	d = min(closest_pair(v,w,l,m,1),closest_pair(v,w,m,r,1));
	merge(v+l,v+m,v+m,v+r,w+l,[](vec a, vec b) { return a.y < b.y; });
	for (int i = l, s = l; i < r; i++) if (sq((v[i] = w[i]).x - x) < d) {
		for (int j = s-1; j >= l && sq(w[i].y - w[j].y) < d; j--)
			upd(pvv(w[i],w[j]));
		w[s++] = v[i];
	}
	return d;
}

const int N = 1e5+7;
int n;
vec v[N], w[N];

int main () {
	d = LLONG_MAX;
	scanf("%d", &n);
	for (int i = 0; i < n; i++){
		scanf("%lld %lld", &v[i].x, &v[i].y);
	}

	closest_pair(v, w, 0, n, 0);
	printf("%lld %lld\n%lld %lld\n", res.first.x, res.first.y, res.second.x, res.second.y);
}
