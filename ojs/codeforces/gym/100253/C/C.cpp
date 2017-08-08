#include <bits/stdc++.h>
#define debug if (1)

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

typedef long double cood;
cood eps = 1e-8;

const cood pi = acos(-1.);

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
	cood nr (vec o = vec())
	{ return sqrt(sq(o)); }

	cood ar (vec a, vec b) // ccw signed area (positive if this is to the left of ab)
	{ return (b - a) ^ ((*this) - a); }
	int sd (vec a, vec b) // which side is this from ab? (-1 left, 0 over, 1 right)
	{ cood o = ar(a, b); return (o < -eps) - (eps < o); }

	// === ADVANCED ===
	// rotate ccw by a (fails with ll)
	vec rotate (cood a)
	{ return vec(cosl(a) * x - sinl(a) * y, sinl(a) * x + cosl(a) * y); }

	// divide the plane relative to anc
	// 0 if the ccw angle from anc to this is in [0,pi) and 1 otherwise, origin goes to 0
	bool halfplane (vec anc = vec(1,0)) {
		int l = sd(vec(), anc);
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

		int l = sd(o, vec());
		if (l == 0)
			return sq() - o.sq() < -eps;
		return (l == -1);
	}

	// is this inside segment st? (tip of segment included, change for < -eps otherwise)
	bool in_seg (vec s, vec t)
	{ return (sd(s, t) == 0) && !(eps < ((*this) - s) * ((*this) - t)); }
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
		if (d < eps && -eps < d) throw 0; // parallel
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

const int N = 103;

int n;
vec d[2][2];
vec r[5][4];
int m;

cood ar[N];
int p[N];
int f[N];

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    cin >> n;
    
    for (int i = 0; i < n; i++) {
        for (int a = 0; a < 2; a++)
            for (int b = 0; b < 2; b++)
                cin >> d[a][b].x >> d[a][b].y;

        vec u = d[0][1] - d[0][0];
        cood ang = atan2l(u.y,u.x);
        cood dx = d[0][1].nr(d[0][0]);
        cood dy = d[1][1].nr(d[1][0]);

        cin >> m;

        for (int j = 0; j < m; j++) {
            for (int k = 0; k < 4; k++) {
                cin >> r[j][k].x >> r[j][k].y;

                r[j][k] = r[j][k].rotate(-ang);
                r[j][k].x *= 100./dx;
                r[j][k].y *= 100./dy;
            }

            ar[i] += abs(r[j][0].ar(r[j][1], r[j][2]));
        }

        p[i] = i;
    }

    sort(p, p+n, [] (int i, int j) {
        return ar[i] < ar[j];
    });

    int cl = 1;
    for (int _i = 0; _i < n; _i++) {
        int i = p[_i];
        if (!_i || abs(ar[i] - ar[p[_i-1]]) < 1e-4)
            f[i] = cl;
        else 
            f[i] = ++cl;
    }

    for (int i = 0; i < n; i++)
        cout << f[i] << " ";
    cout << endl;
}
