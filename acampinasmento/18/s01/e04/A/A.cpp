#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

typedef double cood;
const cood eps = 1e-8;
const int M = 2e4+7;

struct pnt {
	cood x, y, z;
};

struct vec {
	cood x, y;
	vec () : x(0),y(0) {} vec (cood a, cood b) : x(a), y(b) {}
	inline vec operator - (vec o) { return {x - o.x, y - o.y}; }
	inline vec operator + (vec o) { return {x + o.x, y + o.y}; }
	inline cood operator ^ (vec o) { return x * o.y - y * o.x; }
	inline cood operator * (vec o) { return x * o.x + y * o.y; }

	inline cood cross (vec a, vec b) { return ((*this)-a)^((*this)-b); }
	inline cood inner (vec a, vec b) { return ((*this)-a)*((*this)-b); }
	inline int ccw (vec a, vec b) { cood o = cross(a,b); return (eps < o) - (o < -eps); }

	inline cood sq (vec o = vec()) { return inner(o,o); }

	inline bool operator < (const vec & o) const {
		return (o.x!=x)?x<o.x:y<o.y;
	}
};

int convex_hull (vec * v, int n, int border_in) {
	if (n <= 1) return n;
	swap(v[0], *max_element(v,v+n));
	sort(v+1, v+n, [&v] (vec a, vec b) {
		int o = b.ccw(v[0],a);
		if (o) return (o == 1);
		return v[0].sq(a) < v[0].sq(b);
	});
	int s = 0;
	for (int i = 0; i < n; i++) {
		if (s && abs(v[s-1].x - v[i].x) <= eps && abs(v[s-1].y - v[i].y) <= eps) continue;
		while (s >= 2 && v[s-1].ccw(v[s-2],v[i]) >= border_in) s--;
		v[s++] = v[i];
	}
	return s;
}

vec p[M];
int ps;

void addInter (pnt s, pnt t, double z) {
	if (s.z > t.z) swap(s,t);
	if (s.z > z + eps || z > t.z + eps) return;
	if (abs(s.z - t.z) <= eps) {
		p[ps].x = s.x; p[ps].y = s.y; ps++;
		p[ps].x = t.x; p[ps].y = t.y; ps++;
	} else {
		double dx = (t.x - s.x)/(t.z - s.z);
		double dy = (t.y - s.y)/(t.z - s.z);
		vec r;
		r.x = s.x + dx*(z - s.z);
		r.y = s.y + dy*(z - s.z);
		p[ps].x = r.x; p[ps].y = r.y; ps++;
	}
}

const int N = 1e2+3;

int n, z_min, z_max;
pnt v[N];

int main () {
#ifdef ONLINE_JUDGE
	freopen("aerodynamics.in", "r", stdin);
	freopen("aerodynamics.out", "w", stdout);
#endif

	scanf("%d %d %d", &n, &z_min, &z_max);
	for (int i = 0; i < n; i++) {
		scanf("%lf %lf %lf", &v[i].x, &v[i].y, &v[i].z);
	}

	for (int z = z_min; z <= z_max; z++) {
		ps = 0;
		for (int i = 0; i < n; i++)
			for (int j = i+1; j < n; j++)
				addInter(v[i],v[j],z);
		ps = convex_hull(p,ps,0);
		double area = 0;
		for (int i = 1; i < ps-1; i++) {
			area += p[0].cross(p[i],p[i+1]);
		}
		printf("%.20f\n", abs(area)/2);
	}
}
