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
double dist2_seg (vec a, vec b, vec c, vec d){return inter_seg(a,b,c,d)?0.:min({ a.dist2_seg(c,d), b.dist2_seg(c,d), c.dist2_seg(a,b), d.dist2_seg(a,b) });}
ostream& operator<<(ostream& os, lin o) { return os << '[' << o.p << "*(x,y) = " << o.c << ']'; }
ostream& operator<<(ostream& os, cir o) { return os << '[' << o.c << o.r << ']'; }

const int N = 2e3+7;

struct Seg {
	vec s, t;
	int id;
	vector<vec> v;

	bool operator < (const Seg & ot) const { return (s==ot.s)?t<ot.t:s<ot.s; }
};


int n;
vector<Seg> sg;
int uf[N];
map<vec, vector<vec> > mp;

int find (int u) {
	if (uf[u] < 0) return u;
	return uf[u] = find(uf[u]);
}

void join (int u, int v) {
	if ((u = find(u)) == (v = find(v))) return;
	if (-uf[u] < -uf[v]) swap(u,v);
	uf[u] += uf[v];
	uf[v] = u;
}

int polygon_pos (vec v, vec *p, int n) {
	int in = -1;
	for (int i = 0; i < n; i++) {
		vec a = p[i], b = p[i?i-1:n-1]; if (a.x > b.x) swap(a,b);
		if (a.x + eps <= v.x && v.x < b.x + eps) { in *= v.ccw(a,b); }
		else if (v.in_seg(a,b)) return 0;
	}
	return in;
}

vector<vec> pl[N];
int idx[N];

int main () {
	scanf("%d", &n);
	double sm = 0, res = 0;

	for (int i = 0; i < n; i++) {
		int m;
		scanf("%d", &m);
		vec fst, ls, v;
		scanf("%lf %lf", &fst.x, &fst.y);
		ls = fst;
		double loc = 0;
		idx[i] = sg.size();
		pl[i].pb(fst);
		for (int j = 1; j < m; j++) {
			scanf("%lf %lf", &v.x, &v.y);
			sg.pb({ls,v,i});
			pl[i].pb(v);
			if (j > 1) loc += fst.cross(ls,v);
			ls = v;
		}
		sg.pb({ls,fst,i});
		sm += abs(loc);
	}
	
	for (int i = 0; i < sg.size(); i++) {
		if (sg[i].t < sg[i].s) swap(sg[i].s,sg[i].t);
		uf[i] = -1;
	}
	uf[sg.size()] = -1;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (i == j) continue;
			for (vec v : pl[j])
				if (polygon_pos(v, &pl[i][0], pl[i].size()) != -1)
					join(idx[i],idx[j]);
		}
	}
	
	for (int i = 0; i < sg.size(); i++) {
		for (int j = 0; j < sg.size(); j++) {
			if (!inter_seg(sg[i].t,sg[i].s,sg[j].t,sg[j].s)) continue;
			join(i,j);

			if (abs((sg[i].t-sg[i].s)^(sg[j].t-sg[j].s)) <= eps) {
				for (vec w : {sg[j].t, sg[j].s})
					if (w.in_seg(sg[i].s,sg[i].t))
						sg[i].v.pb(w);
			} else {
				vec itr = lin(sg[i].s,sg[i].t).inter(lin(sg[j].s,sg[j].t));
				sg[i].v.pb(itr);
			}
		}

		sort(sg[i].v.begin(), sg[i].v.end(), [i] (vec a, vec b) { return sg[i].s.sq(a) < sg[i].s.sq(b); });
		sg[i].v.resize(unique(sg[i].v.begin(), sg[i].v.end()) - sg[i].v.begin());
		//cout << "[" << sg[i].s << " " << sg[i].t << "]:";
		for (int j = 0; j < sg[i].v.size(); j++) {
			//cout << " " << sg[i].v[j];
			if (j) mp[sg[i].v[j]].pb(sg[i].v[j-1]);
			if (j + 1 < sg[i].v.size()) mp[sg[i].v[j]].pb(sg[i].v[j+1]);
		}
		//cout << endl;
	}

	for (auto & it : mp) {
		//cout << it.first << ":";
		sort(it.second.begin(), it.second.end(), [it] (vec a, vec b) { return vec(it.first).compare(a,b); });
		it.second.resize(unique(it.second.begin(), it.second.end()) - it.second.begin());
		if (it.second.front() == it.first) it.second.erase(it.second.begin());
	//	for (vec v : it.second)
	//		cout << " " << v;
	//	cout << endl;
	}

	for (int i = 0; i < sg.size(); i++) {
		//cout << "===" << endl;
		double loc = 0;
		if (find(i) == find(sg.size())) continue;

		vec fst = sg[i].s;
		for (int j = i+1; j < sg.size(); j++) if (find(i) == find(j)) fst = min(fst,sg[j].s);
		vec ls = fst;
		vec v = mp[ls].front();
		//cout << "[" << v << "]";
		//cout << fst << endl;

		while (!(v == fst)) {
			//cout << v << endl;
			int k = 0;
			vector<vec> & adj = mp[v];
			while (!(adj[k] == ls)) k++; // I like to live dangerously
			ls = v;
			v = adj[(k+1)%adj.size()];
			loc += fst.cross(ls,v);
		}

		res += abs(loc);
		join(i,sg.size());
	}

	printf("%.20f %.20f\n", sm/2, res/2);
}
