#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef pair<ll,ll> pii;

const double pi = acos(-1.);
typedef ll cood;
const cood eps = 0;

struct vec {
	cood x,  y;
	vec() : x(0), y(0) {}
	vec(cood a, cood b) : x(a), y(b) {}

	vec operator - (vec o)
	{ return vec(x - o.x, y - o.y); }
	vec operator + (vec o)
	{ return vec(x + o.x, y + o.y); }

	cood operator ^ (vec o)
	{ return x * o.y - y * o.x; }
	cood operator * (vec o)
	{ return x * o.x + y * o.y; }

	cood sq (vec o = vec())
	{ return ((*this)-o)*((*this)-o); }

	cood ar (vec a, vec b)
	{ return (b - a) ^ ((*this) - a); }
	int sd (vec a, vec b)
	{ cood o = ar(a, b); return (o < -eps) - (o > eps); }

	bool in_seg (vec s, vec t)
	{ return (sd(s,t) == 0); }
};

bool seg_inter (vec a, vec b, vec c, vec d) {
	//if (a.in_seg(c, d) || b.in_seg(c,d) || c.in_seg(a,b) || d.in_seg(a,b))
		//return true;
	return (c.sd(a,b) * d.sd(a,b) == -1 && a.sd(c,d) * b.sd(c,d) == -1);
}

// ab is a line
bool lin_seg (vec a, vec b, vec c, vec d) {
	//if (a.in_seg(c, d) || b.in_seg(c,d) || c.in_seg(a,b) || d.in_seg(a,b))
		//return true;
	return (c.sd(a,b) * d.sd(a,b) == -1);
}

typedef long double dbl;
const dbl EPS = 1e-12;

struct lin {
	// maybe change this to ll since it is integer
	dbl a, b, c;
	dbl xo, yo, ax, ay;
	lin(vec s, vec t) : a(t.y - s.y), b(s.x - t.x), c(a * s.x + b * s.y), xo(s.x), yo(s.y), ax(t.x - s.x), ay(t.y - s.y) {}

	dbl inter(lin o) {
		dbl d = a * o.b - o.a * b;
		if(abs(d) < EPS) return 1. / 0.;
		//assert(abs(d) > EPS);
		dbl x = (o.b * c - b * o.c) / d, y = (a * o.c - o.a * c) / d;
		x -= xo; y -= yo;
		if(abs(ax) > abs(ay)) return x / ax;
		return y / ay;
	}
};

const int N = 11234;
vec v[N];
int n;

int main () {
	ios::sync_with_stdio(false);
	cin.tie(0);

	cin >> n;
	dbl res = 0;
	for (int i = 0; i < n; i++) {
		cin >> v[i].x >> v[i].y;
	}
	for(int i = n; i < 2 * n; i++) v[i] = v[i - n];

	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			//if ((i+1)%n == j || (i+n-1)%n == j)
			//	continue;
            if (v[i+n-1].sd(v[i], v[i+1]) == -1) {
                if (v[j].sd(v[i],v[i+1]) == 1 || v[j].sd(v[i], v[i+n-1]) == -1)
                    continue;
            } else {
                if (v[j].sd(v[i],v[i+n-1]) != 1 && v[j].sd(v[i], v[i+1]) != -1)
                    continue;
            }

			vec A = v[i], B = v[j];
			vec AB = B - A;
			lin lab(A, B);
			dbl l = -1. / 0., r = 1. / 0.;
			//printf(" at %d -- %d\n", i, j); 

			bool ok = 1;
			for (int k = 0; k < n; k++)
				if (lin_seg(A, B, v[k], v[(k+1)%n])) {
					dbl d = lab.inter(lin(v[k], v[k + 1]));
					//printf("(%d, %d) intersects with d = %.10f\n", k, k + 1, (double)d);
					if(d <= 1 - EPS) l = max(l, d);
					if(d >= 0 + EPS) r = min(r, d);
				}
			for(int k = 2; k <= n + 1; k++)
				if(v[k].in_seg(A, B)) {
					//printf(" %d inside \n" , k);
					vec v1 = v[k - 1];
					vec v2 = v[k + 1];
					if(v1.sd(A, B) == v2.sd(A, B)) continue;
					if(v1.sd(A, B) * v2.sd(A, B) == 0) {
					//if(v1.sd(A,B) * v2.sd(A,B) != -1) {
						//if(v1.sd(A, B) + v2.sd(A, B) == 1) continue;
						if(v2.sd(v1, v[k]) == 1) continue;
					}
					//printf(" %d ok \n" , k);
					dbl d;
					if(abs(AB.x) > abs(AB.y)) d = dbl(v[k].x - A.x) / dbl(AB.x);
					else d = dbl(v[k].y - A.y) / dbl(AB.y);
					//printf("%d intersects with d = %.10f\n", k, (double)d);
					if(d <= 1 - EPS) l = max(l, d);
					if(d >= 0 + EPS) r = min(r, d);
				}

			assert(r - l != 1./0.);
			//cout << i << " -- " << j << ": " << l << " " << r << endl;
			res = max(res, (r - l) * sqrt((B - A).sq()));			
		}
	}

	cout << setprecision(20) << res << endl;
}
