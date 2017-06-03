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

typedef double cood;
const cood eps = 1e-9;
const double pi = acos(-1.);

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

	// is this inside segment st? (tip of segment included, change for < -eps otherwise)
	bool in_seg (vec s, vec t)
	{ return (sd(s, t) == 0) && ((*this) - s) * ((*this) - t) <= eps; }
};
ostream& operator<<(ostream& os, vec o)
{ return os << setprecision(20) << o.x << " " << o.y; }

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

// tests TODO
// returns any point on the intersection of ab and cd (including all tips)
bool seg_inter (vec a, vec b, vec c, vec d) {
	if (a.in_seg(c, d) || b.in_seg(c, d) || c.in_seg(a, b) || d.in_seg(a, b))
		return true;
	return (c.sd(a, b) * d.sd(a, b) == -1 && a.sd(c, d) * b.sd(c, d) == -1);
}

vec v[4];
int ts;
bool ok;

void fim (vector<vec> res) {
    if (ok) return;

    for (int i = 0; i < 3; i++) {
        if (res[i].x >= 1e6 - eps) return;
        if (res[i].y >= 1e6 - eps) return;
    }

    cout << "YES";
    for (int i = 0; i < 3; i++)
        cout << " " << res[i];
    cout << endl;

    ok = 1;
}

int main () {
    cin >> ts;
    while (ts--) {
        ok = 0;
        for (int i = 0; i < 4; i++)
            cin >> v[i].x >> v[i].y;

        for (int i = 0; !ok && i < 4; i++) {
            for (int j = 0; !ok && j < 4; j++) {
                for (int k = 0; !ok && k < 4; k++) {
                    if (i == j || k == i || k == j) continue;

                    if (v[k].in_seg(v[i], v[j])) {
                        for (int l = 0; l < 4; l++)
                            if (l != k && l != i && l != j)
                                fim({v[i], v[j], v[l]});
                    }
                }
            }
        }

        if (ok) continue;

        for (int i = 0; !ok && i < 4; i++) {
            for (int j = 0; !ok && j < 4; j++) {
                for (int k = 0; !ok && k < 4; k++) {
                    for (int l = 0; !ok && l < 4; l++) {
                        vec a = v[i], b = v[j], c = v[k], d = v[l];
                        if (b.sd(a,c) >= 0) continue; // fixa cone convexo
                        
                        if (!(d.sd(c,a) == 1 && d.sd(c,b) == -1 && d.sd(a,b) == -1)) continue; // fixa cone acb com d fora do triang

                        lin ll = lin(a,b).parll(d);
                        fim({c, ll.inter(lin(c,a)), ll.inter(lin(c,b))});
                    }
                }
            }
        }

        if (ok) continue;

        cout << "NO" << endl;
    }
}
