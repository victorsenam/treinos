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
	vector<vec> q;
	sort(v, v+n, [] (vec a, vec b) { return (a.x!=b.x)?a.x<b.x:a.y<b.y; });
	if (n == 1) q.pb(v[0]);
	else if (n > 1) {
		for (int k = 0; k < 2; k++) {
			int start = q.size();
			for (int i = 0; i < n; i++) {
				while (q.size() >= start + 2 && q[q.size()-2].cross(q.back(), v[i]) <= 0)
					q.pop_back();
				q.push_back(v[i]);
			}
			q.pop_back();
			reverse(v,v+n);
		}
	}
	for (int i = 0; i < q.size(); i++) v[i] = q[i];
	return q.size();
}

int convex_hull2 (vec * v, int n) {
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

ll Rot(vector<vec> & p, vector<vec> & q) {
	int a = 0, b =0;
	int n = p.size(), m = q.size();
	for (int i = 0; i < n; i++) if (p[i].y > p[a].y) a = i;
	for (int i = 0; i < m; i++) if (q[i].y < q[b].y) b = i;
	p.pb(p[0]); q.pb(q[0]);

	ll ans = 0;
	for (int i = 0; i < n; i++) {
		while ( p[a].cross(p[a+1],q[b+1]) > p[a].cross(p[a+1],q[b]) )
			b = (b + 1)%m;
		for (vec u : {p[a],p[a+1]}) for (vec w : {q[b],q[b+1]})
			ans = max(ans, u.sq(w));
		a = (a + 1)%n;
	}
	p.pop_back(); q.pop_back();
	return ans;
}

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
		res = max({ res, Rot(v[l],v[md+1]), Rot(v[md+1],v[l]) });
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
