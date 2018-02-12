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
	inline vec operator + (vec o) { return {x+o.x,y+o.y}; }
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
ostream & operator << (ostream & os, vec o) { return os << "(" << o.x << "," << o.y << ")"; }
ostream & operator << (ostream & os, vector<vec> & o) { os << o.size() << ": "; for (vec v : o) os << " " << v; return os; }

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

ll mink (vector<vec> & p, vector<vec> & q) {
	if (p.empty() || q.empty()) return 0;
	p.resize(convex_hull(&p[0],p.size()));
	q.resize(convex_hull(&q[0],q.size()));
	int n = p.size(), m = q.size();
	//cout << "====" << endl << p << endl << q << endl;
	ll res = 0; int i = 0, j = 0; vector<vec> r;
	do {
		r.pb(p[i]+q[j]);
		res = max(res, r.back().sq());
		int o = r.back().ccw(p[(i+1)%n]+q[j],p[i]+q[(j+1)%m]);
		i += (o >= 0); j += (o <= 0); i %= n; j %= m;
	} while (i != 0 || j != 0);
	//cout << r << endl;
	return res;
}

ll go (int l, int r) {
	if (l == r) return 0;
	int md = (l+r)/2;
	ll res = max(go(l,md),go(md+1,r));

	int n = v[l].size();
	int m = v[md+1].size();

	//cout << l << ".." << r << endl;
	
	for (int i = 0; i < v[md+1].size(); i++)
		v[md+1][i] = ((vec){0,0}) - v[md+1][i];
	res = max(res, mink(v[l],v[md+1]));

	v[l].reserve(n + m);
	for (int i = 0; i < v[md+1].size(); i++)
		v[l].pb(((vec){0,0}) - v[md+1][i]);;
	v[md+1].clear();
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
