#include <bits/stdc++.h>
#define cout if (0) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

// area de calota na altura h : 2.pi.R.h
// volume de calota na altura h : pi.h/6 * (3r^2 + h^2)

// XXX marks risky behaviour and TODO marks untested functions
typedef ll cood; cood eps = 0; cood inf = 1./0.;
const double pi = acos(-1.);
inline ll sq (ll x) { return x*x; }
inline double sq (double x) { return x*x; }
struct vec { // vector
	cood x, y;
	int sg;
	vec () : x(0), y(0) {} vec (cood a, cood b) : x(a), y(b) {}
	inline vec operator - (vec o) const { return vec(x - o.x, y - o.y); }
	inline vec operator + (vec o) { return vec(x + o.x, y + o.y); }
	inline vec operator * (cood o) { return vec(x * o, y * o); }
	inline vec operator / (cood o) { return vec(x / o, y / o); }
	inline cood operator ^ (vec o) { return x * o.y - y * o.x; }
	inline cood operator * (vec o) { return x * o.x + y * o.y; }

	inline bool operator == (const vec & o) const { return x == o.x && y == o.y; }
	inline cood cross (vec a, vec b) const { return ((*this)-a) ^ ((*this)-b); } // |(this)a|sen(angle)
	inline cood inner (vec a, vec b) { return ((*this)-a) * ((*this)-b); } // |(this)a|cos(angle)
	inline double angle (vec a, vec b) { return atan2(cross(a,b),inner(a,b)); } // ccw angle from (this)a to (this)b in range [-pi,pi]
	inline int ccw (vec a, vec b) const { cood o = cross(a,b); return (eps < o) - (o < -eps); } // this is to the (1 left, 0 over, -1 right) of ab
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
		if ((a == (*this)) || (b == (*this))) return (a == (*this)) && !(b == (*this));
		if ((a < (*this)) != (b < (*this))) return a < (*this);
		return this->ccw(a,b) > 0;
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

const int N = 4e4+8;

vec anc;

struct seg {
	vec s, t;
	vec rf;
	int ty; // -1 : ignore, 0 : ref, 1 : wall open, 2: wall close

	bool operator < (const seg & o) const {
		cout << ty << s << t << " ? " << o.ty << o.s << o.t << endl;
		if (anc.ccw(o.s,s) > 0) return !((s == o.s && t == o.t) || (o < (*this)));
		cout << "return " << (o.s.ccw(s,t) == -1) << endl;
		return o.s.ccw(s,t) == -1;
	}
};
ostream& operator<<(ostream& os, seg o) { return os << o.ty << o.s << o.t; }

int n, m, wals;
vec v[N], u[N];
seg w[N];
int p[N];

int main () {
	while (scanf("%d %d %d", &n, &m, &wals) != EOF) {
		cout << "==" << n << endl;
		for (int i = 0; i < m; i++) {
			scanf("%lld %lld", &v[i].x, &v[i].y);
			w[i].rf = w[i].s = w[i].t = v[i];	
			w[i].ty = 0;
		}
		for (int i = m; i < m+wals; i++) {
			scanf("%lld %lld", &w[i].s.x, &w[i].s.y);
			scanf("%lld %lld", &w[i].t.x, &w[i].t.y);
			w[i+wals].s = w[i].s;
			w[i+wals].t = w[i].t;
			w[i].rf = w[i].s;
			w[i+wals].rf = w[i].t;
			w[i].ty = 1;
			w[i+wals].ty = 2;
		}

		for (int i = 0; i < n; i++) {
			cout << "=========================== " << v[i] <<  endl;
			anc = v[i];
			set<seg> op;

			for (int j = 0; j < m+wals+wals; j++) {
				if (v[i].ccw(w[j].s,w[j].t) == -1)
					swap(w[j].s,w[j].t);
				
				w[j].rf = w[j].s;
				if (w[j].ty == 2) {
					w[j].rf = w[j].t;
					if (v[i].compare(w[j].t, w[j].s)) {
						cout << "open " << w[j] << endl;
						op.insert(w[j]);
					}
				}
			}
			cout << op.size() << endl;

			sort(w, w+m+wals+wals, [] (seg a, seg b) {
				return anc.compare(a.rf,b.rf);
			});

			int res = 0;
			for (int j = 0; j < m+wals+wals; j++) {
				if (v[i] == w[j].s) continue;
				cout << w[j].rf << endl;
				if (w[j].ty == 0) {
					auto it = op.lower_bound(w[j]);
					if (it == op.begin()) {
						assert(w[j].s == w[j].t);
						cout << v[i] << " vê " << w[j].s << endl;
						res++;
					} else {
						--it;
						cout << v[i] << " nao vê " << w[j].s << " por causa de " << it->s << it->t << endl;
					}
				} else if (w[j].ty == 1) {
					op.insert(w[j]);
				} else if (w[j].ty == 2) {
					op.erase(w[j]);
				} else {
					cout << "EROOO" << endl;
				}
			}

			printf("%d\n", res);
		}
	}
}
