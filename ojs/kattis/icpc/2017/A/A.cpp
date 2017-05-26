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
typedef ll cood;
const ll eps = 0;
typedef long double ldbl;

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
	ldbl nr (vec o = vec())
	{ return sqrt(ldbl(sq(o))); }

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

	// is this inside segment st? (tip of segment included, change for < -eps otherwise)
	bool in_seg (vec s, vec t)
	{ return (sd(s, t) == 0) && ((*this) - s) * ((*this) - t) < -eps; }
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

    ll din (lin o) {
        return a * o.b - o.a * b;
    }

    vec inter2 (lin o) {
		return vec((o.b * c - b * o.c), (a * o.c - o.a * c));
    }
};

ldbl seg_dist (vec a, vec b, vec x, vec y) {
    lin s(a,b), t(x,y);

    ll d = s.din(t);
    vec p = s.inter2(t);
    
    p.x -= x.x * d;
    p.y -= x.y * d;

    ldbl nx = ldbl(p.x)/ldbl(d);
    ldbl ny = ldbl(p.y)/ldbl(d);

    return sqrt(nx*nx + ny*ny);
}

// tests TODO
// returns any point on the intersection of ab and cd (including all tips)
bool seg_inter (vec a, vec b, vec c, vec d) {
	//if (a.in_seg(c, d) || b.in_seg(c, d) || c.in_seg(a, b) || d.in_seg(a, b))
		//return true;
	return (c.sd(a, b) * d.sd(a, b) == -1 && a.sd(c, d) * b.sd(c, d) == -1);
}
// cd is line
bool lin_inter (vec a, vec b, vec c, vec d) {
	//if (a.in_seg(c, d) || b.in_seg(c, d) || c.in_seg(a, b) || d.in_seg(a, b))
		//return true;
	return (a.sd(c, d) * b.sd(c, d) == -1);
}

const int N = 1e3;
const int M = 5e6;

int n;
vec v[N];

bool is_interest (int k, vec a, vec b) {
    if (v[k].sd(a,b) != 0) return 0;
    if (v[k+n-1].sd(a,b) * v[k+1].sd(a,b) == -1)
        return 1;
    if (v[k+1].sd(v[k+n-1],v[k]) == -1)
        return 1;
    return 0;
}

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> v[i].x >> v[i].y;
        v[i+n] = v[i];
    }

    ldbl res = 0.;
    for (int i = 0; i < n; i++) {
        for (int j = i+1; j < n; j++) {
            if (v[i+n-1].sd(v[i], v[i+1]) == -1) {
                if (v[j].sd(v[i],v[i+1]) == 1 || v[j].sd(v[i], v[i+n-1]) == -1)
                    continue;
            } else {
                if (v[j].sd(v[i],v[i+n-1]) != 1 && v[j].sd(v[i], v[i+1]) != -1)
                    continue;
            }

            bool ok = 1;

            //cout << v[i] << " -- " << v[j] << endl;
            ldbl di = 1./0., dj = 1./0.;

            for (int k = 0; ok && k < n; k++) {
                if (seg_inter(v[k], v[k+1], v[i], v[j])) {
                    //cout << v[k] << " to " << v[k + 1] << " crosses" << endl;
                    ok = 0;
                } else if (lin_inter(v[k], v[k+1], v[i], v[j])) {
                    ldbl ni = seg_dist(v[k], v[k+1], v[i], v[j]);
                    ldbl nj = seg_dist(v[k], v[k+1], v[j], v[i]);
                    //cout << v[k] << " to " << v[k + 1] << " interest : " << ni << " " << nj << endl;
                    if (ni < nj + 1e-12)
                        di = min(di, ni);
                    else
                        dj = min(dj, nj);
                }

                if (is_interest(k, v[i], v[j])) {
                    if (v[k].in_seg(v[i],v[j])) {
                        //cout << v[k] << " stops" << endl;
                        ok = 0;
                    } else if (v[k].dr(v[i],v[j]) == 1) {
                        //cout << v[k] << " interest for " << v[j] << " : " << v[k].nr(v[j]) << endl;
                        dj = min(dj, ldbl(v[k].nr(v[j])));
                    } else {
                        //cout << v[k] << " interest for " << v[i] << " : " << v[k].nr(v[i]) << endl;
                        di = min(di, ldbl(v[k].nr(v[i])));
                    }
                }
            }
            

            //cout << v[i] << " " << v[j] << " = " << di + dj + v[i].nr(v[j]) << " = " << di << "+" << dj << "+" << v[i].nr(v[j]) << endl;
            if (ok)
                res = max(res, di + dj + v[i].nr(v[j]));
        }
    }
    cout << setprecision(20) << res << endl;
}
