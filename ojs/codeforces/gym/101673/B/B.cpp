#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int T = 2e2+3;
const int N = T*T*4;

typedef double cood; cood eps = 1e-8;
const double pi = acos(-1.);
template<typename T> inline T sq (T x) { return x*x; }
struct vec {
	cood x, y; int cid;
	vec () : x(0), y(0) {} vec (cood a, cood b) : x(a), y(b) {} 
	inline vec operator - (vec o) { return {x-o.x,y-o.y}; }
	inline vec operator + (vec o) { return {x+o.x,y+o.y}; }
	inline vec operator * (cood o) { return { x*o,y*o} ;} 
	inline vec operator / (cood o) { return { x/o,y/o} ;} 
	inline cood operator ^ (vec o) { return x*o.y - y*o.x; }
	inline cood operator * (vec o) { return x*o.x + y*o.y; }
	inline cood cross (vec a, vec b) { return (*this-a)^(*this-b); }
	inline cood inner (vec a, vec b) { return (*this-a)*(*this-b); }
	inline double angle (vec a, vec b) { return atan2(cross(a,b),inner(a,b)); }
	inline int ccw (vec a, vec b) { cood o = cross(a,b); return (eps < o) - (o < -eps); }
	inline int dir (vec a, vec b) { cood o = inner(a,b); return (eps < o) - (o < -eps); }
	inline cood sq (vec o = vec()) { return inner(o,o); }
	inline cood nr (vec o = vec()) { return sqrt(sq(o)); }
	inline vec operator ~ () { return (*this)/nr(); }
	inline vec rot90 () { return {-y,x}; }
	inline vec rotate (double a) { return vec(cos(a)*x - sin(a)*y, sin(a)*x + cos(a)*y); }
	inline bool operator == (vec o) { return (abs(x-o.x) <= eps && abs(y-o.y) <= eps); }
	inline bool operator < (vec o) const { return (abs(x-o.x)>eps)?(x<o.x):(y>o.y); }
};
ostream & operator << (ostream & os, vec v) { return os << "(" << v.x << "," << v.y << ")[" << v.cid << "]"; }

int n, m, s;
vec v[N];

struct cir {
	vec c; cood r; int id;
	cir () {} cir(vec v, cood d) : c(v), r(d) {}
	inline bool contains (vec w) { return c.sq(w) <= sq(r) + eps; }
	inline bool border (vec w) { return abs(c.sq(w) - sq(r)) <= eps; }
	inline double arc_len(vec a, vec b) { return c.angle(a,b)*r; }
	inline double arc_area(vec a, vec b) { return c.angle(a,b)*r*r/2; }
	inline double cut_area(vec a, vec b) { return arc_area(a,b) - c.cross(a,b)/2; }
	pair<vec,vec> tan (vec v) {
		cood d2 = c.sq(v); double s = sqrt(d2 - r*r); s = (s==s)?s:0;
		double al = atan2(r,s); vec t = (~(c-v));
		return pair<vec,vec>(v + t.rotate(al)*s, v + t.rotate(-al)*s);
	}
	void tan (cir v) {
		if (r > v.r) { v.tan(*this); return; }
		v.r -= r;
		if (v.contains(c)) return;
		if (v.r <= eps) {
			vec d = (~(v.c - c).rot90())*r;
			 ::v[m++] = c+d; ::v[m-1].cid = id;
			 ::v[m++] = c-d; ::v[m-1].cid = id;
			 ::v[m++] = v.c+d; ::v[m-1].cid = v.id;
			 ::v[m++] = v.c-d; ::v[m-1].cid = v.id;
			return;
		}
		pair<vec,vec> rt = v.tan(c);
		for (vec p : {rt.first, rt.second}) {
			vec d = (~(p-v.c))*r;
			 ::v[m++] = p+d; ::v[m-1].cid = v.id;
			 ::v[m++] = c+d; ::v[m-1].cid = id;
		}
	}
};
cir c[T];

int convex_hull (vec * v, int n) {
	swap(v[0], *min_element(v,v+n));
	sort(v+1, v+n, [&v] (vec a, vec b) {
		int o = b.ccw(v[0],a);
		if (o) return (o == 1);
		return v[0].sq(a) < v[0].sq(b);
	});
	int s = 0;
	for (int i = 0; i < n; i++) {
		if (s && v[s-1] == v[i]) continue;
		while (s >= 2 && v[s-1].ccw(v[s-2],v[i]) >= 0) s--;
		v[s++] = v[i];
	}
	return s;
}
int main () {
	scanf("%d", &n);

	for (int i = 0; i < n; i++) {
		scanf("%lf %lf %lf", &c[i].c.x, &c[i].c.y, &c[i].r);
		c[i].r += 10;
		c[i].id = i;
		for (int j = 0; j < i; j++)
			c[i].tan(c[j]);
	}
	
	for (int i = 0; i < m; i++) {
		bool ok = 1;
		for (int j = 0; ok && j < n; j++)
			if (j != v[i].cid && c[j].contains(v[i]))
				ok = 0;
		if (ok) v[s++] = v[i];
	}
	double res = 0;
	if (s == 0) {
		for (int i = 0; i < n; i++) res = max(res, 2.*pi*c[i].r);
	} else {
		s = convex_hull(v, s);

		for (int i = 0; i < s; i++) {
			if (v[i].cid == (v[(i+1)%s].cid))
				res += abs(c[v[i].cid].arc_len(v[i],v[(i+1)%s]));
			else
				res += v[i].nr(v[(i+1)%s]);
		}
	}
	printf("%.20f\n", res);
}
