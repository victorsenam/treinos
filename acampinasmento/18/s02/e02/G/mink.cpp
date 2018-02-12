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

int n, m;
vector<vec> v[N];

void mink (vector<vec> & p, vector<vec> & q) {
	for (vec a : p)
		cout << a << " ";
	cout << endl;
	for (vec a : q)
		cout << a << " ";
	cout << endl;
	int n = p.size(), m = q.size();
	p.pb(p[0]); p.pb(p[1]); q.pb(q[0]); q.pb(q[1]);
	vector<vec> mnk;
	mnk.pb(p[0]+q[0]);
	int j = 0;
	for (int i = 0; i < n; i++) {
		for (; j < m && mnk.back().ccw(p[i]+q[j+1],p[i+1]+q[j]) >= 0; j++)
			mnk.pb(p[i]+q[j+1]);
		mnk.pb(p[i+1]+q[j]);
	}
	for (; j < m; j++) mnk.pb(p[n-1]+q[j+1]);
	ll res = 0;
	cout << "sums " << endl;
	for (vec a : mnk) {
		cout << a << " ";
	}
	cout << endl;
}

int main () {
	scanf("%d %d", &n, &m);

	vector<vec> p,q;
	for (int i = 0; i < n; i++) {
		vec u; scanf("%lld %lld", &u.x, &u.y); p.pb(u);
	}
	for (int i = 0; i < m; i++) {
		vec u; scanf("%lld %lld", &u.x, &u.y); q.pb(u);
	}

	mink(p,q);
}
