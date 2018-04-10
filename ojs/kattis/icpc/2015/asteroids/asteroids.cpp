#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

typedef double cood; cood eps = 1e-8; // risky: XXX, untested: TODO
const double pi = acos(-1.);
template<typename T> inline T sq(T x) { return x*x; }
struct vec {
	cood x, y;
	vec () : x(0), y(0) {} vec (cood a, cood b) : x(a), y(b) {}
	inline vec operator - (vec o) { return {x - o.x, y - o.y}; }
	inline vec operator + (vec o) { return {x + o.x, y + o.y}; }
	inline vec operator * (cood o) { return {x * o, y * o}; }
	inline vec operator / (cood o) { return {x / o, y / o}; }
	inline cood operator ^ (vec o) { return x * o.y - y * o.x; }
	inline cood operator * (vec o) { return x * o.x + y * o.y; }
	inline cood cross (vec a, vec b) { return ((*this)-a) ^ ((*this)-b); } // |(this)a||(this)b|sen(angle)
	inline cood inner (vec a, vec b) { return ((*this)-a) * ((*this)-b); } // |(this)a||(this)b|cos(angle)
	inline double angle (vec a, vec b) { return atan2(cross(a,b),inner(a,b)); } // ccw angle from (this)a to (this)b in range [-pi,pi]
	inline int ccw (vec a, vec b) { cood o = cross(a,b); return (eps < o) - (o < -eps); } // this is to the (1 left, 0 over, -1 right) of ab
	inline int dir (vec a, vec b) { cood o = inner(a,b); return (eps < o) - (o < -eps); } // a(this) is to the (1 same, 0 none, -1 opposite) direction of ab
	inline cood sq (vec o = vec()) { return inner(o,o); }
	inline double nr (vec o = vec()) { return sqrt(sq(o)); } //$
	inline vec operator ~ () { return (*this)/nr(); }
	inline vec proj (vec a, vec b) { return a + (b-a)*(a.inner((*this),b) / a.sq(b)); } // projects this onto line ab
	inline vec rotate (double a) { return vec(cos(a) * x - sin(a) * y, sin(a) * x + cos(a) * y); } // ccw by a radians
	inline vec rot90 () { return vec(-y,x); } // rotate(pi/2)$
	bool in_seg (vec a, vec b) { return ccw(a,b) == 0 && dir(a,b) <= 0; } // tips included
	double dist2_lin (vec a, vec b) { return a.sq(b) <= eps ? sq(a) : double(::sq(cross(a,b)))/a.sq(b); } // see cir.has_inter_lin
	double dist2_seg (vec a, vec b) { return a.dir((*this),b) == (b.dir((*this),a)) ? dist2_lin(a,b) : min(sq(a),sq(b)); }
	inline bool operator == (const vec & o) const { return abs(x-o.x) <= eps && abs(y-o.y) <= eps; }
	inline bool operator < (const vec & o) const { return (abs(x-o.x)>eps)?(x < o.x):(y > o.y); } // lex compare (inc x, dec y)
	// full ccw angle strict compare beginning upwards (this+(0,1)) around (*this)
	// incresing distance on ties, this is the first
	bool compare (vec a, vec b) { 
		if ((*this < a) != (*this < b)) return *this < b;
		int o = ccw(a,b); return o?o>0:((a == *this && !(a == b)) || a.dir(*this,b) < 0);
	}
}; //$
struct lin { // line
	vec p; cood c; // p*(x,y) = c
	lin () {} lin (vec a, cood b) : p(a), c(b) {}
	lin (vec s, vec t) : p((s-t).rot90()), c(p*s) {}
	inline lin parll (vec v) { return lin(p,v*p); }
	inline lin perp () { return lin(p.rot90(),c); }
	vec inter (lin o) { if (vec(0,0).ccw(p,o.p) == 0) throw 1; cood d = (p^o.p); return vec((c*o.p.y - p.y*o.c)/d,(o.c*p.x - o.p.x*c)/d); }
	bool contains (vec v) { return abs(p*v - c) <= eps; }
	vec at_x (cood x) { return vec(x,(c-p.x*x)/p.y); }
	vec at_y (cood y) { return vec((c-y*p.y)/p.x,y); }
	double sign_dist (vec v) { return double(p*v - c)/p.nr(); }
}; //$
struct cir { // circle
	vec c; cood r;
	cir () {} cir (vec v, cood d) : c(v), r(d) {}
	cir (vec u, vec v, vec w) { // XXX untreated degenerates
		vec mv = (u+v)/2; lin s(mv, mv+(v-u).rot90());
		vec mw = (u+w)/2; lin t(mw, mw+(w-u).rot90());
		c = s.inter(t); r = c.nr(u);
	}
	inline bool contains (vec w) { return c.sq(w) <= sq(r) + eps; } // border included
	inline bool border (vec w) { return abs(c.sq(w) - sq(r)) <= eps; }
	inline bool has_inter (cir o) { return c.sq(o.c) <= sq(r + o.r) + eps; } // borders included
	inline bool has_border_inter (cir o) { return has_inter(o) && c.sq(o.c) + eps >= sq(r - o.r); }
	inline bool has_inter_lin (vec a, vec b) { return a.sq(b) <= eps ? contains(a) : sq(c.cross(a,b)) <= sq(r)*a.sq(b) + eps; } // borders included XXX overflow
	inline bool has_inter_seg (vec a, vec b) { return has_inter_lin(a,b) && (contains(a) || contains(b) || a.dir(c,b)*b.dir(c,a) != -1); } // borders and tips included XXX overflow
	inline double arc_area (vec a, vec b) { return c.angle(a,b)*r*r/2; } // smallest arc, ccw positive
	inline double arc_len (vec a, vec b) { return c.angle(a,b)*r; } // smallest arc, ccw positive
	pair<vec,vec> tan (vec v) { // XXX low precision
		if (contains(v) && !border(v)) throw 0;
		cood d2 = c.sq(v); double s = sqrt(d2 - r*r); s = (s==s)?s:0;
		double al = atan2(r,s); vec t = (~(c-v));
		return pair<vec,vec>(v + t.rotate(al)*s, v + t.rotate(-al)*s);
	}
	pair<vec,vec> border_inter (cir o) {
		if (!has_border_inter(o) || o.c == (*this).c) throw 0;
		double a = (sq(r) + o.c.sq(c) - sq(o.r))/(2*o.c.nr(c));
		vec v = (o.c - c)/o.c.nr(c); vec m = c + v * a;
		double h = sqrt(sq(r) - sq(a)); h = h!=h?0:h;
		return pair<vec,vec>(m + v.rot90()*h, m - v.rot90()*h);
	}
	pair<vec,vec> border_inter_lin (vec a, vec b) { // first is closest to a than second
		if (a.sq(b) <= eps) { if (border(a)) return pair<vec,vec>(a,a); throw 0; }
		if (a.dir(b,c) == -1) swap(a,b);
		if (!has_inter_lin(a,b)) throw 0;
		double d2 = c.dist2_lin(a,b); vec p = (b-a)/a.nr(b);
		double h = sqrt(r*r - d2); h = h!=h?0:h; 
		double y = sqrt(c.sq(a) - d2); y = y!=y?0:y;
		return pair<vec,vec>(a + p*(y-h), a + p*(y+h));
	}
	double triang_inter (vec a, vec b) { // ccw oriented, this with (c,a,b)
		if (c.sq(a) > c.sq(b)) return -triang_inter(b,a);
		if (contains(b)) return c.cross(a,b)/2;
		if (!has_inter_seg(a,b)) return arc_area(a,b);
		pair<vec,vec> itr = border_inter_lin(b,a); // order important
		if (contains(a)) return c.cross(a,itr.first)/2 + arc_area(itr.first,b);
		return arc_area(a,itr.second) + c.cross(itr.second,itr.first)/2 + arc_area(itr.first,b);
	}
}; //$
bool inter_seg (vec a, vec b, vec c, vec d) {
	if (a.in_seg(c, d) || b.in_seg(c, d) || c.in_seg(a, b) || d.in_seg(a, b)) return true;
	return (c.ccw(a, b) * d.ccw(a, b) == -1 && a.ccw(c, d) * b.ccw(c, d) == -1);
}
double dist2_seg (vec a, vec b, vec c, vec d){return inter_seg(a,b,c,d)?0.:min({ a.dist2_seg(c,d), b.dist2_seg(c,d), c.dist2_seg(a,b), d.dist2_seg(a,b) });}

int polygon_pos_convex (vec * p, int n, vec v) { // lg(n) | (-1 out, 0 border, 1 in) TODO 
	if (v.sq(p[0]) <= eps) return 0;
	if (n <= 1) return 0; if (n == 2) return v.in_seg(p[0],p[1])?0:-1;
	if (v.ccw(p[0],p[1]) < 0 || v.ccw(p[0],p[n-1]) > 0) return -1;
	int di = lower_bound(p+1,p+n-1,v, [&p](vec a,vec v) { return v.ccw(p[0],a) > 0; }) - p;
	if (di == 1) return v.ccw(p[1],p[2]) >= 0?0:-1;
	return v.ccw(p[di-1],p[di]);
}//$
int mink_sum (vec * a, int n, vec * b, int m, vec * r) { // (n+m) | a[0]+b[0] should belong to sum, doesn't create new border points TODO
	if (!n || !m) return 0; int i, j, s; r[0] = a[0] + b[0];
	for (i = 0, j = 0, s = 1; i < n || j < m; s++) {
		if (i >= n) j++;
		else if (j >= m) i++;
		else {
			int o = (a[(i+1)%n]+b[j%m]).ccw(r[s-1],a[i%n]+b[(j+1)%m]);
			j += (o >= 0); i += (o <= 0);
		}
		r[s] = a[i%n] + b[j%m];
	}
	return s-1;
}//$
ostream & operator << (ostream & os, vec p) { return os << "(" << p.x << " " << p.y << ")"; }
int inter_convex (vec * p, int n, vec * q, int m, vec * r) { // (n+m) | 
	int a = 0, b = 0, aa = 0, ba = 0, inflag = 0, s = 0;
	while ((aa < n || ba < m) && aa < n+n && ba < m+m) {
		vec p1 = p[a], p2 = p[(a+1)%n], q1 = q[b], q2 = q[(b+1)%m];
		vec A = p2 - p1, B = q2 - q1;
		int cross = vec(0,0).ccw(A,B), ha = p1.ccw(p2,q2), hb = q1.ccw(q2,p2);
		if (cross == 0 && p2.ccw(p1,q1) == 0 && A*B < -eps) {
			if (q1.in_seg(p1,p2)) r[s++] = q1;
			if (q2.in_seg(p1,p2)) r[s++] = q2;
			if (p1.in_seg(q1,q2)) r[s++] = p1;
			if (p2.in_seg(q1,q2)) r[s++] = p2;
			if (s < 2) return s;
			inflag = 1; break;
		} else if (cross != 0 && inter_seg(p1,p2,q1,q2)) {
			if (inflag == 0) aa = ba = 0;
			r[s++] = lin(p1,p2).inter(lin(q1,q2));
			inflag = (hb > 0) ? 1 : -1;
		}
		if (cross == 0 && hb < 0 && ha < 0) return s;
		bool t = cross == 0 && hb == 0 && ha == 0;
		if (t ? (inflag == 1) : (cross >= 0) ? (ha <= 0) : (hb > 0)) {
			if (inflag == -1) r[s++] = q2;
			ba++; b++; b %= m;
		} else {
			if (inflag == 1) r[s++] = p2;
			aa++; a++; a %= n;
		}
	}
	if (inflag == 0) {
		if (polygon_pos_convex(q,m,p[0]) >= 0) { copy(p, p+n, r); return n; }
		if (polygon_pos_convex(p,n,q[0]) >= 0) { copy(q, q+m, r); return m; }
	}
	s = unique(r, r+s) - r;
	if (s > 1 && r[0] == r[s-1]) s--;
	return s;
}

const int N = 12;
int n, m;
vec p[N], q[N], r[N+N];
vec v, u;
vec a[N+N], b[N+N];

double poly_dist (vec * p, int n, vec * q, int m, double s) {
	for (int i = 0; i < n; i++)
		a[i+n] = a[i] = p[i] + v*s;
	int rr = 0;
	for (int i = 0; i < n; i++)
		if (a[i] < a[rr])
			rr = i;
	for (int i = 0; i < m; i++)
		b[i+m] = b[i] = vec(0,0) - q[i] - u*s;
	int ll = 0;
	for (int i = 0; i < m; i++)
		if (b[i] < b[ll])
			ll = i;
	int z = mink_sum(a+rr,n,b+ll,m,r);
	double res = 1./0.;
	if (polygon_pos_convex(r,z,vec(0,0)) >= 0) return 0;
	for (int i = 0; i < z; i++) {
		res = min(res, r[i].sq());
		res = min(res, vec(0,0).dist2_seg(r[i],r[(i+1)%z]));
	}
	return res;
}

double inter_area (vec * p, int n, vec * q, int m, double s) {
	for (int i = 0; i < n; i++) {
		a[i] = p[i] + v*s;
		//cout << a[i] << " ";
	}
	//cout << endl;
	for (int i = 0; i < m; i++) {
		b[i] = q[i] + u*s;
		//cout << b[i] << " ";
	}
	//cout << endl;
	int z = inter_convex(a,n,b,m,r);
	double res = 0;
	for (int i = 0; i + 1 < z; i++) {
		res += r[0].cross(r[i],r[i+1]);
		//cout << r[i] << " ";
	}
	//cout << endl;
	return abs(res);
}

bool ray_inter (vec a, vec b, vec c, vec d) {
	for (vec x : {c,d})
		if (x.ccw(a,b) == 0 && a.dir(b,x) >= 0) return true;
	if (c.ccw(a,b) != d.ccw(a,b))
		return a.ccw(c,d) == a.ccw(c,b);
	return false;
}

bool ext_inter (vec a, vec b, vec c, vec d, vec v) {
	if (inter_seg(a,b,c,d)) return true;
	if (v.sq() <= eps) {
		return false;
	} else if (a.ccw(b,a+v) == 0) {
		if (a.dir(b,a+v) == -1) swap(a,b);
		return ray_inter(a,b,c,d);
	} else {
		for (vec x : {c,d})
			if (x.ccw(a,a+v)*x.ccw(b,b+v) <= 0 && x.ccw(a,b)*(a+v).ccw(a,b) >= 0)
				return true;
		if (ray_inter(a,a+v,c,d) || ray_inter(b,b+v,c,d))
			return true;
	}
	return false;
}

bool poly_inter (vec * p, int n, vec * q, int m, vec v) {
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			if (ext_inter(p[i],p[(i+1)%n],q[j],q[(j+1)%m],v))
				return true;
	return false;
}

int main () {
	scanf("%d", &n);
	for (int i = 0; i < n; i++) scanf("%lf %lf", &p[i].x, &p[i].y);
	scanf("%lf %lf", &v.x, &v.y);
	scanf("%d", &m);
	for (int i = 0; i < m; i++) scanf("%lf %lf", &q[i].x, &q[i].y);
	scanf("%lf %lf", &u.x, &u.y);
	reverse(p,p+n);
	reverse(q,q+m);

	if (!poly_inter(p, n, q, m, v-u)) {
		printf("never\n");
		return 0;
	}

	int ts = 200;
	double lo = 0., hi = 1e8;
	while (ts--) {
		double q1 = (lo+lo+hi)/3, q2 = (lo+hi+hi)/3;
		double v1 = poly_dist(p, n, q, m, q1), v2 = poly_dist(p, n, q, m, q2);
		if (v1 <= v2) hi = q2;
		else lo = q1;
	}
	double t0 = lo;

	lo = t0, hi = 1e8;
	ts = 300;
	while (ts--) {
		double q1 = (lo+lo+hi)/3, q2 = (lo+hi+hi)/3;
		double v1 = inter_area(p, n, q, m, q1), v2 = inter_area(p, n, q, m, q2);
		if (max(v1,v2) <= eps) hi = q2;
		else if (v1 + eps < v2) lo = q1;
		else hi = q2;
	}

	//printf("%.20f\n", inter_area(p, n, q, m, lo));
	printf("%.20f\n", lo);
}
