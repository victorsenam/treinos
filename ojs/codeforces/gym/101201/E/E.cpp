#include <bits/stdc++.h>
//#define ONLINE_JUDGE
#ifndef ONLINE_JUDGE
#define debug if (true)
#else
#define debug if (false)
#endif

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

// NOT STANDART FROM HERE

typedef ll cood;
cood eps = 0;

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
	{ cood o = ar(a, b); return (o < -eps) - (eps < o); }

	// === ADVANCED ===
	// rotate ccw by a (fails with ll)
	vec rotate (double a)
	{ return vec(cos(a) * x - sin(a) * y, sin(a) * x + cos(a) * y); }

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

// tests TODO
// brd = do points on the border belong to convex?
// computes convex hull of given vector (inplace)
// returns size of convex hull
int graham (vec v[], int n, int brd) {
    for (int i = 1; i < n; i++) {
        if (v[i].x < v[0].x || (v[i].x == v[0].x && v[i].y < v[0].y))
            swap(v[0], v[i]);
    }

    sort(v+1, v+n, [v] (vec a, vec b) {
        int o = b.sd(v[0], a);
        if (o) return (o == -1);
        return v[0].sq(a) < v[0].sq(b);
    });

    if (brd) {
        int s = n-1;
        while (s > 1 && v[s].sd(v[s-1],v[0]) == 0)
            s--;
        for (int i = s; i < n - 1 - (i - s); i++)
            swap(v[i], v[n-1-(i-s)]);
    }

    int s = 0;
    for (int i = 0; i < n; i++) {
        while (s >= 2 && v[s-1].sd(v[s-2],v[i]) <= -brd)
            s--;
        v[s++] = v[i];
    }

    return s;
}

const int N = 2e5+7;

int n, k, s;
ll ar[N];
vec v[N];

// index of first point to the left of a
int flf (vec a) {
    int lo = 1;
    int hi = s;

    while (lo < hi) {
        int md = (lo+hi)/2;

        if (v[md].sd(v[0], a) == -1)
            hi = md;
        else
            lo = md+1;
    }

    return lo;
}

int main () {
    cin >> n >> k;
    
    for (int i = 0; i < n; i++)
        cin >> v[i].x >> v[i].y;

    s = graham(v, k, 0);

    debug cout << v[0] << endl;
    for (int i = 1; i < s; i++) {
        ar[i] = ar[i-1] + v[i].ar(v[0], v[i-1]);
        debug cout << v[i] << endl;
    }
    ar[s] = ar[s-1];

    ll res = ar[s];

    for (int i = k; i < n; i++) {
        int z = flf(v[i]);
        debug cout << "===== " << v[i] << " =====" << z <<endl;
        debug cout << "fica entre " << v[z - 1] << " e " << v[z%s] << endl;

        if (v[i].sd(v[0],v[1]) != -1 && v[i].sd(v[s-1],v[0]) != -1) {
            debug cout << "tira" << endl;

            // primeiro que fica até z
            int lo = 1;
            int hi = z;
            while (lo < hi) {
                int md = (lo + hi)/2;
                if (v[md].sd(v[i],v[md+1]) != 1)
                    lo = md + 1;
                else
                    hi = md;
            }
            int l = lo;

            // ultimo que a partir de z
            lo = z;
            hi = s-1;
            while (lo < hi) {
                int md = (lo + hi + 1)/2;
                if (v[md].sd(v[md-1],v[i]) != 1)
                    hi = md - 1;
                else
                    lo = md;
            }
            int r = lo;

            debug cout << "fica [" << v[l] << "," << v[r%s] << "] :";
            ll loc = ar[r] - ar[l] + abs(v[l].ar(v[0],v[i])) + abs(v[i].ar(v[0],v[r]));
            debug cout << loc << endl;
            res = max(res, loc);
        } else if (v[i].sd(v[z%s],v[(z+1)%s]) != 1 && v[i].sd(v[z-1],v[z%s]) != 1) {
            debug cout << "dentro" << endl;
        } else {
            debug cout << "deixa" << endl;

            // ultimo que fica antes de z
            int lo = 0;
            int hi = z-1;
            while (lo < hi) {
                int md = (lo + hi + 1)/2;
                if (v[md].sd(v[md-1],v[i]) != 1)
                    hi = md - 1;
                else
                    lo = md;
            }
            int l = lo;

            // primeiro que fica a partir de z
            lo = z;
            hi = s;
            while (lo < hi) {
                int md = (lo + hi)/2;
                if (v[md].sd(v[i],v[(md+1)%s]) != 1)
                    lo = md+1;
                else
                    hi = md;
            }
            int r = lo;

            debug cout << "tira ]" << v[l] << "," << v[r%s] << "[ :";
            ll loc = ar[s] - ar[r] + ar[l] + v[i].ar(v[0],v[l]) + v[r].ar(v[0],v[i]);
            debug cout << loc << endl;
            res = max(res, loc);
        }
    }

    printf("%.1f\n", .5*double(res));
}
