#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

typedef double cood; cood eps = 1e-8; cood inf = 1./0.; // risky: XXX, untested: TODO
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
	inline double nr (vec o = vec()) { return sqrt(sq(o)); }
	inline vec operator ~ () { return (*this)/nr(); }
	inline vec proj (vec a, vec b) { return a + (b-a)*(a.inner((*this),b) / a.sq(b)); } // projects this onto line ab
	inline vec rotate (double a) { return vec(cos(a) * x - sin(a) * y, sin(a) * x + cos(a) * y); } // ccw by a radians
	inline vec rot90 () { return vec(-y,x); } // rotate(pi/2)
	inline bool operator == (const vec & o) const { return abs(x-o.x) <= eps && abs(y-o.y) <= eps; }
	inline bool operator < (const vec & o) const { return (abs(x-o.x)>eps)?(x < o.x):(y > o.y); } // lex compare (inc x, dec y)
	// full ccw angle strict compare beginning upwards (this+(0,1)) around (*this)
	// incresing distance on ties, this is the first
	bool compare (vec a, vec b) { 
		if ((*this < a) != (*this < b)) return *this < b;
		int o = ccw(a,b); return o?o>0:((a == *this && !(a == b)) || a.dir(*this,b) < 0);
	}
	bool in_seg (vec a, vec b) { return ccw(a,b) == 0 && dir(a,b) <= 0; } // tips included
	double dist2_lin (vec a, vec b) { return a.sq(b) <= eps ? sq(a) : double(::sq(cross(a,b)))/a.sq(b); } // see cir.has_inter_lin
	double dist2_seg (vec a, vec b) { return a.dir((*this),b) == (b.dir((*this),a)) ? dist2_lin(a,b) : min(sq(a),sq(b)); }
};
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
};
ostream& operator<<(ostream& os, vec o) { return os << '(' << o.x << ", " << o.y << ')'; }
struct cir { // circle
	vec c; cood r; cood h;
	cir () {} cir (vec v, cood d) : c(v), r(d) {}
	cir (vec u, vec v, vec w) { // XXX untreated degenerates
		vec mv = (u+v)/2; lin s(mv, mv+(v-u).rot90());
		vec mw = (u+w)/2; lin t(mw, mw+(w-u).rot90());
		c = s.inter(t); r = c.nr(u);
	}
	inline bool contains (vec w) { return c.sq(w) <= sq(r) + eps; } // border included
	inline bool border (vec w) { return abs(c.sq(w) - sq(r)) <= eps; }
	inline bool contains_strict (vec w) { return contains(w) && !border(w); }
	inline bool has_inter (cir o) { return c.sq(o.c) <= sq(r + o.r) + eps; } // borders included
	inline bool has_border_inter (cir o) { return has_inter(o) && c.sq(o.c) + eps >= sq(r - o.r); }
	inline bool has_inter_lin (vec a, vec b) { return a.sq(b) <= eps ? contains(a) : sq(c.cross(a,b)) <= sq(r)*a.sq(b) + eps; } // borders included XXX overflow
	inline bool has_inter_seg (vec a, vec b) { return has_inter_lin(a,b) && (contains(a) || contains(b) || a.dir(c,b)*b.dir(c,a) != -1); } // borders and tips included XXX overflow
	inline bool has_inter_lin_strict (vec a, vec b) { return a.sq(b) <= eps ? contains_strict(a) : sq(c.cross(a,b)) < sq(r)*a.sq(b) - eps; }
	inline bool has_inter_seg_strict (vec a, vec b) { return has_inter_lin_strict(a,b) && (contains_strict(a) || contains_strict(b) || a.dir(c,b)*b.dir(c,a) == 1); }
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
	vec inner_tan (cir o) { return (c*o.r + o.c*r)/(r + o.r); }
};
bool inter_seg (vec a, vec b, vec c, vec d) {
	if (a.in_seg(c, d) || b.in_seg(c, d) || c.in_seg(a, b) || d.in_seg(a, b)) return true;
	return (c.ccw(a, b) * d.ccw(a, b) == -1 && a.ccw(c, d) * b.ccw(c, d) == -1);
}
double dist2_seg (vec a, vec b, vec c, vec d){return inter_seg(a,b,c,d)?0.:min({ a.dist2_seg(c,d), b.dist2_seg(c,d), c.dist2_seg(a,b), d.dist2_seg(a,b) });}
ostream& operator<<(ostream& os, lin o) { return os << '[' << o.p << "*(x,y) = " << o.c << ']'; }
ostream& operator<<(ostream& os, cir o) { return os << '[' << o.c << o.r << ']'; }

const int N = 102;

int n;
vec ret[4];
cir v[N];
int ts;

bool go (int id, vec m, vec a) {
	vec tom = (~(m - a)); vec b = v[id].c*2 - a;
	vec r[4] = {a, a + tom*v[id].h, b + tom*v[id].h, b};
	int orient = r[0].ccw(r[1],r[2]);
	assert(orient);

	for (int i = 0; i < n; i++) if (i != id) {
		bool isout = false;
		for (int j = 0; j < 4; j++) {
			vec a = r[j], b = r[(j+1)%4];
			if (v[i].c.ccw(a,b)*orient == -1)
				isout = true;
			if (v[i].has_inter_seg_strict(a,b)) return false;
		}
		if (!isout) return false;
	}
	for (int k = 0; k < 4; k++) {
		for (int j = 0; j < 4; j++) {
			if (inter_seg(r[j], r[(j+1)%4], ret[k], ret[(k+1)%4])) return false;
		}
	}
	//cout << "rolou " << id << " de " << a << " para " << m << endl;
	return true;
}

bool testa (int id, vec m) {
	if (v[id].contains(m) && !v[id].border(m)) return false;
	pair<vec,vec> from = v[id].tan(m);
	for (vec a : {from.first, from.second}) {
		if (go(id,m,a)) return true;
	}
	return false;
}

int main () {
	srand(time(NULL));
	scanf("%lf %lf %lf %lf", &ret[0].x, &ret[0].y, &ret[2].x, &ret[2].y);
	while (++ts && scanf("%d", &n) != EOF && n) {
		ret[1].x = ret[0].x; ret[1].y = ret[2].y;
		ret[3].x = ret[2].x; ret[3].y = ret[0].y;
		for (int i = 0; i < n; i++) {
			scanf("%lf %lf %lf %lf", &v[i].c.x, &v[i].c.y, &v[i].r, &v[i].h);
			v[i].r /= 2;
		}
		random_shuffle(v, v+n);
		int in_n = n;		
		bool cut = false;
		do {
			cut = false;

			for (int i = 0; i < n; i++) {
				bool cut_this = false;
				for (vec dir : {vec(1,v[i].r),vec(v[i].r,1),vec(-1,v[i].r),vec(v[i].r,-1)}) {
					if (testa(i,v[i].c+dir)) {
						cut_this = true;
						break;
					}
				}
				for (int j = 0; !cut_this && j < 4; j++) {
					for (vec dir : {vec(v[i].r,0),vec(0,v[i].r),vec(-v[i].r,0),vec(0,-v[i].r)}) { 
						try {
							pair<vec,vec> itr = cir(v[i].c,v[i].h-v[i].r).border_inter_lin(ret[j]+dir, ret[(j+1)%4]+dir);
							if (!cut_this) cut_this = testa(i,itr.first-dir);
							if (!cut_this) cut_this = testa(i,itr.second-dir);
						} catch (int e) {
						}
					}
				}
				for (int j = 0; !cut_this && j < n; j++) if (i != j)
					cut_this = testa(i,v[i].inner_tan(v[j]));
				if (cut_this) {
					cut = true;
					n--;
					swap(v[i], v[n]);
				}
			}
		} while (cut);

		printf("Forest %d\n%d tree(s) can be cut\n\n", ts, in_n - n);
		scanf("%lf %lf %lf %lf", &ret[0].x, &ret[0].y, &ret[2].x, &ret[2].y);
	}
}
