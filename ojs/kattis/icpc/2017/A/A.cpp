#include <bits/stdc++.h>
//#define ONLINE_JUDGE
#ifndef ONLINE_JUDGE
#define debug(...) {fprintf(stdout, __VA_ARGS__);}
#else
#define debug(...) {}
#endif

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

// NOT STANDART FROM HERE

const double pi = acos(-1.);
typedef double cood;
const double eps = 1e-9;

struct vec { // vector
	// === BASIC ===
	cood x, y;
	vec () : x(0), y(0) {}
	vec (cood a, cood b) : x(a), y(b) {}
	friend ostream& operator<<(ostream& os, vec o);

	vec operator - (vec o)
	{ return vec(x - o.x, y - o.y); }
	vec operator + (vec o)
	{ return vec(x + o.x, y + o.y); }
	vec operator * (cood o)
	{ return vec(x * o, y * o); }
	vec operator / (cood o)
	{ return vec(x / o, y / o); }
	cood operator ^ (vec o)
	{ return x * o.y - y * o.x; }
	cood operator * (vec o)
	{ return x * o.x + y * o.y; }

	cood sq (vec o = vec())
	{ return ((*this)-o)*((*this)-o); }
	double nr (vec o = vec())
	{ return sqrt(sq(o)); }

	cood ar (vec a, vec b) // ccw signed area (positive if this is to the left of ab)
	{ return (b - a) ^ ((*this) - a); }
	int sd (vec a, vec b) // which side is this from ab? (-1 left, 0 over, 1 right)
	{ cood o = ar(a, b); return (o < -eps) - (o > eps); }

    cood pr (vec a, vec b)
    { return (b - a) * ((*this) - a); }
    int dr (vec a, vec b)
    { cood o = pr(a, b); return (o > eps) - (o < -eps); }

	// === ADVANCED ===
	// rotate ccw by a (fails with ll)
	vec rotate (double a)
	{ return vec(cos(a) * x - sin(a) * y, sin(a) * x + cos(a) * y); }

	// divide the plane relative to anc
	// 0 if the ccw angle from anc to this is in [0,pi) and 1 otherwise, origin goes to 0
	bool halfplane (vec anc = vec(1,0)) {
		cood l = sd(vec(), anc);
		if (l == 0)
			return (x < -eps);
		return (l == 1);
	}

	// ordering (ccw angle from anc, distance to origin)
	// is this < o?
	// PRECISION : ok with double if norm in [-1e4,1e3]
	bool compare (vec o, vec anc = vec(1,0)) {
		bool s[2] = {halfplane(anc), o.halfplane(anc)};
		if (s[0] != s[1])
			return s[0] < s[1];

		cood l = sd(o, vec());
		if (l == 0)
			return sq() < o.sq() - eps;
		return (l == -1);
	}

	// tests TODO
	// is this inside segment st? (tip of segment included, change for -eps otherwise)
	bool in_seg (vec s, vec t)
	{ return (sd(s, t) == 0) && ((*this) - s) * ((*this) - t) < eps; }

};
ostream& operator<<(ostream& os, vec o)
{ return os << '(' << o.x << ", " << o.y << ')'; }

// tests TODO
struct lin { // line
	cood a, b, c;

	lin () {}
	lin (cood x, cood y, cood z) : a(x), b(y), c(z) {}
	lin (vec s, vec t) : a(t.y - s.y), b(s.x - t.x), c(a * s.x + b * s.y) {}

	// parallel to this through p
	lin parll (vec p) { return lin(a, b, a * p.x + b * p.y); }

	// line intersection
	vec inter (lin o) {
		cood d = a * o.b - o.a * b;
		if (abs(d) < eps) throw 0; // parallel
		return vec((o.b * c - b * o.c) / d, (a * o.c - o.a * c) / d);
	}
};

// ab is a line, cd is a seg
bool seg_inter (vec a, vec b, vec c, vec d) {
	//if (a.in_seg(c, d) || b.in_seg(c, d) || c.in_seg(a, b) || d.in_seg(a, b))
		//return true;
	return (c.sd(a, b) * d.sd(a, b) == -1);
}

void upd (bool & n, vec & a, vec o, vec ref, vec to) {
    if (o.dr(ref,to) == 1)
        if (n || ref.sq(o) < ref.sq(a)) {
            n = 0;
            a = o;
        }
}

const int N = 1e3;
int n;
vec v[N];

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n;

    for (int i = 0; i < n; i++)
        v[i+n] = v[i];

    double res = 0.;
    for (int i = 0; i < n; i++) {
        for (int j = i+1; j < n; j++) {
            bool ok = 1;   

            bool nl = 1, nr = 1;
            vec l, r;

            for (int k = 0; ok && k < n; k++) {
                if (seg_inter(v[i],v[j],v[k],v[k+1])) {
                    vec at = lin(v[i],v[j]).inter(lin(v[k],v[k+1]));

                    upd(nl, l, at, v[i], v[j]);
                    upd(nr, r, at, v[j], v[i]);
                }

                if (v[k+1].sd(v[i],v[j]) == 0) {
                    if ((v[k].sd(v[i],v[j]) * v[k+2].sd(v[i],v[j]) == -1) ||
                        v[k+2].sd(v[k],v[k+1]) == 1) {
                            upd(nl, l, v[k+1], v[i], v[j]);
                            upd(nr, r, v[k+1], v[j], v[i]);
                    }
                }
            }

            if (!nl && !nr && r.dr(v[j],v[i]) != 1 && l.dr(v[i],v[j]) != 1)
                res = max(res,l.nr(r));
        }
    }

    cout << setprecision(20) << res << endl;
}
