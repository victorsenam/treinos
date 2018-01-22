#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

typedef double cood; cood eps = 1e-8;
inline double sq (double x) { return x*x; }
struct vec {
	cood x, y;
	vec () : x(0), y(0) {} vec (cood a, cood b) : x(a), y(b) {}
	inline vec operator + (vec o) { return vec(x+o.x,y+o.y); }
	inline vec operator - (vec o) { return vec(x-o.x,y-o.y); }
	inline cood operator * (vec o) { return x * o.x + y * o.y; }
	inline vec operator / (cood o) { return vec(x/o,y/o); }
	inline vec operator * (cood o) { return vec(x*o,y*o); }
	inline cood inner (vec a, vec b) { return ((*this)-a) * ((*this)-b); }
	inline vec rot90 () { return vec(-y,x); }

	inline bool operator < (vec o) { return (x!=o.x)?x<o.x:y<o.y; }

	inline cood sq (vec o = vec()) { return inner(o,o); }
	inline double nr (vec o = vec()) { return sqrt(sq(o)); }
};

struct cir {
	vec c; cood r;
	cir () {} cir (vec v, cood d) : c(v), r(d) {}

	pair<vec,vec> border_inter (cir o) {
		double a = (sq(r) + o.c.sq(c) - sq(o.r))/(2*o.c.nr(c));
		vec v = (o.c - c)/o.c.nr(c); vec m = c + v*a;
		double h = sqrt(sq(r) - sq(a)); h = h!=h?0:h;
		return pair<vec,vec>(m + v.rot90()*h, m - v.rot90()*h);
	}
};

int main () {
	int ts;
	scanf("%d", &ts);
	while (ts--) {
		cir a, b;
		scanf("%lf %lf %lf", &a.c.x, &a.c.y, &a.r);
		scanf("%lf %lf %lf", &b.c.x, &b.c.y, &b.r);

		if (max({ abs(a.c.x - b.c.x), abs(a.c.y - b.c.y), abs(a.r - b.r) }) <= eps) {
			printf("Oops, too many points\n");
		} else if (abs(a.c.sq(b.c) - sq(a.r + b.r)) <= eps || abs(a.c.sq(b.c) - sq(a.r - b.r)) <= eps) {
			pair<vec,vec> res = a.border_inter(b);
			printf("There are only 1 of them\n");
			printf("%.20f %.20f\n", res.first.x, res.first.y);
		} else if (a.c.sq(b.c) < sq(a.r + b.r) + eps && a.c.sq(b.c) + eps > sq(a.r - b.r)) {
			pair<vec,vec> res = a.border_inter(b);
			printf("There are only 2 of them\n");
			if (res.second < res.first) swap(res.first, res.second);
			printf("%.20f %.20f\n", res.first.x, res.first.y);
			printf("%.20f %.20f\n", res.second.x, res.second.y);
		} else {
			printf("There are no points\n");
		}

		if (ts) printf("\n");
	}
}
