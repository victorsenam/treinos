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

typedef double cood;
const double eps = 1e-9;

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

// tests TODO
// returns any point on the intersection of ab and cd (including all tips)
bool seg_inter (vec a, vec b, vec c, vec d) {
	if (a.in_seg(c, d) || b.in_seg(c, d) || c.in_seg(a, b) || d.in_seg(a, b))
		return true;
	return (c.sd(a, b) * d.sd(a, b) == -1 && a.sd(c, d) * b.sd(c, d) == -1);
}

const int N = 307;
const int M = 1e6+7;

int n, m;
vec pp[N][2];
vec v[M];
int ty[M];
int visi[M], turn;

bool operator< (vec a, vec b) {
    if (a.x < b.x - eps || a.x > b.x + eps) return a.x < b.x - eps;
    return a.y < b.y - eps;
}

map<vec, int> mp;
vector<int> pts[N];
vector<pair<int, double> > adj[M];

double dfs (int u, int p, int t, int d) {
    if (u == 0 && t == 0) {
        printf("-1\n");
        exit(0);
    }
    assert(u != 1 || t == 0);
    if (ty[u] == t) {
        ty[u] = d;
        return 0;
    }
    if (visi[u] == turn || ty[u] == d)
        return 0;
    visi[u] = turn;

    double rr = 0.;
    for (pair<int, double> v : adj[u]) {
        if (v.first == p) continue;
        rr += v.second + dfs(v.first, u, t, d);
    }
    return rr;
}

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    cin >> n >> m;

    double res = 0.;
    double check = 0.;

    for (int i = 0; i < n; i++) {
        cin >> pp[i][0].x >> pp[i][0].y >> pp[i][1].x >> pp[i][1].y;
        res += pp[i][0].nr(pp[i][1]);
    }
    m += 2;
    for (int i = 2; i < m; i++) {
        cin >> v[i].x >> v[i].y;
        mp[v[i]] = i;
        ty[i] = 0; // closing

        for (int j = 0; j < n; j++)
            if (v[i].in_seg(pp[j][0], pp[j][1]))
                pts[j].push_back(i);
    }
    for (int i = 0; i < 2; i++) {
        cin >> v[i].x >> v[i].y;
        mp[v[i]] = i;
        ty[i] = 1; // spec

        for (int j = 0; j < n; j++)
            if (v[i].in_seg(pp[j][0], pp[j][1]))
                pts[j].push_back(i);
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 2; j++) {
            v[m] = pp[i][j];
            if (mp.find(v[m]) != mp.end()) continue;
            mp[v[m]] = m;
            ty[m] = 4;
            pts[i].push_back(m);
            m++;
        }
        for (int j = 0; j < i; j++) {
            if (seg_inter(pp[i][0], pp[i][1], pp[j][0], pp[j][1])) {
                ty[m] = 0;
                for (int a = 0; a < 2 && !ty[m]; a++)
                    for (int b = 0; b < 2 && !ty[m]; b++)
                        if (abs(pp[i][a].x - pp[j][b].x) < eps && abs(pp[i][a].y - pp[j][b].y) < eps) {
                            v[m] = pp[i][a];
                            ty[m] = 2;
                        }
                if (ty[m] != 2) {
                    ty[m] = 2; // inter
                    v[m] = lin(pp[i][0], pp[i][1]).inter(lin(pp[j][0], pp[j][1]));
                }
                
                int idx = m;
                if (mp.find(v[m]) != mp.end())
                    idx = mp[v[m]];
                else {
                    mp[v[m]] = m;
                    m++;
                }

                pts[i].push_back(idx);
                pts[j].push_back(idx);
            }
        }
    }

    for (int i = 0; i < n; i++) {
        sort(pts[i].begin(), pts[i].end(), [i] (int x, int y) {
            return pp[i][0].sq(v[x]) < pp[i][0].sq(v[y]);
        });

        cout << "segm " << pp[i][0] << " " << pp[i][1] << endl;
        cout << "[" << pts[i][0] << "] " << v[pts[i][0]] << " ty=" << ty[pts[i][0]] << endl;
        for (int j = 1; j < pts[i].size(); j++) {
            if (pts[i][j-1] == pts[i][j]) continue;
            cout << "[" << pts[i][j] << "] " << v[pts[i][j]] << " ty=" << ty[pts[i][j]] << endl;
            double dist = v[pts[i][j-1]].nr(v[pts[i][j]]);
            adj[pts[i][j-1]].push_back(pair<int, double>(pts[i][j],dist));
            adj[pts[i][j]].push_back(pair<int, double>(pts[i][j-1],dist));
            check += dist;
        }
    }

    assert(abs(check - res) < eps);

    turn++;
    dfs(1, 1, 0, 3);
    turn++;
    res -= dfs(0, 0, 3, -1);
    cout << setprecision(20) << res << endl;
}
