#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

typedef ll cood; cood eps = 0;

struct vec {
	cood x, y;
	inline vec operator - (vec o) { return {x-o.x,y-o.y}; }
	inline cood operator ^ (vec o) { return x*o.y - y*o.x; }
	inline cood operator * (vec o) { return x*o.x + y*o.y; }

	inline cood cross (vec a, vec b) { return ((*this)-a)^((*this)-b); }
	inline cood inner (vec a, vec b) { return ((*this)-a)*((*this)-b); }
	inline int ccw (vec a, vec b) { cood o = cross(a,b); return (eps < o) - (o < -eps); }
	inline int dir (vec a, vec b) { cood o = inner(a,b); return (eps < o) - (o < -eps); }

	inline cood sq (vec o = {0,0}) { return inner(o,o); }
	inline double nr (vec o = {0,0}) { return sqrt(sq(o)); }

	inline bool operator < (const vec & o) const { return (x != o.x)?(x < o.x):(y > o.y); }
};
ostream & operator << (ostream & os, vec o) {
	return os << "(" << o.x << "," << o.y << ")";
}

int convex_hull (vec * v, int n) {
	if (n <= 1) return n;
	swap(v[0], *min_element(v,v+n));
	sort(v+1, v+n, [&v] (vec a, vec b) {
		int o = b.ccw(v[0],a);
		if (o) return (o == 1);
		return v[0].sq(a) < v[0].sq(b);
	});
	int s = 0;
	for (int i = 0; i < n; i++) {
		if (s && v[s-1].x == v[i].x && v[s-1].y == v[i].y) continue;
		while (s >= 2 && v[s-1].ccw(v[s-2],v[i]) >= 0) s--;
		v[s++] = v[i];
	}
	return s;
}

const int N = 250007;

int n;
vector<vec> v[N];

ll go (int l, int r) {
	if (l == r) {
		//cout << l << ".." << r << endl;
		v[l].resize(convex_hull(&v[l][0], v[l].size()));
		//for (vec a : v[l]) { cout << a << " "; } cout << endl;
		return 0;
	}
	int md = (l+r)/2;
	ll res = max(go(l,md),go(md+1,r));

	int n = v[l].size();
	int m = v[md+1].size();

	//cout << l << ".." << r << endl;
	//for (vec a : v[l]) { cout << a << " "; } cout << endl;
	//for (vec a : v[md+1]) { cout << a << " "; } cout << endl;
	
	if (v[l].size() && v[md+1].size()) {
	/*
		vector<vec> p; p.reserve(n+m);
		p.pb(v[l][0]-v[md+1][0]);
		int j = 1;
		for (int i = 1; i < n; i++) {
			while (j < m && p.back().ccw(v[l][i]-v[md+1][j-1],v[l][i-1]-v[md+1][j]) > 0)
				p.pb(v[l][i-1]-v[md+1][j++]);
			p.pb(v[l][i]-v[md+1][j-1]);
		}
		while (j < m)
			p.pb(v[l][n-1]-v[md+1][j++]);

		for (vec x : p)
			res = max(res, x.sq());

		//for (vec a : p) { cout << a << " "; } cout << endl;
	*/
	/*
		int j = 0;
		for (int i = 0; i < n+n; i++) {
			while (j < m+m && ((v[md+1][(j+1)%m]-v[md+1][j%m])*(v[l][(i+1)%n]-v[l][i%n]) >= 0 || ((v[md+1][(j+1)%m]-v[md+1][j%m])^(v[l][(i+1)%n]-v[l][i%n])) >= 0)) {
				for (int x = 0; x <= 1; x++) for (int y = 0; y <= 1; y++)
					res = max(res, v[l][(i+x)%n].sq(v[md+1][(j+y)%m]));
				j++;
			}
			for (int x = 0; x <= 1; x++) for (int y = 0; y <= 1; y++)
				res = max(res, v[l][(i+x)%n].sq(v[md+1][(j+y)%m]));
		}
	*/
	/*
		vector<vec> & p = v[l];
		vector<vec> & q = v[md+1];
		for (int i = 0; i < n; i++) {
			vec a = p[i], b = p[(i+1)%n];
			
			if (q[0].cross(a,b) < q[1].cross(a,b)) {
				int lo = 0, hi = m-1;
				while (lo < hi) {
					int md = (lo+hi+1)/2;
					if (q[0].cross(a,b) >= q[md].cross(a,b) || q[md-1].cross(a,b) > q[md].cross(a,b))
						hi = md-1;
					else
						lo = md;
				}
				for (int k = m-1; k <= m+1; k++)
					res = max({ res, a.sq(q[(lo+k)%m]), b.sq(q[(lo+k)%m]) });
				lo = 0; hi = m-1;
				while (lo < hi) {
					int md = (lo+hi)/2;
					if (q[0].cross(a,b) < q[md].cross(a,b) || q[md+1].cross(a,b) > q[md].cross(a,b))
						lo = md+1;
					else
						hi = md;
				}
				for (int k = m-1; k <= m+1; k++)
					res = max({ res, a.sq(q[(lo+k)%m]), b.sq(q[(lo+k)%m]) });
			} else {
				int lo = 0, hi = m-1;
				while (lo < hi) {
					int md = (lo+hi+1)/2;
					if (q[0].cross(a,b) < q[md].cross(a,b) || q[md-1].cross(a,b) > q[md].cross(a,b))
						hi = md-1;
					else
						lo = md;
				}
				for (int k = m-1; k <= m+1; k++)
					res = max({ res, a.sq(q[(lo+k)%m]), b.sq(q[(lo+k)%m]) });
				lo = 0; hi = m-1;
				while (lo < hi) {
					int md = (lo+hi)/2;
					if (q[0].cross(a,b) >= q[md].cross(a,b) || q[md+1].cross(a,b) > q[md].cross(a,b))
						lo = md+1;
					else
						hi = md;
				}
				for (int k = m-1; k <= m+1; k++)
					res = max({ res, a.sq(q[(lo+k)%m]), b.sq(q[(lo+k)%m]) });
			}
		}
	*/
	}

	v[l].reserve(n + m);
	for (int i = 0; i < m; i++)
		v[l].pb(v[md+1][i]);
	v[md+1].clear();
	v[l].resize(convex_hull(&v[l][0], v[l].size()));
	return res;
}

int main () {
	scanf("%d", &n);

	for (int i = 0; i < n; i++) {
		vec u; int t;
		scanf("%lld %lld %d", &u.x, &u.y, &t);
		v[t-1].pb(u);
	}

	printf("%lld\n", go(0,n-1));
}
