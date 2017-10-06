#include <bits/stdc++.h>
#define debug if (1)

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

	bool operator < (vec o) const 
	{ return (x < o.x || (x == o.x && y > o.y)); }

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

	cood cross (vec a, vec b) // ccw signed area (positive if this is to the left of ab)
	{ return (b - a) ^ ((*this) - a); }
	int ccw (vec a, vec b) // which side is this from ab? (1 left, 0 over, -1 right)
	{ cood o = cross(a, b); return (eps < o) - (o < -eps); } 

	cood inner (vec a, vec b) // norm of projection of (this)a over (this)b times norm of (this)b
	{ return (a-(*this)) * (b-(*this)); }
	int dir (vec a, vec b) // direction of (thia)a relative to (this)b (-1 opposite, 0 none, 1 same)
	{ cood o = inner(a, b); return (eps < o) - (o < -eps); }

	vec rotate (double a) // rotate ccw by a (fails with ll)
	{ return vec(cos(a) * x - sin(a) * y, sin(a) * x + cos(a) * y); }
	vec rot90 () // rotate pi/2 ccw
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
		int o = ccw(a,b);
		if (o) return o > 0;
		return a.dir((*this),b) < 0;
	}

	// is this inside segment st? (tip of segment included, change for dr < 0 otherwise)
	bool in_seg (vec s, vec t)
	{ return (ccw(s,t) == 0) && (dir(s,t) <= 0); }

	// XXX squared distance from this to line defined by st
	double dist2_lin (vec s, vec t)
	{ return double(::sq((t-s).rot90().sq(t-(*this)))) / t.sq(s); }

	// XXX squared distance from this to segment st
	double dist2_seg (vec s, vec t) 
	{ return dir(s,t) < 0 ? dist2_lin(s,t) : min(sq(s),sq(t)); }

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

			if (ccw(v[0],v[1]) > 0) {
				prec = 1;
				succ = 0;
			} else if (ccw(v[0],v[1]) < 0) {
				prec = 0;
				succ = 1;
			} else {
				prec = succ = (v[0].dir((*this),v[1]) < 0);
			}
			return 0;
		}
		
		if (ccw(v[0],v[1]) > 0 || ccw(v[0],v[n-1]) < 0) {
		// case where v[0] is not removed
			// last diagonal before or over this
			int di = lower_bound(p.begin() + 1, p.end(), -1, [this,v] (int i, int j) {
				assert(j == -1);
				return ccw(v[0],v[i]) >= 0;
			}) - p.begin() - 1;

			// is this inside the polygon?
			prec = di;
			if (di == n-1) {
			// last segment
				if (ccw(v[0],v[n-1]) == 0 && ccw(v[n-2],v[n-1]) >= 0)
					return 1;
			} else {
			// inside otherwise
				if (ccw(v[di],v[di+1]) >= 0)
					return 1;
			}

			// last that stays before (or eq to) di
			prec = lower_bound(p.begin() + 1, p.begin() + di + 1, -1, [this,v] (int i, int j) {
				assert(j == -1);
				return ccw(v[i-1],v[i]) > 0;
			}) - p.begin() - 1;

			// first that stays after di
			succ = lower_bound(p.begin() + di + 1, p.end(), -1, [this,v,n] (int i, int j) {
				assert(j == -1);
				return ccw(v[(i+1)%n],v[i]) >= 0;
			}) - p.begin();
			if (succ == n) succ = 0;
		} else {
		// case where v[0] is removed
			// first diagonal before of over this
			// di is certainly not removed
			int di = lower_bound(p.begin() + 1, p.end() - 1, -1, [this,v] (int i, int j) {
				assert(j == -1);
				return ccw(v[0],v[i]) < 0;
			}) - p.begin();

			// first that stays (<= di)
			succ = lower_bound(p.begin(), p.begin() + di, -1, [this,v] (int i, int j) {
				assert(j == -1);
				return ccw(v[i+1],v[i]) >= 0;
			}) - p.begin();

			// last that stays (>= di)
			prec = lower_bound(p.begin() + di + 1, p.end(), -1, [this,v] (int i, int j) {
				assert(j == -1);
				return ccw(v[i-1],v[i]) > 0;
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
	vec c; cood r;

	// borders included
	bool contains (vec w)
	{ return c.sq(w) <= sq(r) + eps; }
	bool has_inter (cir o)
	{ return c.sq(o.c) <= sq(r + o.r) + eps; }
	bool has_inter_lin (vec s, vec t)
	{ return c.dist2_lin(s,t) <= sq(r) + eps; }
	bool has_inter_seg (vec s, vec t)
	{ return c.dist2_seg(s,t) <= sq(r) + eps; }

	// borders not included
	bool contains (cir o)
	{ return (o.r < r - eps && c.sq(o.c) < sq(r - o.r) - eps); }

	// double only
	pair<vec,vec> inter_pts (cir o) {
		assert(has_inter(o) && !contains(o)); // fully contained case
		double d = c.nr(o.c);
		double a = (r*r + d*d - o.r*o.r) / (2.*d); // r*cos(ans,v,c.v)
		double h = sqrt(r*r - a*a);
		if (::isnan(h)) h = 0;
		vec p = o.c - c;
		return pair<vec,vec>(c + p*(a/d) + (p.rot90()*(h/d)), c + p*(a/d) - (p.rot90()*(h/d)));
	}

	// double only
	pair<vec,vec> inter_pts (vec s, vec t) { 
		assert(has_inter_lin(s,t));
		double d = s.nr(t);
		double h = abs(s.cross(t,c)) / (2.*d);
		double x = sqrt(s.sq(c) - h*h);
		double y = sqrt(r*r - h*h);
		if (::isnan(y)) y = 0;
		vec p = t - s;
		return pair<vec,vec>(s + p*((x-y)/d), s + p*((x+y)/d));
	}
};

// do the segments ab and cd intersect? (borders included) XXX
bool inter_seg (vec a, vec b, vec c, vec d) {
	if (a.in_seg(c, d) || b.in_seg(c, d) || c.in_seg(a, b) || d.in_seg(a, b))
		return true;
	return (c.ccw(a, b) * d.ccw(a, b) == -1 && a.ccw(c, d) * b.ccw(c, d) == -1);
}

// squared distance from segments ab and cd XXX
double dist2_seg (vec a, vec b, vec c, vec d)
{ return inter_seg(a,b,c,d) ? 0. : min({ a.dist2_seg(c,d), b.dist2_seg(c,d), c.dist2_seg(a,b), d.dist2_seg(a,b) }); }

// brd = do points on the border belong to convex?
// computes convex hull of given vector (inplace)
// returns size of convex hull
int graham (vec v[], int n, int brd) {
	for (int i = 1; i < n; i++) {
		if (v[i].x < v[0].x || (v[i].x == v[0].x && v[i].y < v[0].y))
			swap(v[0], v[i]);
	}

	sort(v+1, v+n, [v] (vec a, vec b) {
		int o = b.ccw(v[0], a);
		if (o) return (o == 1);
		return v[0].sq(a) < v[0].sq(b);
	});

	if (brd) {
		int s = n-1;
		while (s > 1 && v[s].ccw(v[s-1],v[0]) == 0)
			s--;
		for (int i = s; i < n - 1 - (i - s); i++)
			swap(v[i], v[n-1-(i-s)]);
	}

	int s = 0;
	for (int i = 0; i < n; i++) {
		if (s && v[s-1].x == v[i].x && v[s-1].y == v[i].y) continue;
		while (s >= 2 && v[s-1].ccw(v[s-2],v[i]) >= brd)
			s--;
		v[s++] = v[i];
	}

	return s;
}

struct point {
	vec v;
	int idx;
	int type; // 0 : tip, 1 : query

	bool operator < (point & ot) {
		return v.x < ot.v.x;
	}
};

const int N = 1e6+7;

int n, m, q;
point v[N], inp[N];
int p[N];
int gr[N], ns;
vector<int> is_on[N];
int tips[N][2];
int node[N];
int visi[N];
vector<int> adj[N];

void dfs (int u) {
	if (visi[u]) return;
	visi[u] = 1;
	for (int v : adj[u])
		dfs(v);
}

struct segm {
	int i, j;
	int idx;

	int oth (int x) {
		if (i == x) return j;
		return i;
	}

	bool operator < (segm o) const {
		assert(v[i].v.x <= v[o.i].v.x);
		assert(i != j);
		assert(idx != N-1);
		//cout << "with " << idx << " " << v[i].v << " " << v[j].v;
		int r = v[o.i].v.ccw(v[i].v, v[j].v);
		//cout << " -> " << r << endl;
		return r == 1;
	}
};

segm sg[N];
set<segm> s;

int main () {
	scanf("%d %d %d", &n, &m, &q);
	ns = 1;

	for (int i = 0; i < n; i++) {
		scanf("%lld %lld", &v[i].v.x, &v[i].v.y);
		v[i].idx = i;
		v[i].type = 0;
		inp[i] = v[i];
		p[i] = i;
	}
	
	for (int i = 0; i < m; i++) {
		int a, b;
		scanf("%d %d", &a, &b);
		a--; b--;

		tips[i][0] = ns++;
		tips[i][1] = ns++;

		if (v[b].v < v[a].v)
			swap(a,b);
		sg[i] = segm({a,b,i});
		is_on[a].pb(i);
		is_on[b].pb(i);
	}

	for (int i = 0; i < n; i++) {
		sort(is_on[i].begin(), is_on[i].end(), [i] (int x, int y) {
			int a = sg[x].oth(i);
			int b = sg[y].oth(i);

			if ((v[a].v < v[i].v) != (v[b].v < v[i].v))
				return v[a].v < v[i].v;
			return v[a].v.ccw(v[i].v, v[b].v) == 1;
		});

		for (int j = 0; j < is_on[i].size(); j++) {
			segm a = sg[is_on[i][j]];
			segm b = sg[is_on[i][(j+1)%is_on[i].size()]];
			
			int x = tips[a.idx][!(v[i].v < v[a.oth(i)].v)];
			int y = tips[b.idx][!(v[b.oth(i)].v < v[i].v)];

			adj[x].pb(y);
			adj[y].pb(x);
		}
	}

	for (int i = 0; i < q; i++) {
		scanf("%lld %lld", &v[i+n].v.x, &v[i+n].v.y);
		v[i+n].idx = i;
		v[i+n].type = 1;
		p[i+n] = i+n;

		node[i+n] = ns++;
	}

	sort(p, p+n+q, [] (int i, int j) {
		return v[i] < v[j];
	});

	for (int _i = 0; _i < n+q;) {
		point ev = v[p[_i]];

		vector<int> queries;
		vector<int> vertical, before, after;

		while (_i < n+q && !(ev < v[p[_i]])) {
			int i = p[_i];
			cout << v[i].v << " ";
			if (v[i].type == 0) {
				for (int j : is_on[i]) {
					int a = sg[j].oth(i);
					if (v[i].v.x == v[a].v.x) {
						if (v[i].v.y < v[a].v.y)
							vertical.pb(j);
					} else if (v[i].v < v[a].v) {
						after.pb(j);
					} else {
						before.pb(j);
					}
				}
			} else {
				queries.pb(i);
			}
			_i++;
		}
		cout << endl;

		for (int j : vertical) {
			// segmento acima (ou que passa pelo) sg[j].i (não sg[j].j)
			int x = 0;
			auto it = s.lower_bound(sg[j]);
			if (it != s.end()) x = it->idx;

			adj[tips[j][0]].pb(tips[x][0]);
			adj[tips[x][0]].pb(tips[j][0]);
		}

		for (int j : queries) {
			// segmento acima de v[j].v
			sg[N-1].i = sg[N-1].j = j;
			sg[N-1].idx = N-1;
			int x = 0;
			cout << "query " << j << endl;
			for (segm ss : s)
				cout << "with " << ss.idx << " " << v[ss.i].v << " " << v[ss.j].v << " -> " << v[j].v.ccw(v[ss.i].v, v[ss.j].v) << endl;
			auto it = s.lower_bound(sg[N-1]);
			if (it != s.end()) x = it->idx;
			cout << "results in " << x << endl;

			adj[node[j]].pb(tips[x][0]);
			adj[tips[x][0]].pb(node[j]);
		}

		for (int j : before) {
			s.erase(sg[j]);
			cout << "remove " << j << endl;
			for (segm ss : s)
				cout << "with " << ss.idx << " " << v[ss.i].v << " " << v[ss.j].v << " -> " << v[sg[j].i].v.ccw(v[ss.i].v, v[ss.j].v) << endl;
		}

		for (int j : after) {
			s.insert(sg[j]);
			cout << "add " << j << " : " << v[sg[j].i].v << " " << v[sg[j].j].v << endl;
			for (segm ss : s)
				cout << "with " << ss.idx << " " << v[ss.i].v << " " << v[ss.j].v << " -> " << v[sg[j].i].v.ccw(v[ss.i].v, v[ss.j].v) << endl;
		}

		for (int j : queries) {
			// segmento acima de v[j].v
			sg[N-1].i = sg[N-1].j = j;
			sg[N-1].idx = N-1;
			int x = 0;
			auto it = s.lower_bound(sg[N-1]);
			if (it != s.end()) x = it->idx;

			adj[node[j]].pb(tips[x][0]);
			adj[tips[x][0]].pb(node[j]);
		}
		
		for (int j : vertical) {
			// segmento acima (ou que passa pelo) sg[j].i (não sg[j].j)
			int x = 0;
			auto it = s.lower_bound(sg[j]);
			if (it != s.end()) x = it->idx;

			adj[tips[j][1]].pb(tips[x][0]);
			adj[tips[x][0]].pb(tips[j][1]);
		}
	}

	for (int i = 0; i < q; i++)
		if (visi[node[i+n]])
			printf("Yes\n");
		else
			printf("No\n");
}
