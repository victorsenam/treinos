#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

// area de calota na altura h : 2.pi.R.h
// volume de calota na altura h : pi.h/6 * (3r^2 + h^2)

// XXX marks risky behaviour and TODO marks untested functions
 typedef double cood; cood eps = 0; cood inf = 1./0.;
const double pi = acos(-1.);
inline ll sq (ll x) { return x*x; }
inline double sq (double x) { return x*x; }
struct vec { // vector
	cood x, y;
	vec () : x(0), y(0) {} vec (cood a, cood b) : x(a), y(b) {}
	inline vec operator - (vec o) { return vec(x - o.x, y - o.y); }
	inline vec operator + (vec o) { return vec(x + o.x, y + o.y); }
	inline vec operator * (cood o) { return vec(x * o, y * o); }
	inline vec operator / (cood o) { return vec(x / o, y / o); }
	inline cood operator ^ (vec o) { return x * o.y - y * o.x; }
	inline cood operator * (vec o) { return x * o.x + y * o.y; }

	inline cood cross (vec a, vec b) { return ((*this)-a) ^ ((*this)-b); } // |(this)a|sen(angle)
	inline cood inner (vec a, vec b) { return ((*this)-a) * ((*this)-b); } // |(this)a|cos(angle)
	inline double angle (vec a, vec b) { return atan2(cross(a,b),inner(a,b)); } // ccw angle from (this)a to (this)b in range [-pi,pi]
	inline int ccw (vec a, vec b) { cood o = cross(a,b); return (eps < o) - (o < -eps); } // this is to the (1 left, 0 over, -1 right) of ab
	inline int dir (vec a, vec b) { cood o = inner(a,b); return (eps < o) - (o < -eps); } // a(this) is to the (1 same, 0 none, -1 opposite) direction of ab
	inline cood sq (vec o = vec()) { return inner(o,o); }
	inline double nr (vec o = vec()) { return sqrt(sq(o)); }
	inline vec proj (vec a, vec b) { return a + (b-a)*(a.inner((*this),b) / a.sq(b)); }
	inline vec rotate (double a) { return vec(cos(a) * x - sin(a) * y, sin(a) * x + cos(a) * y); } // ccw by a radians
	inline vec rot90 () { return vec(-y,x); } // rotate(pi/2)

	inline bool operator < (const vec & o) const { return (x != o.x)?(x < o.x):(y > o.y); } // lex compare (inc x, dec y)
	// full ccw angle from compare beginning upwards (this+(0,1)) around (*this)
	// incresing distance on ties
	bool compare (vec a, vec b) { 
		if ((a < (*this)) != (b < (*this))) return a < (*this);
		int o = ccw(a,b); if (o) return o > 0;
		return a.dir((*this),b) < 0;
	}

	bool in_seg (vec a, vec b) { return ccw(a,b) == 0 && dir(a,b) <= 0; } // tips included
	double dist2_lin (vec a, vec b) { return a.sq(b) <= eps ? sq(a) : double(::sq(cross(a,b)))/a.sq(b); } // see cir.has_inter_lin
	double dist2_seg (vec a, vec b) { return a.dir((*this),b) == (b.dir((*this),a)) ? dist2_lin(a,b) : min(sq(a),sq(b)); }
};
struct lin { // line
	cood a, b, c; // a*x + b*y = c
	lin () {} lin (cood x, cood y, cood z) : a(x), b(y), c(z) {}
	lin (vec s, vec t) : a(t.y - s.y), b(s.x - t.x), c(a * s.x + b * s.y) {}
	inline lin parll (vec p) { return lin{a, b, a*p.x + b * p.y}; }
	inline lin perp () { return lin{-b, a, c}; }
	vec inter (lin o) {
		cood d = a * o.b - o.a * b;
		if (-eps <= d && d <= eps) throw 1; // parallel
		return vec((o.b * c - b * o.c) / d, (a * o.c - o.a * c) / d);
	}
	bool contains (vec v) { return abs(a*v.x + b*v.y - c) <= eps; }
	vec at_x (cood x) { return vec(x,(c-a*x)/b); }
	vec at_y (cood y) { return vec((c-b*y)/a,y); }
};
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
	pair<vec,vec> border_inter (cir o) {
		if (!has_border_inter(o)) throw 0;
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
};
bool inter_seg (vec a, vec b, vec c, vec d) {
	if (a.in_seg(c, d) || b.in_seg(c, d) || c.in_seg(a, b) || d.in_seg(a, b)) return true;
	return (c.ccw(a, b) * d.ccw(a, b) == -1 && a.ccw(c, d) * b.ccw(c, d) == -1);
}
double dist2_seg (vec a, vec b, vec c, vec d){return inter_seg(a,b,c,d)?0.:min({ a.dist2_seg(c,d), b.dist2_seg(c,d), c.dist2_seg(a,b), d.dist2_seg(a,b) });} // TODO
ostream& operator<<(ostream& os, vec o) { return os << '(' << o.x << ", " << o.y << ')'; }
ostream& operator<<(ostream& os, lin o) { return os << '[' << o.a << "x + " << o.b << "y = " << o.c << ']'; }
ostream& operator<<(ostream& os, cir o) { return os << '[' << o.c << o.r << ']'; }

cir min_spanning_circle (vec * v, int n) {
	srand(time(NULL)); random_shuffle(v, v+n); cir c(vec(), 0);
	for (int i = 0; i < n; i++) if (!c.contains(v[i])) {
		c = cir(v[i], 0);
		for (int j = 0; j < i; j++) if (!c.contains(v[j])) {
			c = cir((v[i] + v[j])/2, v[i].nr(v[j])/2);
			for (int k = 0; k < j; k++) if (!c.contains(v[k]))
				c = cir(v[i],v[j],v[k]);
		}
	}
    return c;
}
int convex_hull (vec * v, int n, int border_in) {
	swap(v[0], *max_element(v,v+n));
	sort(v+1, v+n, [&v] (vec a, vec b) {
		int o = b.ccw(v[0], a);
		if (o) return (o == 1);
		return v[0].sq(a) < v[0].sq(b);
	});
	if (border_in) {
		int s = n-1;
		while (s > 1 && v[s].ccw(v[s-1],v[0]) == 0) s--;
		for (int i = s; i < n - 1 - (i - s); i++) swap(v[i], v[n-1-(i-s)]);
	}
	int s = 0;
	for (int i = 0; i < n; i++) {
		if (s && v[s-1].x == v[i].x && v[s-1].y == v[i].y) continue;
		while (s >= 2 && v[s-1].ccw(v[s-2],v[i]) >= border_in) s--;
		v[s++] = v[i];
	} 
	return s;
}
double polygon_inter (vec * p, int n, cir c) { // signed area
	return inner_product(p, p+n-1, p+1, c.triang_inter(p[n-1],p[0]), std::plus<double>(), [&c] (vec a, vec b) { return c.triang_inter(a,b); });
}
int polygon_pos (vec * p, int n, vec v, bool verb = 0) { // p should be simple (-1 out, 0 border, 1 in)
	if (verb) cout << v << endl;
	int in = -1; // it's a good idea to randomly rotate the points in the double case, numerically safer
	for (int i = 0; i < n; i++) {
		vec a = p[i], b = p[i?i-1:n-1]; if (a.x > b.x) swap(a,b);
		if (a.x + eps <= v.x && v.x < b.x + eps) { in *= v.ccw(a,b); }
		else if (v.in_seg(a,b)) { return 0; }
	}
	return in;
}
// v is the pointset, w is auxiliary with size at least equal to v's
cood closest_pair (vec * v, vec * w, int l, int r, bool sorted = 0) { // TODO
	if (l + 1 >= r) return inf;
	if (!sorted) sort(v+l,v+r,[](vec a, vec b){ return a.x < b.x; });
	int m = (l+r)/2; cood x = v[m].x;
	cood res = min(closest_pair(v,w,l,m,1),closest_pair(v,w,m,r,1));
	merge(v+l,v+m,v+m,v+r,w+l,[](vec a, vec b){ return a.y < b.y; });
	for (int i = l, s = l; i < r; i++) if (sq((v[i] = w[i]).x - x) < res) {
		for (int j = s-1; j >= l && sq(w[i].y - w[j].y) < res; j--)
			res = min(res, w[i].sq(w[j]));
		w[s++] = v[i];
	}
	return res;
}
// if false, p[t..s] + v is the convex hull of p + v
// if true, v is inside (p[0],p[s],p[t]), s <= t and t - s is minimal
// border is considered inside, assumes convex hull excludes border points
/*
bool in_convex_polygon (vector<vec> & p, vec v, int & s, int & t) {
	int n = p.size(); assert(n > 2);
	if (v.nr(p[0]) <= eps) { s = t = 0; return 1; }
	if (v.ccw(p[0],p[1]) > 0 || v.ccw(p[0],p[n-1]) < 0) { // p[0] stays
		int di = t = s = lower_bound(p.begin() + 1, p.end(), v, [&p] (vec a, vec v) {
			return v.ccw(p[0],a) >= 0;
		}) - p.begin() - 1; // last diagonal before or over this
		if (di == n-1) {
			if (v.ccw(p[0],p[n-1]) == 0 && v.ccw(p[n-2],p[n-1]) >= 0) return 1;
		} else if (di != 0) {
			t += (v.ccw(p[0],p[s]) > 0);
			if (v.ccw(p[s],p[t]) >= 0) return 1;
		}
		s = lower_bound(p.begin() + 1, p.begin() + di + 1, v, [&p] (vec & a, vec v) {
			return v.ccw(*((&a)-1),a) > 0;
		}) - p.begin() - 1; // last that stays <= di
		t = (lower_bound(p.begin() + di + 1, p.end(), -1, [&p,n] (vec & a, vec v) {
			return v.ccw(p[((&a)-(&p[0])+1)%n],a) >= 0;
		}) - p.begin())%n; // first that stays > di
	} else { // p[0] removed
		int di = lower_bound(p.begin() + 1, p.end() - 1, v, [&p] (vec a, vec v) {
			return v.ccw(p[0],a) < 0;
		}) - p.begin(); // first diagonal before of over this
		s = lower_bound(p.begin(), p.begin() + di, v, [&p] (vec & a, vec v) {
			return v.ccw(*((&a)+1),a) >= 0;
		}) - p.begin(); // first that stays < di
		t = lower_bound(p.begin() + di + 1, p.end(), -1, [&p] (vec & a, vec v) {
			return v.ccw(*((&a)-1),a) > 0;
		}) - p.begin() - 1; // last that stays >= di
	}
	return 0;
}
*/

const int N = 103;
int n;
vec v[N];

int main () {
	int tt = 1;
	while (scanf("%d", &n) != EOF) {
		for (int i = 0; i < n; i++)
			scanf("%lf %lf", &v[i].x, &v[i].y);
		cir c = min_spanning_circle(v,n);
		//if (abs(c.c.x) < 5e-3) c.c.x = 0;
		//if (abs(c.c.y) < 5e-3) c.c.y = 0;
		printf("Instancia %d\n%.2lf %.2lf %.2lf\n\n", tt++, c.c.x, c.c.y, abs(c.r));
	}
}
