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

int convex_hull (vec * v, int n) {
	if (n <= 1) return n;
	swap(v[0], *max_element(v,v+n));
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

ll calc (int s, int t, int l, int r, int lo, int hi, int w) {
	if (l > r) return 0;
	int md = (l+r)/2;

	int b = lo;
	for (int k = lo+1; k <= hi; k++) {
		if (v[s][md].sq(v[t][k]) > v[s][md].sq(v[t][b]))
			b = k;
	}

	if (w)
		return max({
			calc(s,t,l,md-1,lo,b,w),
			calc(s,t,md+1,r,b,hi,w),
			v[s][md].sq(v[t][b])
		});
	else
		return max({
			calc(s,t,l,md-1,b,hi,w),
			calc(s,t,md+1,r,lo,b,w),
			v[s][md].sq(v[t][b])
		});
}

ll go (int l, int r) {
	if (l == r) return 0;
	int md = (l+r)/2;
	ll res = max(go(l,md),go(md+1,r));

	int n = v[l].size();
	int m = v[md+1].size();
	v[l].reserve(n+n);
	v[md+1].reserve(m+m);
	for (int i = 0; i < n; i++)
		v[l].pb(v[l][i]);
	for (int i = 0; i < m; i++)
		v[md+1].pb(v[md+1][i]);

	if (v[l].size() && v[md+1].size()) {
		int a = 0;
		while (v[l][a].x < v[l][a+1].x) a++;
		int b = a;
		while (v[l][b].x > v[l][b+1].x) b++;

		int c = 0;
		while (v[md+1][c].x < v[md+1][c+1].x) c++;
		int d = c;
		while (v[md+1][d].x > v[md+1][d+1].x) d++;
		for (int k = 0; k < 2; k++)
		res = max({
			res,
			calc(l,md+1,a,b,c,d,k),
			calc(l,md+1,b,a+n,c,d,k),
			calc(l,md+1,a,b,d,c+m,k),
			calc(l,md+1,b,a+n,d,c+m,k)
				});
	}

	v[l].resize(n);
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
