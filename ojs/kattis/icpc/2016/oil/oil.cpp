#include <bits/stdc++.h>
#define cout if (0) cout

// XXX without explanation marks untested functions

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

// NOT STANDART FROM HERE

// area de calota 2.pi.R.h (h altura)
// volume de calota pi.h/6 * (3r^2 + h^2)

 typedef ll cood;
 cood eps = 0;
// tests for double were made with eps = 1e-8

const double pi = acos(-1.);

inline ll sq (ll x)
{ return x*x; }
inline double sq (double x)
{ return x*x; }

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

	cood pr (vec a, vec b) // norm of projection of (this)a over (this)b times norm of (this)b
	{ return (a-(*this)) * (b-(*this)); }
	int dr (vec a, vec b) // direction of (thia)a relative to (this)b (-1 opposite, 0 none, 1 same)
	{ cood o = pr(a, b); return (eps < o) - (o < -eps); }

	vec rotate (double a) // rotate ccw by a (fails with ll)
	{ return vec(cos(a) * x - sin(a) * y, sin(a) * x + cos(a) * y); }
	vec flip () // rotate pi/2 ccw
	{ return vec(-y, x); }

	inline bool halfplane () // 0 is upper half plane (y > 0) and (x,0) where x >= 0, 1 is otherwise
	{ return (y < eps || (abs(y) <= eps && x < eps)); }

	// === ADVANCED ===
	// full ordering (ccw angle from this+(1,0), distance to this)
	// is a < b?
	// PRECISION : ok with double if norm in [-1e9,5e3]
	bool compare (vec a, vec b) {
		if ((a-(*this)).halfplane() != (b-(*this)).halfplane())
			return (b-(*this)).halfplane();
		int o = sd(a,b);
		if (o) return o < 0;
		return a.dr((*this),b) < 0;
	}

	// is this inside segment st? (tip of segment included, change for dr < 0 otherwise)
	bool in_seg (vec s, vec t)
	{ return (sd(s,t) == 0) && (dr(s,t) <= 0); }

	// squared distance from this to line defined by st
	double dist_lin (vec s, vec t)
	{ return double(::sq((t-s).flip().sq(t-(*this)))) / (t-s).sq(); }

	// squared distance from this to segment st
	double dist_seg (vec s, vec t) 
	{ return dr(s,t) < 0 ? dist_lin(s,t) : min(sq(s),sq(t)); }

	// is this inside (borders included) the convex polygon v of size n?
	// if yes, prec is the vec that this on acw order from v[0] or 0 if there is no such
	// if not, prec is the predecessor of this when added to poly and succ is the sucessor
	// p should be a vector with [0..n-1]
	// n should be >= 2
	bool in_conv_poly (vec v[], int n, const vector<int> & p, int & prec, int & succ) {
		if (nr(v[0]) <= eps) {
			prec = 0;
			return 1;
		}

		if (n == 2) {
			if (in_seg(v[0],v[1]))
				return (prec = 1);

			if (sd(v[0],v[1]) < 0) {
				prec = 1;
				succ = 0;
			} else if (sd(v[0],v[1]) > 0) {
				prec = 0;
				succ = 1;
			} else {
				prec = succ = (v[0].dr((*this),v[1]) < 0);
			}
			return 0;
		}
		
		if (sd(v[0],v[1]) < 0 || sd(v[0],v[n-1]) > 0) {
		// case where v[0] is not removed
			// last diagonal before or over this
			int di = lower_bound(p.begin() + 1, p.end(), -1, [this,v] (int i, int j) {
				assert(j == -1);
				return sd(v[0],v[i]) <= 0;
			}) - p.begin() - 1;

			// is this inside the polygon?
			prec = di;
			if (di == n-1) {
			// last segment
				if (sd(v[0],v[n-1]) == 0 && sd(v[n-2],v[n-1]) <= 0)
					return 1;
			} else {
			// inside otherwise
				if (sd(v[di],v[di+1]) <= 0)
					return 1;
			}

			// last that stays before (or eq to) di
			prec = lower_bound(p.begin() + 1, p.begin() + di + 1, -1, [this,v] (int i, int j) {
				assert(j == -1);
				return sd(v[i-1],v[i]) < 0;
			}) - p.begin() - 1;

			// first that stays after di
			succ = lower_bound(p.begin() + di + 1, p.end(), -1, [this,v,n] (int i, int j) {
				assert(j == -1);
				return sd(v[(i+1)%n],v[i]) <= 0;
			}) - p.begin();
			if (succ == n) succ = 0;
		} else {
		// case where v[0] is removed
			// first diagonal before of over this
			// di is certainly not removed
			int di = lower_bound(p.begin() + 1, p.end() - 1, -1, [this,v] (int i, int j) {
				assert(j == -1);
				return sd(v[0],v[i]) > 0;
			}) - p.begin();

			// first that stays (<= di)
			succ = lower_bound(p.begin(), p.begin() + di, -1, [this,v] (int i, int j) {
				assert(j == -1);
				return sd(v[i+1],v[i]) <= 0;
			}) - p.begin();

			// last that stays (>= di)
			prec = lower_bound(p.begin() + di + 1, p.end(), -1, [this,v] (int i, int j) {
				assert(j == -1);
				return sd(v[i-1],v[i]) < 0;
			}) - p.begin() - 1;
		}
		return 0;
	}
};
ostream& operator<<(ostream& os, vec o)
{ return os << '(' << o.x << ", " << o.y << ')'; }

// XXX
struct lin { // line
	cood a, b, c;

	lin () {}
	lin (cood x, cood y, cood z) : a(x), b(y), c(z) {}
	lin (vec s, vec t) : a(t.y - s.y), b(s.x - t.x), c(a * s.x + b * s.y) {}

	lin parll (vec p) // parallel to this through p
	{ return lin(a, b, a * p.x + b * p.y); }

	vec inter (lin o) {
		cood d = a * o.b - o.a * b;
		if (d < eps && -eps < d) throw 0; // parallel
		return vec((o.b * c - b * o.c) / d, (a * o.c - o.a * c) / d);
	}
};

// XXX
struct cir { // circle
	vec v; cood r;

	bool conta (vec w) // is w in this? (borders included)
	{ return v.sq(w) <= sq(r) + eps; }

	bool inter (cir c) // do this intersect with c? (borders included)
	{ return v.sq(c.v) <= sq(r + c.r) + eps; }

	bool insid (cir c) // is this inside c? (borders can touch)
	{ return (r <= c.r + eps && v.sq(c.v) <= sq(r - c.r) + eps); }

	// watch out for fully contained case
	vec inter (cir c, bool q) { // get q-th intersection this border with c border (assumes 1 or 2 pts)
		cood d = v.nr(c.v);
		double a = (r*r + d*d - c.r*c.r)/(2.*d); // r*cos(ans,v,c.v)
		double h = sqrt(r*r - a*a);
		if (h != h) h = 0;
		vec p = c.v - v;
		return v + p*(a/d) + (p.flip()*(h/d))*(q - !q);
	}
};

// do the segments ab and cd intersect? (borders included) XXX
bool seg_inter (vec a, vec b, vec c, vec d) {
	if (a.in_seg(c, d) || b.in_seg(c, d) || c.in_seg(a, b) || d.in_seg(a, b))
		return true;
	return (c.sd(a, b) * d.sd(a, b) == -1 && a.sd(c, d) * b.sd(c, d) == -1);
}

// squared distance from segments ab and cd XXX
double seg_dist (vec a, vec b, vec c, vec d)
{ return seg_inter(a,b,c,d) ? 0. : min({ a.dist_seg(c,d), b.dist_seg(c,d), c.dist_seg(a,b), d.dist_seg(a,b) }); }

// brd = do points on the border belong to convex?
// computes convex hull of given vector (inplace)
// returns size of convex hull
int graham (vec v[], int n, int brd) {
	for (int i = 1; i < n; i++) {
		if (v[i].x < v[0].x || (v[i].x == v[0].x && v[i].y < v[0].y))
			swap(v[0], v[i]);
	}

	sort(v+1, v+n, [v] (vec a, vec b) {
		int o = b.sd(v[0], a);
		if (o) return (o == -1);
		return v[0].sq(a) < v[0].sq(b);
	});

	if (brd) {
		int s = n-1;
		while (s > 1 && v[s].sd(v[s-1],v[0]) == 0)
			s--;
		for (int i = s; i < n - 1 - (i - s); i++)
			swap(v[i], v[n-1-(i-s)]);
	}

	int s = 0;
	for (int i = 0; i < n; i++) {
		if (s && v[s-1].x == v[i].x && v[s-1].y == v[i].y) continue;
		while (s >= 2 && v[s-1].sd(v[s-2],v[i]) <= -brd)
			s--;
		v[s++] = v[i];
	}

	return s;
}

const int N = 4e3+7;

vec v[N];
int n;
vec anc;

struct evt {
	vec v; int i, close;
	ll val;

	bool operator < (evt ot) const {
		int o = vec(v).sd(anc, ot.v);
		//return o < 0;
		if (o) return o < 0;
		return (!close && ot.close);
	}
};

int main () {
	scanf("%d", &n);

	for (int i = 0; i < n+n; i+=2) {
		scanf("%lld %lld %lld", &v[i].x, &v[i+1].x, &v[i].y);
		if (v[i].x > v[i+1].x) swap(v[i].x, v[i+1].x);
		v[i].y = -v[i].y;
		v[i+1].y = v[i].y;
	}

	ll res = 0;

	for (int i = 0; i < n+n; i++) {
		anc = v[i];
		vector<evt> p;

		for (int j = 0; j < n+n; j+=2) {
			if (v[i].y == v[j].y) continue;
			evt a, b;
			a.close = 0; b.close = 1;
			a.i = b.i = j;
			a.val = v[j+1].x - v[j].x;
			b.val = v[j].x - v[j+1].x;

			if (v[j].y < v[i].y) {
				a.v = v[i] + v[i] - v[j+1];
				b.v = v[i] + v[i] - v[j];
			} else {
				a.v = v[j];
				b.v = v[j+1];
			}

			p.pb(a); p.pb(b);
		}

		sort(p.begin(), p.end());
		ll loc = abs(v[i].x - v[i^1].x);
		res = max(res, loc);
		cout << " == " << v[i] << " == " << endl;

		for (int j = 0; j < p.size(); j++) {
			cout << (p[j].close ? "-" : "+") << p[j].v << " ";
			loc += p[j].val;
			cout << endl;

			res = max(res, loc);
		}
	}

	printf("%lld\n", res);
}
