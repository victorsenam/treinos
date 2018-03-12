#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

typedef double cood; cood eps = 1e-8; 
struct vec {
	cood x, y;
	vec () : x(0), y(0) {} vec (cood a, cood b) : x(a), y(b) {}
	inline vec operator - (vec o) { return {x-o.x,y-o.y}; }
	inline vec operator + (vec o) { return {x+o.x,y+o.y}; }
	inline cood operator ^ (vec o) { return x*o.y-y*o.x; }
	inline cood cross (vec a, vec b) { return (a-*this)^(b-*this); }
	inline int ccw (vec a, vec b) { cood o = cross(a,b); return (eps < o) - (o < -eps); }
	inline cood operator * (vec o) { return x*o.x+y*o.y; }
	inline cood inner (vec a, vec b) { return (a-*this)*(b-*this); }
	inline int dir(vec a, vec b) { cood o = inner(a,b); return (eps < o) - (o < -eps); }
	inline vec rot90 () { return {-y,x}; }
};

struct lin {
	vec p; cood c;
	lin () {} lin (vec a, cood b) : p(a), c(b) {}
	lin (vec s, vec t) : p((s-t).rot90()), c(p*s) {}
	lin revert () { return lin(vec(0,0)-p,-c); }
	vec at_x (cood x) { return vec(x,(c-p.x*x)/p.y); }
	vec at_y (cood y) { return vec((c-p.y*y)/p.x,y); }
	double operator () (cood y) { return at_y(y).x; }
	double inter (lin o) { cood d = (p^o.p); if (abs(d) <= eps) throw 0; return (o.c*p.x - o.p.x*c)/d; }
};

typedef double num;
struct envelope {
	deque<lin> q; num lo, hi; envelope (num _lo, num _hi) : lo(_lo), hi(_hi) {}
	void push_back (lin l) {
		if (!q.empty() && q.back()(hi) <= l(hi)) return;
		for (num x; q.size(); q.pop_back()) {
			x = (q.size()<=1?lo:min(max(lo,next(q.rbegin())->inter(q.back())),hi));
			if (l(x) >= q.back()(x)) break;
		}
		q.push_back(l);
	}
};

const int N = 1e2+7;

int n;
vector<vec> v[N];
vector<ll> y;

bool covers (double a, double b, double l, double r) {
	if (a > b) swap(a,b); if (l > r) swap(l,r);
	return a <= l + eps && r <= b + eps; 
}

int main () {
	scanf("%d", &n);

	double sm = 0;
	for (int i = 0; i < n; i++) {
		int m;
		scanf("%d", &m);
		v[i].resize(m);
		for (vec & w : v[i]) {
			ll yy;
			scanf("%lf", &w.x);
			scanf("%lld", &yy);
			w.y = yy;
			y.pb(yy);
		}
		double loc = 0;
		for (int j = 1; j < m-1; j++)
			loc += v[i][0].cross(v[i][j],v[i][j+1]);
		sm += abs(loc);
	}
	sort(y.begin(),y.end());
	y.resize(unique(y.begin(),y.end()) - y.begin());
	
	double res = 0;
	for (int i = 0; i < y.size() - 1; i++) {
		envelope env(y[i],y[i+1]);

		vector<lin> inss[2];
		for (int j = 0; j < n; j++) {
			int sz = v[j].size();
			for (int k = 0; k < sz; k++) {
				vec s = v[j][k], t = v[j][(k+1)%sz];
				if (abs(s.y - t.y) <= eps || !covers(s.y,t.y,env.lo,env.hi)) continue;
				inss[0].pb(lin(s,t));
				s.x = 1000 - s.x; t.x = 1000 - t.x;
				inss[1].pb(lin(s,t));
			}
		}
		for (int kk = 0; kk < 2; kk++) {
			vector<lin> & ins = inss[kk];
			for (int i = 0; i < ins.size(); i++) if (ins[i].p.x > 0) ins[i] = ins[i].revert();
			sort(ins.begin(), ins.end(), [] (lin a, lin b) { return b.p.ccw(vec(0,0),a.p) == 1; });
			for (int i = 0; i < ins.size(); i++) env.pb(ins[i]);
			double ls = y[i];
			for (int i = 0; i < env.q.size(); i++) {
				double en = y[i+1];
				if (i < env.q.size()-1) en = env.q[i].inter(env.q[i+1]);
				double md = (env.q[i](ls) + env.q[i](en))/2;
				res -= (md)*(en-ls);
				ls = en;
			}
			env.q.clear();
		}

		res += 1000.*(y[i+1]-y[i]);
	}
	printf("%.20f %.20f\n", sm/2, res);
}
